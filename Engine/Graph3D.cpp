#include "Graph3D.h"

Graph3D::Graph3D(IDirect3DDevice9 &device)
{
	appDevice3D = &device;
}

void Graph3D::AddVertex(float x, float y, float z, int r, int g, int b)
{
	CustomVertex v;
	v.x = x;
	v.y = y;
	v.z = z;

	v.color = D3DCOLOR_ARGB(255, r, g, b);

	data.push_back(v);
}

void Graph3D::Initialize()
{
	int size = data.size();

	//VB = new IDirect3DVertexBuffer9();

	HRESULT r = appDevice3D->CreateVertexBuffer(size * sizeof(CustomVertex), 0, CustomVertex::FVF,
		D3DPOOL_MANAGED, &VB, NULL);

	

	VOID* pVerts;

	r = VB->Lock(0, sizeof(data), (void**)&pVerts, 0);

	memcpy(pVerts, &data[0], sizeof(CustomVertex) * size);

	VB->Unlock();

	isInitialized = true;
}

void Graph3D::Render()
{
	GetWorld();

	appDevice3D->SetTexture(0, NULL);

	appDevice3D->SetTransform(D3DTS_WORLD, &World);

	appDevice3D->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	appDevice3D->SetFVF(CustomVertex::FVF);

	appDevice3D->SetStreamSource(0, VB, 0, sizeof(CustomVertex));

	if (type == 1)
	{
		appDevice3D->DrawPrimitive(D3DPT_POINTLIST, 0, data.size());
	}
	else if (type == 2)
	{
		appDevice3D->DrawPrimitive(D3DPT_LINELIST, 0, data.size() / 2);
	}

	//

	
}

void Graph3D::GetWorld()
{
	D3DXMATRIX Size, Rx, Ry, Rz, Translate;

	D3DXMatrixRotationX(&Rx, D3DXToRadian(Rotation.x));
	D3DXMatrixRotationY(&Ry, D3DXToRadian(Rotation.y));
	D3DXMatrixRotationZ(&Rz, D3DXToRadian(Rotation.z));

	D3DXMatrixScaling(&Size, Scale.x, Scale.y, Scale.z);

	D3DXMatrixTranslation(&Translate, Position.x, Position.y, Position.z);

	World = Size * Rx * Ry * Rz * Translate;
}

void Graph3D::Clear()
{
	data.clear();

	if (VB != nullptr)
		VB->Release();

	VB = nullptr;

	isInitialized = false;
}