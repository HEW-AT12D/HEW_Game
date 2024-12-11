#pragma once
#include "../../Framework/Precompiled/pch.h"

//! -----------設計メモ：ISceneを作った後の話-----------------
//! シーンクラスはテンプレートにして、基底クラスとしてISceneを持たせとくべきじゃない？？

/**
 * @brief シーンの抽象クラス
 *
 * 全てのシーンがこれを継承するのでポリモーフィズムでシーンを管理できる
 * 
 * ここにオブジェクトマネージャ置いとくべき？
 */
class IScene
{
public:
	IScene();
	virtual ~IScene();

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Uninit(void) = 0;

private:

};
