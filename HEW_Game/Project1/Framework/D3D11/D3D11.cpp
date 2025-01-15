#include "../Precompiled/pch.h"
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <locale.h>
#include <atltypes.h> // CRectを使うためのヘッダーファイル
#include <io.h>
#include <stdio.h>
#include <string.h>
#include "D3D11.h"
//へんこう
int i;
//--------------------------------------------------------------------------------------
// Direct3Dの初期化
//--------------------------------------------------------------------------------------
HRESULT D3D11::Init(HWND hwnd)
{
	HRESULT  hr; // HRESULT型・・・Windowsプログラムで関数実行の成功/失敗を受け取る

	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;
	CRect              rect;
	::GetClientRect(hwnd, &rect);
	
	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	::ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// デバイスとスワップチェインを同時に作成する関数の呼び出し
	// ここでnewと同じ効果を得る→deleteは？Release？
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		pLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		&level,
		&m_pDeviceContext);
	if (FAILED(hr)) return hr; // 上の関数呼び出しが失敗してないかifでチェック

	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	if (FAILED(hr)) return hr;
	hr = m_pDevice->CreateRenderTargetView(renderTarget, NULL, &m_pRenderTargetView);
	renderTarget->Release();
	if (FAILED(hr)) return hr;

	// デプスステンシルバッファ作成
	// ※（デプスバッファ = 深度バッファ = Zバッファ）→奥行を判定して前後関係を正しく描画できる
	ID3D11Texture2D* depthStencile;
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	hr = m_pDevice->CreateTexture2D(&textureDesc, NULL, &depthStencile);
	if (FAILED(hr)) return hr;

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	hr = m_pDevice->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(hr)) return hr;
	depthStencile->Release();

	// ビューポートを作成（→画面分割などに使う、描画領域の指定のこと）
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)rect.Width();
	viewport.Height = (FLOAT)rect.Height();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &viewport);

	// インプットレイアウト作成
	D3D11_INPUT_ELEMENT_DESC layout[]
	{
		// 位置座標があるということを伝える
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 色情報があるということを伝える
	    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// UV座標
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	hr = CreateVertexShader(m_pDevice, "VertexShader.hlsl", "vs_main", "vs_5_0",
		layout, numElements, &m_pVertexShader, &m_pInputLayout);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return E_FAIL;
	}

	// ピクセルシェーダーオブジェクトを生成
	hr = CreatePixelShader(m_pDevice, "PixelShader.hlsl", "ps_main", "ps_5_0", &m_pPixelShader);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return E_FAIL;
	}

	// サンプラー作成
	// →　テクスチャをポリゴンに貼るときに、拡大縮小される際のアルゴリズム
	D3D11_SAMPLER_DESC smpDesc;
	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
	if (FAILED(hr)) return hr;

	// 定数バッファ作成
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	hr = m_pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
	if (FAILED(hr)) return hr;

	// ブレンドステート作成 →透過処理や加算合成を可能にする色の合成方法
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = m_pDevice->CreateBlendState(&BlendState, &m_pBlendState);
	if (FAILED(hr)) return hr;

	//深度テストを無効にする
	ID3D11DepthStencilState* pDSState;
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.DepthEnable = FALSE; // 深度テストを無効にする
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = m_pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	if (FAILED(hr)) return hr;
	m_pDeviceContext->OMSetDepthStencilState(pDSState, 1);


	return S_OK;
}

//--------------------------------------------------------------------------------------
// Direct3Dの描画
//--------------------------------------------------------------------------------------
void D3D11::StartRender()
{
	// 画面塗りつぶし色
	float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

	// 描画先のキャンバスと使用する深度バッファを指定する
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	// 描画先キャンバスを塗りつぶす
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	// 深度バッファをリセットする
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pDeviceContext->IASetInputLayout(m_pInputLayout);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	// サンプラーをピクセルシェーダーに渡す
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);

	// 定数バッファを頂点シェーダーにセットする
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//ブレンドステートをセットする
	m_pDeviceContext->OMSetBlendState( m_pBlendState, NULL, 0xffffffff);
}

void D3D11::FinishRender()
{
	// ダブルバッファの切り替えを行い画面を更新する
	m_pSwapChain->Present(0, 0);
}

