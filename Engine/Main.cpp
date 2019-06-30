#include "stdafx.h"
#include "EditorApp.h"
#include "Main.h"

#include <strsafe.h>
#pragma warning( default : 4996 )

EditorApp *Editor;

#pragma region basic_initialization 
void InitD3D(HWND hWnd, int width, int height)
{
	Editor = new EditorApp();

	Editor->SetEverything(hWnd, width, height);

	Editor->Init();
}

void InitWorld()
{
	Editor->InitWorld();
}

void Render()
{
	Editor->Render();
}

void Cleanup()
{
	Editor->~EditorApp();
}

void Update()
{
	Editor->GlobalUpdate();
}


void TestUpdate(int command, float mouse_x, float mouse_y)
{
	Editor->TestUpdate(command, mouse_x, mouse_y);
}

void ChangeCameraSpeed(float to)
{
	if (Editor)
		Editor->ChangeCameraSpeed(to);
}

#pragma endregion basic_initialization


///////////Console functions
#pragma region Console

void CreateObject(int type)
{

	if (type != 0)
	{
		if (type == 1)
		{
			Editor->worldSystem->CreateCube();
		}
	}

	
}



void MoveObject(float x, float y, float z)
{
	Editor->worldSystem->MoveObject(x, y, z);
}

void Rotate(float x, float y, float z)
{
	Editor->worldSystem->Rotate(x, y, z);
}

void ResizeObject(float x, float y, float z)
{
	Editor->worldSystem->ResizeObject(x, y, z);
}

void SelectObject1(int index)
{
	Editor->worldSystem->SetSelected(index);
}

void DeleteEntity()
{
	Editor->worldSystem->DeleteObject();
}

void ResizeViewport(float to)
{
	Editor->ResizeViewport(to);
}

void SetTexture(char* t)
{
	Editor->worldSystem->SetTexture(t);
}

void Translate(float x, float y, float z)
{
	Editor->worldSystem->Translate(x, y, z);
}

void IncreaseDecrease(float x, float y, float z)
{
	Editor->worldSystem->IncreaseDecrease(x, y, z);
}

void Clone()
{
	Editor->worldSystem->Clone();
	
}

void ChangeName(const char* to)
{
	Editor->worldSystem->ChangeName(to);
}

void StartAnimation()
{
	/*if (isPlaying)
	{
		for (int i = 0; i < World.size(); i++)
		{
			World[i]->InitAnimator();
		}

		for (int i = 0; i < World.size(); i++)
		{
			GlobalAnimationManager->GetKeysFromAnimation(World[i]->AnimationController);
		}

		GlobalAnimationManager->Initialize();
	}*/
}

void CreateFromModel(char* path)
{

	Editor->worldSystem->CreateFromModel(path);
}

void ChangeColor(int r, int g, int b)
{
	Editor->worldSystem->ChangeColor(r, g, b);
}

void Next()
{
	//GlobalAnimationManager->NextOrder();
}

void Prev()
{
	//World[selected]->PrevKey();
}

#pragma endregion Console


#pragma region AnimationLanguage


void AddKey(int type, int start, float duration, float x, float y, float z)
{
	Key *k = new Key();

	k->duration = duration;

	k->startOrder = start;

	if (type == 1)
	{
		k->Destination.Position = D3DXVECTOR3(x, y, z);
		k->setPosition = true;
	}
	else if (type == 2)
	{
		k->Destination.Rotation = D3DXVECTOR3(x, y, z);
		k->setRotation = true;
	}
	else if (type == 3)
	{
		k->Destination.Scale = D3DXVECTOR3(x, y, z);
		k->setScale = true;
	}

	
	/*if (k->setPosition || k->setRotation || k->setScale)
		World[selected]->AddKey(k);*/
}

void Reset()
{
	//World[selected]->ResetAnimator();
}

void SetProperty(int _property, int value)
{
	/*if (_property != 0)
	{
		if (_property == 1)
		{
			World[selected]->SetEndlessProperty(value);
		}
	}*/
}

#pragma endregion AnimationLanguage
//////////////////////////////////

#pragma region objects data
////////////Retrieve an object`s data


int EntityNumber()
{
	return Editor->worldSystem->EntityNumber();
}

float* GetPosition(int index)
{
	return Editor->worldSystem->GetPosition(index);
}

void ReleaseMemory(void* &ptr)
{

	if (ptr)
	{
		delete[] ptr;

		ptr = nullptr;
	}
	
}
bool ChechPointerIsCorrect(void* ptr)
{
	if (ptr == nullptr)
	{
		return false;
	}
	return true;
}

#pragma endregion objects data
/////////////////////////////////////


#pragma region UI Editor

void SetPlaying()
{
	//isPlaying = true;
}

void ClearUI()
{
	/*for (int i = 0; i < UI.size(); i++)
	{
		UI[i]->~UIElement();
	}

	UI.clear();*/
}

void InitUI()
{
	/*for (int i = 0; i < UI.size(); i++)
	{
		UI[i]->Initialize(*t->GetDevice());
	}*/
}

void AddLabel(const wchar_t* text, const char* fontName, int posX, int posY, int sizeX, int sizeY, int fontSize)
{
	//Text2D *txt = new Text2D();

	//std::wstring ws(text);
	//std::string f(fontName);

	//txt->message = ws;
	//txt->Position = D3DXVECTOR2(posX, posY);
	//txt->Size.x = sizeX;
	//txt->Size.y = sizeY;
	//txt->fontSize = fontSize;

	//txt->fontName = f;

	//SetRect(&txt->Margin, 5, 5, 5, 5);

	//txt->Color = White;

	////txt->Initialize(*t->GetDevice());

	//UI.push_back(txt);
}


void AddSprite(const char* path, int posX, int posY, int sizeX, int sizeY)
{
	/*Sprite2D *sprite = new Sprite2D();

	sprite->Color = White;
	
	sprite->Position = D3DXVECTOR2(posX, posY);

	sprite->Size.x = sizeX;
	sprite->Size.y = sizeY;

	sprite->SetPath((char*)path);

	UI.push_back(sprite);*/
}
#pragma endregion

#pragma region Graph3D

void IsDrawGraph(bool state)
{
	//isDrawGraph = state;
}

void SetType(int type)
{
	//Graph->type = type;
}

void AddGraph3DVertex(float x, float y, float z, int r, int g, int b)
{
	//Graph->AddVertex(x, y, z, r, g, b);
}

void InitializeGraph()
{
	/*if (IsDrawGraph)
	{
		Graph->Initialize();
	}*/
}

void ResetGraph3D()
{
	//Graph->Clear();
}

void BuildGraph3D(const float *x, const float *y, const float *z, int size)
{
	/*for (int i = 0; i < size; i++)
	{
		AddGraph3DVertex(x[i], y[i], z[i], rand() % 255, rand() % 255, rand() % 255);
	}*/
}
#pragma endregion 

#pragma region others

void Screenshot()
{

}

#pragma endregion others