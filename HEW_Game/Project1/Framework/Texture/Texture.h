#pragma once
#include "../D3D11/D3D11.h"
#include "../Component/Transform/Transform.h"
#include "../WICTextureLoader/WICTextureLoader.h"


/**
 * Textureクラス
 * 
 * ・画像の読み込み
 * ・描画
 * ・解放
 * を行う
 * 
 * @brief 
 * ＜要素＞
 * 画像分割数、uv座標、頂点座標、頂点バッファ、テクスチャ変数、トランスフォーム
 * ＜機能＞
 * 画像の読み込み、描画、画像の解放、色の設定
 * 
 * アニメーションどうする問題
 * →レンダラークラスを作るなら描画機能は完全にレンダラーに依存させて、レンダラーからアニメーションを呼び出す、とかにするべき
 */
class Texture
{
protected:
	//! トランスフォーム
	Transform transform;
	//! 画像分割数
	XMFLOAT2 split;
	//! 画像番号
	XMFLOAT2 uv;
	//! 頂点座標
	Vertex vertexList[4] =
	{
		//   x     y    z       r    g    b    a     u    v
		{ -0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f},  // 0番目の頂点座標
		{  0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f},  // 1番目の頂点座標
		{ -0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f},  // 2番目の頂点座標
		{  0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f},  // 3番目の頂点座標
	};

	//! 頂点バッファ
	ID3D11Buffer* m_pVertexBuffer;
	//! テクスチャ用変数
	ID3D11ShaderResourceView* m_pTextureView;

private:
	//bool Load(const wchar_t* _Filename);				//! 画像の読み込み（結果を返す）
	//! 初期化（画像ファイルパス、画像分割数、トランスフォーム、uv座標(画像番号)）
	void Init(const wchar_t* _Filename, Transform _Transform, XMFLOAT2 _Split, XMFLOAT2 _Splitnum);
	void Draw();				//! 描画
	void Uninit();				//! 終了
};