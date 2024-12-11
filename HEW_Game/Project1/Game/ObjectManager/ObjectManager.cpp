#include "ObjectManager.h"

ObjectManager::ObjectManager() {

}

ObjectManager::~ObjectManager() {

}

/**
 * @brief �I�u�W�F�N�g�폜�֐�
 *
 * ���̃Q�[���ł͋��͍Ō�ɒǉ������I�u�W�F�N�g�Ȃ̂�pop_back���g��
 * @param object �I�u�W�F�N�g�z��
*/
void ObjectManager::DeleteObject(GameObject* object) {
	//! �I�u�W�F�N�g�z�񂪋�łȂ����
	if (!this->objects.empty()) {
		//! �Ō�̗v�f���폜
		this->objects.pop_back();
	}
}

void ObjectManager::Init(void) {
	
}

void ObjectManager::Update(void) {
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
		//! �X�N���[��������o����I�u�W�F�N�g���폜
		if (objects[i]->GetPos().x > SCREEN_WIDTH / 2 || objects[i]->GetPos().x < 0 - SCREEN_WIDTH / 2 ||
			objects[i]->GetPos().y > SCREEN_HEIGHT / 2 || objects[i]->GetPos().y < 0 - SCREEN_HEIGHT / 2) {
			this->DeleteObject(objects[i].get());
		}
	}
	
}

void ObjectManager::Draw(void) {
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}
}

void ObjectManager::Uninit(void) {
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Uninit();
	}
}
