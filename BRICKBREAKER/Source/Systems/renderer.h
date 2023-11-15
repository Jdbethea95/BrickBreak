#include <DDSTextureLoader.h>
#include <d3dcompiler.h>	// required for compiling shaders on the fly, consider pre-compiling instead
#include "h2bParser.h"
#include "../FileIntoString.h"
#include "load_data_oriented.h"
#include "../Packet.h"
#include "../Font.h"
#include "../Sprite.h"
#include <d3d11.h>
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//converions notes
/*Lines updated
* 161-165 (declaration of level data)
* 201 (vertex buffer)
* 221 (index buffer)
* 381 (drawindex)
* 428 (stride)
* initalizedpipeline, compileGSShader
*/

enum Cameras
{
	MainCamera, ArialCamera, LeftCamera, RightCamera
};

// enumeration to easily index into an array of textures
// mostly used for whoever is reading this can figure out which item is being indexed to
enum TEXTURE_ID 
{ 
	//we could add more depending on the hud files we implement 
	FONT_COMIC_SANS, 
	COUNT 
};

namespace BBG
{


	struct SceneData
	{
		GW::MATH::GVECTORF vec_SunDirection, vec_SunColor;
		GW::MATH::GMATRIXF mat_View, mat_Projection;
		GW::MATH::GVECTORF sunAmbient, cameraPos;
	};

	struct MeshData
	{
		GW::MATH::GMATRIXF mat_World[200]; //turn to array[200]
		H2B::ATTRIBUTES material[200];	//turn to array[200]
	};

	struct GSData
	{
		GW::MATH::GVECTORF index;
	};

	struct IdData
	{
		GW::MATH::GVECTORF tmIDS; //these are the id's for the transform array and material array
	};								//for use in the vertex and pixel shaders

	struct SPRITE_DATA
	{
		GW::MATH::GVECTORF pos_scale;
		GW::MATH::GVECTORF rotation_depth;
	};

	struct TextData
	{
		Text staticText[3]; //used for titles and more perm text
		Text dynamicText[5]; //used for adjusting numbers like the score.
	};

	// Creation, Rendering & Cleanup
	class Renderer
	{
		// proxy handles
		GW::SYSTEM::GWindow win;
		GW::GRAPHICS::GDirectX11Surface d3d;

		// what we need at a minimum to draw a triangle
		Microsoft::WRL::ComPtr<ID3D11Buffer>		vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	pixelShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	vertexFormat;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> gsShader;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	vsShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	psShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	vtrFormat;

		Microsoft::WRL::ComPtr<ID3D11Buffer>		indexBuffer = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Buffer> sceneConstantBuffer = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Buffer> meshConstantBuffer = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Buffer> gsConstantBuffer = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Buffer> idConstantBuffer = nullptr; //another buffer for id's is needed. transform and count
		Microsoft::WRL::ComPtr<ID3D11Buffer> txtConstantBuffer = nullptr;
		//Text vertex buffers
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBufferStaticText[3];
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBufferDynamicText[5];
		
		// texuring related interface objects
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	shaderResourceView[TEXTURE_ID::COUNT];
		Microsoft::WRL::ComPtr<ID3D11SamplerState>			samplerState;

		// blending related interface objects
		Microsoft::WRL::ComPtr<ID3D11BlendState>			blendState;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		depthStencilState;

		//math libraries
		GW::MATH::GMatrix matrixMath;
		GW::MATH::GVector vectorMath;

		//Space Matrices for GPU/Vertex Shader
		GW::MATH::GMATRIXF world = GW::MATH::GMATRIXF();
		GW::MATH::GMATRIXF wordWorld = GW::MATH::GMATRIXF();
		GW::MATH::GMATRIXF view = GW::MATH::GMATRIXF();
		GW::MATH::GMATRIXF projection = GW::MATH::GMATRIXF();
		GW::MATH::GVECTORF lightDirection = GW::MATH::GVECTORF();
		GW::MATH::GVECTORF lightColor = GW::MATH::GVECTORF();


		GW::MATH::GMATRIXF cameras[4] = { GW::MATH::GMATRIXF() };
		Cameras currentCam = Cameras::ArialCamera;

		std::vector<GamePacket> changedItems;

		// variables used to store the client's width and height
		UINT width = 0, height = 0;

		//text
		Font consolas32;
		Font ComicSans32;

		// variable to hold the constant buffer information for a sprite, aka text
		SPRITE_DATA	constantBufferData = { 0 };

		//not currently being used
		SPRITE_DATA UpdateSpriteConstantBufferData(const Sprite& s)
		{
			SPRITE_DATA temp = { 0 };
			temp.pos_scale.x = s.GetPosition().x;
			temp.pos_scale.y = s.GetPosition().y;
			temp.pos_scale.z = s.GetScale().x;
			temp.pos_scale.w = s.GetScale().y;
			temp.rotation_depth.x = s.GetRotation();
			temp.rotation_depth.y = s.GetDepth();
			return temp;
		}

		//used for static and dynamic text
		SPRITE_DATA UpdateTextConstantBufferData(const Text& s)
		{
			SPRITE_DATA temp = { 0 };
			temp.pos_scale.x = s.GetPosition().x;
			temp.pos_scale.y = s.GetPosition().y;
			temp.pos_scale.z = s.GetScale().x;
			temp.pos_scale.w = s.GetScale().y;
			temp.rotation_depth.x = s.GetRotation();
			temp.rotation_depth.y = s.GetDepth();
			return temp;
		}

		SceneData sceneData;
		MeshData meshData;
		GSData gsData;
		IdData idTMData;
		TextData textData;
		
		D3D11_VIEWPORT viewports[2];

		GW::INPUT::GInput gateInput;
		GW::INPUT::GController gateController;
		//Clock data for deltaTime calculation in rotation of the world matrix
		std::chrono::steady_clock clock;
		std::chrono::time_point<std::chrono::steady_clock> ping;
		std::chrono::time_point<std::chrono::steady_clock> lastPing;

		Level_Data dataOrientedLoader;
		unsigned currVIndex;
		int cameraIndex = 4;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> wireframeRS;

		HRESULT hr = E_NOTIMPL;

