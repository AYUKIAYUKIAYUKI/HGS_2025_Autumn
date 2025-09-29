//============================================================================
// 
// エントリーポイント [main.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "main.h"

// マネージャー系統
#include "window.h"
#include "renderer.h"

// アセット系統
#include "font.manager.h"
#include "texture.manager.h"
#include "X_manager.h"
#include "sound.h"

// ゲーム系統
#include "camera_manager.h"
#include "light.h"
#include "input.manager.h"
#include "scene_manager.h"

/* 油揚げ */
#include "object.manager.h"

//============================================================================
// エントリーポイント
//============================================================================
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hInstancePrev*/, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/)
{
	// CRTメモリリーク検出用
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ウィンドウの明示的な生成と初期化
	if (!CWindow::RefInstance().Initialize(hInstance))
	{
		return 0;
	}

	// ウィンドウハンドルの取得
	HWND hWnd = CWindow::RefInstance().GetWindowHandle();

	// レンダラーの明示的な生成と初期化
	if (!CRenderer::RefInstance().Initialize(hWnd, TRUE))
	{
		return 0;
	}

	// フォントマネージャーの明示的な生成
	CFontManager::RefInstance();

	// テクスチャマネージャーの明示的な生成
	CTextureManager::RefInstance();

	// Xモデルマネージャーの明示的な生成
	CX_Manager::RefInstance();

	// カメラマネージャーの明示的な生成 : 魔界
	CCamera_Manager::RefInstance();

	// インプットマネージャーの明示的な生成 : 魔界
	if (!CInputManager::RefInstance().Initialize(hInstance))
	{
		return 0;
	}

	// ライトマネージャーの明示的な生成 : 魔界
	//CLightManager::RefInstance();

	// サウンド by AKR TNK
	CSound::GetInstance()->Init(hWnd);

	// シーンマネージャーの明示的な生成 : 魔界
	CSceneManager::RefInstance();

	useful::up<CLight> upLight = std::make_unique<CLight>();

	// メッセージループ
	CWindow::CSingleton::RefInstance().MessageLoop(
		[]() -> void
		{
			// シーンの更新処理
			CSceneManager::RefInstance().GetScene()->Update();

			// レンダラーの更新処理
			CRenderer::CSingleton::RefInstance().Update_ε(
				[]() -> void
				{
					// フリーカメラの更新
					CCamera::UpdateFreeCam();

					// 選択中カメラの更新
					CCamera_Manager::RefInstance().RefSelectCamera().Update();

					CObjectManager::RefInstance().UpdateAllObject();
					CObjectManager::RefInstance().LateUpdateAllObject();
				});

			// インプットの更新処理
			CInputManager::RefInstance().Update();

			// レンダラーの描画処理
			CRenderer::CSingleton::RefInstance().Draw_ε(
				[]() -> void
				{
					CObjectManager::RefInstance().DrawAllObject();
				});
		});

	// サウンド by AKR TNK
	CSound::GetInstance()->Release();

	return 0;
}