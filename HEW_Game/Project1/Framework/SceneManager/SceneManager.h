#pragma once
#include "../Scene/IScene.h"

//! TODO:scenemanager��titlescene��resultscene���C���N���[�h����ƁA���ꂼ��ŃC���N���[�h����Ă���objectmanager��IScene���Փ˂��Ă��܂�
//! ��scenemanager.cpp�ł̂�titlescene��resultscene���C���N���[�h���ĉ���
//! 
//! TODO:�V�[����vector�Ŏ��ׂ��Hmap�Ŏ��ׂ��H

enum SceneName {
	TITLE,
	GAME,
	RESULT,

	SCENE_MAX
};

/**
 * @brief �V�[���Ǘ��N���X
 *
 * �������ŃV�[�������ׂĔz��Ɋi�[
 * �V�[���؂�ւ��֐����K�v
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init(void);		//! ������
	void Update(void);		//! �X�V
	void Draw(void);		//! �`��
	void Uninit(void);		//! �I��

	void ChangeScene(SceneName scene);	//! �V�[���؂�ւ�

private:
	std::vector<std::unique_ptr<IScene>> scenes;	// �V�[���z��
	SceneName scenename;
};

