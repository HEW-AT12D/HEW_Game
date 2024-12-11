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
>>>>>>> parent of cecf57c (隱ｿ謨ｴ荳ｭ)
=======
#include "../Precompiled/pch.h"
>>>>>>> parent of c18ec40 (pch.h縺ｮ蜑企勁縺ｨmain.h繧偵☆縺ｹ縺ｦ縺ｫinclude)
#include <Windows.h>

/**
 * @brief ゲームクラスを保持するウィンドウクラス
 *
 * 初期化、ゲームループ、終了処理、ウィンドウプロシージャ関数を機能として持つ
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
	static HINSTANCE   m_hInst;        // インスタンスハンドル
	static HWND        m_hWnd;         // ウィンドウハンドル
	static uint32_t    m_Width;        // ウィンドウの横幅
	static uint32_t    m_Height;       // ウィンドウの縦幅
};

Window::Window()
{
}

Window::~Window()
{
}
