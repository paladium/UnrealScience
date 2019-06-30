#include <d3d9.h>
#include <d3dx9.h>
#include <string>


#define D3DFVF_COLOREDVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct COLORED_VERTEX
{

	float x, y, z;  //Position

	DWORD color;    //Color
};


class Effect{

private:

	LPD3DXEFFECT g_lpEffect = NULL;

	LPDIRECT3DVERTEXBUFFER9 g_lpVertexBuffer = NULL;

	D3DXMATRIX g_ShaderMatrix;

	IDirect3DDevice9* appDevice3D;

public:

	std::string path;

	Effect(IDirect3DDevice9 &device);

	~Effect();


	void Render();

	bool Initialize();

};

