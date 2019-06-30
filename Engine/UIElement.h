#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class UIElement{

public:

	UIElement();
	~UIElement(){ if (appDevice3D != nullptr){ appDevice3D->Release(); appDevice3D = nullptr; } }

	virtual void Initialize(IDirect3DDevice9& app) = 0;

	virtual void Draw() = 0;


	D3DXVECTOR2 Position;
	POINT Size;

	RECT Margin;

	D3DXCOLOR Color;

	void ScaleObject(float to);
protected:
	IDirect3DDevice9* appDevice3D;

	D3DXVECTOR2 scale = D3DXVECTOR2(1, 1);
};