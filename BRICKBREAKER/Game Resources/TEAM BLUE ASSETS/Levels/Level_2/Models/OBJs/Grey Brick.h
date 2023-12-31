// "Grey Brick.h" generated by "Obj2Header.exe" [Version 1.9d] Author: L.Norri Fullsail University.
// Data is converted to left-handed coordinate system and UV data is V flipped for Direct3D/Vulkan.
// The companion file "Grey Brick.h2b" is a binary dump of this format(-padding) for more flexibility.
// Loading *.h2b: read version, sizes, handle strings(max len 260) by reading until null-terminated.
/***********************/
/*  Generator version  */
/***********************/
#ifndef _Grey_Brick_version_
const char Grey_Brick_version[4] = { '0','1','9','d' };
#define _Grey_Brick_version_
#endif
/************************************************/
/*  This section contains the model's size data */
/************************************************/
#ifndef _Grey_Brick_vertexcount_
const unsigned Grey_Brick_vertexcount = 216;
#define _Grey_Brick_vertexcount_
#endif
#ifndef _Grey_Brick_indexcount_
const unsigned Grey_Brick_indexcount = 324;
#define _Grey_Brick_indexcount_
#endif
#ifndef _Grey_Brick_materialcount_
const unsigned Grey_Brick_materialcount = 1; // can be used for batched draws
#define _Grey_Brick_materialcount_
#endif
#ifndef _Grey_Brick_meshcount_
const unsigned Grey_Brick_meshcount = 1;
#define _Grey_Brick_meshcount_
#endif
/************************************************/
/*  This section contains the raw data to load  */
/************************************************/
#ifndef __OBJ_VEC3__
typedef struct _OBJ_VEC3_
{
	float x,y,z; // 3D Coordinate.
}OBJ_VEC3;
#define __OBJ_VEC3__
#endif
#ifndef __OBJ_VERT__
typedef struct _OBJ_VERT_
{
	OBJ_VEC3 pos; // Left-handed +Z forward coordinate w not provided, assumed to be 1.
	OBJ_VEC3 uvw; // D3D/Vulkan style top left 0,0 coordinate.
	OBJ_VEC3 nrm; // Provided direct from obj file, may or may not be normalized.
}OBJ_VERT;
#define __OBJ_VERT__
#endif
#ifndef _Grey_Brick_vertices_
// Raw Vertex Data follows: Positions, Texture Coordinates and Normals.
const OBJ_VERT Grey_Brick_vertices[216] =
{
	{	{ -2.167018f, 0.000008f, 1.945853f },	{ 0.304897f, 0.360630f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.167018f, 0.000008f, 1.825212f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.108821f, 0.000008f, 1.825212f },	{ 0.015857f, 0.984143f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.108821f, 0.483009f, 1.823306f },	{ 0.195103f, 0.039877f, 0.000000f },	{ -0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.108821f, 0.030241f, 1.823306f },	{ 0.342636f, 0.039877f, 0.000000f },	{ -0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.167018f, 0.030241f, 1.823306f },	{ 0.342636f, 0.328917f, 0.000000f },	{ -0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.106838f, 0.483009f, 1.945853f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.106838f, 0.030241f, 1.945853f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.106838f, 0.030241f, 1.825212f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.167018f, 0.513243f, 1.825212f },	{ 0.625651f, 0.360630f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.167018f, 0.513243f, 1.945853f },	{ 0.625651f, 0.984143f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.108821f, 0.513243f, 1.945853f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.167018f, 0.483009f, 1.947759f },	{ 0.015857f, 0.039877f, 0.000000f },	{ 0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.167018f, 0.030241f, 1.947759f },	{ 0.163390f, 0.039877f, 0.000000f },	{ 0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.108821f, 0.030241f, 1.947759f },	{ 0.163390f, 0.328917f, 0.000000f },	{ 0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.169002f, 0.483009f, 1.945853f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -0.919700f, 0.019400f, 0.392100f }	},
	{	{ -2.168421f, 0.483009f, 1.947201f },	{ 0.657364f, 0.993995f, 0.000000f },	{ -0.918300f, 0.019100f, 0.395500f }	},
	{	{ -2.168164f, 0.500467f, 1.946954f },	{ 0.647512f, 0.989831f, 0.000000f },	{ -0.948300f, 0.025600f, 0.316400f }	},
	{	{ -2.167018f, 0.513243f, 1.945853f },	{ 0.625651f, 0.984143f, 0.000000f },	{ -0.687600f, 0.123300f, 0.715600f }	},
	{	{ -2.168421f, 0.504391f, 1.945853f },	{ 0.635502f, 0.984143f, 0.000000f },	{ -0.775200f, 0.122900f, 0.619600f }	},
	{	{ -2.168164f, 0.500467f, 1.946954f },	{ 0.631339f, 0.993995f, 0.000000f },	{ -0.687800f, 0.123300f, 0.715400f }	},
	{	{ -2.167018f, 0.483009f, 1.947759f },	{ 0.015857f, 0.039877f, 0.000000f },	{ -0.366100f, 0.018900f, 0.930400f }	},
	{	{ -2.167018f, 0.504391f, 1.947201f },	{ 0.006005f, 0.039877f, 0.000000f },	{ -0.292100f, 0.024900f, 0.956100f }	},
	{	{ -2.168164f, 0.500467f, 1.946954f },	{ 0.010169f, 0.030025f, 0.000000f },	{ -0.294400f, 0.024800f, 0.955400f }	},
	{	{ -2.167018f, 0.000008f, 1.945853f },	{ 0.304897f, 0.360630f, 0.000000f },	{ -0.687600f, -0.123200f, 0.715600f }	},
	{	{ -2.167018f, 0.008867f, 1.947201f },	{ 0.304897f, 0.350779f, 0.000000f },	{ -0.589200f, -0.121600f, 0.798800f }	},
	{	{ -2.168164f, 0.012791f, 1.946954f },	{ 0.314749f, 0.354943f, 0.000000f },	{ -0.687800f, -0.123200f, 0.715400f }	},
	{	{ -2.169002f, 0.030241f, 1.945853f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -0.919700f, -0.019400f, 0.392100f }	},
	{	{ -2.168421f, 0.008867f, 1.945853f },	{ 0.814749f, 0.984143f, 0.000000f },	{ -0.949100f, -0.025800f, 0.314000f }	},
	{	{ -2.168164f, 0.012791f, 1.946954f },	{ 0.810585f, 0.993995f, 0.000000f },	{ -0.948300f, -0.025600f, 0.316400f }	},
	{	{ -2.167018f, 0.030241f, 1.947759f },	{ 0.163390f, 0.039877f, 0.000000f },	{ -0.366200f, -0.018900f, 0.930300f }	},
	{	{ -2.168421f, 0.030241f, 1.947201f },	{ 0.163390f, 0.030025f, 0.000000f },	{ -0.369600f, -0.018600f, 0.929000f }	},
	{	{ -2.168164f, 0.012791f, 1.946954f },	{ 0.173241f, 0.034189f, 0.000000f },	{ -0.294300f, -0.024800f, 0.955400f }	},
	{	{ -2.108821f, 0.483009f, 1.947759f },	{ 0.015857f, 0.328917f, 0.000000f },	{ 0.366100f, 0.018900f, 0.930400f }	},
	{	{ -2.107418f, 0.483009f, 1.947201f },	{ 0.015857f, 0.338769f, 0.000000f },	{ 0.369400f, 0.018600f, 0.929100f }	},
	{	{ -2.107676f, 0.500467f, 1.946954f },	{ 0.006005f, 0.334605f, 0.000000f },	{ 0.294400f, 0.024800f, 0.955400f }	},
	{	{ -2.108821f, 0.513243f, 1.945853f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.687600f, 0.123300f, 0.715600f }	},
	{	{ -2.108821f, 0.504391f, 1.947201f },	{ 0.336610f, 0.993995f, 0.000000f },	{ 0.589500f, 0.121600f, 0.798600f }	},
	{	{ -2.107676f, 0.500467f, 1.946954f },	{ 0.326759f, 0.989831f, 0.000000f },	{ 0.687800f, 0.123300f, 0.715400f }	},
	{	{ -2.106838f, 0.483009f, 1.945853f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 0.919700f, 0.019400f, 0.392100f }	},
	{	{ -2.107418f, 0.504391f, 1.945853f },	{ 0.826759f, 0.360630f, 0.000000f },	{ 0.949100f, 0.025800f, 0.314000f }	},
	{	{ -2.107676f, 0.500467f, 1.946954f },	{ 0.830922f, 0.350779f, 0.000000f },	{ 0.948300f, 0.025600f, 0.316400f }	},
	{	{ -2.108821f, 0.030241f, 1.947759f },	{ 0.163390f, 0.328917f, 0.000000f },	{ 0.366200f, -0.018900f, 0.930300f }	},
	{	{ -2.108821f, 0.008867f, 1.947201f },	{ 0.173241f, 0.328917f, 0.000000f },	{ 0.292500f, -0.025000f, 0.955900f }	},
	{	{ -2.107676f, 0.012791f, 1.946954f },	{ 0.169077f, 0.338769f, 0.000000f },	{ 0.294800f, -0.024800f, 0.955200f }	},
	{	{ -2.106838f, 0.030241f, 1.945853f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 0.919600f, -0.019400f, 0.392400f }	},
	{	{ -2.107418f, 0.030241f, 1.947201f },	{ 0.984143f, 0.350779f, 0.000000f },	{ 0.918100f, -0.019100f, 0.395800f }	},
	{	{ -2.107676f, 0.012791f, 1.946954f },	{ 0.993995f, 0.354943f, 0.000000f },	{ 0.948100f, -0.025500f, 0.316900f }	},
	{	{ -2.108821f, 0.000008f, 1.945853f },	{ 0.015857f, 0.360630f, 0.000000f },	{ 0.687600f, -0.123200f, 0.715600f }	},
	{	{ -2.107418f, 0.008867f, 1.945853f },	{ 0.006005f, 0.360630f, 0.000000f },	{ 0.775500f, -0.122800f, 0.619300f }	},
	{	{ -2.107676f, 0.012791f, 1.946954f },	{ 0.010169f, 0.350779f, 0.000000f },	{ 0.687800f, -0.123200f, 0.715400f }	},
	{	{ -2.169002f, 0.483009f, 1.825212f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -0.919700f, 0.019400f, -0.392100f }	},
	{	{ -2.168421f, 0.504391f, 1.825212f },	{ 0.647512f, 0.360630f, 0.000000f },	{ -0.949100f, 0.025800f, -0.314000f }	},
	{	{ -2.168164f, 0.500467f, 1.824111f },	{ 0.651676f, 0.350779f, 0.000000f },	{ -0.948300f, 0.025600f, -0.316400f }	},
	{	{ -2.167018f, 0.483009f, 1.823306f },	{ 0.195103f, 0.328917f, 0.000000f },	{ -0.366100f, 0.018900f, -0.930400f }	},
	{	{ -2.168421f, 0.483009f, 1.823864f },	{ 0.195103f, 0.338769f, 0.000000f },	{ -0.369400f, 0.018600f, -0.929100f }	},
	{	{ -2.168164f, 0.500467f, 1.824111f },	{ 0.185251f, 0.334605f, 0.000000f },	{ -0.294400f, 0.024800f, -0.955400f }	},
	{	{ -2.167018f, 0.513243f, 1.825212f },	{ 0.625651f, 0.360630f, 0.000000f },	{ -0.687600f, 0.123300f, -0.715600f }	},
	{	{ -2.167018f, 0.504391f, 1.823864f },	{ 0.625651f, 0.350779f, 0.000000f },	{ -0.589500f, 0.121600f, -0.798600f }	},
	{	{ -2.168164f, 0.500467f, 1.824111f },	{ 0.635502f, 0.354943f, 0.000000f },	{ -0.687800f, 0.123300f, -0.715400f }	},
	{	{ -2.167018f, 0.030241f, 1.823306f },	{ 0.342636f, 0.328917f, 0.000000f },	{ -0.366500f, -0.018900f, -0.930200f }	},
	{	{ -2.167018f, 0.008867f, 1.823864f },	{ 0.352487f, 0.328917f, 0.000000f },	{ -0.292200f, -0.025000f, -0.956000f }	},
	{	{ -2.168164f, 0.012791f, 1.824111f },	{ 0.348324f, 0.338769f, 0.000000f },	{ -0.294500f, -0.024800f, -0.955300f }	},
	{	{ -2.169002f, 0.030241f, 1.825212f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -0.919500f, -0.019400f, -0.392500f }	},
	{	{ -2.168421f, 0.030241f, 1.823864f },	{ 0.804897f, 0.350779f, 0.000000f },	{ -0.918100f, -0.019100f, -0.395900f }	},
	{	{ -2.168164f, 0.012791f, 1.824111f },	{ 0.814749f, 0.354943f, 0.000000f },	{ -0.948200f, -0.025500f, -0.316800f }	},
	{	{ -2.167018f, 0.000008f, 1.825212f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.687600f, -0.123200f, -0.715600f }	},
	{	{ -2.168421f, 0.008867f, 1.825212f },	{ 0.314749f, 0.984143f, 0.000000f },	{ -0.775500f, -0.122800f, -0.619300f }	},
	{	{ -2.168164f, 0.012791f, 1.824111f },	{ 0.310585f, 0.993995f, 0.000000f },	{ -0.687800f, -0.123200f, -0.715400f }	},
	{	{ -2.108821f, 0.483009f, 1.823306f },	{ 0.195103f, 0.039877f, 0.000000f },	{ 0.366100f, 0.018900f, -0.930400f }	},
	{	{ -2.108821f, 0.504391f, 1.823864f },	{ 0.185251f, 0.039877f, 0.000000f },	{ 0.292100f, 0.025000f, -0.956100f }	},
	{	{ -2.107676f, 0.500467f, 1.824111f },	{ 0.189415f, 0.030025f, 0.000000f },	{ 0.294400f, 0.024800f, -0.955400f }	},
	{	{ -2.106838f, 0.483009f, 1.825212f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 0.919700f, 0.019400f, -0.392100f }	},
	{	{ -2.107418f, 0.483009f, 1.823864f },	{ 0.836610f, 0.993995f, 0.000000f },	{ 0.918300f, 0.019100f, -0.395500f }	},
	{	{ -2.107676f, 0.500467f, 1.824111f },	{ 0.826759f, 0.989831f, 0.000000f },	{ 0.948300f, 0.025600f, -0.316400f }	},
	{	{ -2.108821f, 0.513243f, 1.825212f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.687600f, 0.123300f, -0.715600f }	},
	{	{ -2.107418f, 0.504391f, 1.825212f },	{ 0.326759f, 0.360630f, 0.000000f },	{ 0.775200f, 0.122900f, -0.619600f }	},
	{	{ -2.107676f, 0.500467f, 1.824111f },	{ 0.330923f, 0.350779f, 0.000000f },	{ 0.687800f, 0.123300f, -0.715400f }	},
	{	{ -2.108821f, 0.000008f, 1.825212f },	{ 0.015857f, 0.984143f, 0.000000f },	{ 0.687600f, -0.123200f, -0.715600f }	},
	{	{ -2.108821f, 0.008867f, 1.823864f },	{ 0.015857f, 0.993995f, 0.000000f },	{ 0.589100f, -0.121500f, -0.798800f }	},
	{	{ -2.107676f, 0.012791f, 1.824111f },	{ 0.006005f, 0.989831f, 0.000000f },	{ 0.687800f, -0.123200f, -0.715400f }	},
	{	{ -2.106838f, 0.030241f, 1.825212f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 0.919700f, -0.019400f, -0.392100f }	},
	{	{ -2.107418f, 0.008867f, 1.825212f },	{ 0.993995f, 0.984143f, 0.000000f },	{ 0.949100f, -0.025800f, -0.314000f }	},
	{	{ -2.107676f, 0.012791f, 1.824111f },	{ 0.989831f, 0.993995f, 0.000000f },	{ 0.948300f, -0.025600f, -0.316400f }	},
	{	{ -2.108821f, 0.030241f, 1.823306f },	{ 0.342636f, 0.039877f, 0.000000f },	{ 0.366200f, -0.018900f, -0.930300f }	},
	{	{ -2.107418f, 0.030241f, 1.823864f },	{ 0.342636f, 0.030025f, 0.000000f },	{ 0.369600f, -0.018600f, -0.929000f }	},
	{	{ -2.107676f, 0.012791f, 1.824111f },	{ 0.352487f, 0.034189f, 0.000000f },	{ 0.294300f, -0.024800f, -0.955400f }	},
	{	{ -2.108821f, 0.000008f, 1.825212f },	{ 0.015857f, 0.984143f, 0.000000f },	{ -0.000000f, -0.150400f, -0.988600f }	},
	{	{ -2.167018f, 0.000008f, 1.825212f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.000000f, -0.150400f, -0.988600f }	},
	{	{ -2.167018f, 0.008867f, 1.823864f },	{ 0.304897f, 0.993995f, 0.000000f },	{ -0.000000f, -0.150400f, -0.988600f }	},
	{	{ -2.108821f, 0.008867f, 1.823864f },	{ 0.352487f, 0.039877f, 0.000000f },	{ 0.000000f, -0.026100f, -0.999700f }	},
	{	{ -2.167018f, 0.008867f, 1.823864f },	{ 0.352487f, 0.328917f, 0.000000f },	{ 0.000000f, -0.026100f, -0.999700f }	},
	{	{ -2.167018f, 0.030241f, 1.823306f },	{ 0.342636f, 0.328917f, 0.000000f },	{ 0.000000f, -0.026100f, -0.999700f }	},
	{	{ -2.167018f, 0.000008f, 1.825212f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.167018f, 0.000008f, 1.945853f },	{ 0.304897f, 0.360630f, 0.000000f },	{ -0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.168421f, 0.008867f, 1.945853f },	{ 0.314749f, 0.360630f, 0.000000f },	{ -0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.168421f, 0.008867f, 1.825212f },	{ 0.814749f, 0.360630f, 0.000000f },	{ -0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.168421f, 0.008867f, 1.945853f },	{ 0.814749f, 0.984143f, 0.000000f },	{ -0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.169002f, 0.030241f, 1.945853f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.167018f, 0.030241f, 1.947759f },	{ 0.163390f, 0.039877f, 0.000000f },	{ -0.370000f, 0.000000f, 0.929000f }	},
	{	{ -2.167018f, 0.483009f, 1.947759f },	{ 0.015857f, 0.039877f, 0.000000f },	{ -0.369900f, -0.000000f, 0.929100f }	},
	{	{ -2.168421f, 0.483009f, 1.947201f },	{ 0.015857f, 0.030025f, 0.000000f },	{ -0.369900f, -0.000000f, 0.929100f }	},
	{	{ -2.168421f, 0.030241f, 1.947201f },	{ 0.804897f, 0.993995f, 0.000000f },	{ -0.918400f, 0.000000f, 0.395700f }	},
	{	{ -2.168421f, 0.483009f, 1.947201f },	{ 0.657364f, 0.993995f, 0.000000f },	{ -0.918400f, 0.000000f, 0.395600f }	},
	{	{ -2.169002f, 0.483009f, 1.945853f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -0.918400f, 0.000000f, 0.395600f }	},
	{	{ -2.106838f, 0.483009f, 1.825212f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.106838f, 0.030241f, 1.825212f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.107418f, 0.030241f, 1.823864f },	{ 0.984143f, 0.993995f, 0.000000f },	{ 0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.107418f, 0.483009f, 1.823864f },	{ 0.195103f, 0.030025f, 0.000000f },	{ 0.369900f, -0.000000f, -0.929100f }	},
	{	{ -2.107418f, 0.030241f, 1.823864f },	{ 0.342636f, 0.030025f, 0.000000f },	{ 0.370000f, 0.000000f, -0.929000f }	},
	{	{ -2.108821f, 0.030241f, 1.823306f },	{ 0.342636f, 0.039877f, 0.000000f },	{ 0.370000f, 0.000000f, -0.929000f }	},
	{	{ -2.106838f, 0.030241f, 1.945853f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 0.918400f, 0.000000f, 0.395600f }	},
	{	{ -2.106838f, 0.483009f, 1.945853f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 0.918400f, 0.000000f, 0.395700f }	},
	{	{ -2.107418f, 0.483009f, 1.947201f },	{ 0.836610f, 0.350779f, 0.000000f },	{ 0.918400f, 0.000000f, 0.395700f }	},
	{	{ -2.107418f, 0.030241f, 1.947201f },	{ 0.163390f, 0.338769f, 0.000000f },	{ 0.369900f, 0.000000f, 0.929100f }	},
	{	{ -2.107418f, 0.483009f, 1.947201f },	{ 0.015857f, 0.338769f, 0.000000f },	{ 0.370000f, 0.000000f, 0.929000f }	},
	{	{ -2.108821f, 0.483009f, 1.947759f },	{ 0.015857f, 0.328917f, 0.000000f },	{ 0.370000f, 0.000000f, 0.929000f }	},
	{	{ -2.169002f, 0.030241f, 1.825212f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.169002f, 0.483009f, 1.825212f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.168421f, 0.483009f, 1.823864f },	{ 0.657364f, 0.350779f, 0.000000f },	{ -0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.168421f, 0.030241f, 1.823864f },	{ 0.342636f, 0.338769f, 0.000000f },	{ -0.369900f, 0.000000f, -0.929100f }	},
	{	{ -2.168421f, 0.483009f, 1.823864f },	{ 0.195103f, 0.338769f, 0.000000f },	{ -0.370000f, 0.000000f, -0.929000f }	},
	{	{ -2.167018f, 0.483009f, 1.823306f },	{ 0.195103f, 0.328917f, 0.000000f },	{ -0.370000f, 0.000000f, -0.929000f }	},
	{	{ -2.108821f, 0.513243f, 1.825212f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.108821f, 0.513243f, 1.945853f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.107418f, 0.504391f, 1.945853f },	{ 0.326759f, 0.984143f, 0.000000f },	{ 0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.107418f, 0.504391f, 1.825212f },	{ 0.826759f, 0.984143f, 0.000000f },	{ 0.999600f, 0.027600f, 0.000000f }	},
	{	{ -2.107418f, 0.504391f, 1.945853f },	{ 0.826759f, 0.360630f, 0.000000f },	{ 0.999600f, 0.027600f, 0.000000f }	},
	{	{ -2.106838f, 0.483009f, 1.945853f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 0.999600f, 0.027600f, 0.000000f }	},
	{	{ -2.108821f, 0.513243f, 1.945853f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.000000f, 0.150100f, 0.988700f }	},
	{	{ -2.167018f, 0.513243f, 1.945853f },	{ 0.625651f, 0.984143f, 0.000000f },	{ 0.000000f, 0.150100f, 0.988700f }	},
	{	{ -2.167018f, 0.504391f, 1.947201f },	{ 0.625651f, 0.993995f, 0.000000f },	{ 0.000000f, 0.150100f, 0.988700f }	},
	{	{ -2.108821f, 0.504391f, 1.947201f },	{ 0.006005f, 0.328917f, 0.000000f },	{ -0.000000f, 0.026400f, 0.999700f }	},
	{	{ -2.167018f, 0.504391f, 1.947201f },	{ 0.006005f, 0.039877f, 0.000000f },	{ -0.000000f, 0.026400f, 0.999700f }	},
	{	{ -2.167018f, 0.483009f, 1.947759f },	{ 0.015857f, 0.039877f, 0.000000f },	{ -0.000000f, 0.026400f, 0.999700f }	},
	{	{ -2.108821f, 0.000008f, 1.945853f },	{ 0.015857f, 0.360630f, 0.000000f },	{ 0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.108821f, 0.000008f, 1.825212f },	{ 0.015857f, 0.984143f, 0.000000f },	{ 0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.107418f, 0.008867f, 1.825212f },	{ 0.006005f, 0.984143f, 0.000000f },	{ 0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.107418f, 0.008867f, 1.945853f },	{ 0.993995f, 0.360630f, 0.000000f },	{ 0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.107418f, 0.008867f, 1.825212f },	{ 0.993995f, 0.984143f, 0.000000f },	{ 0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.106838f, 0.030241f, 1.825212f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.167018f, 0.513243f, 1.825212f },	{ 0.625651f, 0.360630f, 0.000000f },	{ 0.000000f, 0.150100f, -0.988700f }	},
	{	{ -2.108821f, 0.513243f, 1.825212f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.000000f, 0.150100f, -0.988700f }	},
	{	{ -2.108821f, 0.504391f, 1.823864f },	{ 0.336610f, 0.350779f, 0.000000f },	{ 0.000000f, 0.150100f, -0.988700f }	},
	{	{ -2.167018f, 0.504391f, 1.823864f },	{ 0.185251f, 0.328917f, 0.000000f },	{ 0.000000f, 0.026400f, -0.999700f }	},
	{	{ -2.108821f, 0.504391f, 1.823864f },	{ 0.185251f, 0.039877f, 0.000000f },	{ 0.000000f, 0.026400f, -0.999700f }	},
	{	{ -2.108821f, 0.483009f, 1.823306f },	{ 0.195103f, 0.039877f, 0.000000f },	{ 0.000000f, 0.026400f, -0.999700f }	},
	{	{ -2.167018f, 0.513243f, 1.945853f },	{ 0.625651f, 0.984143f, 0.000000f },	{ -0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.167018f, 0.513243f, 1.825212f },	{ 0.625651f, 0.360630f, 0.000000f },	{ -0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.168421f, 0.504391f, 1.825212f },	{ 0.635502f, 0.360630f, 0.000000f },	{ -0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.168421f, 0.504391f, 1.945853f },	{ 0.647512f, 0.984143f, 0.000000f },	{ -0.999600f, 0.027600f, -0.000000f }	},
	{	{ -2.168421f, 0.504391f, 1.825212f },	{ 0.647512f, 0.360630f, 0.000000f },	{ -0.999600f, 0.027600f, -0.000000f }	},
	{	{ -2.169002f, 0.483009f, 1.825212f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -0.999600f, 0.027600f, -0.000000f }	},
	{	{ -2.167018f, 0.000008f, 1.945853f },	{ 0.304897f, 0.360630f, 0.000000f },	{ 0.000000f, -0.150400f, 0.988600f }	},
	{	{ -2.108821f, 0.000008f, 1.945853f },	{ 0.015857f, 0.360630f, 0.000000f },	{ 0.000000f, -0.150400f, 0.988600f }	},
	{	{ -2.108821f, 0.008867f, 1.947201f },	{ 0.015857f, 0.350779f, 0.000000f },	{ 0.000000f, -0.150400f, 0.988600f }	},
	{	{ -2.167018f, 0.008867f, 1.947201f },	{ 0.173241f, 0.039877f, 0.000000f },	{ -0.000000f, -0.026100f, 0.999700f }	},
	{	{ -2.108821f, 0.008867f, 1.947201f },	{ 0.173241f, 0.328917f, 0.000000f },	{ -0.000000f, -0.026100f, 0.999700f }	},
	{	{ -2.108821f, 0.030241f, 1.947759f },	{ 0.163390f, 0.328917f, 0.000000f },	{ -0.000000f, -0.026100f, 0.999700f }	},
	{	{ -2.169002f, 0.483009f, 1.825212f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.169002f, 0.030241f, 1.825212f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.169002f, 0.030241f, 1.945853f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.108821f, 0.000008f, 1.945853f },	{ 0.015857f, 0.360630f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.167018f, 0.483009f, 1.823306f },	{ 0.195103f, 0.328917f, 0.000000f },	{ -0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.106838f, 0.483009f, 1.825212f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.108821f, 0.513243f, 1.825212f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.108821f, 0.483009f, 1.947759f },	{ 0.015857f, 0.328917f, 0.000000f },	{ 0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.168421f, 0.504391f, 1.945853f },	{ 0.647512f, 0.984143f, 0.000000f },	{ -0.949100f, 0.025800f, 0.314000f }	},
	{	{ -2.167018f, 0.504391f, 1.947201f },	{ 0.625651f, 0.993995f, 0.000000f },	{ -0.589500f, 0.121600f, 0.798600f }	},
	{	{ -2.168421f, 0.483009f, 1.947201f },	{ 0.015857f, 0.030025f, 0.000000f },	{ -0.369400f, 0.018600f, 0.929100f }	},
	{	{ -2.168421f, 0.008867f, 1.945853f },	{ 0.314749f, 0.360630f, 0.000000f },	{ -0.775500f, -0.122800f, 0.619300f }	},
	{	{ -2.168421f, 0.030241f, 1.947201f },	{ 0.804897f, 0.993995f, 0.000000f },	{ -0.918300f, -0.019200f, 0.395500f }	},
	{	{ -2.167018f, 0.008867f, 1.947201f },	{ 0.173241f, 0.039877f, 0.000000f },	{ -0.292000f, -0.025000f, 0.956100f }	},
	{	{ -2.108821f, 0.504391f, 1.947201f },	{ 0.006005f, 0.328917f, 0.000000f },	{ 0.292100f, 0.025000f, 0.956100f }	},
	{	{ -2.107418f, 0.504391f, 1.945853f },	{ 0.326759f, 0.984143f, 0.000000f },	{ 0.775200f, 0.122900f, 0.619600f }	},
	{	{ -2.107418f, 0.483009f, 1.947201f },	{ 0.836610f, 0.350779f, 0.000000f },	{ 0.918300f, 0.019100f, 0.395500f }	},
	{	{ -2.107418f, 0.030241f, 1.947201f },	{ 0.163390f, 0.338769f, 0.000000f },	{ 0.369600f, -0.018600f, 0.929000f }	},
	{	{ -2.107418f, 0.008867f, 1.945853f },	{ 0.993995f, 0.360630f, 0.000000f },	{ 0.949000f, -0.025500f, 0.314300f }	},
	{	{ -2.108821f, 0.008867f, 1.947201f },	{ 0.015857f, 0.350779f, 0.000000f },	{ 0.589200f, -0.121500f, 0.798800f }	},
	{	{ -2.168421f, 0.483009f, 1.823864f },	{ 0.657364f, 0.350779f, 0.000000f },	{ -0.918300f, 0.019100f, -0.395500f }	},
	{	{ -2.167018f, 0.504391f, 1.823864f },	{ 0.185251f, 0.328917f, 0.000000f },	{ -0.292100f, 0.024900f, -0.956100f }	},
	{	{ -2.168421f, 0.504391f, 1.825212f },	{ 0.635502f, 0.360630f, 0.000000f },	{ -0.775200f, 0.122900f, -0.619600f }	},
	{	{ -2.168421f, 0.030241f, 1.823864f },	{ 0.342636f, 0.338769f, 0.000000f },	{ -0.369800f, -0.018600f, -0.928900f }	},
	{	{ -2.168421f, 0.008867f, 1.825212f },	{ 0.814749f, 0.360630f, 0.000000f },	{ -0.949000f, -0.025500f, -0.314200f }	},
	{	{ -2.167018f, 0.008867f, 1.823864f },	{ 0.304897f, 0.993995f, 0.000000f },	{ -0.589100f, -0.121600f, -0.798800f }	},
	{	{ -2.107418f, 0.483009f, 1.823864f },	{ 0.195103f, 0.030025f, 0.000000f },	{ 0.369400f, 0.018600f, -0.929100f }	},
	{	{ -2.107418f, 0.504391f, 1.825212f },	{ 0.826759f, 0.984143f, 0.000000f },	{ 0.949100f, 0.025800f, -0.314000f }	},
	{	{ -2.108821f, 0.504391f, 1.823864f },	{ 0.336610f, 0.350779f, 0.000000f },	{ 0.589500f, 0.121600f, -0.798600f }	},
	{	{ -2.107418f, 0.008867f, 1.825212f },	{ 0.006005f, 0.984143f, 0.000000f },	{ 0.775500f, -0.122800f, -0.619300f }	},
	{	{ -2.107418f, 0.030241f, 1.823864f },	{ 0.984143f, 0.993995f, 0.000000f },	{ 0.918300f, -0.019200f, -0.395500f }	},
	{	{ -2.108821f, 0.008867f, 1.823864f },	{ 0.352487f, 0.039877f, 0.000000f },	{ 0.291900f, -0.025000f, -0.956100f }	},
	{	{ -2.108821f, 0.008867f, 1.823864f },	{ 0.015857f, 0.993995f, 0.000000f },	{ -0.000000f, -0.150400f, -0.988600f }	},
	{	{ -2.108821f, 0.030241f, 1.823306f },	{ 0.342636f, 0.039877f, 0.000000f },	{ 0.000000f, -0.026100f, -0.999700f }	},
	{	{ -2.168421f, 0.008867f, 1.825212f },	{ 0.314749f, 0.984143f, 0.000000f },	{ -0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.169002f, 0.030241f, 1.825212f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.168421f, 0.030241f, 1.947201f },	{ 0.163390f, 0.030025f, 0.000000f },	{ -0.370000f, 0.000000f, 0.929000f }	},
	{	{ -2.169002f, 0.030241f, 1.945853f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -0.918400f, 0.000000f, 0.395700f }	},
	{	{ -2.107418f, 0.483009f, 1.823864f },	{ 0.836610f, 0.993995f, 0.000000f },	{ 0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.108821f, 0.483009f, 1.823306f },	{ 0.195103f, 0.039877f, 0.000000f },	{ 0.369900f, -0.000000f, -0.929100f }	},
	{	{ -2.107418f, 0.030241f, 1.947201f },	{ 0.984143f, 0.350779f, 0.000000f },	{ 0.918400f, 0.000000f, 0.395600f }	},
	{	{ -2.108821f, 0.030241f, 1.947759f },	{ 0.163390f, 0.328917f, 0.000000f },	{ 0.369900f, 0.000000f, 0.929100f }	},
	{	{ -2.168421f, 0.030241f, 1.823864f },	{ 0.804897f, 0.350779f, 0.000000f },	{ -0.918400f, 0.000000f, -0.395700f }	},
	{	{ -2.167018f, 0.030241f, 1.823306f },	{ 0.342636f, 0.328917f, 0.000000f },	{ -0.369900f, 0.000000f, -0.929100f }	},
	{	{ -2.107418f, 0.504391f, 1.825212f },	{ 0.326759f, 0.360630f, 0.000000f },	{ 0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.106838f, 0.483009f, 1.825212f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 0.999600f, 0.027600f, 0.000000f }	},
	{	{ -2.108821f, 0.504391f, 1.947201f },	{ 0.336610f, 0.993995f, 0.000000f },	{ 0.000000f, 0.150100f, 0.988700f }	},
	{	{ -2.108821f, 0.483009f, 1.947759f },	{ 0.015857f, 0.328917f, 0.000000f },	{ -0.000000f, 0.026400f, 0.999700f }	},
	{	{ -2.107418f, 0.008867f, 1.945853f },	{ 0.006005f, 0.360630f, 0.000000f },	{ 0.987700f, -0.156400f, -0.000000f }	},
	{	{ -2.106838f, 0.030241f, 1.945853f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 0.999600f, -0.027200f, -0.000000f }	},
	{	{ -2.167018f, 0.504391f, 1.823864f },	{ 0.625651f, 0.350779f, 0.000000f },	{ 0.000000f, 0.150100f, -0.988700f }	},
	{	{ -2.167018f, 0.483009f, 1.823306f },	{ 0.195103f, 0.328917f, 0.000000f },	{ 0.000000f, 0.026400f, -0.999700f }	},
	{	{ -2.168421f, 0.504391f, 1.945853f },	{ 0.635502f, 0.984143f, 0.000000f },	{ -0.987700f, 0.156200f, -0.000000f }	},
	{	{ -2.169002f, 0.483009f, 1.945853f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -0.999600f, 0.027600f, -0.000000f }	},
	{	{ -2.167018f, 0.008867f, 1.947201f },	{ 0.304897f, 0.350779f, 0.000000f },	{ 0.000000f, -0.150400f, 0.988600f }	},
	{	{ -2.167018f, 0.030241f, 1.947759f },	{ 0.163390f, 0.039877f, 0.000000f },	{ -0.000000f, -0.026100f, 0.999700f }	},
	{	{ -2.169002f, 0.483009f, 1.945853f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
};
#define _Grey_Brick_vertices_
#endif
#ifndef _Grey_Brick_indices_
// Index Data follows: Sequential by mesh, Every Three Indices == One Triangle.
const unsigned int Grey_Brick_indices[324] =
{
	 0, 1, 2,
	 3, 4, 5,
	 6, 7, 8,
	 9, 10, 11,
	 12, 13, 14,
	 15, 16, 17,
	 18, 19, 20,
	 21, 22, 23,
	 24, 25, 26,
	 27, 28, 29,
	 30, 31, 32,
	 33, 34, 35,
	 36, 37, 38,
	 39, 40, 41,
	 42, 43, 44,
	 45, 46, 47,
	 48, 49, 50,
	 51, 52, 53,
	 54, 55, 56,
	 57, 58, 59,
	 60, 61, 62,
	 63, 64, 65,
	 66, 67, 68,
	 69, 70, 71,
	 72, 73, 74,
	 75, 76, 77,
	 78, 79, 80,
	 81, 82, 83,
	 84, 85, 86,
	 87, 88, 89,
	 90, 91, 92,
	 93, 94, 95,
	 96, 97, 98,
	 99, 100, 101,
	 102, 103, 104,
	 105, 106, 107,
	 108, 109, 110,
	 111, 112, 113,
	 114, 115, 116,
	 117, 118, 119,
	 120, 121, 122,
	 123, 124, 125,
	 126, 127, 128,
	 129, 130, 131,
	 132, 133, 134,
	 135, 136, 137,
	 138, 139, 140,
	 141, 142, 143,
	 144, 145, 146,
	 147, 148, 149,
	 150, 151, 152,
	 153, 154, 155,
	 156, 157, 158,
	 159, 160, 161,
	 0, 2, 162,
	 3, 5, 163,
	 6, 8, 164,
	 9, 11, 165,
	 12, 14, 166,
	 15, 17, 167,
	 18, 20, 168,
	 21, 23, 169,
	 24, 26, 170,
	 27, 29, 171,
	 30, 32, 172,
	 33, 35, 173,
	 36, 38, 174,
	 39, 41, 175,
	 42, 44, 176,
	 45, 47, 177,
	 48, 50, 178,
	 51, 53, 179,
	 54, 56, 180,
	 57, 59, 181,
	 60, 62, 182,
	 63, 65, 183,
	 66, 68, 184,
	 69, 71, 185,
	 72, 74, 186,
	 75, 77, 187,
	 78, 80, 188,
	 81, 83, 189,
	 84, 86, 190,
	 87, 89, 191,
	 90, 92, 192,
	 93, 95, 193,
	 96, 98, 194,
	 99, 101, 195,
	 102, 104, 196,
	 105, 107, 197,
	 108, 110, 198,
	 111, 113, 199,
	 114, 116, 200,
	 117, 119, 201,
	 120, 122, 202,
	 123, 125, 203,
	 126, 128, 204,
	 129, 131, 205,
	 132, 134, 206,
	 135, 137, 207,
	 138, 140, 208,
	 141, 143, 209,
	 144, 146, 210,
	 147, 149, 211,
	 150, 152, 212,
	 153, 155, 213,
	 156, 158, 214,
	 159, 161, 215,
};
#define _Grey_Brick_indices_
#endif
// Part of an OBJ_MATERIAL, the struct is 16 byte aligned so it is GPU register friendly.
#ifndef __OBJ_ATTRIBUTES__
typedef struct _OBJ_ATTRIBUTES_
{
	OBJ_VEC3    Kd; // diffuse reflectivity
	float	    d; // dissolve (transparency) 
	OBJ_VEC3    Ks; // specular reflectivity
	float       Ns; // specular exponent
	OBJ_VEC3    Ka; // ambient reflectivity
	float       sharpness; // local reflection map sharpness
	OBJ_VEC3    Tf; // transmission filter
	float       Ni; // optical density (index of refraction)
	OBJ_VEC3    Ke; // emissive reflectivity
	unsigned    illum; // illumination model
}OBJ_ATTRIBUTES;
#define __OBJ_ATTRIBUTES__
#endif
// This structure also has been made GPU register friendly so it can be transfered directly if desired.
// Note: Total struct size will vary depenedening on CPU processor architecture (string pointers).
#ifndef __OBJ_MATERIAL__
typedef struct _OBJ_MATERIAL_
{
	// The following items are typically used in a pixel/fragment shader, they are packed for GPU registers.
	OBJ_ATTRIBUTES attrib; // Surface shading characteristics & illumination model
	// All items below this line are not needed on the GPU and are generally only used during load time.
	const char* name; // the name of this material
	// If the model's materials contain any specific texture data it will be located below.
	const char* map_Kd; // diffuse texture
	const char* map_Ks; // specular texture
	const char* map_Ka; // ambient texture
	const char* map_Ke; // emissive texture
	const char* map_Ns; // specular exponent texture
	const char* map_d; // transparency texture
	const char* disp; // roughness map (displacement)
	const char* decal; // decal texture (lerps texture & material colors)
	const char* bump; // normal/bumpmap texture
	void* padding[2]; // 16 byte alignment on 32bit or 64bit
}OBJ_MATERIAL;
#define __OBJ_MATERIAL__
#endif
#ifndef _Grey_Brick_materials_
// Material Data follows: pulled from a .mtl file of the same name if present.
const OBJ_MATERIAL Grey_Brick_materials[1] =
{
	{
		{{ 0.600000f, 0.600000f, 0.600000f },
		1.000000f,
		{ 0.200000f, 0.200000f, 0.200000f },
		500.000000f,
		{ 1.000000f, 1.000000f, 1.000000f },
		60.000000f,
		{ 1.000000f, 1.000000f, 1.000000f },
		1.500000f,
		{ 0.000000f, 0.000000f, 0.000000f },
		2},
		"default",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
	},
};
#define _Grey_Brick_materials_
#endif
/************************************************/
/*  This section contains the model's structure */
/************************************************/
#ifndef _Grey_Brick_batches_
// Use this conveinence array to batch render all geometry by like material.
// Each entry corresponds to the same entry in the materials array above.
// The two numbers provided are the IndexCount and the IndexOffset into the indices array.
// If you need more fine grained control(ex: for transformations) use the OBJ_MESH data below.
const unsigned int Grey_Brick_batches[1][2] =
{
	{ 324, 0 },
};
#define _Grey_Brick_batches_
#endif
#ifndef __OBJ_MESH__
typedef struct _OBJ_MESH_
{
	const char* name;
	unsigned    indexCount;
	unsigned    indexOffset;
	unsigned    materialIndex;
}OBJ_MESH;
#define __OBJ_MESH__
#endif
#ifndef _Grey_Brick_meshes_
// Mesh Data follows: Meshes are .obj groups sorted & split by material.
// Meshes are provided in sequential order, sorted by material first and name second.
const OBJ_MESH Grey_Brick_meshes[1] =
{
	{
		"default",
		324,
		0,
		0,
	},
};
#define _Grey_Brick_meshes_
#endif
