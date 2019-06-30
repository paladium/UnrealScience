#include <d3dx9.h>

class Camera3D{

public:


	Camera3D(float aspectRatio, float FOV);

	D3DXVECTOR3 Position = D3DXVECTOR3(0, 0, -5);

	D3DXVECTOR3 Up = D3DXVECTOR3(0, 1, 0);

	D3DXVECTOR3 Rotation = D3DXVECTOR3(0, 0, 0);

	float Sensitivity = 5;

	float Step = 0.01f;

	D3DXMATRIX GetViewMatrix()
	{
		return view;
	}

	D3DXMATRIX GetProjectionMatrix()
	{
		return projection;
	}

	void Move(float unit);

	void Strafe(float unit);

	void Rotate(float, float);

	void ChangeAspectRatio(float to);

	void RotateTo(float x, float y);

	float GetAspectRatio()
	{
		return aspectRatio;
	}

	void FreeRotate();

	bool freeRotate = false;

	D3DXVECTOR3 target = D3DXVECTOR3(0, 0, 0);

private:

	D3DXVECTOR3 lookForward;

	D3DXVECTOR3 temp;

	D3DXMATRIX view;

	D3DXMATRIX projection;

	void UpdateViewMatrix();

	void SetRotation();

	float FOV;

	float aspectRatio;
};