#pragma once
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include "../../pch.h"
=======
#include "../main.h"
>>>>>>> c18ec40d02bbcc93ab399e4036a21f857ba308be
=======
#include "../../Framework/Precompiled/pch.h"
>>>>>>> parent of cecf57c (調整中)
=======
#include "../../Framework/Precompiled/pch.h"
>>>>>>> parent of c18ec40 (pch.hの削除とmain.hをすべてにinclude)
#include "../../Framework/Scene/IScene.h"


//! TODO:scenemanager��titlescene��resultscene���C���N���[�h����ƁA���ꂼ��ŃC���N���[�h����Ă���objectmanager��IScene���Փ˂��Ă��܂�
//! ��scenemanager.cpp�ł̂�titlescene��resultscene���C���N���[�h���ĉ���

enum SceneName {
	TITLE,
	GAME,
	RESULT,

	SCENE_MAX
};

/**
 * @brief �V�[���Ǘ��N���X
 * 
 * �^�C�g���A�Q�[���A���U���g�̂R�����Ȃ̂ō����array���g�p
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
	std::array<std::unique_ptr<IScene>, 3> scenes;
	SceneName scenename;
};

