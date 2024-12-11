#include "../Precompiled/pch.h"
#include "Window.h"

// �萔��`
const auto ClassName = TEXT("HEW2D");			//!< �E�B���h�E�N���X��.
const auto WindowName = TEXT("���Ƃ߂�p���b�g");	//!< �E�B���h�E��.


/**
 * @brief �E�B���h�E�̏�����
 *
 * �E�B���h�E�̓o�^�ƍ쐬"����"���s��
 *
 * @param
*/
bool Window::Init(void) {
	//! �E�B���h�E�̏�����
	// �C���X�^���X�n���h�����擾.
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr)
	{
		return false;
	}

	// �E�B���h�E�̐ݒ�.
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

	// �E�B���h�E�̓o�^.
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	// �C���X�^���X�n���h���ݒ�.
	m_hInst = hInst;

	// �E�B���h�E�̃T�C�Y��ݒ�.
	RECT rc = {};
	rc.right = static_cast<LONG>(m_Width);
	rc.bottom = static_cast<LONG>(m_Height);

	// �E�B���h�E�T�C�Y�𒲐�.
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// �E�B���h�E�𐶐�.
	m_hWnd = CreateWindowEx(
		0,
		//        WS_EX_TOPMOST,
		ClassName,				// �g���E�B���h�E�X�^�C��
		WindowName,				// �E�B���h�E�̖��O
		style,					// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,			// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,			// �E�B���h�E�̍���x���W 
		rc.right - rc.left,		// �E�B���h�E�̕�
		rc.bottom - rc.top,		// �E�B���h�E�̍���
		nullptr,				// �e�E�B���h�E�̃n���h��
		nullptr,				// ���j���[�n���h���܂��͎q�E�B���h�EID
		m_hInst,				// �C���X�^���X�n���h��
		nullptr);				// �E�B���h�E�쐬�f�[�^


	if (m_hWnd == nullptr)
	{
		return false;
	}

	// �E�B���h�E��\��.
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// �E�B���h�E���X�V.
	UpdateWindow(m_hWnd);

	// �E�B���h�E�Ƀt�H�[�J�X��ݒ�.
	SetFocus(m_hWnd);
}


//-----------------------------------------------------------------------------
// ���C�����[�v
//-----------------------------------------------------------------------------
void Window::WinMain(void) {


	MSG msg = {};

	//! ������

	//// �t�B�[���h(�e�X�g�I�u�W�F�N�g)
	//
	////TestPlane plane;
	////TestCube cube;
	////TestModel model;
	////GolfBall ball;

	//// �I�u�W�F�N�g�z��쐬
	//std::vector<std::unique_ptr<Object>> Objects;
	////Objects.emplace_back(new TestCube);
	////Objects.emplace_back(new TestModel);
	//Objects.emplace_back(new GolfBall);
	//Objects.emplace_back(new Ground);

	//// �J�����i�I�u�W�F�N�g�̂O�Ԗڂ�GolfBall*�Ƀ_�E���L���X�g�j
	//GolfBall* ball = dynamic_cast<GolfBall*>(Objects[0].get());
	//Camera camera(*ball);

	//// ���͏���
	//Input input;

	//// �`�揉����
	//Renderer::Init();

	//// �J����������
	//camera.Init();


	//// �I�u�W�F�N�g������
	//for (auto& o : Objects) {
	//	o->Init();
	//}

	//ball->SetGround(dynamic_cast<Ground*>(Objects[1].get()));

	// FPS�v���p�ϐ�
	int fpsCounter = 0;
	long long oldTick = GetTickCount64(); // �O��v�����̎���
	long long nowTick = oldTick; // ����v�����̎���

	// FPS�Œ�p�ϐ�
	LARGE_INTEGER liWork; // work�����ϐ��͍�Ɨp�ϐ�
	long long frequency;// �ǂꂭ�炢�ׂ������Ԃ��J�E���g�ł��邩
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;
	// ���ԁi�P�ʁF�J�E���g�j�擾
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;// �O��v�����̎���
	long long nowCount = oldCount;// ����v�����̎���


	// �Q�[�����[�v
	while (1)
	{
		// �V���Ƀ��b�Z�[�W�������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// �uWM_QUIT�v���b�Z�[�W���󂯎�����烋�[�v�𔲂���
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			QueryPerformanceCounter(&liWork);// ���ݎ��Ԃ��擾
			nowCount = liWork.QuadPart;
			// 1/60�b���o�߂������H
			if (nowCount >= oldCount + frequency / 60) {



				// �Q�[���������s

				//! �X�V


				//// �J�����X�V
				//camera.Update();

				//// ���͏����X�V
				//input.Update();


				//// �I�u�W�F�N�g�X�V
				//for (auto& o : Objects) {
				//	o->Update();
				//}

				//// �`��O����
				//Renderer::Begin();

				//! �`��


				//// �J�����Z�b�g
				//camera.Draw();


				//// �I�u�W�F�N�g�`��
				//for (auto& o : Objects) {
				//	o->Draw();
				//}

				//// �`��㏈��
				//Renderer::End();

				fpsCounter++; // �Q�[�����������s������{�P����
				oldCount = nowCount;
			}


		}
	}
	//! �I������
	//Game::Uninit();
}


