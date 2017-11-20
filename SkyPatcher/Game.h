#pragma once

#include "Graphics.h"
#include "Button.h"
#include <random>
#include "Hearts.h"
#include <algorithm>
#include "Sky.h"

class Game
{
public:
	Game(Graphics & gfx, MainWindow & mouse, Sky & sky);
	void Go();
	void ComposeFrame();
	void UpdateLogic();

private:
	MainWindow & window;
	Graphics & gfx;
	Sky & sky;

private:
	Button ReviveBox;
	Button DeadLock;

	std::unique_ptr<Graphics::Sprite::Image> background;

	std::vector<std::shared_ptr<Graphics::Sprite::Image>> heart1;
	std::vector<std::shared_ptr<Graphics::Sprite::Image>> heart2;
 
	std::vector<Heart> hearts;
	
	static constexpr size_t numHearts = 5;
	
};

