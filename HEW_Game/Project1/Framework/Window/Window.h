#pragma once
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include "../../pch.h"
=======
#include "../main.h"
>>>>>>> c18ec40d02bbcc93ab399e4036a21f857ba308be
=======
#include "../Precompiled/pch.h"
>>>>>>> parent of cecf57c (調整中)
=======
#include "../Precompiled/pch.h"
>>>>>>> parent of c18ec40 (pch.hの削除とmain.hをすべてにinclude)
#include <Windows.h>

/**
 * @brief �Q�[���N���X��ێ�����E�B���h�E�N���X
 *
 * �������A�Q�[�����[�v�A�I�������A�E�B���h�E�v���V�[�W���֐����@�\�Ƃ��Ď���
*/
class Window
{
public:
	Window();
	~Window();

	bool Init(void);
	void WinMain(void);
	void Uninit(void);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


private:
	static HINSTANCE   m_hInst;        // �C���X�^���X�n���h��
	static HWND        m_hWnd;         // �E�B���h�E�n���h��
	static uint32_t    m_Width;        // �E�B���h�E�̉���
	static uint32_t    m_Height;       // �E�B���h�E�̏c��
};

Window::Window()
{
}

Window::~Window()
{
}
