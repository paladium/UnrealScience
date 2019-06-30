#include "Text2D.h"

Text2D::Text2D()
{
	
}


void Text2D::Initialize(IDirect3DDevice9& app)
{
	appDevice3D = &app;

	Font = NULL;
	
	
	D3DXCreateFont(appDevice3D, fontSize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, fontName.c_str(), &Font);
	
	//SetRect(&rectangle, 0, 0, GetSystemMetrics(SM_CXSCREEN) / 3, GetSystemMetrics(SM_CYSCREEN));

	SetRect(&rectangle, Position.x, Position.y, Size.x + Position.x, Size.y + Position.y);

	rectangle.bottom += Margin.bottom;

	rectangle.left += Margin.left;

	rectangle.right += Margin.right;

	rectangle.top += Margin.top;
	
	
}

D3DXVECTOR2 unproject(D3DXVECTOR3 source, D3DXMATRIX view, D3DXMATRIX proj, int width, int height)
{
	D3DXMATRIX viewProj = proj * view;

	D3DXVECTOR3 temp(0, 0, 0);

	D3DXVec3TransformCoord(&temp, &source, &viewProj);

	float winX = ((temp.x + 1) / 2) * width / 100;
	float winY = ((1 - temp.y) / 2) * height / 100;

	return D3DXVECTOR2(winX, winY);
}
void Text2D::Draw()
{
	if (Font)
	{
		D3DXVECTOR2 Center = D3DXVECTOR2(Size.x / 2, Size.y / 2);

		
		
		D3DXVECTOR3 near(0, 0, 0);
		
		D3DVIEWPORT9 v;
		appDevice3D->GetViewport(&v);
		D3DXMATRIX proj, view, world;
		appDevice3D->GetTransform(D3DTS_PROJECTION, &proj);
		appDevice3D->GetTransform(D3DTS_VIEW, &view);
		appDevice3D->GetTransform(D3DTS_WORLD, &world);

		D3DXVECTOR2 pos = unproject(D3DXVECTOR3(0, 0, 1), view, proj, v.Width, v.Height);

		D3DXMATRIX mat;


		
		D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, 0, 0, &pos);

		

		Font->DrawTextW(NULL, message.c_str(), -1, &rectangle, DT_LEFT | DT_WORDBREAK, Color);
		
	}

}
