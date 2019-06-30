#include "d3dUtil.h"

using namespace d3dUtil;

class Cube3D{

public:

	D3DXVECTOR3 Scale = D3DXVECTOR3(1, 1, 1);
	D3DXVECTOR3 Position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0, 0, 0);

	D3DXVECTOR2 TextureRepeat = D3DXVECTOR2(1, 1);

	char* texPath;

	Cube3D();
	~Cube3D(){ if (VB != NULL) VB->Release(); if (IB != NULL) IB->Release(); if (Texture != NULL) Texture->Release(); }

	void Init(IDirect3DDevice9 &device);
	void Render();
	void Update(float time);

	bool IsDeviceCreated()
	{
		return (appDevice3D != nullptr);
	}

	void UpdateWorldMatrix();

	void LoadTexture();

	void LoadTextureFromFile(char* path);

protected:
	IDirect3DDevice9* appDevice3D;
	D3DXMATRIX World;

	IDirect3DVertexBuffer9* VB;
	IDirect3DIndexBuffer9* IB;

	IDirect3DTexture9* Texture;

	D3DMATERIAL9 Material;


	void GetWorld();

};
