//============================================================================
// 
// マネージャー [manager.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "input.manager.h"
#include "window.h"

//****************************************************
// 無名名前空間を定義 
//****************************************************
namespace
{
	/* この名前空間を削除してください */

	// 引数付き初期化
	template <typename T> std::unique_ptr<T> DedicatedInitialize(HINSTANCE hInstance, HWND hWnd)
	{
		useful::up<T> upInstance = std::make_unique<T>();

		if (!upInstance)
		{
			return nullptr;
		}

		if (FAILED(upInstance->Init(hInstance, hWnd)))
		{
			return nullptr;
		}

		return upInstance;
	}

	// 引数付き解放
	template <typename T> void DedicatedRelease(T* pInstance)
	{
		if (pInstance)
		{
			pInstance->Uninit();
		}
	}
};

//============================================================================
// 更新処理
//============================================================================
void CInputManager::Update()
{
	// キーボードの更新
	m_upKeyboard->Update();

	// マウスの更新
	m_upMouse->Update();

	// パッドの更新
	m_upPad->Update();
}

//============================================================================
// キーボードの取得
//============================================================================
CInputKeyboard* CInputManager::GetKeyboard() const
{
	return m_upKeyboard.get();
}

//============================================================================
// マウスの取得
//============================================================================
CInputMouse* CInputManager::GetMouse() const
{
	return m_upMouse.get();
}

//============================================================================
// パッドの取得
//============================================================================
CInputPad* CInputManager::GetPad() const
{
	return m_upPad.get();
}

// コンストラクタ
//============================================================================
CInputManager::CInputManager() :
	m_upKeyboard(nullptr),
	m_upMouse(nullptr),
	m_upPad(nullptr)
{}

//============================================================================
// デストラクタ
//============================================================================
CInputManager::~CInputManager()
{
	// 終了処理
	Finalize();
}

//============================================================================
// 初期化処理
//============================================================================
bool CInputManager::Initialize(HINSTANCE hInstance)
{
	HWND hWnd = CWindow::RefInstance().GetWindowHandle();

	// キーボードの生成
	m_upKeyboard = DedicatedInitialize<CInputKeyboard>(hInstance, hWnd);

	// マウスの生成
	m_upMouse = DedicatedInitialize<CInputMouse>(hInstance, hWnd);

	// パッドの生成
	m_upPad = DedicatedInitialize<CInputPad>(hInstance, hWnd);

	return true;
}

// 終了処理
//============================================================================
void CInputManager::Finalize()
{
	// パッドの終了処理
	DedicatedRelease<CInputPad>(m_upPad.get());

	// マウスの終了処理
	DedicatedRelease<CInputMouse>(m_upMouse.get());

	// キーボードの終了処理
	DedicatedRelease<CInputKeyboard>(m_upKeyboard.get());
}