#pragma once
#include "UIElement.h"


class Text2D : public UIElement
{
public:
	Text2D();
	
	~Text2D(){ /*if (message) delete[] message;*/ if (Font) Font->Release(); }

	void Draw() override;

	std::wstring message;

	void Initialize(IDirect3DDevice9& app) override;

	int fontSize = 20;

	std::string fontName;

	RECT Margin;
private:

	ID3DXFont *Font;

	RECT rectangle;
	
};