#include "SceneManager.h"
#include "../../Game/Scene/TitleScene.h"
#include "../../Game/Scene/ResultScene.h"
#include "../../Game/Scene/GameScene.h"

SceneManager::SceneManager()
{
	//! �V�[������
	scenes[0] = std::make_unique<TitleScene>();
	scenes[1] = std::make_unique<GameScene>();
	scenes[2] = std::make_unique<TitleScene>();
}

SceneManager::~SceneManager()
{

}

/**
 * @brief �V�[���z�񏉊���
 * @param  
*/
void SceneManager::Init(void) {
	

}

void SceneManager::Draw(void) {
	scenes[scenename]->Draw();
}

void SceneManager::Uninit(void) {
	// ���݃V�[���̏I������
	scenes[scenename].un
}

/**
 * @brief �V�[���؂�ւ��֐�
 * @param  
*/
void SceneManager::ChangeScene(SceneName scenename) {
	this->scenename = scenename;
}
