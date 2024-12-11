#include "../../Framework/Precompiled/pch.h"
#include "Game.h"

void Game::Init(HWND hWnd)
{
	d3d11.Init(hWnd);                 // DirectX��������
	player.Init(L"asset/char01.png", 3, 4); //�v���C���[��������
	player.SetPos(100.0f, 0.0f, 0.0f);     //�ʒu��ݒ�
	player.SetSize(200.0f, 300.0f, 0.0f);  //�傫����ݒ�
	player.SetAngle(0.0f);                 //�p�x��ݒ�
	player.SetColor(1.0f, 1.0f, 1.0f, 0.5f);                 //�p�x��ݒ�

	background.Init(L"asset/back_img_01.png");   //�w�i��������
	background.SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	background.SetSize(640.0f, 480.0f, 0.0f); //�傫����ݒ�
	background.SetAngle(0.0f);                //�p�x��ݒ�

}

void Game::Update(void)
{
	input.Update();

	//�v���C���[�̃A�j���[�V����
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

	// I�L�[�Ńt���X�N���[����
	if (input.GetKeyTrigger(VK_I)) {
		
		
		
		
		d3d11.GetSwapChain()->SetFullscreenState(TRUE, NULL);
	}
	// K�L�[�Ńt���X�N���[������
	if (input.GetKeyTrigger(VK_K)) {
		d3d11.GetSwapChain()->SetFullscreenState(FALSE, NULL);
	}

	player.SetPos(pos.x, pos.y, pos.z);

}

void Game::Draw(void)
{
	d3d11.StartRender();	// �`��J�n
	background.Draw();		// �w�i��`��
	player.Draw();			// �v���C���[��`��
	d3d11.FinishRender();	// �`��I��
}

void Game::Uninit(void)
{
	player.Uninit();		// �v���C���[���I��
	background.Uninit();	// �v���C���[���I��
	d3d11.Release();		// DirectX���I��
}
