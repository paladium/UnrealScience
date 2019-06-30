#include "ColoredBox.h"


ColoredBox::ColoredBox()
{
	D3DXMatrixIdentity(&World);

	Material.Ambient = (D3DXCOLOR)d3dUtil::White;
	Material.Diffuse = (D3DXCOLOR)d3dUtil::White;
	Material.Emissive = (D3DXCOLOR)d3dUtil::Green;
	Material.Specular = (D3DXCOLOR)d3dUtil::White;
	Material.Power = 5.0f;
}

void ColoredBox::Init(IDirect3DDevice9 &device)
{


	appDevice3D = &device;

	if (!appDevice3D)
		return;

	VertexPositionColor verts[] =
	{
		VertexPositionColor(-1, 1, -1, Red),
		VertexPositionColor(1, 1, -1, Green),
		VertexPositionColor(-1, -1, -1, Yellow),
		VertexPositionColor(1, -1, -1, Blue),
		VertexPositionColor(-1, 1, 1, Red),
		VertexPositionColor(1, 1, 1, Green),
		VertexPositionColor(-1, -1, 1, Yellow),
		VertexPositionColor(1, -1, 1, Blue)
	};

	//VertexPositionNormalTexture verts[] =
	//{

	//	//Front face
	//	VertexPositionNormalTexture(-1, 1, -1, 0, 0, -1, 0, 0),
	//	VertexPositionNormalTexture(1, 1, -1, 0, 0, -1, 1 * TextureRepeat.x, 0),
	//	VertexPositionNormalTexture(-1, -1, -1, 0, 0, -1, 0, 1 * TextureRepeat.y),
	//	VertexPositionNormalTexture(1, -1, -1, 0, 0, -1, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

	//	//Back face

	//	VertexPositionNormalTexture(1, 1, 1, 0, 0, 1, 0, 0),
	//	VertexPositionNormalTexture(-1, 1, 1, 0, 0, 1, 1 * TextureRepeat.x, 0),
	//	VertexPositionNormalTexture(1, -1, 1, 0, 0, 1, 0, 1 * TextureRepeat.y),
	//	VertexPositionNormalTexture(-1, -1, 1, 0, 0, 1, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

	//	//Left face

	//	VertexPositionNormalTexture(-1, 1, 1, -1, 0, 0, 0, 0),
	//	VertexPositionNormalTexture(-1, 1, -1, -1, 0, 0, 1 * TextureRepeat.x, 0),
	//	VertexPositionNormalTexture(-1, -1, 1, -1, 0, 0, 0, 1 * TextureRepeat.y),
	//	VertexPositionNormalTexture(-1, -1, -1, -1, 0, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

	//	//Right face
	//	VertexPositionNormalTexture(1, 1, -1, 1, 0, 0, 0, 0),
	//	VertexPositionNormalTexture(1, 1, 1, 1, 0, 0, 1 * TextureRepeat.x, 0),
	//	VertexPositionNormalTexture(1, -1, -1, 1, 0, 0, 0, 1 * TextureRepeat.y),
	//	VertexPositionNormalTexture(1, -1, 1, 1, 0, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

	//	//Top face
	//	VertexPositionNormalTexture(-1, 1, 1, 0, 1, 0, 0, 0),
	//	VertexPositionNormalTexture(1, 1, 1, 0, 1, 0, 1 * TextureRepeat.x, 0),
	//	VertexPositionNormalTexture(-1, 1, -1, 0, 1, 0, 0, 1 * TextureRepeat.y),
	//	VertexPositionNormalTexture(1, 1, -1, 0, 1, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

	//	//Bottom face
	//	VertexPositionNormalTexture(1, -1, 1, 0, -1, 0, 0, 0),
	//	VertexPositionNormalTexture(-1, -1, 1, 0, -1, 0, 1 * TextureRepeat.x, 0),
	//	VertexPositionNormalTexture(1, -1, -1, 0, -1, 0, 0, 1 * TextureRepeat.x),
	//	VertexPositionNormalTexture(-1, -1, -1, 0, -1, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),
	//};


	//WORD indices[36] =
	//{
	//	0, 1, 2,    // side 1
	//	2, 1, 3,
	//	4, 0, 6,    // side 2
	//	6, 0, 2,
	//	7, 5, 6,    // side 3
	//	6, 5, 4,
	//	3, 1, 7,    // side 4
	//	7, 1, 5,
	//	4, 5, 0,    // side 5
	//	0, 5, 1,
	//	3, 7, 2,    // side 6
	//	2, 7, 6,
	//};

	WORD indices[36] =
	{
		0, 1, 2,
		2, 1, 3,

		4, 5, 6,
		6, 5, 7,

		8, 9, 10,
		10, 9, 11,

		12, 13, 14,
		14, 13, 15,

		16, 17, 18,
		18, 17, 19,

		20, 21, 22,
		22, 21, 23
	};

	int size = sizeof(verts) / sizeof(*verts);

	appDevice3D->CreateVertexBuffer(size * sizeof(VertexPositionColor), 0, VertexPositionColor::FVF,
		D3DPOOL_MANAGED, &VB, NULL);

	appDevice3D->CreateIndexBuffer((sizeof(indices) / sizeof(*indices)) * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	//copy vertex data
	VOID* pVerts;

	VB->Lock(0, sizeof(verts), (void**)&pVerts, 0);

	memcpy(pVerts, verts, sizeof(verts));

	VB->Unlock();

	//copy index data
	VOID* pIndeces;
	IB->Lock(0, sizeof(indices), (void**)&pIndeces, 0);
	memcpy(pIndeces, indices, sizeof(indices));
	IB->Unlock();

	GetWorld();
}

void ColoredBox::Update(float time)
{
	//Rotation.x += (rand() % 10) / 10000.0;
	//Rotation.y += 0.001f;

	GetWorld();
}

void ColoredBox::Render()
{
	appDevice3D->SetMaterial(&Material);
	appDevice3D->SetTransform(D3DTS_WORLD, &World);
	appDevice3D->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	appDevice3D->SetStreamSource(0, VB, 0, sizeof(VertexPositionColor));
	appDevice3D->SetIndices(IB);
	appDevice3D->SetFVF(VertexPositionColor::FVF);
	appDevice3D->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 36, 0, 12);
}

void ColoredBox::GetWorld()
{
	D3DXMATRIX Size, Rx, Ry, Rz, Translate;

	D3DXMatrixRotationX(&Rx, Rotation.x);
	D3DXMatrixRotationY(&Ry, Rotation.y);
	D3DXMatrixRotationZ(&Rz, Rotation.z);

	D3DXMatrixScaling(&Size, Scale.x, Scale.y, Scale.z);

	D3DXMatrixTranslation(&Translate, Position.x, Position.y, Position.z);

	World = Size * Rx * Ry * Rz * Translate;
}

void ColoredBox::UpdateWorldMatrix()
{
	GetWorld();
}