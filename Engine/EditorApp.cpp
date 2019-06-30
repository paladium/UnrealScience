#include "EditorApp.h"

EditorApp::EditorApp() : D3DApp()
{

}

EditorApp::~EditorApp()
{
	worldSystem->Cleanup();

	delete worldSystem;

	delete grid;

	delete camera;
}

void EditorApp::SetEverything(HWND hwnd, int width, int height)
{
	appWindow = hwnd;
	clientWidth = width;
	clientHeight = height;
}

void EditorApp::InitFPS()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);

	secPerCount = 1 / (countsPerSecond * 1.0f);

	QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);
}

void EditorApp::UpdateViewMatrix(D3DXMATRIX view)
{
	appDevice3D->SetTransform(D3DTS_VIEW, &view);
}

bool EditorApp::Init()
{
	if (!D3DApp::Init())
		return false;


	camera = new Camera3D((float)(clientHeight / (1.0 * clientWidth)), D3DX_PI / 3);

	camera->Step = 0.1f;

	camera->freeRotate = false;

	appDevice3D->SetTransform(D3DTS_VIEW, &camera->GetViewMatrix());

	appDevice3D->SetTransform(D3DTS_PROJECTION, &camera->GetProjectionMatrix());

	appDevice3D->SetRenderState(D3DRS_LIGHTING, true);
	appDevice3D->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	//appDevice3D->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	appDevice3D->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);

	//appDevice3D->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);


	grid = new Grid(*appDevice3D);

	grid->MainColor = D3DCOLOR_ARGB(255, 128, 128, 128);

	grid->Position = D3DXVECTOR3(-16, 0, -16);

	grid->Initialize();

	worldSystem = new WorldSystem(*appDevice3D);

	return true;
}

void EditorApp::ChangeCameraSpeed(float to)
{
	if (camera)
	{
		camera->Step = to;
	}
}

void EditorApp::InitWorld()
{
	Update(0);
	UpdateViewMatrix(camera->GetViewMatrix());
}

void EditorApp::UpdateWorld(float dt)
{
	worldSystem->Update(camera->GetProjectionMatrix(), camera->GetViewMatrix());
}

void EditorApp::Update(float dt)
{
	UpdateWorld(dt);
}

void EditorApp::Render()
{
	appDevice3D->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3dUtil::Background, 1.0f, 0);


	D3DLIGHT9 light;

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Position = D3DXVECTOR3(-2, 2, 0);
	light.Direction = D3DXVECTOR3(0, -10, 0);

	D3DXCOLOR color = d3dUtil::White;

	light.Ambient = color;
	light.Diffuse = color;
	light.Specular = color;
	light.Range = 20;
	light.Attenuation0 = 1 / power;
	light.Attenuation1 = 1 / power;
	light.Attenuation2 = 1 / power;

	appDevice3D->SetLight(0, &light);

	appDevice3D->LightEnable(0, true);

	appDevice3D->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

	appDevice3D->SetRenderState(D3DRS_LIGHTING, TRUE);

	appDevice3D->BeginScene();

	//Rendering

	grid->Render();

	worldSystem->Render();
	///

	appDevice3D->EndScene();

	appDevice3D->Present(0, 0, 0, 0);

}

void EditorApp::GlobalUpdate()
{
	__int64 currTime = 0;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	float deltaTime = (currTime - GetPrevTime()) * GetSecPerCount();

	Update(1.0 / deltaTime);

	SetPrevTime(currTime);
}

void EditorApp::TestUpdate(int command, float mouse_x, float mouse_y)
{
	if (command == 1)
	{
		camera->Move(camera->Step);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	if (command == 2)
	{
		camera->Move(-camera->Step);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	if (command == 3)
	{
		camera->Strafe(camera->Step);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	if (command == 4)
	{
		camera->Strafe(-camera->Step);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	if (command == 6)
	{
		camera->Rotate(0.1f, 0);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	if (command == 7)
	{
		camera->Rotate(-0.1f, 0);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	if (command == 8)
	{
		camera->Rotate(0, 0.1f);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	if (command == 9)
	{
		camera->Rotate(0, -0.1f);

		UpdateViewMatrix(camera->GetViewMatrix());
	}

	//if (command == 10)
	//{
	//	camera->RotateTo(0, 2 * D3DX_PI);

	//	UpdateViewMatrix(camera->GetViewMatrix());
	//}

	if (mouse_x != 0 || mouse_y != 0)
	{
		camera->Rotate(mouse_x, mouse_y);

		UpdateViewMatrix(camera->GetViewMatrix());

	}

	GlobalUpdate();
}

void EditorApp::ResizeViewport(float to)
{
	camera->ChangeAspectRatio(to);

	appDevice3D->SetTransform(D3DTS_PROJECTION, &camera->GetProjectionMatrix());
}