#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class Animation;
struct Key;

struct CustomVertex{

	float x, y, z;

	D3DCOLOR color;

	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	CustomVertex(float _x, float _y, float _z, D3DCOLOR _color);

	CustomVertex(){}

};

struct PositionNormal
{
	float x, y, z;

	float nx, ny, nz;

	//D3DCOLOR color = Green;

	PositionNormal(float _x, float _y, float _z, float _nx, float _ny, float _nz);

	PositionNormal();

	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
};


struct PositionNormalTexture
{
	float x, y, z;

	float nx, ny, nz;

	float u, v;

	//D3DCOLOR color = Green;

	PositionNormalTexture(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v);

	PositionNormalTexture();

	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
};

class Mesh3D{

public:

	Mesh3D();
	~Mesh3D(){ if (VB != NULL) VB->Release(); if (IB != NULL) IB->Release(); if (Texture != NULL) Texture->Release(); if (AnimationController != NULL) delete AnimationController; }

	D3DXVECTOR3 Scale = D3DXVECTOR3(1, 1, 1);
	D3DXVECTOR3 Position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0, 0, 0);

	D3DXVECTOR2 TextureRepeat = D3DXVECTOR2(1, 1);

	void Init(IDirect3DDevice9 &device);
	void Render();
	void Update(float time);

	bool IsDeviceCreated()
	{
		return (appDevice3D != nullptr);
	}

	void UpdateWorldMatrix();

	void GenerateMesh(std::vector<CustomVertex>, int size);

	void SetColor(D3DCOLOR);

	bool LoadMesh(char* path);

	bool InitMesh(char* path);

	void LoadTextureFromFile(char* path);

	void ChangeName(const char* to);

	const char* GetName();

	void AddKey(Key *t);

	void InitAnimator();

	void StartAnimation();

	void SetEndlessProperty(int value);

	void ResetAnimator();

	void NextKey();

	void PrevKey();

	Animation* AnimationController;

	void SetProjectionMatrix(D3DXMATRIX proj);
	
	void SetViewMatrix(D3DXMATRIX _view);

protected:
	IDirect3DDevice9* appDevice3D;
	D3DXMATRIX World;

	IDirect3DVertexBuffer9* VB;
	IDirect3DIndexBuffer9* IB;

	D3DMATERIAL9 Material;

	int triangle_number = 0;

	int actualVerticesNumber;

	int facesNum = 0;

	WORD* indices;

	std::vector<PositionNormalTexture> vertices;

	IDirect3DTexture9* Texture;

	void GetWorld();

	bool isIndexed = false;

	const char* Name = "entity";

	LPD3DXEFFECT shader_effect = NULL;

	D3DXMATRIX projection;

	D3DXMATRIX view;

	float time;
};