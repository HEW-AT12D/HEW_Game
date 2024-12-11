#pragma once
#include "../../pch.h"
#include "../../Framework/D3D11/D3D11.h"
#include "../../Framework/WICTextureLoader/WICTextureLoader.h"	// テクスチャ読み込みライブラリ
#include"../../Framework/Component/Transform/Transform.h"		//Transform.h読み込み

/// <summary>
/// TODO:オブジェクトの描画方法を変更する
/// 
/// 現在：頂点バッファのみで描画
/// 目標：インデックスバッファを使用した描画に変更
/// 
/// 良い点：頂点情報を共有できるので規模が大きくなればなるほど描画処理の負荷が減る
/// 
/// --------------改善案----------------
/// d3dクラスのポインタ→参照？ユニークポインタ？d3dクラスをstatic化？Rendererクラス作成？
/// </summary>

/**
 * @brief 基本となるゲームオブジェクトクラス
 * 
 * 一旦コンポーネント指向ではなくオブジェクト指向で止めておく
 * @param vertices 頂点データ
 * @param d3d11 d3dクラスのポインタ（描画に使用）
 * @param transform トランスフォーム（座標、回転、大きさ）
 * @param color 色情報
 * 
*/
class GameObject {
private:
	//! 頂点データ
	//! このゲームでは擬音を吸い込むことがあるため頂点を可変にしておく
	std::vector<Vertex> vertices =
	{
		//   x     y    z       r    g    b    a     u    v
		{ -0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f},  // 0番目の頂点座標
		{  0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f},  // 1番目の頂点座標
		{ -0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f},  // 2番目の頂点座標
		{  0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f},  // 3番目の頂点座標
	};
	
	// d3dクラス
	D3D11* d3d11;

	// 座標,大きさ,角度
	Transform transform;
	// 色
	Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 頂点バッファ
	ID3D11Buffer* m_pVertexBuffer;
	// テクスチャ用変数
	ID3D11ShaderResourceView* m_pTextureView;

	//テクスチャが縦横に何分割されているか
	Vector2 m_Split{ 1.0f,1.0f };

	//左上から何段目を切り抜いて表示するか
	Vector2 m_Number{ 0.0f,0.0f };


public:
	

	void Init(const wchar_t* imgname, int sx = 1, int sy = 1); //初期化
	void Draw();						//描画
	void Uninit();						//終了
	void SetPosition(Vector3 _Pos);		//座標をセット
	void SetScale(Vector3 _Size);		//大きさをセット
	void SetRotation(Vector3 _Rot);		//角度をセット
	void SetColor(Vector4 _Color);		//色をセット

	// 個別の当たり判定もここに追加？オブジェクトの基本となるクラスならここじゃなくて、判定が必要なオブジェクトにそれぞれ追加？

	Vector3 GetPosition(void);			//座標を取得
	Vector3 GetScale(void);				//大きさを取得
	Vector3 GetRotation(void);			//角度を取得
	Vector4 GetColor(void);				//色を取得
};
