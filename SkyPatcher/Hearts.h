#pragma once

#include <random>
#include <string>
#include "Graphics.h"
#include <algorithm>


class Heart
{
public:
	Heart(const std::wstring & FilePath, MainWindow & window);
	void Draw(MainWindow & window);
	void Clamp(float X, float Y, float Width, float Height);

private:
	float velX = 0.02f, velY = 0.02f;
    std::unique_ptr<Graphics::Sprite::Image> heart;
	std::mt19937 random;
	std::uniform_real_distribution<float> ColorDist;
	std::uniform_real_distribution<float> distX, distY;
};

