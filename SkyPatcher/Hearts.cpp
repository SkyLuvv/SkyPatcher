
#include "Hearts.h"


Heart::Heart(const std::wstring & FilePath, MainWindow & window)
	:
	random(std::random_device()()),
	distX(0.0f, (float)window.Width),
	distY(0.0f, (float)window.Height),
	ColorDist(0.0f, 1.0f)
{

	
	heart = std::make_unique<Graphics::Sprite::Image>(Graphics::Sprite::Image({ distX(random),distY(random) }, FilePath));

	heart->SetTint({ ColorDist(random), ColorDist(random), ColorDist(random)});

}

void Heart::Draw(MainWindow & window)
{
	Clamp(180.0f, 0.0f, (float)window.Width, (float)window.Height);

	heart->SetPosition({ heart->GetPosX() + velX, heart->GetPosY() + velY });
	heart->Draw();
}

void Heart::Clamp(float X, float Y, float Width, float Height)
{
	
	auto collidingx = std::clamp(heart->GetPosX(), X, Width);

	auto collidingy = std::clamp(heart->GetPosY(), Y, Height);

	//set the positions to clamp the heart inside the specified region
	heart->SetPosition({ collidingx, collidingy });

	//then reverse the move direction
	if (collidingx == Width || collidingx == X)
		velX *= -1;

	if (collidingy == Height || collidingy == Y)
		velY *= -1;

}

