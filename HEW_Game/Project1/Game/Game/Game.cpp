#include "../../Framework/Precompiled/pch.h"
#include "Game.h"

void Game::Init(HWND hWnd)
{
	d3d11.Init(hWnd);                 // DirectXを初期化
	player.Init(L"asset/char01.png", 3, 4); //プレイヤーを初期化
	player.SetPos(100.0f, 0.0f, 0.0f);     //位置を設定
	player.SetSize(200.0f, 300.0f, 0.0f);  //大きさを設定
	player.SetAngle(0.0f);                 //角度を設定
	player.SetColor(1.0f, 1.0f, 1.0f, 0.5f);                 //角度を設定

	background.Init(L"asset/back_img_01.png");   //背景を初期化
	background.SetPos(0.0f, 0.0f, 0.0f);      //位置を設定
	background.SetSize(640.0f, 480.0f, 0.0f); //大きさを設定
	background.SetAngle(0.0f);                //角度を設定

}

void Game::Update(void)
{
	input.Update();

	//プレイヤーのアニメーション
	player.numU++;
	if (player.numU >= 3) {
		player.numU = 0;
	}
	DirectX::XMFLOAT3 pos = player.GetPos();
//	pos.x += 1.0f;

	if (input.GetKeyPress(VK_W)) { pos.y += 1.0f; }
	if (input.GetKeyPress(VK_A)) { pos.x -= 1.0f; }
	if (input.GetKeyPress(VK_S)) { pos.y -= 1.0f; }
	if (input.GetKeyPress(VK_D)) { pos.x += 1.0f; }

	// Iキーでフルスクリーン化
	if (input.GetKeyTrigger(VK_I)) {
		
		
		
		
		d3d11.GetSwapChain()->SetFullscreenState(TRUE, NULL);
	}
	// Kキーでフルスクリーン解除
	if (input.GetKeyTrigger(VK_K)) {
		d3d11.GetSwapChain()->SetFullscreenState(FALSE, NULL);
	}

	player.SetPos(pos.x, pos.y, pos.z);

}

void Game::Draw(void)
{
	d3d11.StartRender();	// 描画開始
	background.Draw();		// 背景を描画
	player.Draw();			// プレイヤーを描画
	d3d11.FinishRender();	// 描画終了
}

void Game::Uninit(void)
{
	player.Uninit();		// プレイヤーを終了
	background.Uninit();	// プレイヤーを終了
	d3d11.Release();		// DirectXを終了
}