//--------------------------------------------------------------------------------------
// Direct3Dの解放（終了処理）
//--------------------------------------------------------------------------------------
// ※DirectXの各機能は作成した後、アプリ終了時に必ず解放しなければならない
void D3D11::Release()
{
	if (m_pDeviceContext) m_pDeviceContext->ClearState();
	SAFE_RELEASE(m_pBlendState);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pSampler);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
}

//--------------------------------------------------------------------------------------
// シェーダーをファイル拡張子に合わせてコンパイル
//--------------------------------------------------------------------------------------
HRESULT D3D11::CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut)
{
	*ppBlobOut = nullptr;
	int aaa = strlen(szFileName);
	//拡張子をhlslからcsoに変更したファイル名を作成
	char* csoFileName = new char[strlen(szFileName)];
	const char* dot = strrchr(szFileName, '.'); // 最後の"."を探す
	if (dot != NULL) {
		size_t prefixLength = dot - szFileName;
		strncpy_s(csoFileName, prefixLength + 1, szFileName, _TRUNCATE); // 拡張子以外をコピー
		strcpy_s(csoFileName + prefixLength, 5, ".cso"); // 新しい拡張子を追加
	}
	else {
		strcpy_s(csoFileName, strlen(szFileName), szFileName); // 拡張子がない場合はそのままコピー
	}

	FILE* fp;
	// コンパイル済みシェーダーファイル(cso)があれば読み込む
	if (fopen_s(&fp, csoFileName, "rb") == 0)
	{
		long int size = _filelength(_fileno(fp));
		unsigned char* buffer = new unsigned char[size];
		fread(buffer, size, 1, fp);
		if (!buffer) return E_FAIL;
		*ShaderObject = buffer;
		ShaderObjectSize = size;
		fclose(fp);
	}
	// コンパイル済みシェーダーファイルが無ければシェーダーファイル(hlsl)をコンパイルする
	else
	{
		ID3DBlob* p1 = nullptr;
		HRESULT hr = S_OK;
		WCHAR	filename[512];
		size_t 	wLen = 0;
		int err = 0;

		// char -> wcharに変換
		setlocale(LC_ALL, "japanese");
		err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		// D3DCOMPILE_DEBUGフラグを設定すると、シェーダーにデバッグ情報が埋め込まれる
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob = nullptr;
		hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hr))
		{
			if (pErrorBlob != nullptr) {
				MessageBoxA(NULL, (char*)pErrorBlob->GetBufferPointer(), "Error", MB_OK);
			}
			if (pErrorBlob) pErrorBlob->Release();
			if (*ppBlobOut)(*ppBlobOut)->Release();
			return hr;
		}
		if (pErrorBlob) pErrorBlob->Release();

		*ShaderObject = (*ppBlobOut)->GetBufferPointer();
		ShaderObjectSize = (*ppBlobOut)->GetBufferSize();
	}

	delete[] csoFileName;
	return S_OK;
}


//////////////////////////////////
//			シェーダー系			//
//////////////////////////////////

//--------------------------------------------------------------------------------------
// 頂点シェーダーオブジェクトを生成
//--------------------------------------------------------------------------------------
HRESULT D3D11::CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout)
{
	HRESULT   hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	  ShaderObjectSize;

	// ファイルの拡張子に合わせてコンパイル
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	// 頂点シェーダーを生成
	hr = device->CreateVertexShader(ShaderObject, ShaderObjectSize, NULL, ppVertexShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	// 頂点データ定義生成
	hr = device->CreateInputLayout(
		layout,
		numElements,
		ShaderObject,
		ShaderObjectSize,
		ppVertexLayout);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateInputLayout error", "error", MB_OK);
		pBlob->Release();
		return E_FAIL;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーオブジェクトを生成
//--------------------------------------------------------------------------------------
HRESULT D3D11::CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader)
{
	HRESULT   hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	  ShaderObjectSize;

	// ファイルの拡張子に合わせてコンパイル
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// ピクセルシェーダーを生成
	hr = device->CreatePixelShader(ShaderObject, ShaderObjectSize, NULL, ppPixelShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	return S_OK;
}


ID3D11Device* D3D11::GetDevice(void)
{
	return m_pDevice;
}

ID3D11DeviceContext* D3D11::GetDeviceContext(void)
{
	return m_pDeviceContext;
}

IDXGISwapChain* D3D11::GetSwapChain(void)
{
	return m_pSwapChain;
}

ID3D11Buffer* D3D11::GetConststBuffer(void)
{
	return m_pConstantBuffer;
}
