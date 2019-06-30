#pragma once
#include "UIElement.h"


class Sprite2D : public UIElement
{
public:
	void Initialize(IDirect3DDevice9& app) override;

	Sprite2D();

	~Sprite2D();

	bool SetTexture();

	void SetSize(int width, int height);

	void SetPosition(int x, int y);

	void Draw() override;

	float aspectRatio;

	void SetPath(char* path);
private:

	LPDIRECT3DTEXTURE9 texture;

	LPD3DXSPRITE sprite;

	std::string textPath;
};