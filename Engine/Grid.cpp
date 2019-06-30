#include "Grid.h"

Grid::Grid(IDirect3DDevice9 &device, int _width, int _height)
{
	appDevice3D = &device;

	width = _width;

	height = _height;
}

void Grid::Initialize()
{
	for (int i = 0; i < width; i += step)
	{
		vertices.push_back(CustomVertex(i, 0, 0, MainColor));

		vertices.push_back(CustomVertex(i, 0, height - 1, MainColor));
	}
	
	for (int j = 0; j < height; j += step)
	{
		vertices.push_back(CustomVertex(0, 0, j, MainColor));

		vertices.push_back(CustomVertex(width - 1, 0, j, MainColor));
	}

	int size = vertices.size();

	HRESULT r = appDevice3D->CreateVertexBuffer(size * sizeof(CustomVertex), 0, CustomVertex::FVF,
		D3DPOOL_MANAGED, &VB, NULL);

	VOID* pVerts;

	r = VB->Lock(0, sizeof(vertices), (void**)&pVerts, 0);

	memcpy(pVerts, &vertices[0], sizeof(CustomVertex) * size);

	VB->Unlock();
}


void Grid::Render()
{
	GetWorld();

	appDevice3D->SetTexture(0, NULL);

	appDevice3D->SetTransform(D3DTS_WORLD, &World);

	appDevice3D->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	appDevice3D->SetFVF(CustomVertex::FVF);

	appDevice3D->SetStreamSource(0, VB, 0, sizeof(CustomVertex));

	appDevice3D->DrawPrimitive(D3DPT_LINELIST, 0, vertices.size() / 2);
}

void Grid::GetWorld()
{
	D3DXMATRIX Size, Rx, Ry, Rz, Translate;

	D3DXMatrixRotationX(&Rx, D3DXToRadian(Rotation.x));
	D3DXMatrixRotationY(&Ry, D3DXToRadian(Rotation.y));
	D3DXMatrixRotationZ(&Rz, D3DXToRadian(Rotation.z));

	D3DXMatrixScaling(&Size, Scale.x, Scale.y, Scale.z);

	D3DXMatrixTranslation(&Translate, Position.x, Position.y, Position.z);

	World = Size * Rx * Ry * Rz * Translate;
}