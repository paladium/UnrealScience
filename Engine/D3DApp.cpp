#include "D3DApp.h"


namespace
{
	D3DApp* g_pointer;
}


D3DApp::D3DApp()
{
	//appInstance = hInstance;
	appWindow = NULL;
	clientWidth = 800;
	clientHeight = 700;

	g_pointer = this;

}

int D3DApp::Run()
{

	__int64 countsPerSecond = 0;

	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);

	float secPerCount = 1 / (countsPerSecond * 1.0f);

	__int64 previousTime = 0;

	QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);



	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			__int64 currTime = 0;

			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			float deltaTime = (currTime - previousTime) * secPerCount;

			CalculateFPS(deltaTime);

			//input->Frame();
			Update(deltaTime);
			Render();

			previousTime = currTime;
		}
	}

	return static_cast<int>(msg.wParam);
}


bool D3DApp::Init()
{

	if (!InitDirect3D())
		return false;

	/*input = new DirectInput();

	if (!input->Init(appWindow, appInstance, clientWidth, clientHeight))
	{
	return false;
	}*/

	return true;
}


bool D3DApp::InitDirect3D()
{

	appDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!appDirect3D)
	{
		MessageBox(NULL, "Failed to create direct3d", "Error", NULL);
		return false;
	}

	D3DCAPS9 devCaps;

	appDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devCaps);

	int vp;

	if (devCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	ZeroMemory(&appPresenterParams, sizeof(D3DPRESENT_PARAMETERS));

	appPresenterParams.BackBufferWidth = clientWidth;
	appPresenterParams.BackBufferHeight = clientHeight;

	appPresenterParams.Windowed = true;
	appPresenterParams.BackBufferCount = 1;
	appPresenterParams.BackBufferFormat = D3DFMT_X8R8G8B8;
	appPresenterParams.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	appPresenterParams.MultiSampleQuality = 0;
	appPresenterParams.hDeviceWindow = appWindow;
	appPresenterParams.Flags = 0;
	appPresenterParams.EnableAutoDepthStencil = true;
	appPresenterParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	appPresenterParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	appPresenterParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	appPresenterParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	appDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		appWindow,
		vp,
		&appPresenterParams,
		&appDevice3D);

	if (!appDevice3D)
	{
		MessageBox(NULL, "Failed device creation", "Error", NULL);
		return false;
	}

	D3DVIEWPORT9 viewport;

	ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));

	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = clientWidth;
	viewport.Height = clientHeight;
	viewport.MinZ = 0;
	viewport.MaxZ = 1;

	appDevice3D->SetViewport(&viewport);



	return true;
}


bool D3DApp::InitInput(HINSTANCE hInstance)
{
	input = new DirectInput();

	appInstance = hInstance;

	if (!input->Init(appWindow, appInstance, clientWidth, clientHeight))
	{
		return false;
	}

	return true;
}

void D3DApp::Shutdown()
{
	DestroyWindow(appWindow);

	appWindow = nullptr;

	UnregisterClass("WINDOW", appInstance);

	appInstance = nullptr;

	g_pointer = nullptr;
}

void D3DApp::CalculateFPS(float dt)
{
	static int frameCount;

	static float elapsedTime;

	frameCount++;

	elapsedTime += dt;

	if (elapsedTime >= 1.0f)
	{
		FPS = frameCount;

		frameCount = 0;
		elapsedTime = 0;
	}
}