#include "D3DApp.h"
#include "Camera3D.h"
#include "WorldSystem.h"
#include "Grid.h"
#include "ScreenEffect.h"

class EditorApp : public D3DApp
{
public:

	EditorApp();

	~EditorApp();

	bool Init() override;

	void Update(float dt) override;
	void Render() override;

	void SetEverything(HWND hwnd, int width, int height);

	int GetWidth(){ return clientWidth; }

	int GetHeight(){ return clientHeight; }

	IDirect3DDevice9* GetDevice()
	{
		return appDevice3D;
	}

	Grid* grid;

	WorldSystem* worldSystem;

	Camera3D* camera;

	void ChangeCameraSpeed(float to);

	void TestUpdate(int command, float mouse_x, float mouse_y);

	void GlobalUpdate();

	void ResizeViewport(float to);

	void InitWorld();

private:
	__int64 countsPerSecond = 0;

	float secPerCount;

	__int64 previousTime = 0;

	float power = 10;

	void CalculateDelta();

	float deltaTime;

	void UpdateWorld(float dt);

	float GetDelta();

	float GetSecPerCount(){ return secPerCount; }

	__int64 GetPrevTime(){ return previousTime; }

	void SetPrevTime(__int64 t){ previousTime = t; }

	void InitFPS();

	void UpdateViewMatrix(D3DXMATRIX view);

	
};

