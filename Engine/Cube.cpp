#include "Cube.h"

Cube::Cube()
{
	//Initialize();

	isIndexed = true;

	actualVerticesNumber = 36;

	triangle_number = 12;
}

void Cube::Initialize()
{
	PositionNormalTexture verts[] =
	{

		//Front face
		PositionNormalTexture(-1, 1, -1, 0, 0, -1, 0, 0),
		PositionNormalTexture(1, 1, -1, 0, 0, -1, 1 * TextureRepeat.x, 0),
		PositionNormalTexture(-1, -1, -1, 0, 0, -1, 0, 1 * TextureRepeat.y),
		PositionNormalTexture(1, -1, -1, 0, 0, -1, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

		//Back face

		PositionNormalTexture(1, 1, 1, 0, 0, 1, 0, 0),
		PositionNormalTexture(-1, 1, 1, 0, 0, 1, 1 * TextureRepeat.x, 0),
		PositionNormalTexture(1, -1, 1, 0, 0, 1, 0, 1 * TextureRepeat.y),
		PositionNormalTexture(-1, -1, 1, 0, 0, 1, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

		//Left face

		PositionNormalTexture(-1, 1, 1, -1, 0, 0, 0, 0),
		PositionNormalTexture(-1, 1, -1, -1, 0, 0, 1 * TextureRepeat.x, 0),
		PositionNormalTexture(-1, -1, 1, -1, 0, 0, 0, 1 * TextureRepeat.y),
		PositionNormalTexture(-1, -1, -1, -1, 0, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

		//Right face
		PositionNormalTexture(1, 1, -1, 1, 0, 0, 0, 0),
		PositionNormalTexture(1, 1, 1, 1, 0, 0, 1 * TextureRepeat.x, 0),
		PositionNormalTexture(1, -1, -1, 1, 0, 0, 0, 1 * TextureRepeat.y),
		PositionNormalTexture(1, -1, 1, 1, 0, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

		//Top face
		PositionNormalTexture(-1, 1, 1, 0, 1, 0, 0, 0),
		PositionNormalTexture(1, 1, 1, 0, 1, 0, 1 * TextureRepeat.x, 0),
		PositionNormalTexture(-1, 1, -1, 0, 1, 0, 0, 1 * TextureRepeat.y),
		PositionNormalTexture(1, 1, -1, 0, 1, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),

		//Bottom face
		PositionNormalTexture(1, -1, 1, 0, -1, 0, 0, 0),
		PositionNormalTexture(-1, -1, 1, 0, -1, 0, 1 * TextureRepeat.x, 0),
		PositionNormalTexture(1, -1, -1, 0, -1, 0, 0, 1 * TextureRepeat.x),
		PositionNormalTexture(-1, -1, -1, 0, -1, 0, 1 * TextureRepeat.x, 1 * TextureRepeat.y),
	};


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

	appDevice3D->CreateVertexBuffer(size * sizeof(PositionNormalTexture), 0, PositionNormalTexture::FVF,
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
}