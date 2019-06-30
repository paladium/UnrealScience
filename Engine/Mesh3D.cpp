#include "Mesh3D.h"
#include <fstream>
#include "Animation.h"

#pragma warning(disable: 4996)

///Custom Vertex

CustomVertex::CustomVertex(float _x, float _y, float _z, D3DCOLOR c)
{
	x = _x;
	y = _y;
	z = _z;


	color = c;
}

///////////////////////////

PositionNormal::PositionNormal(float _x, float _y, float _z, float _nx, float _ny, float _nz)
{
	x = _x;
	y = _y;
	z = _z;

	nx = _nx;
	ny = _ny;
	nz = _nz;
}

PositionNormal::PositionNormal()
{

}

PositionNormalTexture::PositionNormalTexture(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v)
{
	x = _x;
	y = _y;
	z = _z;

	nx = _nx;
	ny = _ny;
	nz = _nz;

	u = _u;
	v = _v;
}

PositionNormalTexture::PositionNormalTexture()
{

}

///////////////////////////


Mesh3D::Mesh3D()
{
	D3DXMatrixIdentity(&World);

	AnimationController = new Animation();

	Texture = NULL;
}

void Mesh3D::SetColor(D3DCOLOR c)
{
	Material.Ambient = (D3DXCOLOR)c;
	Material.Diffuse = (D3DXCOLOR)c;
	Material.Emissive = (D3DXCOLOR)D3DCOLOR_ARGB(255, 0, 0, 0);
	Material.Specular = (D3DXCOLOR)c;
	Material.Power = 1.0f;
}




void Mesh3D::Init(IDirect3DDevice9 &device)
{
	appDevice3D = &device;

	if (!appDevice3D)
		return;

	GetWorld();

	if (FAILED(D3DXCreateEffectFromFile(appDevice3D, "effect_2.fx", NULL, NULL, D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, NULL, &shader_effect, NULL)))
	{
		int a;
	}

	
}

void Mesh3D::GenerateMesh(std::vector<CustomVertex> vertices, int size)
{
	appDevice3D->CreateVertexBuffer(size * sizeof(CustomVertex), 0, CustomVertex::FVF,
		D3DPOOL_MANAGED, &VB, NULL);

	WORD* indices = new WORD[3 * size];

	triangle_number = size - 2;

	/*int k = 0;

	for (int i = 0; i < size; i++)
	{
	indices[k] = i;
	indices[k + 1] = i + 1;
	indices[k + 2] = i + 2;

	indices[k + 3] = indices[k + 2];
	indices[k + 4] = indices[k + 1];
	indices[k + 5] = i + 3;

	k += 6;
	i += 6;
	}*/

	appDevice3D->CreateIndexBuffer(3 * size * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);


	/*CustomVertex v[] = {
		CustomVertex(1, 1, 1, D3DCOLOR_ARGB(255, 0, 0, 255)),
		CustomVertex(1, 0, 1, D3DCOLOR_ARGB(255, 0, 0, 255)),
		CustomVertex(-1, 1, 1, D3DCOLOR_ARGB(255, 0, 0, 255)),
		};*/


	//copy vertex data
	VOID* pVerts;

	VB->Lock(0, sizeof(vertices), (void**)&pVerts, 0);

	memcpy(pVerts, &vertices[0], sizeof(CustomVertex)* vertices.size());


	/*VB->Lock(0, sizeof(verts), (void**)&pVerts, 0);

	memcpy(pVerts, v, sizeof(v));*/

	VB->Unlock();

	//copy index data
	/*VOID* pIndeces;
	IB->Lock(0, sizeof(indices), (void**)&pIndeces, 0);
	memcpy(pIndeces, indices, sizeof(indices));
	IB->Unlock();*/


}

void Mesh3D::Update(float time)
{
	/*Rotation.x += (rand() % 10) / 10000.0;
	Rotation.y += 0.001f;*/

	/*if (AnimationController->IsAnimationRunning())
	{
		AnimationController->Update(time);
	}*/

	GetWorld();
}

void Mesh3D::LoadTextureFromFile(char* path)
{
	if (strcmp(path, "") != 0)
	{
		D3DXCreateTextureFromFile(appDevice3D, path, &Texture);
	}
}

void Mesh3D::SetProjectionMatrix(D3DXMATRIX proj)
{
	projection = proj;
}

void Mesh3D::SetViewMatrix(D3DXMATRIX _view)
{
	view = _view;
}