	public:
		Renderer(GW::SYSTEM::GWindow _win, GW::GRAPHICS::GDirectX11Surface _d3d, Level_Data passin,
				 GW::INPUT::GInput in, GW::INPUT::GController pad)
		{
			win = _win;
			d3d = _d3d;
			ID3D11Device* creator = nullptr;
			d3d.GetDevice((void**)&creator);
			dataOrientedLoader = passin;
			gateInput = in;
			gateController = pad;

			// store the current width and height of the client's window
			win.GetClientWidth(width);
			win.GetClientHeight(height);

			//new viewport
			unsigned int screen_width, screen_height;
			win.GetWidth(screen_width);
			win.GetHeight(screen_height);

			viewports[1].Width = screen_width / 4;
			viewports[1].Height = screen_height / 4;
			viewports[1].MinDepth = 0;
			viewports[1].MaxDepth = 1;
			viewports[1].TopLeftX = 0;
			viewports[1].TopLeftY = 0;



			viewports[0].Width = screen_width;
			viewports[0].Height = screen_height;
			viewports[0].MinDepth = 0;
			viewports[0].MaxDepth = 1;
			viewports[0].TopLeftX = 0;
			viewports[0].TopLeftY = 0;

			currVIndex = 0;
			gsData.index.x = currVIndex; //there is a reason, trust me. May not be a good reason, but there is one.

			GW::GReturn ret = GW::GReturn();
			ret = matrixMath.Create(); //FAILURE_UNSUPPORTED (-8)
			vectorMath.Create();


			//world matrix creation for mesh data ####CLEANUP####
			ret = matrixMath.IdentityF(world); //needs to rotate on the y axis. 
			world = GW::MATH::GIdentityMatrixF; //GW::MATH::GIdentityMatrixF this works.
			ret = matrixMath.IdentityF(wordWorld);
			//meshData.mat_World = wordWorld;

			//view matrix and camera creation for scene data

			//Main Camera
			ret = matrixMath.IdentityF(cameras[1]);
			MyTranslation(cameras[1], 0.75f, 0.45f, -1.0f); //creates a GVECTORF and calls TranslateLocalF
			matrixMath.LookAtLHF(cameras[0].row4, MyVector4(0.15f, 0.45f, 0), MyVector4(0, 1, 0), cameras[0]);
			matrixMath.InverseF(cameras[0], cameras[0]);
			sceneData.cameraPos = cameras[0].row4;
			matrixMath.InverseF(cameras[0], cameras[0]);
			sceneData.mat_View = cameras[0];


			//projection matrix creation scene data
			float ratio;
			d3d.GetAspectRatio(ratio);
			ret = matrixMath.ProjectionDirectXLHF(65.0f, ratio, 0.1f, 100.0f, projection); //FAILURE (-1)
			sceneData.mat_Projection = projection;

			//light direction creation for scene data
			lightDirection = MyVector4(-1, -1, 2); //creates a GVECTORF
			vectorMath.NormalizeF(lightDirection, lightDirection);
			sceneData.vec_SunDirection = lightDirection;

			//light color creation for scene data
			lightColor = MyVector4(0.9f, 0.9f, 1.0f); // w/a is set to 1 automatically in Vector4
			sceneData.vec_SunColor = lightColor;

			//assigning Ambient light
			sceneData.sunAmbient = MyVector4(0.25f, 0.25f, 0.35f);
			//assigning material
			//meshData.material = FSLogo_materials[0].attrib; ####CLEANUP####


			for (int i = 0; i < dataOrientedLoader.levelTransforms.size(); i++)
			{
				meshData.mat_World[i] = dataOrientedLoader.levelTransforms[i]; //assigning to world array

				if (i == 4)
				{
					std::cout << "(" << dataOrientedLoader.levelTransforms[i].row4.x << ", " <<
										dataOrientedLoader.levelTransforms[i].row4.y << ", " << 
										dataOrientedLoader.levelTransforms[i].row4.z << ")" << std::endl;
					std::cout << i << " : " << "RenderData" << std::endl;
				}
			}

			for (int j = 0; j < dataOrientedLoader.levelMaterials.size(); j++)
			{
				meshData.material[j] = dataOrientedLoader.levelMaterials[j].attrib; //assigning to material array
			}
			

			//from blender cameras
			//dataOrientedLoader.levelTransforms, camera matrices are not loaded in data.

			SetLevelCameras();

			// creation of the blending state
			// this is used to alpha blend objects with transparency
			CD3D11_BLEND_DESC blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
			blendDesc.RenderTarget[0].BlendEnable = true;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			hr = creator->CreateBlendState(&blendDesc, blendState.GetAddressOf());

			// creation of the depth stencil state
			// this is used to blend with objects when they are on the same z-plane
			// the depth function needs to be set to less_equal instead of less
			CD3D11_DEPTH_STENCIL_DESC depthStencilDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			hr = creator->CreateDepthStencilState(&depthStencilDesc, depthStencilState.GetAddressOf());

			// when loading a texture from disk to an interface object for directx 11
			// we use this function call "CreateDDSTextureFromFile"
			// this requires a wide string as a parameter for the file path
			// the shaderResourceView is a directx 11 interface object that points to the texture information on the gpu

			//A .dds file type is a DirectDraw Surface
			//Follow links to learn more: 
			//https://en.wikipedia.org/wiki/DirectDraw_Surface
			//https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dx-graphics-dds-pguide

			// an array to store all of the texture names
			// this makes looping over and creating shader resource views easier
			std::wstring texture_names[] =
			{
				L"font_Comic_Sans_32.dds"
			};

			// loop used for creating shader resource views
			for (size_t i = 0; i < ARRAYSIZE(texture_names); i++)
			{
				// create a wide string to store the file path and file name
				std::wstring texturePath = L"../Textures/";
				texturePath += texture_names[i];
				// load texture from disk 
				hr = CreateDDSTextureFromFile(creator, texturePath.c_str(), nullptr, shaderResourceView[i].GetAddressOf());
			}

			// samplerStates are needed when using textures
			// this is for filtering the texture
			// some options are bilinear, trilinear, anisotropic, etc..
			CD3D11_SAMPLER_DESC samp_desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
			hr = creator->CreateSamplerState(&samp_desc, samplerState.GetAddressOf());
		

			//Font loading
			std::string filepath = "../Source/XML/font_Comic_Sans_32.xml";
			bool success = ComicSans32.LoadFromXML(filepath);

			textData.staticText[0] = Text();
			textData.staticText[0].SetText("Current Score:");
			textData.staticText[0].SetFont(&ComicSans32);
			textData.staticText[0].SetPosition(-0.55f, 0.85f);
			textData.staticText[0].SetScale(0.7f, 0.7f);
			textData.staticText[0].SetRotation(0.0f);
			textData.staticText[0].SetDepth(0.05f);

			textData.staticText[1] = Text();
			textData.staticText[1].SetText("High Score:");
			textData.staticText[1].SetFont(&ComicSans32);
			textData.staticText[1].SetPosition(-0.63f, 0.75f);
			textData.staticText[1].SetScale(0.70f, 0.70f);
			textData.staticText[1].SetRotation(0.0f);
			textData.staticText[1].SetDepth(0.00f);

			textData.staticText[2] = Text();
			textData.staticText[2].SetText("Lives:");
			textData.staticText[2].SetFont(&ComicSans32);
			textData.staticText[2].SetPosition(-0.73f, -0.85f);
			textData.staticText[2].SetScale(0.70f, 0.70f);
			textData.staticText[2].SetRotation(0.0f);
			textData.staticText[2].SetDepth(0.00f);

			// update will create the vertices so they will be ready to use
			// for static text this only needs to be done one time
			int numberOfStaticText = sizeof(textData.staticText) / sizeof(Text);

			for (size_t i = 0; i < sizeof(textData.staticText) / sizeof(Text); i++)
			{
				textData.staticText[i].Update(width, height);
			}

			 /*setting up the dynamic text object with information
			 keep in mind the position will always be the center of the text*/

			//Current Score
			textData.dynamicText[0] = Text();
			textData.dynamicText[0].SetFont(&ComicSans32);
			textData.dynamicText[0].SetPosition(0.0f, 0.85f);
			textData.dynamicText[0].SetScale(0.70f, 0.70f);
			textData.dynamicText[0].SetRotation(0.0f);
			textData.dynamicText[0].SetDepth(0.05f);

			//Highscore
			textData.dynamicText[1] = Text();
			textData.dynamicText[1].SetFont(&ComicSans32);
			textData.dynamicText[1].SetPosition(0.0f, 0.75f);
			textData.dynamicText[1].SetScale(0.70f, 0.70f);
			textData.dynamicText[1].SetRotation(0.0f);
			textData.dynamicText[1].SetDepth(0.05f);

			//Life
			textData.dynamicText[2] = Text();
			textData.dynamicText[2].SetFont(&ComicSans32);
			textData.dynamicText[2].SetPosition(-0.45f, -0.85f);
			textData.dynamicText[2].SetScale(0.70f, 0.70f);
			textData.dynamicText[2].SetRotation(0.0f);
			textData.dynamicText[2].SetDepth(0.05f);

			//Pause
			textData.dynamicText[3] = Text();
			textData.dynamicText[3].SetFont(&ComicSans32);
			textData.dynamicText[3].SetPosition(0.0f, 0.0f);
			textData.dynamicText[3].SetScale(0.70f, 0.70f);
			textData.dynamicText[3].SetRotation(0.0f);
			textData.dynamicText[3].SetDepth(0.05f);

			//Start
			textData.dynamicText[4] = Text();
			textData.dynamicText[4].SetFont(&ComicSans32);
			textData.dynamicText[4].SetPosition(0.0f, 0.0f);
			textData.dynamicText[4].SetScale(0.70f, 0.70f);
			textData.dynamicText[4].SetRotation(0.0f);
			textData.dynamicText[4].SetDepth(0.05f);

			IntializeGraphics();
		}

