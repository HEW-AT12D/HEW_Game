#pragma once
#include "Transform.h"
#include "../IComponent/IComponent.h"

/// <summary>
/// Transform�̊e���l�̍s��ϊ���Transform���ōs���ATransformComponent���ł͊e���l�̕ύX�i�X�V�j�������s��
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