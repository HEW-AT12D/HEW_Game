#pragma once
#include "../../Game/Objcet/GameObject.h"
#include "../../Framework/Input/input.h"
#include "../../Framework/D3D11/D3D11.h"
#include "../../Framework/SceneManager/SceneManager.h"

class Game {
private:
	SceneManager scenemanager;	// �V�[���Ǘ��N���X
	D3D11 d3d11;				// DirectX11�Ǘ��N���X
	Input input;				// ���͊Ǘ��N���X
	
	GameObject player;		// �v���C���[�I�u�W�F�N�g
	GameObject background;	// �w�i�I�u�W�F�N�g
	

public:
	void Init(HWND hWnd); // ������
	void Update(void);    // �X�V
	void Draw();          // �`��
	void Uninit();        // �I��
};
