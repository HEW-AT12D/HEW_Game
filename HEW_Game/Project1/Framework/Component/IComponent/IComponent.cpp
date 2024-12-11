#include "../../../pch.h"
#include "IComponent.h"

// �R���X�g���N�^
IComponent::IComponent()
{
	m_pOwner = nullptr;
}

// �f�X�g���N�^ 
IComponent::~IComponent()
{
}

// �I�u�W�F�N�g�̃A�^�b�`(�����F�I�u�W�F�N�g(�Q��))
void IComponent::SetOwner(GameObject& _obj) {
	// �Q�Ƃ����I�u�W�F�N�g�̃A�h���X��&�ő��
	m_pOwner = &_obj;
}

// �A�^�b�`��̃I�u�W�F�N�g�̎擾
GameObject* IComponent::GetOwner(void) {
	return m_pOwner;
}

