#pragma once
#include "WindowsIncludes.h"
#include "DimensionStructs.h"

class Mouse
{
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Position GetPos()const
	{
		return pos;
	}
	void OnMouseMove(float X, float Y)
	{
		pos = { X, Y };
	}
	float GetPosX() const
	{
		return pos.X;
	}
	float GetPosY()const
	{
		return pos.Y;
	}
	bool LeftIsPressed()const
	{
		return leftispressed;
	}
	bool RightIsPressed()const
	{
		return rightispressed;
	}
	void OnLeftPressed(float X, float Y)
	{
		pos = { X, Y };
		leftispressed = true;
	}
	void OnRightPressed(float X, float Y)
	{
		pos = { X, Y };
		rightispressed = true;
	}
	void OnLeftReleased(float X, float Y)
	{
		pos = { X, Y };
		leftispressed = false;
	}
	void OnRightReleased(float X, float Y)
	{
		pos = { X, Y };
		rightispressed = false;
	}

private:
	bool leftispressed = false;
	bool rightispressed = false;
	Position pos;


};