//-----------------------------------------------------------------------------
// �E�B���h�E�̏I������
//-----------------------------------------------------------------------------
void Window::Uninit(void) {
	// �E�B���h�E�̓o�^������.
	if (m_hInst != nullptr)
	{
		UnregisterClass(ClassName, m_hInst);
	}

	m_hInst = nullptr;
	m_hWnd = nullptr;
}


//--------------------------------------------------------------------------------------
//�E�B���h�E�v���V�[�W���i�v���V�[�W�� = �葱���j
//--------------------------------------------------------------------------------------
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ��ԊǗ��p�ϐ�
	static bool isFullScreen = false;
	static bool isMessageBoxShowed = false;

	switch (uMsg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �uWM_QUIT�v���b�Z�[�W�𑗂�@���@�A�v���I��
		break;
	case WM_CLOSE:  // �ux�v�{�^���������ꂽ��
	{
		// ���b�Z�[�W�{�b�N�\�����ɂ��������s�����̂ł����ɓ���\��������
		isMessageBoxShowed = true;
		int res = MessageBoxA(NULL, "�I�����܂����H", "�m�F", MB_OKCANCEL);
		isMessageBoxShowed = false;
		if (res == IDOK) {
			DestroyWindow(hWnd);  // �uWM_DESTROY�v���b�Z�[�W�𑗂�
		}
	}
	break;
	case WM_KEYDOWN: //�L�[���͂����������b�Z�[�W
		if (LOWORD(wParam) == VK_ESCAPE) { //���͂��ꂽ�L�[��ESCAPE�Ȃ�
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);//�uWM_CLOSE�v�𑗂�
		}
		else if (LOWORD(wParam) == VK_F11) {
			// F11�L�[�Ńt���X�N���[���ɐ؂�ւ�
			isFullScreen = !isFullScreen;
			if (isFullScreen) {
				// �^���t���X�N���[�����[�h�ɕύX
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);	// �E�B���h�E�g���폜
				// �f�B�X�v���C�𑜓x���擾
				int	screenWidth = GetSystemMetrics(SM_CXSCREEN);
				int screenHeight = GetSystemMetrics(SM_CYSCREEN);
				// �E�B���h�E�T�C�Y��ς���
				SetWindowPos(hWnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
			else {
				// �ʏ�E�B���h�E�ɖ߂�
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);			// �E�B���h�E�g���폜
				SetWindowPos(hWnd, HWND_TOP, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
		}
		else {

		}
		break;
	case WM_ACTIVATE:
		if (wParam == WA_INACTIVE) {
			// �t���X�N���[���\�������b�Z�[�W�{�b�N�X��\���̂Ƃ�
			if (isFullScreen && !isMessageBoxShowed) {
				// �E�B���h�E���ŏ�������i�^�X�N�؂�ւ����ɔw��Ɏc����΍�j
				ShowWindow(hWnd, SW_MINIMIZE);
			}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);	// �W�����������s�����邽��
		break;
	default:
		// �󂯎�������b�Z�[�W�ɑ΂��ăf�t�H���g�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}