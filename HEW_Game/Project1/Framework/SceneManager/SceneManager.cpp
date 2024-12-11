#include "../Precompiled/pch.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	//! シーン生成
	
}

SceneManager::~SceneManager()
{

}

/**
 * @brief シーン配列初期化
 * @param
*/
void SceneManager::Init(void) {


}

void SceneManager::Draw(void) {
	//! 現在シーンを描画
	scenes[scenename]->Draw();
}

void SceneManager::Uninit(void) {
	// 現在シーンの終了処理
	
}

/**
 * @brief シーン切り替え関数
 * @param 切り替え先シーンのタグ
 * 
 * 現在シーンを切り替え先シーンに変更→現在シーンを解放？
 * →シーンを戻ることも想定すると、オーバーロードしておき、”切り替えのみ”の関数と”切り替え・前シーン解放”の機能をもった関数をそれぞれ作っておくべき
*/
void SceneManager::ChangeScene(SceneName scenename) {
	this->scenename = scenename;
}
