// "Green Brick.h" generated by "Obj2Header.exe" [Version 1.9d] Author: L.Norri Fullsail University.
// Data is converted to left-handed coordinate system and UV data is V flipped for Direct3D/Vulkan.
// The companion file "Green Brick.h2b" is a binary dump of this format(-padding) for more flexibility.
// Loading *.h2b: read version, sizes, handle strings(max len 260) by reading until null-terminated.
/***********************/
/*  Generator version  */
/***********************/
#ifndef _Green_Brick_version_
const char Green_Brick_version[4] = { '0','1','9','d' };
#define _Green_Brick_version_
#endif
/************************************************/
/*  This section contains the model's size data */
/************************************************/
#ifndef _Green_Brick_vertexcount_
const unsigned Green_Brick_vertexcount = 216;
#define _Green_Brick_vertexcount_
#endif
#ifndef _Green_Brick_indexcount_
const unsigned Green_Brick_indexcount = 324;
#define _Green_Brick_indexcount_
#endif
#ifndef _Green_Brick_materialcount_
const unsigned Green_Brick_materialcount = 1; // can be used for batched draws
#define _Green_Brick_materialcount_
#endif
#ifndef _Green_Brick_meshcount_
const unsigned Green_Brick_meshcount = 1;
#define _Green_Brick_meshcount_
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
#ifndef _Green_Brick_vertices_
// Raw Vertex Data follows: Positions, Texture Coordinates and Normals.
const OBJ_VERT Green_Brick_vertices[216] =
{
	{	{ -2.381298f, 0.000008f, 2.018836f },	{ 0.304897f, 0.360630f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.381298f, 0.000008f, 1.854336f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.304342f, 0.000008f, 1.854336f },	{ 0.015857f, 0.984143f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.304342f, 0.483009f, 1.851737f },	{ 0.195103f, 0.039877f, 0.000000f },	{ 0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.304342f, 0.030241f, 1.851737f },	{ 0.342636f, 0.039877f, 0.000000f },	{ 0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.381298f, 0.030241f, 1.851737f },	{ 0.342636f, 0.328917f, 0.000000f },	{ 0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.301719f, 0.483009f, 2.018836f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.301719f, 0.030241f, 2.018836f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.301719f, 0.030241f, 1.854336f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.381298f, 0.513243f, 1.854336f },	{ 0.625651f, 0.360630f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.381298f, 0.513243f, 2.018836f },	{ 0.625651f, 0.984143f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.304342f, 0.513243f, 2.018836f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.381298f, 0.483009f, 2.021435f },	{ 0.015857f, 0.039877f, 0.000000f },	{ -0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.381298f, 0.030241f, 2.021435f },	{ 0.163390f, 0.039877f, 0.000000f },	{ -0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.304342f, 0.030241f, 2.021435f },	{ 0.163390f, 0.328917f, 0.000000f },	{ -0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.383921f, 0.483009f, 2.018836f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -0.924300f, 0.025900f, 0.380900f }	},
	{	{ -2.383153f, 0.483009f, 2.020674f },	{ 0.657364f, 0.993995f, 0.000000f },	{ -0.922400f, 0.025400f, 0.385500f }	},
	{	{ -2.382813f, 0.500467f, 2.020336f },	{ 0.647512f, 0.989831f, 0.000000f },	{ -0.950600f, 0.033800f, 0.308500f }	},
	{	{ -2.381298f, 0.513243f, 2.018836f },	{ 0.625651f, 0.984143f, 0.000000f },	{ -0.694200f, 0.164600f, 0.700700f }	},
	{	{ -2.383153f, 0.504391f, 2.018836f },	{ 0.635502f, 0.984143f, 0.000000f },	{ -0.779900f, 0.163500f, 0.604200f }	},
	{	{ -2.382813f, 0.500467f, 2.020336f },	{ 0.631339f, 0.993995f, 0.000000f },	{ -0.694300f, 0.164600f, 0.700600f }	},
	{	{ -2.381298f, 0.483009f, 2.021435f },	{ 0.015857f, 0.039877f, 0.000000f },	{ -0.374900f, 0.025800f, 0.926700f }	},
	{	{ -2.381298f, 0.504391f, 2.020674f },	{ 0.006005f, 0.039877f, 0.000000f },	{ -0.300400f, 0.033900f, 0.953200f }	},
	{	{ -2.382813f, 0.500467f, 2.020336f },	{ 0.010169f, 0.030025f, 0.000000f },	{ -0.303700f, 0.033600f, 0.952200f }	},
	{	{ -2.381298f, 0.000008f, 2.018836f },	{ 0.304897f, 0.360630f, 0.000000f },	{ -0.694200f, -0.164500f, 0.700700f }	},
	{	{ -2.381298f, 0.008867f, 2.020674f },	{ 0.304897f, 0.350779f, 0.000000f },	{ -0.597000f, -0.163000f, 0.785500f }	},
	{	{ -2.382813f, 0.012791f, 2.020336f },	{ 0.314749f, 0.354943f, 0.000000f },	{ -0.694300f, -0.164500f, 0.700700f }	},
	{	{ -2.383921f, 0.030241f, 2.018836f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -0.924300f, -0.026000f, 0.380900f }	},
	{	{ -2.383153f, 0.008867f, 2.018836f },	{ 0.814749f, 0.984143f, 0.000000f },	{ -0.951700f, -0.034200f, 0.305200f }	},
	{	{ -2.382813f, 0.012791f, 2.020336f },	{ 0.810585f, 0.993995f, 0.000000f },	{ -0.950600f, -0.033800f, 0.308600f }	},
	{	{ -2.381298f, 0.030241f, 2.021435f },	{ 0.163390f, 0.039877f, 0.000000f },	{ -0.375000f, -0.025800f, 0.926700f }	},
	{	{ -2.383153f, 0.030241f, 2.020674f },	{ 0.163390f, 0.030025f, 0.000000f },	{ -0.379500f, -0.025300f, 0.924800f }	},
	{	{ -2.382813f, 0.012791f, 2.020336f },	{ 0.173241f, 0.034189f, 0.000000f },	{ -0.303600f, -0.033600f, 0.952200f }	},
	{	{ -2.304342f, 0.483009f, 2.021435f },	{ 0.015857f, 0.328917f, 0.000000f },	{ 0.374900f, 0.025800f, 0.926700f }	},
	{	{ -2.302487f, 0.483009f, 2.020674f },	{ 0.015857f, 0.338769f, 0.000000f },	{ 0.379400f, 0.025300f, 0.924900f }	},
	{	{ -2.302827f, 0.500467f, 2.020336f },	{ 0.006005f, 0.334605f, 0.000000f },	{ 0.303700f, 0.033600f, 0.952200f }	},
	{	{ -2.304342f, 0.513243f, 2.018836f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.694200f, 0.164600f, 0.700700f }	},
	{	{ -2.304342f, 0.504391f, 2.020674f },	{ 0.336610f, 0.993995f, 0.000000f },	{ 0.597200f, 0.163100f, 0.785300f }	},
	{	{ -2.302827f, 0.500467f, 2.020336f },	{ 0.326759f, 0.989831f, 0.000000f },	{ 0.694300f, 0.164600f, 0.700600f }	},
	{	{ -2.301719f, 0.483009f, 2.018836f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 0.924300f, 0.026000f, 0.380900f }	},
	{	{ -2.302487f, 0.504391f, 2.018836f },	{ 0.826759f, 0.360630f, 0.000000f },	{ 0.951700f, 0.034200f, 0.305200f }	},
	{	{ -2.302827f, 0.500467f, 2.020336f },	{ 0.830922f, 0.350779f, 0.000000f },	{ 0.950600f, 0.033800f, 0.308500f }	},
	{	{ -2.304342f, 0.030241f, 2.021435f },	{ 0.163390f, 0.328917f, 0.000000f },	{ 0.375000f, -0.025800f, 0.926700f }	},
	{	{ -2.304342f, 0.008867f, 2.020674f },	{ 0.173241f, 0.328917f, 0.000000f },	{ 0.300300f, -0.033900f, 0.953300f }	},
	{	{ -2.302827f, 0.012791f, 2.020336f },	{ 0.169077f, 0.338769f, 0.000000f },	{ 0.303600f, -0.033600f, 0.952200f }	},
	{	{ -2.301719f, 0.030241f, 2.018836f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 0.924100f, -0.026000f, 0.381200f }	},
	{	{ -2.302487f, 0.030241f, 2.020674f },	{ 0.984143f, 0.350779f, 0.000000f },	{ 0.922200f, -0.025400f, 0.385800f }	},
	{	{ -2.302827f, 0.012791f, 2.020336f },	{ 0.993995f, 0.354943f, 0.000000f },	{ 0.950500f, -0.033700f, 0.308900f }	},
	{	{ -2.304342f, 0.000008f, 2.018836f },	{ 0.015857f, 0.360630f, 0.000000f },	{ 0.694200f, -0.164500f, 0.700700f }	},
	{	{ -2.302487f, 0.008867f, 2.018836f },	{ 0.006005f, 0.360630f, 0.000000f },	{ 0.780100f, -0.163300f, 0.604000f }	},
	{	{ -2.302827f, 0.012791f, 2.020336f },	{ 0.010169f, 0.350779f, 0.000000f },	{ 0.694300f, -0.164500f, 0.700700f }	},
	{	{ -2.383921f, 0.483009f, 1.854336f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -0.924300f, 0.026000f, -0.380800f }	},
	{	{ -2.383153f, 0.504391f, 1.854336f },	{ 0.647512f, 0.360630f, 0.000000f },	{ -0.951700f, 0.034200f, -0.305300f }	},
	{	{ -2.382813f, 0.500467f, 1.852836f },	{ 0.651676f, 0.350779f, 0.000000f },	{ -0.950600f, 0.033800f, -0.308600f }	},
	{	{ -2.381298f, 0.483009f, 1.851737f },	{ 0.195103f, 0.328917f, 0.000000f },	{ -0.374800f, 0.025800f, -0.926700f }	},
	{	{ -2.383153f, 0.483009f, 1.852498f },	{ 0.195103f, 0.338769f, 0.000000f },	{ -0.379400f, 0.025300f, -0.924900f }	},
	{	{ -2.382813f, 0.500467f, 1.852836f },	{ 0.185251f, 0.334605f, 0.000000f },	{ -0.303500f, 0.033600f, -0.952200f }	},
	{	{ -2.381298f, 0.513243f, 1.854336f },	{ 0.625651f, 0.360630f, 0.000000f },	{ -0.694200f, 0.164600f, -0.700700f }	},
	{	{ -2.381298f, 0.504391f, 1.852498f },	{ 0.625651f, 0.350779f, 0.000000f },	{ -0.597400f, 0.163000f, -0.785200f }	},
	{	{ -2.382813f, 0.500467f, 1.852836f },	{ 0.635502f, 0.354943f, 0.000000f },	{ -0.694300f, 0.164600f, -0.700600f }	},
	{	{ -2.381298f, 0.030241f, 1.851737f },	{ 0.342636f, 0.328917f, 0.000000f },	{ -0.375000f, -0.025800f, -0.926700f }	},
	{	{ -2.381298f, 0.008867f, 1.852498f },	{ 0.352487f, 0.328917f, 0.000000f },	{ -0.300200f, -0.033900f, -0.953300f }	},
	{	{ -2.382813f, 0.012791f, 1.852836f },	{ 0.348324f, 0.338769f, 0.000000f },	{ -0.303500f, -0.033600f, -0.952200f }	},
	{	{ -2.383921f, 0.030241f, 1.854336f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -0.924200f, -0.026000f, -0.381100f }	},
	{	{ -2.383153f, 0.030241f, 1.852498f },	{ 0.804897f, 0.350779f, 0.000000f },	{ -0.922300f, -0.025400f, -0.385700f }	},
	{	{ -2.382813f, 0.012791f, 1.852836f },	{ 0.814749f, 0.354943f, 0.000000f },	{ -0.950500f, -0.033700f, -0.309000f }	},
	{	{ -2.381298f, 0.000008f, 1.854336f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.694200f, -0.164500f, -0.700700f }	},
	{	{ -2.383153f, 0.008867f, 1.854336f },	{ 0.314749f, 0.984143f, 0.000000f },	{ -0.780000f, -0.163400f, -0.604100f }	},
	{	{ -2.382813f, 0.012791f, 1.852836f },	{ 0.310585f, 0.993995f, 0.000000f },	{ -0.694300f, -0.164500f, -0.700600f }	},
	{	{ -2.304342f, 0.483009f, 1.851737f },	{ 0.195103f, 0.039877f, 0.000000f },	{ 0.374800f, 0.025800f, -0.926700f }	},
	{	{ -2.304342f, 0.504391f, 1.852498f },	{ 0.185251f, 0.039877f, 0.000000f },	{ 0.300200f, 0.033900f, -0.953300f }	},
	{	{ -2.302827f, 0.500467f, 1.852836f },	{ 0.189415f, 0.030025f, 0.000000f },	{ 0.303500f, 0.033600f, -0.952200f }	},
	{	{ -2.301719f, 0.483009f, 1.854336f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 0.924300f, 0.025900f, -0.380800f }	},
	{	{ -2.302487f, 0.483009f, 1.852498f },	{ 0.836610f, 0.993995f, 0.000000f },	{ 0.922400f, 0.025400f, -0.385400f }	},
	{	{ -2.302827f, 0.500467f, 1.852836f },	{ 0.826759f, 0.989831f, 0.000000f },	{ 0.950600f, 0.033800f, -0.308600f }	},
	{	{ -2.304342f, 0.513243f, 1.854336f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.694200f, 0.164600f, -0.700700f }	},
	{	{ -2.302487f, 0.504391f, 1.854336f },	{ 0.326759f, 0.360630f, 0.000000f },	{ 0.779800f, 0.163500f, -0.604300f }	},
	{	{ -2.302827f, 0.500467f, 1.852836f },	{ 0.330923f, 0.350779f, 0.000000f },	{ 0.694300f, 0.164600f, -0.700600f }	},
	{	{ -2.304342f, 0.000008f, 1.854336f },	{ 0.015857f, 0.984143f, 0.000000f },	{ 0.694200f, -0.164500f, -0.700700f }	},
	{	{ -2.304342f, 0.008867f, 1.852498f },	{ 0.015857f, 0.993995f, 0.000000f },	{ 0.597100f, -0.162900f, -0.785400f }	},
	{	{ -2.302827f, 0.012791f, 1.852836f },	{ 0.006005f, 0.989831f, 0.000000f },	{ 0.694300f, -0.164500f, -0.700600f }	},
	{	{ -2.301719f, 0.030241f, 1.854336f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 0.924300f, -0.026000f, -0.380800f }	},
	{	{ -2.302487f, 0.008867f, 1.854336f },	{ 0.993995f, 0.984143f, 0.000000f },	{ 0.951600f, -0.034200f, -0.305300f }	},
	{	{ -2.302827f, 0.012791f, 1.852836f },	{ 0.989831f, 0.993995f, 0.000000f },	{ 0.950600f, -0.033900f, -0.308700f }	},
	{	{ -2.304342f, 0.030241f, 1.851737f },	{ 0.342636f, 0.039877f, 0.000000f },	{ 0.375000f, -0.025800f, -0.926700f }	},
	{	{ -2.302487f, 0.030241f, 1.852498f },	{ 0.342636f, 0.030025f, 0.000000f },	{ 0.379500f, -0.025300f, -0.924800f }	},
	{	{ -2.302827f, 0.012791f, 1.852836f },	{ 0.352487f, 0.034189f, 0.000000f },	{ 0.303500f, -0.033600f, -0.952200f }	},
	{	{ -2.304342f, 0.000008f, 1.854336f },	{ 0.015857f, 0.984143f, 0.000000f },	{ -0.000000f, -0.203200f, -0.979100f }	},
	{	{ -2.381298f, 0.000008f, 1.854336f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.000000f, -0.203200f, -0.979100f }	},
	{	{ -2.381298f, 0.008867f, 1.852498f },	{ 0.304897f, 0.993995f, 0.000000f },	{ -0.000000f, -0.203200f, -0.979100f }	},
	{	{ -2.304342f, 0.008867f, 1.852498f },	{ 0.352487f, 0.039877f, 0.000000f },	{ -0.000000f, -0.035600f, -0.999400f }	},
	{	{ -2.381298f, 0.008867f, 1.852498f },	{ 0.352487f, 0.328917f, 0.000000f },	{ -0.000000f, -0.035600f, -0.999400f }	},
	{	{ -2.381298f, 0.030241f, 1.851737f },	{ 0.342636f, 0.328917f, 0.000000f },	{ -0.000000f, -0.035600f, -0.999400f }	},
	{	{ -2.381298f, 0.000008f, 1.854336f },	{ 0.304897f, 0.984143f, 0.000000f },	{ -0.978800f, -0.205000f, -0.000000f }	},
	{	{ -2.381298f, 0.000008f, 2.018836f },	{ 0.304897f, 0.360630f, 0.000000f },	{ -0.978800f, -0.205000f, -0.000000f }	},
	{	{ -2.383153f, 0.008867f, 2.018836f },	{ 0.314749f, 0.360630f, 0.000000f },	{ -0.978800f, -0.205000f, -0.000000f }	},
	{	{ -2.383153f, 0.008867f, 1.854336f },	{ 0.814749f, 0.360630f, 0.000000f },	{ -0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.383153f, 0.008867f, 2.018836f },	{ 0.814749f, 0.984143f, 0.000000f },	{ -0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.383921f, 0.030241f, 2.018836f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.381298f, 0.030241f, 2.021435f },	{ 0.163390f, 0.039877f, 0.000000f },	{ -0.379800f, 0.000000f, 0.925100f }	},
	{	{ -2.381298f, 0.483009f, 2.021435f },	{ 0.015857f, 0.039877f, 0.000000f },	{ -0.379700f, -0.000000f, 0.925100f }	},
	{	{ -2.383153f, 0.483009f, 2.020674f },	{ 0.015857f, 0.030025f, 0.000000f },	{ -0.379700f, -0.000000f, 0.925100f }	},
	{	{ -2.383153f, 0.030241f, 2.020674f },	{ 0.804897f, 0.993995f, 0.000000f },	{ -0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.383153f, 0.483009f, 2.020674f },	{ 0.657364f, 0.993995f, 0.000000f },	{ -0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.383921f, 0.483009f, 2.018836f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.301719f, 0.483009f, 1.854336f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 0.922700f, 0.000000f, -0.385600f }	},
	{	{ -2.301719f, 0.030241f, 1.854336f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 0.922700f, 0.000000f, -0.385500f }	},
	{	{ -2.302487f, 0.030241f, 1.852498f },	{ 0.984143f, 0.993995f, 0.000000f },	{ 0.922700f, 0.000000f, -0.385500f }	},
	{	{ -2.302487f, 0.483009f, 1.852498f },	{ 0.195103f, 0.030025f, 0.000000f },	{ 0.379800f, -0.000000f, -0.925100f }	},
	{	{ -2.302487f, 0.030241f, 1.852498f },	{ 0.342636f, 0.030025f, 0.000000f },	{ 0.379800f, -0.000000f, -0.925100f }	},
	{	{ -2.304342f, 0.030241f, 1.851737f },	{ 0.342636f, 0.039877f, 0.000000f },	{ 0.379800f, -0.000000f, -0.925100f }	},
	{	{ -2.301719f, 0.030241f, 2.018836f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.301719f, 0.483009f, 2.018836f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.302487f, 0.483009f, 2.020674f },	{ 0.836610f, 0.350779f, 0.000000f },	{ 0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.302487f, 0.030241f, 2.020674f },	{ 0.163390f, 0.338769f, 0.000000f },	{ 0.379700f, 0.000000f, 0.925100f }	},
	{	{ -2.302487f, 0.483009f, 2.020674f },	{ 0.015857f, 0.338769f, 0.000000f },	{ 0.379800f, 0.000000f, 0.925100f }	},
	{	{ -2.304342f, 0.483009f, 2.021435f },	{ 0.015857f, 0.328917f, 0.000000f },	{ 0.379800f, 0.000000f, 0.925100f }	},
	{	{ -2.383921f, 0.030241f, 1.854336f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -0.922700f, 0.000000f, -0.385600f }	},
	{	{ -2.383921f, 0.483009f, 1.854336f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -0.922700f, 0.000000f, -0.385500f }	},
	{	{ -2.383153f, 0.483009f, 1.852498f },	{ 0.657364f, 0.350779f, 0.000000f },	{ -0.922700f, 0.000000f, -0.385500f }	},
	{	{ -2.383153f, 0.030241f, 1.852498f },	{ 0.342636f, 0.338769f, 0.000000f },	{ -0.379800f, 0.000000f, -0.925100f }	},
	{	{ -2.383153f, 0.483009f, 1.852498f },	{ 0.195103f, 0.338769f, 0.000000f },	{ -0.379800f, 0.000000f, -0.925100f }	},
	{	{ -2.381298f, 0.483009f, 1.851737f },	{ 0.195103f, 0.328917f, 0.000000f },	{ -0.379800f, 0.000000f, -0.925100f }	},
	{	{ -2.304342f, 0.513243f, 1.854336f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.304342f, 0.513243f, 2.018836f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.302487f, 0.504391f, 2.018836f },	{ 0.326759f, 0.984143f, 0.000000f },	{ 0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.302487f, 0.504391f, 1.854336f },	{ 0.826759f, 0.984143f, 0.000000f },	{ 0.999300f, 0.036400f, 0.000000f }	},
	{	{ -2.302487f, 0.504391f, 2.018836f },	{ 0.826759f, 0.360630f, 0.000000f },	{ 0.999300f, 0.036400f, 0.000000f }	},
	{	{ -2.301719f, 0.483009f, 2.018836f },	{ 0.836610f, 0.360630f, 0.000000f },	{ 0.999300f, 0.036400f, 0.000000f }	},
	{	{ -2.304342f, 0.513243f, 2.018836f },	{ 0.336610f, 0.984143f, 0.000000f },	{ 0.000000f, 0.202900f, 0.979200f }	},
	{	{ -2.381298f, 0.513243f, 2.018836f },	{ 0.625651f, 0.984143f, 0.000000f },	{ 0.000000f, 0.202900f, 0.979200f }	},
	{	{ -2.381298f, 0.504391f, 2.020674f },	{ 0.625651f, 0.993995f, 0.000000f },	{ 0.000000f, 0.202900f, 0.979200f }	},
	{	{ -2.304342f, 0.504391f, 2.020674f },	{ 0.006005f, 0.328917f, 0.000000f },	{ -0.000000f, 0.035900f, 0.999400f }	},
	{	{ -2.381298f, 0.504391f, 2.020674f },	{ 0.006005f, 0.039877f, 0.000000f },	{ -0.000000f, 0.035900f, 0.999400f }	},
	{	{ -2.381298f, 0.483009f, 2.021435f },	{ 0.015857f, 0.039877f, 0.000000f },	{ -0.000000f, 0.035900f, 0.999400f }	},
	{	{ -2.304342f, 0.000008f, 2.018836f },	{ 0.015857f, 0.360630f, 0.000000f },	{ 0.978800f, -0.205000f, -0.000000f }	},
	{	{ -2.304342f, 0.000008f, 1.854336f },	{ 0.015857f, 0.984143f, 0.000000f },	{ 0.978800f, -0.204900f, -0.000000f }	},
	{	{ -2.302487f, 0.008867f, 1.854336f },	{ 0.006005f, 0.984143f, 0.000000f },	{ 0.978800f, -0.204900f, -0.000000f }	},
	{	{ -2.302487f, 0.008867f, 2.018836f },	{ 0.993995f, 0.360630f, 0.000000f },	{ 0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.302487f, 0.008867f, 1.854336f },	{ 0.993995f, 0.984143f, 0.000000f },	{ 0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.301719f, 0.030241f, 1.854336f },	{ 0.984143f, 0.984143f, 0.000000f },	{ 0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.381298f, 0.513243f, 1.854336f },	{ 0.625651f, 0.360630f, 0.000000f },	{ 0.000000f, 0.202900f, -0.979200f }	},
	{	{ -2.304342f, 0.513243f, 1.854336f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.000000f, 0.202900f, -0.979200f }	},
	{	{ -2.304342f, 0.504391f, 1.852498f },	{ 0.336610f, 0.350779f, 0.000000f },	{ 0.000000f, 0.202900f, -0.979200f }	},
	{	{ -2.381298f, 0.504391f, 1.852498f },	{ 0.185251f, 0.328917f, 0.000000f },	{ 0.000000f, 0.035900f, -0.999400f }	},
	{	{ -2.304342f, 0.504391f, 1.852498f },	{ 0.185251f, 0.039877f, 0.000000f },	{ 0.000000f, 0.035900f, -0.999400f }	},
	{	{ -2.304342f, 0.483009f, 1.851737f },	{ 0.195103f, 0.039877f, 0.000000f },	{ 0.000000f, 0.035900f, -0.999400f }	},
	{	{ -2.381298f, 0.513243f, 2.018836f },	{ 0.625651f, 0.984143f, 0.000000f },	{ -0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.381298f, 0.513243f, 1.854336f },	{ 0.625651f, 0.360630f, 0.000000f },	{ -0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.383153f, 0.504391f, 1.854336f },	{ 0.635502f, 0.360630f, 0.000000f },	{ -0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.383153f, 0.504391f, 2.018836f },	{ 0.647512f, 0.984143f, 0.000000f },	{ -0.999300f, 0.036400f, -0.000000f }	},
	{	{ -2.383153f, 0.504391f, 1.854336f },	{ 0.647512f, 0.360630f, 0.000000f },	{ -0.999300f, 0.036400f, -0.000000f }	},
	{	{ -2.383921f, 0.483009f, 1.854336f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -0.999300f, 0.036400f, -0.000000f }	},
	{	{ -2.381298f, 0.000008f, 2.018836f },	{ 0.304897f, 0.360630f, 0.000000f },	{ -0.000000f, -0.203200f, 0.979100f }	},
	{	{ -2.304342f, 0.000008f, 2.018836f },	{ 0.015857f, 0.360630f, 0.000000f },	{ -0.000000f, -0.203200f, 0.979100f }	},
	{	{ -2.304342f, 0.008867f, 2.020674f },	{ 0.015857f, 0.350779f, 0.000000f },	{ -0.000000f, -0.203200f, 0.979100f }	},
	{	{ -2.381298f, 0.008867f, 2.020674f },	{ 0.173241f, 0.039877f, 0.000000f },	{ -0.000000f, -0.035600f, 0.999400f }	},
	{	{ -2.304342f, 0.008867f, 2.020674f },	{ 0.173241f, 0.328917f, 0.000000f },	{ -0.000000f, -0.035600f, 0.999400f }	},
	{	{ -2.304342f, 0.030241f, 2.021435f },	{ 0.163390f, 0.328917f, 0.000000f },	{ -0.000000f, -0.035600f, 0.999400f }	},
	{	{ -2.383921f, 0.483009f, 1.854336f },	{ 0.657364f, 0.360630f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.383921f, 0.030241f, 1.854336f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.383921f, 0.030241f, 2.018836f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.304342f, 0.000008f, 2.018836f },	{ 0.015857f, 0.360630f, 0.000000f },	{ -0.000000f, -1.000000f, -0.000000f }	},
	{	{ -2.381298f, 0.483009f, 1.851737f },	{ 0.195103f, 0.328917f, 0.000000f },	{ 0.000000f, 0.000000f, -1.000000f }	},
	{	{ -2.301719f, 0.483009f, 1.854336f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 1.000000f, 0.000000f, -0.000000f }	},
	{	{ -2.304342f, 0.513243f, 1.854336f },	{ 0.336610f, 0.360630f, 0.000000f },	{ 0.000000f, 1.000000f, -0.000000f }	},
	{	{ -2.304342f, 0.483009f, 2.021435f },	{ 0.015857f, 0.328917f, 0.000000f },	{ -0.000000f, 0.000000f, 1.000000f }	},
	{	{ -2.383153f, 0.504391f, 2.018836f },	{ 0.647512f, 0.984143f, 0.000000f },	{ -0.951700f, 0.034200f, 0.305200f }	},
	{	{ -2.381298f, 0.504391f, 2.020674f },	{ 0.625651f, 0.993995f, 0.000000f },	{ -0.597200f, 0.163100f, 0.785300f }	},
	{	{ -2.383153f, 0.483009f, 2.020674f },	{ 0.015857f, 0.030025f, 0.000000f },	{ -0.379400f, 0.025300f, 0.924900f }	},
	{	{ -2.383153f, 0.008867f, 2.018836f },	{ 0.314749f, 0.360630f, 0.000000f },	{ -0.780100f, -0.163400f, 0.604000f }	},
	{	{ -2.383153f, 0.030241f, 2.020674f },	{ 0.804897f, 0.993995f, 0.000000f },	{ -0.922400f, -0.025400f, 0.385500f }	},
	{	{ -2.381298f, 0.008867f, 2.020674f },	{ 0.173241f, 0.039877f, 0.000000f },	{ -0.300300f, -0.033900f, 0.953300f }	},
	{	{ -2.304342f, 0.504391f, 2.020674f },	{ 0.006005f, 0.328917f, 0.000000f },	{ 0.300400f, 0.033900f, 0.953200f }	},
	{	{ -2.302487f, 0.504391f, 2.018836f },	{ 0.326759f, 0.984143f, 0.000000f },	{ 0.779900f, 0.163400f, 0.604200f }	},
	{	{ -2.302487f, 0.483009f, 2.020674f },	{ 0.836610f, 0.350779f, 0.000000f },	{ 0.922400f, 0.025400f, 0.385500f }	},
	{	{ -2.302487f, 0.030241f, 2.020674f },	{ 0.163390f, 0.338769f, 0.000000f },	{ 0.379500f, -0.025300f, 0.924800f }	},
	{	{ -2.302487f, 0.008867f, 2.018836f },	{ 0.993995f, 0.360630f, 0.000000f },	{ 0.951600f, -0.033900f, 0.305400f }	},
	{	{ -2.304342f, 0.008867f, 2.020674f },	{ 0.015857f, 0.350779f, 0.000000f },	{ 0.597000f, -0.163000f, 0.785500f }	},
	{	{ -2.383153f, 0.483009f, 1.852498f },	{ 0.657364f, 0.350779f, 0.000000f },	{ -0.922400f, 0.025400f, -0.385400f }	},
	{	{ -2.381298f, 0.504391f, 1.852498f },	{ 0.185251f, 0.328917f, 0.000000f },	{ -0.300200f, 0.033900f, -0.953300f }	},
	{	{ -2.383153f, 0.504391f, 1.854336f },	{ 0.635502f, 0.360630f, 0.000000f },	{ -0.779800f, 0.163500f, -0.604300f }	},
	{	{ -2.383153f, 0.030241f, 1.852498f },	{ 0.342636f, 0.338769f, 0.000000f },	{ -0.379500f, -0.025300f, -0.924800f }	},
	{	{ -2.383153f, 0.008867f, 1.854336f },	{ 0.814749f, 0.360630f, 0.000000f },	{ -0.951600f, -0.033900f, -0.305500f }	},
	{	{ -2.381298f, 0.008867f, 1.852498f },	{ 0.304897f, 0.993995f, 0.000000f },	{ -0.597100f, -0.162900f, -0.785400f }	},
	{	{ -2.302487f, 0.483009f, 1.852498f },	{ 0.195103f, 0.030025f, 0.000000f },	{ 0.379400f, 0.025300f, -0.924900f }	},
	{	{ -2.302487f, 0.504391f, 1.854336f },	{ 0.826759f, 0.984143f, 0.000000f },	{ 0.951600f, 0.034200f, -0.305300f }	},
	{	{ -2.304342f, 0.504391f, 1.852498f },	{ 0.336610f, 0.350779f, 0.000000f },	{ 0.597400f, 0.163000f, -0.785200f }	},
	{	{ -2.302487f, 0.008867f, 1.854336f },	{ 0.006005f, 0.984143f, 0.000000f },	{ 0.780000f, -0.163300f, -0.604100f }	},
	{	{ -2.302487f, 0.030241f, 1.852498f },	{ 0.984143f, 0.993995f, 0.000000f },	{ 0.922400f, -0.025400f, -0.385400f }	},
	{	{ -2.304342f, 0.008867f, 1.852498f },	{ 0.352487f, 0.039877f, 0.000000f },	{ 0.300200f, -0.033900f, -0.953300f }	},
	{	{ -2.304342f, 0.008867f, 1.852498f },	{ 0.015857f, 0.993995f, 0.000000f },	{ -0.000000f, -0.203200f, -0.979100f }	},
	{	{ -2.304342f, 0.030241f, 1.851737f },	{ 0.342636f, 0.039877f, 0.000000f },	{ -0.000000f, -0.035600f, -0.999400f }	},
	{	{ -2.383153f, 0.008867f, 1.854336f },	{ 0.314749f, 0.984143f, 0.000000f },	{ -0.978800f, -0.205000f, -0.000000f }	},
	{	{ -2.383921f, 0.030241f, 1.854336f },	{ 0.804897f, 0.360630f, 0.000000f },	{ -0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.383153f, 0.030241f, 2.020674f },	{ 0.163390f, 0.030025f, 0.000000f },	{ -0.379800f, 0.000000f, 0.925100f }	},
	{	{ -2.383921f, 0.030241f, 2.018836f },	{ 0.804897f, 0.984143f, 0.000000f },	{ -0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.302487f, 0.483009f, 1.852498f },	{ 0.836610f, 0.993995f, 0.000000f },	{ 0.922700f, 0.000000f, -0.385600f }	},
	{	{ -2.304342f, 0.483009f, 1.851737f },	{ 0.195103f, 0.039877f, 0.000000f },	{ 0.379800f, -0.000000f, -0.925100f }	},
	{	{ -2.302487f, 0.030241f, 2.020674f },	{ 0.984143f, 0.350779f, 0.000000f },	{ 0.922700f, 0.000000f, 0.385500f }	},
	{	{ -2.304342f, 0.030241f, 2.021435f },	{ 0.163390f, 0.328917f, 0.000000f },	{ 0.379700f, 0.000000f, 0.925100f }	},
	{	{ -2.383153f, 0.030241f, 1.852498f },	{ 0.804897f, 0.350779f, 0.000000f },	{ -0.922700f, 0.000000f, -0.385600f }	},
	{	{ -2.381298f, 0.030241f, 1.851737f },	{ 0.342636f, 0.328917f, 0.000000f },	{ -0.379800f, 0.000000f, -0.925100f }	},
	{	{ -2.302487f, 0.504391f, 1.854336f },	{ 0.326759f, 0.360630f, 0.000000f },	{ 0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.301719f, 0.483009f, 1.854336f },	{ 0.836610f, 0.984143f, 0.000000f },	{ 0.999300f, 0.036300f, -0.000000f }	},
	{	{ -2.304342f, 0.504391f, 2.020674f },	{ 0.336610f, 0.993995f, 0.000000f },	{ 0.000000f, 0.202900f, 0.979200f }	},
	{	{ -2.304342f, 0.483009f, 2.021435f },	{ 0.015857f, 0.328917f, 0.000000f },	{ -0.000000f, 0.035900f, 0.999400f }	},
	{	{ -2.302487f, 0.008867f, 2.018836f },	{ 0.006005f, 0.360630f, 0.000000f },	{ 0.978800f, -0.205000f, -0.000000f }	},
	{	{ -2.301719f, 0.030241f, 2.018836f },	{ 0.984143f, 0.360630f, 0.000000f },	{ 0.999400f, -0.035900f, -0.000000f }	},
	{	{ -2.381298f, 0.504391f, 1.852498f },	{ 0.625651f, 0.350779f, 0.000000f },	{ 0.000000f, 0.202900f, -0.979200f }	},
	{	{ -2.381298f, 0.483009f, 1.851737f },	{ 0.195103f, 0.328917f, 0.000000f },	{ 0.000000f, 0.035900f, -0.999400f }	},
	{	{ -2.383153f, 0.504391f, 2.018836f },	{ 0.635502f, 0.984143f, 0.000000f },	{ -0.978800f, 0.204800f, -0.000000f }	},
	{	{ -2.383921f, 0.483009f, 2.018836f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -0.999300f, 0.036400f, -0.000000f }	},
	{	{ -2.381298f, 0.008867f, 2.020674f },	{ 0.304897f, 0.350779f, 0.000000f },	{ -0.000000f, -0.203200f, 0.979100f }	},
	{	{ -2.381298f, 0.030241f, 2.021435f },	{ 0.163390f, 0.039877f, 0.000000f },	{ -0.000000f, -0.035600f, 0.999400f }	},
	{	{ -2.383921f, 0.483009f, 2.018836f },	{ 0.657364f, 0.984143f, 0.000000f },	{ -1.000000f, 0.000000f, -0.000000f }	},
};
#define _Green_Brick_vertices_
#endif
#ifndef _Green_Brick_indices_
// Index Data follows: Sequential by mesh, Every Three Indices == One Triangle.
const unsigned int Green_Brick_indices[324] =
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
#define _Green_Brick_indices_
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
#ifndef _Green_Brick_materials_
// Material Data follows: pulled from a .mtl file of the same name if present.
const OBJ_MATERIAL Green_Brick_materials[1] =
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
#define _Green_Brick_materials_
#endif
/************************************************/
/*  This section contains the model's structure */
/************************************************/
#ifndef _Green_Brick_batches_
// Use this conveinence array to batch render all geometry by like material.
// Each entry corresponds to the same entry in the materials array above.
// The two numbers provided are the IndexCount and the IndexOffset into the indices array.
// If you need more fine grained control(ex: for transformations) use the OBJ_MESH data below.
const unsigned int Green_Brick_batches[1][2] =
{
	{ 324, 0 },
};
#define _Green_Brick_batches_
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
#ifndef _Green_Brick_meshes_
// Mesh Data follows: Meshes are .obj groups sorted & split by material.
// Meshes are provided in sequential order, sorted by material first and name second.
const OBJ_MESH Green_Brick_meshes[1] =
{
	{
		"default",
		324,
		0,
		0,
	},
};
#define _Green_Brick_meshes_
#endif
