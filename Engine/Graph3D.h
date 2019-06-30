#include <d3dx9.h>
#include <d3d9.h>
#include "Mesh3D.h"

class Graph3D
{

public:

	Graph3D(IDirect3DDevice9 &device);
	
	void AddVertex(float x, float y, float z, int r, int g, int b);

	void Render();

	void Initialize();

	D3DXVECTOR3 Position;

	D3DXVECTOR3 Scale = D3DXVECTOR3(1, 1, 1);

	D3DXVECTOR3 Rotation;

	void GetWorld();

	int type;

	bool isInitialized = false;

	void Clear();

private:

	std::vector<CustomVertex> data;


	IDirect3DDevice9* appDevice3D;
	D3DXMATRIX World;

	IDirect3DVertexBuffer9* VB;
};