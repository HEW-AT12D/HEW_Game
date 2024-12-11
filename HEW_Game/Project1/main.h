#pragma once
// プリコンパイルヘッダー一覧
#include <windows.h>
#include <memory>
#include <vector>
#include <DirectXMath.h>	// DirextXの数学関連のヘッダーファイル
#include <SimpleMath.h>
#include <stdlib.h>
#include <d3d11.h>			// DirectX11を使うためのヘッダーファイル


// DirectX::を省略したい
using namespace DirectX;

constexpr uint32_t SCREEN_WIDTH = 1280;
constexpr uint32_t SCREEN_HEIGHT = 720;