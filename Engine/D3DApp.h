#include "stdafx.h"
#include "Input.h"
#include <d3d9.h>
#include <d3dx9.h>

class D3DApp{

public:
	D3DApp();


	virtual ~D3DApp() { if (appDevice3D != NULL) appDevice3D->Release(); if (appDirect3D != NULL) appDirect3D->Release(); };

	int Run();

	bool InitInput(HINSTANCE);

	virtual bool Init();
	virtual void Update(float) = 0;
	virtual void Render() = 0;

	void Shutdown();

protected:

	HWND appWindow;
	HINSTANCE appInstance;
	unsigned int clientWidth;
	unsigned int clientHeight;

	DirectInput* input;

	IDirect3D9* appDirect3D;
	IDirect3DDevice9* appDevice3D;
	D3DPRESENT_PARAMETERS appPresenterParams;

	float FPS;

	bool InitDirect3D();

	void CalculateFPS(float dt);
};