void Mesh3D::Render()
{
	time += 0.1f;
	if (Texture != NULL)
	{
		appDevice3D->SetTexture(0, Texture);
		appDevice3D->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		appDevice3D->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		appDevice3D->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else
	{
		appDevice3D->SetTexture(0, NULL);
	}

	DWORD AlphaValue;
	AlphaValue = D3DCOLOR_ARGB(100, 255, 255, 255);

	appDevice3D->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	appDevice3D->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	appDevice3D->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	appDevice3D->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	appDevice3D->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	appDevice3D->SetTextureStageState(0, D3DTSS_CONSTANT, AlphaValue);
	appDevice3D->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);
	appDevice3D->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	appDevice3D->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	appDevice3D->SetMaterial(&Material);
	appDevice3D->SetTransform(D3DTS_WORLD, &World);
	appDevice3D->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	//appDevice3D->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	appDevice3D->SetSamplerState(D3DVERTEXTEXTURESAMPLER0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	appDevice3D->SetSamplerState(D3DVERTEXTEXTURESAMPLER0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	appDevice3D->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	appDevice3D->SetFVF(PositionNormalTexture::FVF);

	appDevice3D->SetStreamSource(0, VB, 0, sizeof(PositionNormalTexture));

	if (shader_effect != NULL)
	{
		UINT passes = 0;

		shader_effect->SetTechnique("Textured");

		

		shader_effect->Begin(&passes, 0);

		for (int pass = 0; pass < passes; pass++)
		{
			shader_effect->BeginPass(pass);

			shader_effect->SetMatrix("World", &World);
			shader_effect->SetMatrix("View", &view);
			shader_effect->SetMatrix("Projection", &projection);
			

			D3DXMATRIX invWorld;

			D3DXMatrixInverse(&invWorld, NULL, &World);
			D3DXMatrixTranspose(&invWorld, &invWorld);

			shader_effect->SetMatrix("WorldInverseTranspose", &invWorld);

			D3DXVECTOR3 viewVector;

			viewVector.x = view._13;
			viewVector.y = view._23;
			viewVector.z = view._33;

			shader_effect->SetValue("ViewVector", viewVector, sizeof(D3DXVECTOR3));

			if (Texture != nullptr)
			{
				shader_effect->SetTexture("ModelTexture", Texture);
			}

			//shader_effect->SetFloat("time", 0.5);

			if (isIndexed)
			{
				appDevice3D->SetIndices(IB);

				appDevice3D->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, actualVerticesNumber, 0, triangle_number);
			}
			else
			{
				appDevice3D->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangle_number);
			}

			shader_effect->EndPass();
		}

		shader_effect->End();
	}
	else
	{
		if (isIndexed)
		{
			appDevice3D->SetIndices(IB);

			appDevice3D->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, actualVerticesNumber, 0, triangle_number);
		}
		else
		{
			appDevice3D->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangle_number);
		}
	}
	
}

void Mesh3D::GetWorld()
{
	D3DXMATRIX Size, Rx, Ry, Rz, Translate;

	D3DXMatrixRotationX(&Rx, D3DXToRadian(Rotation.x));
	D3DXMatrixRotationY(&Ry, D3DXToRadian(Rotation.y));
	D3DXMatrixRotationZ(&Rz, D3DXToRadian(Rotation.z));

	D3DXMatrixScaling(&Size, Scale.x, Scale.y, Scale.z);

	D3DXMatrixTranslation(&Translate, Position.x, Position.y, Position.z);

	World = Size * Rx * Ry * Rz * Translate;
}

bool Mesh3D::LoadMesh(char* path)
{

	FILE * file = fopen(path, "r");

	if (file == NULL){

	}

	std::vector<int> vertexIndices, normalIndices, uvIndices;

	std::vector<D3DXVECTOR3> temp_vert, temp_norm;

	std::vector<D3DXVECTOR2> temp_uv;

	std::vector<int> faces;



	while (true)
	{
		char cmd[256];

		int res = fscanf(file, "%s", cmd);

		if (res == EOF)
			break;

		if (strcmp(cmd, "v") == 0)
		{
			D3DXVECTOR3 v;

			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);

			temp_vert.push_back(v);
		}
		else if (strcmp(cmd, "vn") == 0)
		{
			D3DXVECTOR3 v;

			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);

			temp_norm.push_back(v);
		}
		else if (strcmp(cmd, "vt") == 0)
		{
			D3DXVECTOR2 v;

			fscanf(file, "%f %f\n", &v.x, &v.y);

			temp_uv.push_back(v);
		}
		else if (strcmp(cmd, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			for (int i = 0; i < 3; i++)
			{
				vertexIndices.push_back(vertexIndex[i]);
				uvIndices.push_back(uvIndex[i]);
				normalIndices.push_back(normalIndex[i]);
			}

			triangle_number++;
		}
	}

	vertices.resize(vertexIndices.size());

	for (int i = 0; i < vertexIndices.size(); i++)
	{
		int vertexIndex = vertexIndices[i];

		D3DXVECTOR3 vertex = temp_vert[vertexIndex - 1];

		D3DXVECTOR3 normal = temp_norm[normalIndices[i] - 1];

		D3DXVECTOR2 uv = temp_uv[uvIndices[i] - 1];

		vertices[i] = PositionNormalTexture(vertex.x, vertex.y, vertex.z, normal.x, normal.y, normal.z, uv.x, uv.y);
	}



	return true;
}

bool Mesh3D::InitMesh(char* path)
{
	LoadMesh(path);

	int size = vertices.size();

	appDevice3D->CreateVertexBuffer(size * sizeof(PositionNormalTexture), 0, PositionNormalTexture::FVF,
		D3DPOOL_MANAGED, &VB, NULL);

	VOID* pVerts;

	VB->Lock(0, sizeof(vertices), (void**)&pVerts, 0);

	memcpy(pVerts, &vertices[0], sizeof(PositionNormalTexture)* vertices.size());

	VB->Unlock();

	return true;
}

void Mesh3D::UpdateWorldMatrix()
{
	GetWorld();
}

void Mesh3D::ChangeName(const char* to)
{
	Name = to;
}

const char* Mesh3D::GetName()
{
	return Name;
}

void Mesh3D::AddKey(Key *k)
{
	AnimationController->AnimationKeys.push_back(k);
}

void Mesh3D::InitAnimator()
{
	AnimationController->Initialize(*this);
}

void Mesh3D::StartAnimation()
{
	AnimationController->StartAnimation();
}

void Mesh3D::SetEndlessProperty(int value)
{
	AnimationController->SetEndlessProperty(value);
}

void Mesh3D::ResetAnimator()
{
	AnimationController->Reset();
}

void Mesh3D::NextKey()
{
	AnimationController->NextKey();
}

void Mesh3D::PrevKey()
{
	AnimationController->PrevKey();
}