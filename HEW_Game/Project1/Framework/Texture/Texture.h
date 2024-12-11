#pragma once
#include "../D3D11/D3D11.h"
#include "../Component/Transform/Transform.h"
#include "../WICTextureLoader/WICTextureLoader.h"


/**
 * Texture�N���X
 * 
 * �E�摜�̓ǂݍ���
 * �E�`��
 * �E���
 * ���s��
 * 
 * @brief 
 * ���v�f��
 * �摜�������Auv���W�A���_���W�A���_�o�b�t�@�A�e�N�X�`���ϐ��A�g�����X�t�H�[��
 * ���@�\��
 * �摜�̓ǂݍ��݁A�`��A�摜�̉���A�F�̐ݒ�
 * 
 * �A�j���[�V�����ǂ�������
 * �������_���[�N���X�����Ȃ�`��@�\�͊��S�Ƀ����_���[�Ɉˑ������āA�����_���[����A�j���[�V�������Ăяo���A�Ƃ��ɂ���ׂ�
 */
class Texture
{
protected:
	//! �g�����X�t�H�[��
	Transform transform;
	//! �摜������
	XMFLOAT2 split;
	//! �摜�ԍ�
	XMFLOAT2 uv;
	//! ���_���W
	Vertex vertexList[4] =
	{
		//   x     y    z       r    g    b    a     u    v
		{ -0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f},  // 0�Ԗڂ̒��_���W
		{  0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f},  // 1�Ԗڂ̒��_���W
		{ -0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f},  // 2�Ԗڂ̒��_���W
		{  0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f},  // 3�Ԗڂ̒��_���W
	};

	//! ���_�o�b�t�@
	ID3D11Buffer* m_pVertexBuffer;
	//! �e�N�X�`���p�ϐ�
	ID3D11ShaderResourceView* m_pTextureView;

private:
	//bool Load(const wchar_t* _Filename);				//! �摜�̓ǂݍ��݁i���ʂ�Ԃ��j
	//! �������i�摜�t�@�C���p�X�A�摜�������A�g�����X�t�H�[���Auv���W(�摜�ԍ�)�j
	void Init(const wchar_t* _Filename, Transform _Transform, XMFLOAT2 _Split, XMFLOAT2 _Splitnum);
	void Draw();				//! �`��
	void Uninit();				//! �I��
};