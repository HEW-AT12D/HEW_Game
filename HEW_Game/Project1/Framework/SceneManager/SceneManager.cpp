#include "../Precompiled/pch.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	//! �V�[������
	
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
	//! ���݃V�[����`��
	scenes[scenename]->Draw();
}

void SceneManager::Uninit(void) {
	// ���݃V�[���̏I������
	
}

/**
 * @brief �V�[���؂�ւ��֐�
 * @param �؂�ւ���V�[���̃^�O
 * 
 * ���݃V�[����؂�ւ���V�[���ɕύX�����݃V�[��������H
 * ���V�[����߂邱�Ƃ��z�肷��ƁA�I�[�o�[���[�h���Ă����A�h�؂�ւ��̂݁h�̊֐��Ɓh�؂�ւ��E�O�V�[������h�̋@�\���������֐������ꂼ�����Ă����ׂ�
*/
void SceneManager::ChangeScene(SceneName scenename) {
	this->scenename = scenename;
}
