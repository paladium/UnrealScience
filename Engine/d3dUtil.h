#include <d3d9.h>
#include <d3dx9.h>
#include "stdafx.h"

namespace d3dUtil
{
	const D3DCOLOR Red = D3DCOLOR_ARGB(255, 255, 0, 0);
	
	const D3DCOLOR Blue = D3DCOLOR_ARGB(255, 0, 0, 255);

	const D3DCOLOR Green = D3DCOLOR_ARGB(255, 0, 255, 0);

	const D3DCOLOR Background = D3DCOLOR_ARGB(255, 20, 20, 20);

	const D3DCOLOR Yellow = D3DCOLOR_ARGB(255, 241, 196, 15);

	const D3DCOLOR White = D3DCOLOR_ARGB(255, 255, 255, 255);

	const D3DCOLOR Black = D3DCOLOR_ARGB(255, 0, 0, 0);

	struct VertexPositionColor
	{
		float x, y, z;

		D3DCOLOR color;

		VertexPositionColor(float _x, float _y, float _z, D3DCOLOR c);
		VertexPositionColor();

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};

	

	struct VertexPositionTexture
	{
		float x, y, z;

		float u, v;

		VertexPositionTexture(float _x, float _y, float _z, float _u, float _v);
		VertexPositionTexture();

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};

	struct VertexPositionNormalTexture
	{
		float x, y, z;

		float nx, ny, nz;

		float u, v;

		//D3DCOLOR color = Green;

		VertexPositionNormalTexture(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v);

		VertexPositionNormalTexture();

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	};


	#define VK_0 0x0030
	#define VK_1 0x0031
	#define VK_2 0x0032
	#define VK_3 0x0033
	#define VK_4 0x0034
	#define VK_5 0x0035
	#define VK_6 0x0036
	#define VK_7 0x0037
	#define VK_8 0x0038
	#define VK_9 0x0039

	#define VK_A 0x0041
	#define VK_B 0x0042
	#define VK_C 0x0043
	#define VK_D 0x0044
	#define VK_E 0x0045
	#define VK_F 0x0046
	#define VK_G 0x0047
	#define VK_H 0x0048
	#define VK_I 0x0049
	#define VK_J 0x004A
	#define VK_K 0x004B
	#define VK_L 0x004C
	#define VK_M 0x004D
	#define VK_N 0x004E
	#define VK_O 0x004F
	#define VK_P 0x0050
	#define VK_Q 0x0051
	#define VK_R 0x0052
	#define VK_S 0x0053
	#define VK_T 0x0054
	#define VK_U 0x0055
	#define VK_V 0x0056
	#define VK_W 0x0057
	#define VK_X 0x0058
	#define VK_Y 0x0059
	#define VK_Z 0x005A
}