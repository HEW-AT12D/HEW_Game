#pragma once
#include "../../../pch.h"
#include "../../../Game/Objcet/GameObject.h"

/// <summary>
/// �S�ẴR���|�[�l���g�̌��ƂȂ�N���X
/// �R���|�[�l���g�͂�����A�^�b�`�i�����j����I�u�W�F�N�g������̂Ń����o�ϐ��Ƃ���GameObjcet�N���X�̃|�C���^������
/// ������ɂ���ăR���|�[�l���g����A�^�b�`���Ă���I�u�W�F�N�g�ɃA�N�Z�X���邱�Ƃ��ł���
/// </summary>

class IComponent
{
public:
	IComponent();
	virtual ~IComponent();

	virtual void Init(void) = 0;		// ������
	virtual void Update(void) = 0;		// �X�V
	virtual void Uninit(void) = 0;		// �I��

	void SetOwner(GameObject& _obj);	// �I�u�W�F�N�g�̃A�^�b�`(�Q�Ɠn��)
	GameObject* GetOwner(void);			// �A�^�b�`��̃I�u�W�F�N�g�̎擾
	//void RemoveOwner(void);			// �A�^�b�`����Ă���I�u�W�F�N�g����̎��O��

protected:
	GameObject* m_pOwner;				// �A�^�b�`����Ă���I�u�W�F�N�g�̃|�C���^(�P��Ȃ̂�unique_ptr�H)
};



