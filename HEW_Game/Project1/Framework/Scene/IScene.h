#pragma once
#include "../../Framework/Precompiled/pch.h"

//! -----------�݌v�����FIScene���������̘b-----------------
//! �V�[���N���X�̓e���v���[�g�ɂ��āA���N���X�Ƃ���IScene���������Ƃ��ׂ�����Ȃ��H�H

/**
 * @brief �V�[���̒��ۃN���X
 *
 * �S�ẴV�[����������p������̂Ń|�����[�t�B�Y���ŃV�[�����Ǘ��ł���
 * 
 * �����ɃI�u�W�F�N�g�}�l�[�W���u���Ƃ��ׂ��H
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
