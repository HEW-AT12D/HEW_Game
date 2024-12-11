#pragma once
#include "../../Framework/Precompiled/pch.h"
#include "../../Game/Objcet/GameObject.h"

/**
 * @brief オブジェクトを管理するクラス
*/
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	/**
	 * @brief オブジェクト追加関数
	 * @tparam T オブジェクトの型
	 * @tparam ...Args 可変長引数の型
	 * @param ...args 実引数
	*/
	template <typename T,typename... Args>
	void AddObject(Args&&... args) {
		//! オブジェクト配列にテンプレート型のクラスのユニークポインタを格納
		//! →その際のコンストラクタに与える引数の型(Args)と、実引数として(args)が存在している。
		//! 　→この場合、std::forwardはTのコンストラクタに引数の型、実引数をそのまま渡すために記述されている
		objects.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	/**
	 * @brief オブジェクト削除関数
	 * @param object 削除対象オブジェクト
	*/
	void DeleteObject(GameObject* object);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	// 当たり判定も追加予定

private:
	//! オブジェクトのユニークポインタをvectorで持つ→オブジェクトマネージャーがオブジェクトを管理する
	std::vector<std::unique_ptr<GameObject>> objects;
};

