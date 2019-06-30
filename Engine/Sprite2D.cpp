#include "Sprite2D.h"

Sprite2D::Sprite2D()
{

}

void Sprite2D::Initialize(IDirect3DDevice9& app)
{
	appDevice3D = &app;

	Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	SetTexture();
}

void Sprite2D::SetSize(int width, int height)
{
	Size.x = width;
	Size.y = height;
}

void Sprite2D::SetPosition(int x, int y)
{
	Position.x = x;
	Position.y = y;
}

void Sprite2D::SetPath(char* path)
{
	textPath = path;
}

bool Sprite2D::SetTexture()
{
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(appDevice3D, textPath.c_str(), Size.x, Size.y, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture)))
	{
		return false;
	}

	if (!SUCCEEDED(D3DXCreateSprite(appDevice3D, &sprite)))
	{
		return false;
	}

	/*SetRect(&rectangle, Position.x, Position.y, Size.x, Size.y);

	rectangle.bottom += Margin.bottom;
	rectangle.left += Margin.left;
	rectangle.right += Margin.right;
	rectangle.top += Margin.top;*/

	return true;
}

void Sprite2D::Draw()
{
	if (sprite && texture)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);


		D3DXVECTOR2 Center = D3DXVECTOR2(Size.x / 2, Size.y / 2);

		D3DXMATRIX mat;

		D3DXVECTOR2 scale;

		scale.x = 1;
		scale.y = 1;

		D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, 0, 0, &Position);

		sprite->SetTransform(&mat);

		sprite->Draw(texture, NULL, 0, 0, Color);

		sprite->End();
	}
}

Sprite2D::~Sprite2D()
{
	if (texture)
	{
		texture->Release();
		texture = 0;
	}

	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}
}