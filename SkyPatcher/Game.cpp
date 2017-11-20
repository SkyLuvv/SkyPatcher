#include "Game.h"
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;

Game::Game(Graphics & gfx, MainWindow & window, Sky & sky)
	:
	gfx(gfx),
	window(window),
	sky(sky),
	ReviveBox({ 20,20 }, window.mouse, gfx, L"Sky\\SkyButtonDown.bmp", L"Sky\\SkyButtonUp.bmp",L"Sky\\SkyFont.spritefont",L"REVIVE ON", DirectX::Colors::Black),
	DeadLock({ 20,110 }, window.mouse, gfx, L"Sky\\SkyButtonDown.bmp", L"Sky\\SkyButtonUp.bmp", L"Sky\\SkyFont.spritefont",L"DEADLOCK ON", DirectX::Colors::Black)
{


	for (size_t i = 0; i < numHearts; ++i)
		hearts.emplace_back(L"Sky\\heart1.png", window);

    
	background = std::make_unique<Graphics::Sprite::Image>(Graphics::Sprite::Image({ 0,0 }, L"Sky\\SkyBackGround.bmp"));

	ReviveBox.buttonText->SetPosition({ ReviveBox.GetPosition().X + 15, ReviveBox.GetPosition().Y + 10 });
	DeadLock.buttonText->SetPosition({ DeadLock.GetPosition().X + 15, DeadLock.GetPosition().Y + 10 });
}

void Game::Go()
{
	UpdateLogic();
	ComposeFrame();
}

void Game::UpdateLogic()
{
	if (ReviveBox.ClickedOn())
	{
		MessageBeep(MB_OK);

		auto rezbox = sky.modsmap.find(modID::ReviveBox);

		if (rezbox->second->IsPatched())
		{
			rezbox->second->UndoPatches();
			sky.AutoReviveOn = false;
			ReviveBox.SetText(L"REVIVE OFF");
		}
		else
		{
			rezbox->second->Patch();
			sky.CreateReviveThread();
			ReviveBox.SetText(L"REVIVE ON");
		}
		
	}
	else if (DeadLock.ClickedOn())
	{
		MessageBeep(MB_OK);

		auto dl = sky.modsmap.find(modID::DeadLock);

		if (dl->second->IsPatched())
		{
			dl->second->UndoPatches();
			DeadLock.SetText(L"DEADLOCK OFF");
		}
		else
		{
			dl->second->Patch();
			DeadLock.SetText(L"DEADLOCK ON");
		}
	}
}


void Game::ComposeFrame()
{
	background->Draw();

	for (auto & heart : hearts)
		heart.Draw(window);

	ReviveBox.Draw();
	DeadLock.Draw();
}
