#pragma once
#include "Transform.h"
#include "../IComponent/IComponent.h"

/// <summary>
/// Transformの各数値の行列変換はTransform側で行い、TransformComponent側では各数値の変更（更新）だけを行う
/// </summary>

class TransformComponent :public IComponent
{
public:
	TransformComponent();
	~TransformComponent();

	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;


private:
	Transform m_Transform;
};

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}