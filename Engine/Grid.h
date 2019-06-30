#include <d3dx9.h>
#include <d3d9.h>
#include "Mesh3D.h"

class Grid
{

public:

	Grid(IDirect3DDevice9 &device, int _width = 32, int _height = 32);

	void Render();

	void Initialize();

	D3DXVECTOR3 Position;

	D3DXVECTOR3 Scale = D3DXVECTOR3(1, 1, 1);

	D3DXVECTOR3 Rotation;

	void GetWorld();

	D3DXCOLOR MainColor;
private:

	std::vector<CustomVertex> vertices;


	IDirect3DDevice9* appDevice3D;
	D3DXMATRIX World;

	IDirect3DVertexBuffer9* VB;

	int width, height;
	
	int step = 1;

	D3DXCOLOR SmallColor = D3DCOLOR_ARGB(255, 0, 255, 0);
};