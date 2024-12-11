#include "../Precompiled/pch.h"
#include "Window.h"

// 定数定義
const auto ClassName = TEXT("HEW2D");			//!< ウィンドウクラス名.
const auto WindowName = TEXT("おとめるパレット");	//!< ウィンドウ名.


/**
 * @brief ウィンドウの初期化
 *
 * ウィンドウの登録と作成"だけ"を行う
 *
 * @param
*/
bool Window::Init(void) {
	//! ウィンドウの初期化
	// インスタンスハンドルを取得.
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr)
	{
		return false;
	}

	// ウィンドウの設定.
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	// ウィンドウの登録.
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	// インスタンスハンドル設定.
	m_hInst = hInst;

	// ウィンドウのサイズを設定.
	RECT rc = {};
	rc.right = static_cast<LONG>(m_Width);
	rc.bottom = static_cast<LONG>(m_Height);

	// ウィンドウサイズを調整.
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// ウィンドウを生成.
	m_hWnd = CreateWindowEx(
		0,
		//        WS_EX_TOPMOST,
		ClassName,				// 拡張ウィンドウスタイル
		WindowName,				// ウィンドウの名前
		style,					// ウィンドウスタイル
		CW_USEDEFAULT,			// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,			// ウィンドウの左上Ｙ座標 
		rc.right - rc.left,		// ウィンドウの幅
		rc.bottom - rc.top,		// ウィンドウの高さ
		nullptr,				// 親ウィンドウのハンドル
		nullptr,				// メニューハンドルまたは子ウィンドウID
		m_hInst,				// インスタンスハンドル
		nullptr);				// ウィンドウ作成データ


	if (m_hWnd == nullptr)
	{
		return false;
	}

	// ウィンドウを表示.
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// ウィンドウを更新.
	UpdateWindow(m_hWnd);

	// ウィンドウにフォーカスを設定.
	SetFocus(m_hWnd);
}


//-----------------------------------------------------------------------------
// メインループ
//-----------------------------------------------------------------------------
void Window::WinMain(void) {


	MSG msg = {};

	//! 初期化

	//// フィールド(テストオブジェクト)
	//
	////TestPlane plane;
	////TestCube cube;
	////TestModel model;
	////GolfBall ball;

	//// オブジェクト配列作成
	//std::vector<std::unique_ptr<Object>> Objects;
	////Objects.emplace_back(new TestCube);
	////Objects.emplace_back(new TestModel);
	//Objects.emplace_back(new GolfBall);
	//Objects.emplace_back(new Ground);

	//// カメラ（オブジェクトの０番目をGolfBall*にダウンキャスト）
	//GolfBall* ball = dynamic_cast<GolfBall*>(Objects[0].get());
	//Camera camera(*ball);

	//// 入力処理
	//Input input;

	//// 描画初期化
	//Renderer::Init();

	//// カメラ初期化
	//camera.Init();


	//// オブジェクト初期化
	//for (auto& o : Objects) {
	//	o->Init();
	//}

	//ball->SetGround(dynamic_cast<Ground*>(Objects[1].get()));

	// FPS計測用変数
	int fpsCounter = 0;
	long long oldTick = GetTickCount64(); // 前回計測時の時間
	long long nowTick = oldTick; // 今回計測時の時間

	// FPS固定用変数
	LARGE_INTEGER liWork; // workがつく変数は作業用変数
	long long frequency;// どれくらい細かく時間をカウントできるか
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;
	// 時間（単位：カウント）取得
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;// 前回計測時の時間
	long long nowCount = oldCount;// 今回計測時の時間


	// ゲームループ
	while (1)
	{
		// 新たにメッセージがあれば
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ウィンドウプロシージャにメッセージを送る
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// 「WM_QUIT」メッセージを受け取ったらループを抜ける
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			QueryPerformanceCounter(&liWork);// 現在時間を取得
			nowCount = liWork.QuadPart;
			// 1/60秒が経過したか？
			if (nowCount >= oldCount + frequency / 60) {



				// ゲーム処理実行

				//! 更新


				//// カメラ更新
				//camera.Update();

				//// 入力処理更新
				//input.Update();


				//// オブジェクト更新
				//for (auto& o : Objects) {
				//	o->Update();
				//}

				//// 描画前処理
				//Renderer::Begin();

				//! 描画


				//// カメラセット
				//camera.Draw();


				//// オブジェクト描画
				//for (auto& o : Objects) {
				//	o->Draw();
				//}

				//// 描画後処理
				//Renderer::End();

				fpsCounter++; // ゲーム処理を実行したら＋１する
				oldCount = nowCount;
			}


		}
	}
	//! 終了処理
	//Game::Uninit();
}


//-----------------------------------------------------------------------------
// ウィンドウの終了処理
//-----------------------------------------------------------------------------
void Window::Uninit(void) {
	// ウィンドウの登録を解除.
	if (m_hInst != nullptr)
	{
		UnregisterClass(ClassName, m_hInst);
	}

	m_hInst = nullptr;
	m_hWnd = nullptr;
}


//--------------------------------------------------------------------------------------
//ウィンドウプロシージャ（プロシージャ = 手続き）
//--------------------------------------------------------------------------------------
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 状態管理用変数
	static bool isFullScreen = false;
	static bool isMessageBoxShowed = false;

	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// 「WM_QUIT」メッセージを送る　→　アプリ終了
		break;
	case WM_CLOSE:  // 「x」ボタンが押されたら
	{
		// メッセージボック表示中にも同時実行されるのでここに入る可能性がある
		isMessageBoxShowed = true;
		int res = MessageBoxA(NULL, "終了しますか？", "確認", MB_OKCANCEL);
		isMessageBoxShowed = false;
		if (res == IDOK) {
			DestroyWindow(hWnd);  // 「WM_DESTROY」メッセージを送る
		}
	}
	break;
	case WM_KEYDOWN: //キー入力があったメッセージ
		if (LOWORD(wParam) == VK_ESCAPE) { //入力されたキーがESCAPEなら
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);//「WM_CLOSE」を送る
		}
		else if (LOWORD(wParam) == VK_F11) {
			// F11キーでフルスクリーンに切り替え
			isFullScreen = !isFullScreen;
			if (isFullScreen) {
				// 疑似フルスクリーンモードに変更
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);	// ウィンドウ枠を削除
				// ディスプレイ解像度を取得
				int	screenWidth = GetSystemMetrics(SM_CXSCREEN);
				int screenHeight = GetSystemMetrics(SM_CYSCREEN);
				// ウィンドウサイズを変える
				SetWindowPos(hWnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
			else {
				// 通常ウィンドウに戻す
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);			// ウィンドウ枠を削除
				SetWindowPos(hWnd, HWND_TOP, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
		}
		else {

		}
		break;
	case WM_ACTIVATE:
		if (wParam == WA_INACTIVE) {
			// フルスクリーン表示かつメッセージボックス非表示のとき
			if (isFullScreen && !isMessageBoxShowed) {
				// ウィンドウを最小化する（タスク切り替え時に背後に残る問題対策）
				ShowWindow(hWnd, SW_MINIMIZE);
			}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 標準挙動を実行させるため
		break;
	default:
		// 受け取ったメッセージに対してデフォルトの処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}