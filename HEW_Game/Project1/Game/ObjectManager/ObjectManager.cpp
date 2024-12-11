#include "ObjectManager.h"

ObjectManager::ObjectManager() {

}

ObjectManager::~ObjectManager() {

}

/**
 * @brief オブジェクト削除関数
 *
 * このゲームでは球は最後に追加されるオブジェクトなのでpop_backを使う
 * @param object オブジェクト配列
*/
void ObjectManager::DeleteObject(GameObject* object) {
	//! オブジェクト配列が空でなければ
	if (!this->objects.empty()) {
		//! 最後の要素を削除
		this->objects.pop_back();
	}
}

void ObjectManager::Init(void) {
	
}

void ObjectManager::Update(void) {
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
		//! スクリーン内から出たらオブジェクトを削除
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
