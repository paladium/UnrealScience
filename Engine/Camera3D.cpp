#include "Camera3D.h"

Camera3D::Camera3D(float aspectRatio, float _fov)
{

	FOV = _fov;

	D3DXMatrixPerspectiveLH(&projection, FOV, aspectRatio,
		1,
		1000);

	/*D3DXMatrixOrthoLH(&projection, 800, 700, 0, 1);*/

	UpdateViewMatrix();
}

void Camera3D::UpdateViewMatrix()
{
	D3DXMatrixLookAtLH(&view, &Position, &lookForward, &Up);
}

void Camera3D::SetRotation()
{
	lookForward.x = sin(D3DXToRadian(Rotation.x)) * cos(D3DXToRadian(Rotation.y));

	lookForward.y = sin(D3DXToRadian(Rotation.y));

	lookForward.z = cos(D3DXToRadian(Rotation.x)) * cos(D3DXToRadian(Rotation.y));

	lookForward += Position;

	Up.x = -sin(D3DXToRadian(Rotation.x)) * sin(D3DXToRadian(Rotation.y));

	Up.y = cos(D3DXToRadian(Rotation.y));

	Up.z = -cos(D3DXToRadian(Rotation.x)) * sin(D3DXToRadian(Rotation.y));
}

void Camera3D::Move(float unit)
{
	SetRotation();

	D3DXVec3Normalize(&temp, &(lookForward - Position));

	Position = Position + unit * temp;

	UpdateViewMatrix();
}

void Camera3D::Strafe(float unit)
{
	SetRotation();

	D3DXVec3Normalize(&temp, &(lookForward - Position));

	D3DXVECTOR3 cross;

	D3DXVec3Cross(&cross, &temp, &Up);

	Position = Position + unit * cross;

	lookForward += unit * cross;

	UpdateViewMatrix();
}

void Camera3D::Rotate(float x, float y)
{
	Rotation.x += Sensitivity * x;

	Rotation.y += Sensitivity * y;

	SetRotation();

	UpdateViewMatrix();
}

void Camera3D::FreeRotate()
{
	if (freeRotate)
	{
		Rotate(0.01f, 0);
		//D3DXMatrixLookAtLH(&view, &Position, &target, &D3DXVECTOR3(0, 1, 0));
	}
}

void Camera3D::ChangeAspectRatio(float to)
{
	aspectRatio = to;
	D3DXMatrixPerspectiveLH(&projection, FOV, to,
		1,
		1000);
}

void Camera3D::RotateTo(float x, float y)
{
	if (x != 0)
	{
		Rotation.x = x;
	}
	
	if (y != 0)
	{
		Rotation.y = y;
	}
	

	SetRotation();

	UpdateViewMatrix();
}