		void ONRESIZE(GW::SYSTEM::GWindow why, bool& shouldI)
		{
			if (!shouldI)
				return;

			unsigned int screen_width, screen_height;
			why.GetWidth(screen_width);
			why.GetHeight(screen_height);

			viewports[1].Width = screen_width / 4;
			viewports[1].Height = screen_height / 4;

			viewports[0].Width = screen_width;
			viewports[0].Height = screen_height;
			shouldI = false;
		}

	private:
		//constructor helper functions
		void IntializeGraphics()
		{
			ID3D11Device* creator;
			d3d.GetDevice((void**)&creator);

			// vertex buffer creation for the staticText
			for (size_t i = 0; i < sizeof(vertexBufferStaticText) / sizeof(Microsoft::WRL::ComPtr<ID3D11Buffer>); i++)
			{
				const auto& staticVerts = textData.staticText[i].GetVertices();
				D3D11_SUBRESOURCE_DATA svbData = { staticVerts.data(), 0, 0 };
				CD3D11_BUFFER_DESC svbDesc(sizeof(TextVertex) * staticVerts.size(), D3D11_BIND_VERTEX_BUFFER);
				hr = creator->CreateBuffer(&svbDesc, &svbData, vertexBufferStaticText[i].GetAddressOf());

			}
			//vertex buffer creation for the dynamic text
			for (size_t i = 0; i < sizeof(vertexBufferDynamicText) / sizeof(Microsoft::WRL::ComPtr<ID3D11Buffer>); i++)
			{
				//dynamic text for later working on static first
				CD3D11_BUFFER_DESC dvbDesc(sizeof(TextVertex) * 6 * 5000,
					D3D11_BIND_VERTEX_BUFFER,
					D3D11_USAGE_DYNAMIC,
					D3D11_CPU_ACCESS_WRITE);

				hr = creator->CreateBuffer(&dvbDesc, nullptr, vertexBufferDynamicText[i].GetAddressOf());
			}
			InitializeVertexBuffer(creator);
			// TODO: Part 1G: creating a indexbuffer that accepts the unsigned int array from image header.
			InitializeIndexBuffer(creator);
			// TODO: Part 2C 
			CreateGPUShaderBuffer(creator, &sceneData, sizeof(SceneData), sceneConstantBuffer.GetAddressOf());
			CreateGPUShaderBuffer(creator, &meshData, sizeof(MeshData), meshConstantBuffer.GetAddressOf());
			CreateGPUShaderBuffer(creator, &meshData, sizeof(GSData), gsConstantBuffer.GetAddressOf());
			CreateGPUShaderBuffer(creator, &idTMData, sizeof(IdData), idConstantBuffer.GetAddressOf());
			CreateTextConstantBuffer(creator, &constantBufferData, sizeof(SPRITE_DATA), txtConstantBuffer.GetAddressOf());


			InitializePipeline(creator);
			// free temporary handle
			creator->Release();
		}

