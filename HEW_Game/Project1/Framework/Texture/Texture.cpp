#include "../Precompiled/pch.h"
#include"Texture.h"

/**
 * @brief テクスチャの初期化
 * @param _Filename ファイルパス
 * @param _Transform トランスフォーム
 * @param _Split 画像分割数
 * @param _Uv 画像番号
*/
void Texture::Init(const wchar_t* _Filename, Transform _Transform, XMFLOAT2 _Split, XMFLOAT2 _Uv)
{
	//UV座標を設定
	uv.x = _Uv.x;
	uv.y = _Uv.y;
	//! 画像分割数を画像番号で割って、分割した何番目を使うかを各頂点ごと計算
	vertexList[1].u = uv.x / split.x;
	vertexList[2].v = uv.y / split.y;
	vertexList[3].u = uv.x / split.x;
	vertexList[3].v = uv.y / split.y;

	// 頂点バッファを作成する
	// ※頂点バッファ→VRAMに頂点データを置くための機能
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// 確保するバッファサイズを指定
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAMに送るデータを指定
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	// テクスチャ読み込み
//	hr = DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &m_pTextureView);
	hr = DirectX::CreateWICTextureFromFileEx(m_pDevice, m_pDeviceContext, _Filename, 0, D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &m_pTextureView);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
		return;
	}
}


void Texture::Draw()
{
	transform.Getpo
}

void Texture::Uninit()
{

}