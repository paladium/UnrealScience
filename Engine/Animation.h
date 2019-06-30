#pragma once

#include "Mesh3D.h"
#include <algorithm>

struct Transformation{

	D3DXVECTOR3 Position;

	D3DXVECTOR3 Rotation;

	D3DXVECTOR3 Scale;

	D3DXMATRIX World;

	void GetWorld()
	{
		D3DXMATRIX Size, Rx, Ry, Rz, Translate;

		D3DXMatrixRotationX(&Rx, D3DXToRadian(Rotation.x));
		D3DXMatrixRotationY(&Ry, D3DXToRadian(Rotation.y));
		D3DXMatrixRotationZ(&Rz, D3DXToRadian(Rotation.z));

		D3DXMatrixScaling(&Size, Scale.x, Scale.y, Scale.z);

		D3DXMatrixTranslation(&Translate, Position.x, Position.y, Position.z);

		World = Size * Rx * Ry * Rz * Translate;
	}
};



struct Key
{
public:

	Key()
	{
		setPosition = 0;
		setRotation = 0;
		setScale = 0;
	}

	void Initialize(Mesh3D &m)
	{
		mesh = &m;
	}

	int startOrder;

	float duration;

	/*D3DXVECTOR3 Start;

	D3DXVECTOR3 Destination;*/

	Transformation Start;
	Transformation Destination;

	bool setPosition = 0, setRotation = 0, setScale = 0;

	bool isPlayed = false;

	static D3DXVECTOR3 LinearInterpolation(D3DXVECTOR3 Left, D3DXVECTOR3 Right, float param)
	{
		return Left + param * (Right - Left);
	}

	static D3DXVECTOR3 QuadraticInterpolation(D3DXVECTOR3 Left, D3DXVECTOR3 Right, float param)
	{
		return LinearInterpolation(Left, Right, param * param);
	}

	static D3DXVECTOR3 QuadraticInOutInterpolation(D3DXVECTOR3 Left, D3DXVECTOR3 Right, float param)
	{
		D3DXVECTOR3 middle = (Left + Right) / 2;

		param = param * 2;

		if (param <= 1)
		{
			return LinearInterpolation(Left, middle, param * param);
		}

		param--;

		return LinearInterpolation(middle, Right, 2 * param - param * param);
	}

	static D3DXVECTOR3 ToRadian(D3DXVECTOR3 a)
	{
		return D3DXVECTOR3(D3DXToRadian(a.x), D3DXToRadian(a.y), D3DXToRadian(a.z));
	}

	void RunAnimation(float dt)
	{
		if (!isPlayed)
		{
			if (amount <= duration)
			{
				amount += dt;

				float param = amount / duration;

				if (setPosition)
				{
					mesh->Position = QuadraticInOutInterpolation(Start.Position, Destination.Position, param);
				}

				if (setRotation)
				{
					mesh->Rotation = QuadraticInOutInterpolation(Start.Rotation,
						Destination.Rotation, param);
				}

				if (setScale)
				{
					mesh->Scale = QuadraticInOutInterpolation(Start.Scale, Destination.Scale, param);
				}

				

				mesh->UpdateWorldMatrix();
			}

			if (amount > duration)
			{
				isPlayed = true;
			}
		}
	}

	void Reset()
	{
		amount = 0;
		isPlayed = false;
	}
private:

	float amount = 0;

	Mesh3D *mesh;
};




//Class to store animation keys
class Animation
{
public:

	Animation();

	~Animation(){ if (AnimationKeys.size()) for (int i = 0; i < AnimationKeys.size(); i++) delete AnimationKeys[i]; }

	std::vector<Key*> AnimationKeys;

	void Initialize(Mesh3D &_m);

	void Update(float dt);

	bool IsMeshLoaded(){ return !(m == nullptr); }

	void StartAnimation(){ isRunning = true; }

	void StopAnimation(){ isRunning = false; }

	bool IsAnimationRunning(){ return isRunning; }

	bool IsAnimationEndless(){ return isEndless; }

	void SetEndlessProperty(bool value){ isEndless = value; }

	void Reset();

	void SetKeys();

	void NextKey();

	void PrevKey();

private:

	float time;

	Mesh3D *m;

	bool isRunning = false;

	bool isEndless = false;

	Transformation InitialTransformation;

	bool isOBO = true;

	int currKey = 0;
};