		void InitializeRenderState(ID3D11Device* creator)
		{
			D3D11_RASTERIZER_DESC wireframeDesc;
			ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
			wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
			wireframeDesc.CullMode = D3D11_CULL_NONE; //BACK, FRONT is also an option here.
			wireframeDesc.DepthClipEnable = true; //normally this is set to true but since we called zeromemory the field is initialzed to 0.

			creator->CreateRasterizerState(&wireframeDesc, wireframeRS.GetAddressOf());
		}

		void InitializeVertexBuffer(ID3D11Device* creator)
		{

			// TODO: Part 1C replaced vert with the FSlogo Vertex Array: DO NOT FORGET TO UPDATE THE STRIDE AND AMOUNT TO DRAW
			CreateVertexBuffer(creator, dataOrientedLoader.levelVertices.data(), sizeof(H2B::VERTEX) * dataOrientedLoader.levelVertices.size()); // reminder: fix hard coded value
		}

		void CreateGPUShaderBuffer(ID3D11Device* creator, const void* data, unsigned int sizeInBytes, ID3D11Buffer** buffer)
		{
			D3D11_SUBRESOURCE_DATA subersourceData{ data, 0, 0 };
			CD3D11_BUFFER_DESC bufferDesc{ sizeInBytes, D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE };
			creator->CreateBuffer(&bufferDesc, &subersourceData, buffer);
		}

		void CreateTextConstantBuffer(ID3D11Device* creator, const void* data, unsigned int sizeInBytes, ID3D11Buffer** buffer)
		{
			D3D11_SUBRESOURCE_DATA subersourceData{ data, 0, 0 };
			CD3D11_BUFFER_DESC bufferDesc{ sizeInBytes, D3D11_BIND_CONSTANT_BUFFER };
			creator->CreateBuffer(&bufferDesc, &subersourceData, buffer);
		}

		void CreateVertexBuffer(ID3D11Device* creator, const void* data, unsigned int sizeInBytes)
		{
			D3D11_SUBRESOURCE_DATA bData = { data, 0, 0 };
			CD3D11_BUFFER_DESC bDesc(sizeInBytes, D3D11_BIND_VERTEX_BUFFER);
			creator->CreateBuffer(&bDesc, &bData, vertexBuffer.GetAddressOf());

			
		}

		void InitializeIndexBuffer(ID3D11Device* creator)
		{
			//A box WITHIN A BOX!!! initialized function made for uniformity.
			CreateIndexBuffer(creator, dataOrientedLoader.levelIndices.data(), sizeof(unsigned) * dataOrientedLoader.levelIndices.size());
		}

		void CreateIndexBuffer(ID3D11Device* creator, const void* data, unsigned int sizeInBytes)
		{
			D3D11_SUBRESOURCE_DATA bData = { data, 0, 0 };
			CD3D11_BUFFER_DESC bDesc(sizeInBytes, D3D11_BIND_INDEX_BUFFER);
			creator->CreateBuffer(&bDesc, &bData, indexBuffer.GetAddressOf());
		}

		void InitializePipeline(ID3D11Device* creator)
		{
			UINT compilerFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if _DEBUG
			compilerFlags |= D3DCOMPILE_DEBUG;
#endif
			Microsoft::WRL::ComPtr<ID3DBlob> psTxtBlob = CompileTxtPixelShader(creator, compilerFlags);
			Microsoft::WRL::ComPtr<ID3DBlob> vsTxtBlob = CompileTxtVertexShader(creator, compilerFlags);
			CreateTxtVertexInputLayout(creator, vsTxtBlob);
			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = CompileVertexShader(creator, compilerFlags);
			Microsoft::WRL::ComPtr<ID3DBlob> gsBlob = CompileGSShader(creator, compilerFlags);
			Microsoft::WRL::ComPtr<ID3DBlob> psBlob = CompilePixelShader(creator, compilerFlags);
			CreateVertexInputLayout(creator, vsBlob);
			InitializeRenderState(creator);

	}


