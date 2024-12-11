#include "SceneManager.h"
#include "../../Game/Scene/TitleScene.h"
#include "../../Game/Scene/ResultScene.h"
#include "../../Game/Scene/GameScene.h"

SceneManager::SceneManager()
{
	//! シーン生成
	scenes[0] = std::make_unique<TitleScene>();
	scenes[1] = std::make_unique<GameScene>();
	scenes[2] = std::make_unique<TitleScene>();
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
	scenes[scenename]->Draw();
}

void SceneManager::Uninit(void) {
	// 現在シーンの終了処理
	scenes[scenename].un
}

/**
 * @brief シーン切り替え関数
 * @param  
*/
void SceneManager::ChangeScene(SceneName scenename) {
	this->scenename = scenename;
}
