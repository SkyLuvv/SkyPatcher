#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "Element2D.h"

class Button
{

public:
	Button(const Button &) = delete;
	void Draw();
	Button(Position position, Mouse & mouse,
		Graphics & gfx,
		const std::wstring & DownImage,
		const std::wstring & UpImage,
		const std::wstring & Font,
		const std::wstring & ButtonText,
		DirectX::XMVECTOR TextColor);

	bool IsDown();
	bool ClickedOn();
	Position GetPosition();
	void SetPosition(Position p);
	bool MouseIsOnButton();
	Dimensions GetDim();
	void SetText(const std::wstring & Text);

private:
	Mouse & mouse;
	Position position;
	bool clicked;
	Dimensions dim;
	Graphics & gfx;

public:
	std::shared_ptr<Graphics::Sprite::Image> buttonUp, buttonDown;
	std::shared_ptr<Graphics::Sprite::Font> buttonText;
};