		Microsoft::WRL::ComPtr<ID3DBlob> CompileVertexShader(ID3D11Device* creator, UINT compilerFlags)
		{
			std::string vertexShaderSource = ReadFileIntoString("../Shaders/VertexShader.hlsl");

			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob, errors;

			HRESULT compilationResult =
				D3DCompile(vertexShaderSource.c_str(), vertexShaderSource.length(),
					nullptr, nullptr, nullptr, "main", "vs_4_0", compilerFlags, 0,
					vsBlob.GetAddressOf(), errors.GetAddressOf());

			if (SUCCEEDED(compilationResult))
			{
				creator->CreateVertexShader(vsBlob->GetBufferPointer(),
					vsBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
			}
			else
			{
				PrintLabeledDebugString("Vertex Shader Errors:\n", (char*)errors->GetBufferPointer());
				abort();
				return nullptr;
			}

			return vsBlob;
		}
		Microsoft::WRL::ComPtr<ID3DBlob> CompilePixelShader(ID3D11Device* creator, UINT compilerFlags)
		{
			std::string pixelShaderSource = ReadFileIntoString("../Shaders/PixelShader.hlsl");

			Microsoft::WRL::ComPtr<ID3DBlob> psBlob, errors;

			HRESULT compilationResult =
				D3DCompile(pixelShaderSource.c_str(), pixelShaderSource.length(),
					nullptr, nullptr, nullptr, "main", "ps_4_0", compilerFlags, 0,
					psBlob.GetAddressOf(), errors.GetAddressOf());

			if (SUCCEEDED(compilationResult))
			{
				creator->CreatePixelShader(psBlob->GetBufferPointer(),
					psBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
			}
			else
			{
				PrintLabeledDebugString("Pixel Shader Errors:\n", (char*)errors->GetBufferPointer());
				abort();
				return nullptr;
			}

			return psBlob;
		}
		Microsoft::WRL::ComPtr<ID3DBlob> CompileGSShader(ID3D11Device* creator, UINT compilerFlags)
		{
			std::string GSShaderSource = ReadFileIntoString("../Shaders/GeometryShader.hlsl");

			Microsoft::WRL::ComPtr<ID3DBlob> gsBlob, errors;

			HRESULT compilationResult =
				D3DCompile(GSShaderSource.c_str(), GSShaderSource.length(),
					nullptr, nullptr, nullptr, "main", "gs_4_0", compilerFlags, 0,
					gsBlob.GetAddressOf(), errors.GetAddressOf());

			if (SUCCEEDED(compilationResult))
			{
				creator->CreateGeometryShader(gsBlob->GetBufferPointer(),
					gsBlob->GetBufferSize(), nullptr, gsShader.GetAddressOf());
			}
			else
			{
				PrintLabeledDebugString("Geometry Shader Errors:\n", (char*)errors->GetBufferPointer());
				abort();
				return nullptr;
			}

			return gsBlob;
		}

		void CreateVertexInputLayout(ID3D11Device* creator, Microsoft::WRL::ComPtr<ID3DBlob>& vsBlob)
		{
			// TODO: Part 1E changed DXGI_FORMAT_R32G32_FLOAT to DXGI_FORMAT_R32G32B32_FLOAT

			D3D11_INPUT_ELEMENT_DESC attributes[3];

			attributes[0].SemanticName = "POSITION";
			attributes[0].SemanticIndex = 0;
			attributes[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			attributes[0].InputSlot = 0;
			attributes[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			attributes[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			attributes[0].InstanceDataStepRate = 0;

			attributes[1].SemanticName = "UVW";
			attributes[1].SemanticIndex = 0;
			attributes[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			attributes[1].InputSlot = 0;
			attributes[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			attributes[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			attributes[1].InstanceDataStepRate = 0;

			attributes[2].SemanticName = "NORMAL";
			attributes[2].SemanticIndex = 0;
			attributes[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			attributes[2].InputSlot = 0;
			attributes[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			attributes[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			attributes[2].InstanceDataStepRate = 0;

			creator->CreateInputLayout(attributes, ARRAYSIZE(attributes),
				vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
				vertexFormat.GetAddressOf());
		}

		Microsoft::WRL::ComPtr<ID3DBlob> CompileTxtVertexShader(ID3D11Device* creator, UINT compilerFlags)
		{
			std::string vertexShaderSource = ReadFileIntoString("../Shaders/SpriteVertexShader.hlsl");

			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob, errors;

			HRESULT compilationResult =
				D3DCompile(vertexShaderSource.c_str(), vertexShaderSource.length(),
					nullptr, nullptr, nullptr, "main", "vs_4_0", compilerFlags, 0,
					vsBlob.GetAddressOf(), errors.GetAddressOf());

			if (SUCCEEDED(compilationResult))
			{
				creator->CreateVertexShader(vsBlob->GetBufferPointer(),
					vsBlob->GetBufferSize(), nullptr, vsShader.GetAddressOf());
			}
			else
			{
				PrintLabeledDebugString("Vertex Shader Errors:\n", (char*)errors->GetBufferPointer());
				abort();
				return nullptr;
			}

			return vsBlob;
		}
		Microsoft::WRL::ComPtr<ID3DBlob> CompileTxtPixelShader(ID3D11Device* creator, UINT compilerFlags)
		{
			std::string pixelShaderSource = ReadFileIntoString("../Shaders/SpritePixelShader.hlsl");

			Microsoft::WRL::ComPtr<ID3DBlob> psBlob, errors;

			HRESULT compilationResult =
				D3DCompile(pixelShaderSource.c_str(), pixelShaderSource.length(),
					nullptr, nullptr, nullptr, "main", "ps_4_0", compilerFlags, 0,
					psBlob.GetAddressOf(), errors.GetAddressOf());

			if (SUCCEEDED(compilationResult))
			{
				creator->CreatePixelShader(psBlob->GetBufferPointer(),
					psBlob->GetBufferSize(), nullptr, psShader.GetAddressOf());
			}
			else
			{
				PrintLabeledDebugString("Pixel Shader Errors:\n", (char*)errors->GetBufferPointer());
				abort();
				return nullptr;
			}

			return psBlob;
		}

		void CreateTxtVertexInputLayout(ID3D11Device* creator, Microsoft::WRL::ComPtr<ID3DBlob>& vsBlob)
		{
			// TODO: Part 1E changed DXGI_FORMAT_R32G32_FLOAT to DXGI_FORMAT_R32G32B32_FLOAT

			D3D11_INPUT_ELEMENT_DESC attributes[2];

			attributes[0].SemanticName = "POSITION";
			attributes[0].SemanticIndex = 0;
			attributes[0].Format = DXGI_FORMAT_R32G32_FLOAT;
			attributes[0].InputSlot = 0;
			attributes[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			attributes[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			attributes[0].InstanceDataStepRate = 0;

			attributes[1].SemanticName = "TEXCOORD";
			attributes[1].SemanticIndex = 0;
			attributes[1].Format = DXGI_FORMAT_R32G32_FLOAT;
			attributes[1].InputSlot = 0;
			attributes[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			attributes[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			attributes[1].InstanceDataStepRate = 0;

			creator->CreateInputLayout(attributes, ARRAYSIZE(attributes),
				vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
				vtrFormat.GetAddressOf());
		}

		void SetLevelCameras()
		{
			matrixMath.InverseF(dataOrientedLoader.cameraTransforms[0], cameras[1]);
			matrixMath.InverseF(dataOrientedLoader.cameraTransforms[1], cameras[2]);
			matrixMath.InverseF(dataOrientedLoader.cameraTransforms[2], cameras[3]);
		}


	public:
		void Render()
		{
			PipelineHandles curHandles = GetCurrentPipelineHandles();
			SetUpPipeline(curHandles);

			D3D11_MAPPED_SUBRESOURCE mappedSubresource;

			SwitchCameras(cameraIndex); // Debug functions
			//SwitchLevels();
			//curHandles.context->RSSetState(wireframeRS.Get());
			// For now, Comment this out to disable wireframe mode.
			curHandles.context->IASetInputLayout(vertexFormat.Get());
			//SCENE DATA ASSIGMENT
			curHandles.context->Map(sceneConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

			switch (currentCam) // the switch is present to keep cameras and cam movement seperate
			{
			case MainCamera:
				sceneData.mat_View = cameras[3];
				break;
			case ArialCamera:
				sceneData.mat_View = cameras[1]; //0
				break;
			case LeftCamera:
				sceneData.mat_View = cameras[2]; //2
				break;
			case RightCamera:
				sceneData.mat_View = cameras[3]; //3
				break;
			}


			memcpy_s(mappedSubresource.pData, sizeof(sceneData), &sceneData, sizeof(sceneData));
			curHandles.context->Unmap(sceneConstantBuffer.Get(), 0);

	

#if 1
			if (!changedItems.empty())
			{
				for (int m = 0; m < changedItems.size(); m++)
				{
					curHandles.context->Map(meshConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

					meshData.mat_World[changedItems[m].objectID] = changedItems[m].matrix;

					memcpy_s(mappedSubresource.pData, sizeof(meshData), &meshData, sizeof(meshData));
					curHandles.context->Unmap(meshConstantBuffer.Get(), 0);
				}
				changedItems.clear();
			}
#endif // 0




			// TODO: Part 1H set the index buffer to the input assembler.
			curHandles.context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			ID3D11Buffer* shaderConstantBuffers[] = { sceneConstantBuffer.Get(), meshConstantBuffer.Get(), idConstantBuffer.Get() };
			ID3D11Buffer* gsConstant[] = { gsConstantBuffer.Get() };
			curHandles.context->VSSetConstantBuffers(0, 3, shaderConstantBuffers);
			curHandles.context->GSSetConstantBuffers(0, 1, gsConstant);
			curHandles.context->PSSetConstantBuffers(0, 3, shaderConstantBuffers);

			//loop viewport index for GS Shader. this can work without this outer loop but it looks faded.
			for (int v = 0; v < 1; v++) //change to 2 for the split screen.
			{

				//GS DATA ASSIGNMENT
				curHandles.context->Map(gsConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
				gsData.index.x = v;
				memcpy_s(mappedSubresource.pData, sizeof(GSData), &gsData, sizeof(gsData));
				curHandles.context->Unmap(gsConstantBuffer.Get(), 0);

				//Loop not looping right
				for (int i = 0; i < dataOrientedLoader.levelModels.size(); i++)
				{


					//Setting constant buffers
					int batchStart = dataOrientedLoader.levelModels[i].batchStart;
					int indexStart = dataOrientedLoader.levelModels[i].indexStart;
					int vertexStart = dataOrientedLoader.levelModels[i].vertexStart;


					hr = curHandles.context->Map(idConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);


					idTMData.tmIDS = MyVector4(dataOrientedLoader.levelInstances[i].transformStart,
						dataOrientedLoader.levelModels[i].materialStart, -1, -1);
					memcpy_s(mappedSubresource.pData, sizeof(IdData), &idTMData, sizeof(idTMData));
					curHandles.context->Unmap(idConstantBuffer.Get(), 0);

					for (int j = 0; j < dataOrientedLoader.levelModels[i].meshCount; j++)
					{

						int index = batchStart + j;

						hr = curHandles.context->Map(idConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
						idTMData.tmIDS.y = dataOrientedLoader.levelMeshes[index].materialIndex + dataOrientedLoader.levelModels[i].materialStart;
						memcpy_s(mappedSubresource.pData, sizeof(IdData), &idTMData, sizeof(idTMData));
						curHandles.context->Unmap(idConstantBuffer.Get(), 0);

						//somewhere a vector subscript is out of range.
						//D3D11_VIEWPORT temp[1] = { viewports[1] };
						//curHandles.context->RSSetViewports(1, temp);

						curHandles.context->DrawIndexedInstanced(dataOrientedLoader.levelMeshes[index].drawInfo.indexCount,
							dataOrientedLoader.levelInstances[i].transformCount,
							dataOrientedLoader.levelMeshes[index].drawInfo.indexOffset + indexStart,
							vertexStart, 0); //can this be 0

						//D3D11_VIEWPORT temp2[1] = { viewports[0] };
						//curHandles.context->RSSetViewports(1, temp2);
						//
						//curHandles.context->DrawIndexedInstanced(dataOrientedLoader.levelMeshes[index].drawInfo.indexCount,
						//	dataOrientedLoader.levelInstances[i].transformCount,
						//	dataOrientedLoader.levelMeshes[index].drawInfo.indexOffset + indexStart,
						//	vertexStart, 0); //can this be 0

					}
					//8532, 0, 0 does produce the whole meshe		
				}
			}

			const UINT TextStrides[] = { sizeof(TextVertex) };
			const UINT TextOffsets[] = { 0 };

			curHandles.context->VSSetShader(vsShader.Get(), nullptr, 0);
			curHandles.context->PSSetShader(psShader.Get(), nullptr, 0);
			curHandles.context->IASetInputLayout(vtrFormat.Get());
			ID3D11Buffer* shaderTxtConstantBuffers[] = { txtConstantBuffer.Get() };
			curHandles.context->VSSetConstantBuffers(0, 1, shaderTxtConstantBuffers);
			curHandles.context->PSSetConstantBuffers(0, 1, shaderTxtConstantBuffers);
			curHandles.context->GSSetShader(nullptr, nullptr, 0);

			//Set Sampler State
			curHandles.context->PSSetSamplers(0, 1, samplerState.GetAddressOf());

			for (size_t i = 0; i < sizeof(vertexBufferStaticText) / sizeof(Microsoft::WRL::ComPtr<ID3D11Buffer>); i++)
			{
				// set the vertex buffer for the static text
				curHandles.context->IASetVertexBuffers(0, 1, vertexBufferStaticText[i].GetAddressOf(), TextStrides, TextOffsets);
				// change the topology to a triangle list
				curHandles.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				// update the constant buffer data for the text
				constantBufferData = UpdateTextConstantBufferData(textData.staticText[i]);
				// bind the texture used for rendering the font
				curHandles.context->PSSetShaderResources(0, 1, shaderResourceView[TEXTURE_ID::FONT_COMIC_SANS].GetAddressOf());
				// update the constant buffer with the text's data
				curHandles.context->UpdateSubresource(txtConstantBuffer.Get(), 0, nullptr, &constantBufferData, 0, 0);
				// draw the static text using the number of vertices
				curHandles.context->Draw(textData.staticText[i].GetVertices().size(), 0);
			}

			for (size_t i = 0; i < sizeof(vertexBufferDynamicText) / sizeof(Microsoft::WRL::ComPtr<ID3D11Buffer>); i++)
			{
				// set the vertex buffer for the dynamic text
				curHandles.context->IASetVertexBuffers(0, 1, vertexBufferDynamicText[i].GetAddressOf(), TextStrides, TextOffsets);
				// change the topology to a triangle list
				curHandles.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				// update the constant buffer data for the text
				constantBufferData = UpdateTextConstantBufferData(textData.dynamicText[i]);
				// bind the texture used for rendering the font
				curHandles.context->PSSetShaderResources(0, 1, shaderResourceView[TEXTURE_ID::FONT_COMIC_SANS].GetAddressOf());
				// update the constant buffer with the text's data
				curHandles.context->UpdateSubresource(txtConstantBuffer.Get(), 0, nullptr, &constantBufferData, 0, 0);
				// draw the static text using the number of vertices
				curHandles.context->Draw(textData.dynamicText[i].GetVertices().size(), 0);
			}
			curHandles.context->VSSetShader(vertexShader.Get(), nullptr, 0);
			curHandles.context->PSSetShader(pixelShader.Get(), nullptr, 0);
			curHandles.context->GSSetShader(gsShader.Get(), nullptr, 0);

			ReleasePipelineHandles(curHandles);
		}

		void UpdateCamera()
		{

			if (currentCam != Cameras::MainCamera)
				return;

			GW::MATH::GMATRIXF cameraMatrix;
			matrixMath.InverseF(cameras[0], cameraMatrix);

			float yChange = 0, zChange = 0, xChange = 0, pitchChange = 0, yawChange = 0,//changeStates
				spaceKey = 0, leftShiftKey = 0, wKey = 0, aKey = 0, sKey = 0, dKey = 0, mouseX = 0, mouseY = 0,//PC
				padRightTrigger = 0, padLeftTrigger = 0, padStickLX = 0, padStickLY = 0, padStickRY = 0, padStickRX = 0, sprintKey = 0;//gamepad


			float cameraSpeed = 0;

			std::chrono::milliseconds ms{ 60 };
			ping = clock.now();
			float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(ping - lastPing).count() / 10000.0f;
			lastPing = ping;

			//G_KEY_RIGHTSHIFT
			gateInput.GetState(G_KEY_LEFTCONTROL, sprintKey);
			if (sprintKey == 0)
				cameraSpeed = 10.0f;
			else cameraSpeed = 40.0f;


			gateInput.GetState(G_KEY_SPACE, spaceKey); gateInput.GetState(G_KEY_LEFTSHIFT, leftShiftKey);
			gateController.GetState(7, G_RIGHT_TRIGGER_AXIS, padRightTrigger); gateController.GetState(7, G_LEFT_TRIGGER_AXIS, padLeftTrigger);
			yChange = (spaceKey - leftShiftKey) + (padRightTrigger - padLeftTrigger);
			cameraMatrix.row4.y += yChange * cameraSpeed * deltaTime;


			float perframeSpeed = cameraSpeed * deltaTime;
			gateInput.GetState(G_KEY_W, wKey); gateInput.GetState(G_KEY_A, aKey); gateController.GetState(7, G_LY_AXIS, padStickLX);
			gateInput.GetState(G_KEY_S, sKey); gateInput.GetState(G_KEY_D, dKey); gateController.GetState(7, G_LX_AXIS, padStickLY);

			zChange = (wKey - sKey) + padStickLY;
			xChange = (dKey - aKey) + padStickLX;

			if (aKey != 0)
				int f = 5;

			MyTranslation(cameraMatrix, xChange * perframeSpeed, 0, zChange * perframeSpeed);


			unsigned int screenHeight = 0, screenWidth = 0;
			win.GetHeight(screenHeight); win.GetWidth(screenWidth);


			float rotateSpeed = 3.141592653589793238f * deltaTime;
			gateInput.GetMouseDelta(mouseX, mouseY);
			gateController.GetState(7, G_RY_AXIS, padStickRY);

			if (mouseX == 1 || mouseX == -1)
				mouseX = 0;

			if (mouseY == 1 || mouseY == -1)
				mouseY = 0;

			pitchChange = (65.0f * mouseY / screenHeight) + padStickRY * rotateSpeed * -1;


			matrixMath.RotateXLocalF(cameraMatrix, Degrees2Radians(pitchChange), cameraMatrix);

			float ratio;
			d3d.GetAspectRatio(ratio);
			gateController.GetState(7, G_RX_AXIS, padStickRX);
			yawChange = 65.0f * ratio * mouseX / screenWidth + padStickRX * rotateSpeed * -1;
			matrixMath.RotateYGlobalF(cameraMatrix, Degrees2Radians(yawChange), cameraMatrix);

			matrixMath.InverseF(cameraMatrix, cameras[0]);

		}

		void GameUpdate(std::vector<GamePacket> flecInfo, int cam = 4)
		{
			for (int i = 0; i < flecInfo.size(); i++)
			{
				changedItems.push_back(flecInfo[i]);
			}
			cameraIndex = cam;
		}

		int currentScore = 0; //0
		int highScore = 0; // 1

		void UpdateText(int hs = 0, int cs = 0, int life = 3, bool pse = false, bool srt = false)
		{
			ID3D11DeviceContext* con = nullptr;
			d3d.GetImmediateContext((void**)&con);
			highScore = hs;
			currentScore = cs;
			// store the client's width and height
			win.GetClientWidth(width);
			win.GetClientHeight(height);

			// set the current dynamic text to this new number
			textData.dynamicText[0].SetText(std::to_string(cs));
			// update the dynamic text so we create the vertices
			textData.dynamicText[0].Update(width, height);

			// set the high score dynamic text to this new number
			textData.dynamicText[1].SetText(std::to_string(hs));
			// update the dynamic text so we create the vertices	
			textData.dynamicText[1].Update(width, height);

			// set the life dynamic text to this new number
			textData.dynamicText[2].SetText(std::to_string(life));
			// update the dynamic text so we create the vertices	
			textData.dynamicText[2].Update(width, height);

			bool paused = pse;

			if (paused)
			{
				// set the pause score dynamic text to this new number
				textData.dynamicText[3].SetText("Paused");
				// update the dynamic text so we create the vertices	
				textData.dynamicText[3].Update(width, height);
			}
			else
			{
				// set the pause score dynamic text to this new number
				textData.dynamicText[3].SetText("");
				// update the dynamic text so we create the vertices	
				textData.dynamicText[3].Update(width, height);
			}

			bool started = srt;

			if (started)
			{
				// set the Start dynamic text to this new number
				textData.dynamicText[4].SetText(" ");
				// update the dynamic text so we create the vertices	
				textData.dynamicText[4].Update(width, height);
			}
			else
			{
				// set the Start dynamic text to this new number
				textData.dynamicText[4].SetText("Press T to Start");
				// update the dynamic text so we create the vertices	
				textData.dynamicText[4].Update(width, height);
			}

			for (size_t i = 0; i < 5; i++)
			{
				// upload the new information to the vertex buffer using map / unmap
				const auto& verts = textData.dynamicText[i].GetVertices();
				D3D11_MAPPED_SUBRESOURCE msr = { 0 };
				con->Map(vertexBufferDynamicText[i].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
				memcpy(msr.pData, verts.data(), sizeof(TextVertex) * verts.size());
				con->Unmap(vertexBufferDynamicText[i].Get(), 0);
			}
		}

	private:
		struct PipelineHandles
		{
			ID3D11DeviceContext* context;
			ID3D11RenderTargetView* targetView;
			ID3D11DepthStencilView* depthStencil;
		};

		PipelineHandles GetCurrentPipelineHandles()
		{
			PipelineHandles retval;
			d3d.GetImmediateContext((void**)&retval.context);
			d3d.GetRenderTargetView((void**)&retval.targetView);
			d3d.GetDepthStencilView((void**)&retval.depthStencil);
			return retval;
		}

		void SetUpPipeline(PipelineHandles handles)
		{
			SetRenderTargets(handles);
			SetVertexBuffers(handles);
			SetShaders(handles);

			handles.context->IASetInputLayout(vertexFormat.Get());
			handles.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			handles.context->RSSetViewports(1, viewports);
		}

		void SetRenderTargets(PipelineHandles handles)
		{
			ID3D11RenderTargetView* const views[] = { handles.targetView };
			handles.context->OMSetRenderTargets(ARRAYSIZE(views), views, handles.depthStencil);
			// set the blend state in order to use transparency
			handles.context->OMSetBlendState(blendState.Get(), NULL, 0xFFFFFFFF);
			// set the depth stencil state for depth comparison [useful for transparency with the hud objects]
			handles.context->OMSetDepthStencilState(depthStencilState.Get(), 0xFFFFFFFF);
		}

		void SetVertexBuffers(PipelineHandles handles)
		{
			const UINT strides[] = { sizeof(H2B::VERTEX) }; // TODO: Part 1E changed to size of OBJ_VEC3, may need to be _OBJ_VERT_
			const UINT offsets[] = { 0 };								//it was indeed _OBJ_VERT_ lol
			ID3D11Buffer* const buffs[] = { vertexBuffer.Get() };
			handles.context->IASetVertexBuffers(0, ARRAYSIZE(buffs), buffs, strides, offsets);
		}

		void SetShaders(PipelineHandles handles)
		{
			handles.context->VSSetShader(vertexShader.Get(), nullptr, 0);
			handles.context->PSSetShader(pixelShader.Get(), nullptr, 0);
			handles.context->GSSetShader(gsShader.Get(), nullptr, 0);
		}

		void ReleasePipelineHandles(PipelineHandles toRelease)
		{
			toRelease.depthStencil->Release();
			toRelease.targetView->Release();
			toRelease.context->Release();
		}

		void SwitchCameras(int cam)
		{

			float camera1 = 0, camera2 = 0, camera3 = 0, camera4 = 0;
			gateInput.GetState(G_KEY_1, camera1); gateInput.GetState(G_KEY_2, camera2); gateInput.GetState(G_KEY_3, camera3); gateInput.GetState(G_KEY_4, camera4);

			if (cam == 0)
			{
				currentCam = Cameras::MainCamera;
			}
			else if (cam == 1)
			{
				currentCam = Cameras::LeftCamera;
			}
			else if (cam == 2)
			{
				currentCam = Cameras::RightCamera;
			}
			else if (cam == 3)
			{
				currentCam = Cameras::ArialCamera;
			}

		}

		void SwitchLevels()
		{

			float level2 = 0, level1 = 0;
			//gateInput.GetState(G_KEY_6, level2); gateInput.GetState(G_KEY_7, level1);


			if (level2 != 0)
			{

				GW::SYSTEM::GLog log; // handy for logging any messages/warning/errors begin loading level
				log.Create("../LevelLoaderLog.txt"); //kept for testing purposes
				log.EnableConsoleLogging(true); // mirror output to the console
				log.Log("Start Program.");

				dataOrientedLoader.LoadLevel("OtherLevel.txt", "Models", log);

				for (int i = 0; i < dataOrientedLoader.levelTransforms.size(); i++)
				{
					meshData.mat_World[i] = dataOrientedLoader.levelTransforms[i]; //assigning to world array
				}

				for (int j = 0; j < dataOrientedLoader.levelMaterials.size(); j++)
				{
					meshData.material[j] = dataOrientedLoader.levelMaterials[j].attrib; //assigning to material array
				}


				//Translation(cameras[0], 0.75f, 0.45f, -1.0f); //creates a GVECTORF and calls TranslateLocalF
				cameras[0].row4 = MyVector4(0.75f, 3.45f, -1.0f);
				matrixMath.LookAtLHF(cameras[0].row4, MyVector4(0.15f, 0.45f, 0), MyVector4(0, 1, 0), cameras[0]);
				matrixMath.InverseF(cameras[0], cameras[0]);
				sceneData.cameraPos = cameras[0].row4;
				matrixMath.InverseF(cameras[0], cameras[0]);
				sceneData.mat_View = cameras[0];


				SetLevelCameras();
				IntializeGraphics();
			}
			else if (level1 != 0)
			{
				dataOrientedLoader.UnloadLevel();
				GW::SYSTEM::GLog log; // handy for logging any messages/warning/errors begin loading level
				log.Create("../LevelLoaderLog.txt"); //kept for testing purposes
				log.EnableConsoleLogging(true); // mirror output to the console
				log.Log("Start Program.");

				dataOrientedLoader.LoadLevel("MyGameLevel.txt", "Models", log);


				for (int i = 0; i < dataOrientedLoader.levelTransforms.size(); i++)
				{
					meshData.mat_World[i] = dataOrientedLoader.levelTransforms[i]; //assigning to world array
				}

				for (int j = 0; j < dataOrientedLoader.levelMaterials.size(); j++)
				{
					meshData.material[j] = dataOrientedLoader.levelMaterials[j].attrib; //assigning to material array
				}

				IntializeGraphics();
			}
		}

	public:
		~Renderer()
		{
			// ComPtr will auto release so nothing to do here yet 
		}
};
	}
