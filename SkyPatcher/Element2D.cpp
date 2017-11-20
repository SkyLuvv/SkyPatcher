#include "Element2D.h"
#include "Graphics.h"

//initialize static data members
Graphics * Element2D::gfx = nullptr;
std::shared_ptr<DirectX::SpriteBatch> Element2D::sprite = 0;

void Element2D::Init(Graphics * gfx_)
{
	gfx = gfx_;
	sprite = std::make_shared<DirectX::SpriteBatch>(gfx->GetDeviceContext().Get());
}

Dimensions Element2D::GetDim()
{
	return dim;
}

Position Element2D::GetPosition()
{
	return position;
}

float Element2D::GetPosX()
{
	return position.X;
}

float Element2D::GetPosY()
{
	return position.Y;
}

void Element2D::SetPosition(Position p)
{
	position = p;
}

void Element2D::SetX(float X)
{
	position.X = X;
}

void Element2D::SetY(float Y)
{
	position.Y = Y;
}
