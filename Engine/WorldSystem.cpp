#include "WorldSystem.h"

WorldSystem::WorldSystem(IDirect3DDevice9 &device)
{
	appDevice3D = &device;
}

bool WorldSystem::CheckIndex()
{
	if (World.size() > 0)
		return selected <= World.size() - 1 && selected >= 0;
	else
		return false;
}

void WorldSystem::Render()
{
	for (int i = 0; i < World.size(); i++)
	{
		if (World[i]->IsDeviceCreated())
			World[i]->Render();
	}
}

void WorldSystem::Cleanup()
{
	for (int i = 0; i < World.size(); i++)
	{
		World[i]->~Mesh3D();
	}
	World.clear();
}

void WorldSystem::Update(D3DXMATRIX projection, D3DXMATRIX view)
{
	for (int i = 0; i < World.size(); i++)
	{
		World[i]->Update(0.01f);
		World[i]->SetProjectionMatrix(projection);
		World[i]->SetViewMatrix(view);
	}
}

void WorldSystem::CreateCube()
{
	Cube *c = new Cube();

	c->Init(*appDevice3D);

	c->Initialize();

	c->SetColor(d3dUtil::White);

	c->Update(0);

	World.push_back(c);

	selected = World.size() - 1;
}

void WorldSystem::MoveObject(float x, float y, float z)
{
	if (CheckIndex())
	{
		World[selected]->Position = D3DXVECTOR3(x, y, z);

		World[selected]->UpdateWorldMatrix();
	}

}

void WorldSystem::Rotate(float x, float y, float z)
{
	if (CheckIndex())
	{
		World[selected]->Rotation = D3DXVECTOR3(x, y, z);

		World[selected]->UpdateWorldMatrix();
	}
}

void WorldSystem::ResizeObject(float x, float y, float z)
{
	if (CheckIndex())
	{
		World[selected]->Scale = D3DXVECTOR3(x, y, z);

		World[selected]->TextureRepeat.x = 2 * x;
		World[selected]->TextureRepeat.y = 2 * z;

		World[selected]->UpdateWorldMatrix();
	}
}

void WorldSystem::DeleteObject()
{
	if (CheckIndex())
	{
		World[selected]->~Mesh3D();

		World.erase(World.begin() + selected);

		if (World.size() != 0)
		{
			selected = World.size() - 1;
		}
	}
}

void WorldSystem::SetTexture(char* t)
{
	if (CheckIndex())
	{
		if (t != nullptr)
		{
			World[selected]->LoadTextureFromFile(t);
		}
	}
}

void WorldSystem::Translate(float x, float y, float z)
{
	if (CheckIndex())
	{
		World[selected]->Position.x += x;
		World[selected]->Position.y += y;
		World[selected]->Position.z += z;

		World[selected]->UpdateWorldMatrix();
	}
}

void WorldSystem::IncreaseDecrease(float x, float y, float z)
{
	World[selected]->Scale.x += x;
	World[selected]->Scale.y += y;
	World[selected]->Scale.z += z;

	World[selected]->UpdateWorldMatrix();
}

void WorldSystem::Clone()
{
	if (CheckIndex())
	{
		//World.push_back(World[selected]);

		Mesh3D *mesh = World[selected];

		World.push_back(new Mesh3D(*mesh));

		selected = World.size() - 1;

		//std::string s = World[selected]->GetName();

		//s += "copy";

		//ChangeName(s.c_str());
	}
}

void WorldSystem::ChangeName(const char* to)
{
	if (CheckIndex())
	{
		World[selected]->ChangeName(to);
	}
}

void WorldSystem::CreateFromModel(char* path)
{
	Mesh3D* m = new Mesh3D();

	//m->Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	m->SetColor(D3DCOLOR_ARGB(50, 255, 255, 255));

	//m->SetColor(White);

	m->Init(*appDevice3D);

	m->InitMesh(path);

	//m->LoadTextureFromFile("test.png");

	m->Update(0);

	World.push_back(m);

	selected = World.size() - 1;
}

void WorldSystem::ChangeColor(int r, int g, int b)
{
	if (CheckIndex())
	{
		World[selected]->SetColor(D3DCOLOR_ARGB(255, r, g, b));
	}
}


///////////////

int WorldSystem::EntityNumber()
{
	return World.size();
}

float* WorldSystem::GetPosition(int index)
{
	float *a = new float[3];

	a[0] = World[index]->Position.x;
	a[1] = World[index]->Position.y;
	a[2] = World[index]->Position.z;

	return a;
}