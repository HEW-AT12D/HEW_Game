#pragma once
#include "../../Framework/Precompiled/pch.h"
#include "../../Game/Objcet/GameObject.h"

/**
 * @brief �I�u�W�F�N�g���Ǘ�����N���X
*/
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	/**
	 * @brief �I�u�W�F�N�g�ǉ��֐�
	 * @tparam T �I�u�W�F�N�g�̌^
	 * @tparam ...Args �ϒ������̌^
	 * @param ...args ������
	*/
	template <typename T,typename... Args>
	void AddObject(Args&&... args) {
		//! �I�u�W�F�N�g�z��Ƀe���v���[�g�^�̃N���X�̃��j�[�N�|�C���^���i�[
		//! �����̍ۂ̃R���X�g���N�^�ɗ^��������̌^(Args)�ƁA�������Ƃ���(args)�����݂��Ă���B
		//! �@�����̏ꍇ�Astd::forward��T�̃R���X�g���N�^�Ɉ����̌^�A�����������̂܂ܓn�����߂ɋL�q����Ă���
		objects.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	/**
	 * @brief �I�u�W�F�N�g�폜�֐�
	 * @param object �폜�ΏۃI�u�W�F�N�g
	*/
	void DeleteObject(GameObject* object);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	// �����蔻����ǉ��\��

private:
	//! �I�u�W�F�N�g�̃��j�[�N�|�C���^��vector�Ŏ����I�u�W�F�N�g�}�l�[�W���[���I�u�W�F�N�g���Ǘ�����
	std::vector<std::unique_ptr<GameObject>> objects;
};

