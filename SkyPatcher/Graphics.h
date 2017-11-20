#pragma once
#include "MainWindow.h"
#include <string>
#include <memory>
#include <optional>
#include "DirectX11Includes.h"
#include "Element2D.h"
#include <typeinfo>

class Graphics
{
public:
	class Sprite
	{
	public:
		class Image : public Element2D
		{
		public:
		    Image(
				Position p,
				const std::wstring & FilePath);
			virtual void Reset(const std::wstring & NewFilePath) override;
			virtual void Draw()override;
			void SetTint(DirectX::XMVECTOR Tint);
		private:
			std::unique_ptr<DirectX::CommonStates>              blendstate;
			DirectX::XMVECTOR Tint;
		};
		class Font : public Element2D
		{
		public:
			Font(
				Position p,
				const std::wstring & FilePath,
				DirectX::XMVECTOR Color,
				const std::wstring & Text);
			virtual void Reset(const std::wstring & NewFilePath)override;
			virtual void Draw()override;
			void SetText(const std::wstring & NewText);
			void SetColor(DirectX::XMVECTOR NewColor);
		private:
			std::wstring Text;
			DirectX::XMVECTOR Color;
		};
	};

public:
	Graphics(HWND hWnd, int ScreenWidth, int ScreenHeight);
	void BeginScene();
	void EndScene();
	static std::optional<Dimensions> GetTextureDim(Microsoft::WRL::ComPtr<ID3D11Resource> resource);
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice()const;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext()const;

private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pDeviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;

	D3D_DRIVER_TYPE                                     DriverType;
	D3D_FEATURE_LEVEL                                   FeatureLevel;
	D3D11_VIEWPORT                                      ViewPort;

private:
	int ScreenWidth;
	int ScreenHeight;
	HWND hWnd;

};
