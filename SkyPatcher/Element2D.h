#pragma once
#include "DimensionStructs.h"
#include "DirectX11Includes.h"

class Graphics;

class Element2D
{
public:
	Element2D(Position position,
		const std::wstring & FilePath)
		:
		position(position),
		FilePath(FilePath)
	{}

	static void Init(Graphics * gfx_);
	virtual Dimensions GetDim();
	virtual Position GetPosition();
	virtual float GetPosX();
	virtual float GetPosY();
	virtual void Draw() = 0;
	virtual void Reset(const std::wstring & NewFilePath) = 0;
	virtual void SetPosition(Position p);
	virtual void SetX(float X);
	virtual void SetY(float Y);


protected:
	Position position;
	Dimensions dim;
	std::wstring FilePath;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>      pTexture;
	Microsoft::WRL::ComPtr<ID3D11Resource>                pResource;

protected:
     static std::shared_ptr<DirectX::SpriteBatch>         sprite;
	 std::shared_ptr<DirectX::SpriteFont>                 spritefont;
	 static Graphics * gfx;

};