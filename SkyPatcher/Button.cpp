#include "Button.h"

Button::Button(Position position, Mouse & mouse, Graphics & gfx, const std::wstring & DownImage,
	const std::wstring & UpImage,
	const std::wstring & Font,
	const std::wstring & ButtonText,
	DirectX::XMVECTOR TextColor)
	:
	mouse(mouse),
	position(position),
	gfx(gfx)
{
	buttonUp = std::make_shared<Graphics::Sprite::Image>(Graphics::Sprite::Image(position, UpImage));

	buttonDown = std::make_shared<Graphics::Sprite::Image>(Graphics::Sprite::Image(position, DownImage));

	buttonText = std::make_shared<Graphics::Sprite::Font>(Graphics::Sprite::Font({ position.X, position.Y }, Font, TextColor, ButtonText));

	dim = buttonDown->GetDim();

	clicked = false;
}

void Button::Draw()
{
	if (IsDown())
		buttonDown->Draw();
	else
		buttonUp->Draw();
	
	buttonText->Draw();
}

bool Button::IsDown()
{
	if (mouse.LeftIsPressed())
		return MouseIsOnButton();
	else
		return false;
}

bool Button::ClickedOn()
{
	//first check if we are sending a left down on the button
	if (IsDown())
	{
		//if the down state was already marked, that means the left click wasn't released
		//so return false because we already clicked on it
		if (clicked)
			return false;
		//if the down state was not marked that means we are barely sending a left down click
		//so mark it true
		else
			return clicked = true;
		
	}

	//if we're not clicking on anything at all simply return false
	return clicked = false;
}

Position Button::GetPosition()
{
	return position;
}

void Button::SetPosition(Position p)
{
	position = p;

	buttonDown->SetPosition(p);
	buttonUp->SetPosition(p);
}

bool Button::MouseIsOnButton()
{
	return (mouse.GetPosX() > position.X && mouse.GetPosX() < (position.X + dim.Width) &&
	    	mouse.GetPosY() > position.Y && mouse.GetPosY() < (position.Y + dim.Height));
}

Dimensions Button::GetDim()
{
	return dim;
}

void Button::SetText(const std::wstring & Text)
{
	buttonText->SetText(Text);
}
