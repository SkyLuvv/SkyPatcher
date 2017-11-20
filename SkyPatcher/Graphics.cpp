#include "Graphics.h"
//#include "Sprite.h"

using namespace Microsoft::WRL;
using namespace DirectX;

Graphics::Graphics(HWND hWnd, int ScreenWidth, int ScreenHeight)
	:
	hWnd(hWnd),
	ScreenWidth(ScreenWidth),
	ScreenHeight(ScreenHeight)
{

	HRESULT	hr;

	//struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd = { 0 };

	// one back buffer
	scd.BufferCount = 1;
	// use 32-bit color
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// how swap chain is to be used
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	// the window to be used
	scd.OutputWindow = hWnd;             
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	// how many multisamples
	scd.SampleDesc.Count = 2;   
	// windowed/full-screen mode
	scd.Windowed = TRUE;                    
	scd.BufferDesc.Width = ScreenWidth;
	scd.BufferDesc.Height = ScreenHeight;

	// create device and front/back buffers
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		0,
		0,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		0,
		&pDeviceContext)))
	{
		MainWindow::ShowMessageBox("Failed : D3D11CreateDeviceAndSwapChain ", "ERROR");
	}

	// get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if (FAILED(hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer)))
	{

	}

	// create a view on backbuffer that we can render to
	if (FAILED(hr = pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView)))
	{
		MainWindow::ShowMessageBox("Failed : CreateRenderTargetView ", "ERROR");
	}

	// set backbuffer as the render target using created view
	pDeviceContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);

	// set viewport dimensions
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (float)ScreenWidth;
	vp.Height = (float)ScreenHeight;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	//set the viewport
	pDeviceContext->RSSetViewports(1, &vp);


	//initialize the 2D static elements
	Element2D::Init(this);

}

void Graphics::BeginScene()
{
	pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), DirectX::Colors::Black);	
}

void Graphics::EndScene()
{
	pSwapChain->Present(0, 0);
	
}

std::optional<Dimensions> Graphics::GetTextureDim(ComPtr<ID3D11Resource> resource)
{
	//enum that will be passed to get the type of buffer our resource is
	D3D11_RESOURCE_DIMENSION type;
	
	resource->GetType(&type);

	switch (type)
	{
		//check if its a 2d texture, if so, get information on it
	case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
	    {
	    	auto Texture = reinterpret_cast<ID3D11Texture2D*>(resource.Get());

	    	D3D11_TEXTURE2D_DESC desc;

	    	Texture->GetDesc(&desc);

			return Dimensions{ (int)desc.Width, (int)desc.Height };
	    }
	default:
		return {};
	}
}

Microsoft::WRL::ComPtr<ID3D11Device> Graphics::GetDevice() const
{
	return pDevice;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> Graphics::GetDeviceContext() const
{
	return pDeviceContext;
}

Graphics::Sprite::Image::Image(Position p, const std::wstring & FilePath)
	:
	Element2D(p, FilePath)
{

	blendstate = std::make_unique<DirectX::CommonStates>(gfx->GetDevice().Get());

	Tint = DirectX::Colors::White;

	Reset(FilePath);
}

void Graphics::Sprite::Image::Reset(const std::wstring & NewFilePath)
{
	FilePath = NewFilePath;

	if (FAILED(DirectX::CreateWICTextureFromFile(gfx->GetDevice().Get(), FilePath.c_str(), pResource.ReleaseAndGetAddressOf(), pTexture.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, ("Failed To Reset Texture : " + std::string(FilePath.begin(), FilePath.end())).c_str(), "SPRITE ERROR", MB_ICONERROR);
		std::terminate();
	}

	auto dimensions = Graphics::GetTextureDim(pResource);

	if (dimensions)
		dim = dimensions.value();
}

void Graphics::Sprite::Image::Draw()
{
	try
	{
		sprite->Begin(DirectX::SpriteSortMode_Deferred, blendstate->AlphaBlend());
		sprite->Draw(pTexture.Get(), DirectX::SimpleMath::Vector2(position.X, position.Y), Tint);
		sprite->End();

	}
	catch (...)
	{
		MessageBox(0, ("Draw Sprite Failed  : " + std::string(FilePath.begin(), FilePath.end())).c_str(), "SPRITE ERROR", MB_ICONERROR);
		std::terminate();
	}
}

void Graphics::Sprite::Image::SetTint(DirectX::XMVECTOR Tint)
{
	this->Tint = Tint;
}

Graphics::Sprite::Font::Font(Position p, const std::wstring & FilePath, DirectX::XMVECTOR Color, const std::wstring & Text)
	:
	Element2D(p, FilePath),
	Color(Color), Text(Text)
{

	spritefont = std::make_shared<DirectX::SpriteFont>(gfx->GetDevice().Get(), FilePath.c_str());
}

void Graphics::Sprite::Font::Reset(const std::wstring & NewFilePath)
{
	spritefont.reset();
	spritefont = std::make_shared<DirectX::SpriteFont>(gfx->GetDevice().Get(), FilePath.c_str());
}

void Graphics::Sprite::Font::Draw()
{
	try
	{
		sprite->Begin();

		spritefont->DrawString(sprite.get(), Text.c_str(), DirectX::SimpleMath::Vector2(position.X, position.Y), Color);

		sprite->End();
	}
	catch (...)
	{
		MessageBox(0, ("Draw Font Failed  : " + std::string(FilePath.begin(), FilePath.end())).c_str(), "SPRITE ERROR", MB_ICONERROR);
		std::terminate();
	}
}

void Graphics::Sprite::Font::SetText(const std::wstring & NewText)
{
	Text = NewText;
}

void Graphics::Sprite::Font::SetColor(DirectX::XMVECTOR NewColor)
{
	Color = NewColor;
}
