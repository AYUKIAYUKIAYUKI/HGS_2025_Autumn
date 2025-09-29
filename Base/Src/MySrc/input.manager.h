//============================================================================
// 
// マネージャー、ヘッダファイル [managaer.h]
// Author : 福田歩希
// 
//============================================================================

// インクルードガード
#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "singleton.h"

#include "input_keyboard.h"
#include "input_mouse.h"
#include "input_pad.h"

//****************************************************
// マネージャークラスを定義
//****************************************************
class CInputManager final : public CSingleton<CInputManager>
{
	//****************************************************
	// フレンド宣言
	//****************************************************
	friend struct std::default_delete<CInputManager>;
	friend CInputManager& CSingleton<CInputManager>::RefInstance();

public:

	//****************************************************
	// function
	//****************************************************
	
	//
	bool Initialize(HINSTANCE hi);
	bool Initialize() { return true; }
	void Finalize();

	/**
	 * メインとなる更新処理です
	 */
	void Update();

	CInputKeyboard* GetKeyboard() const;	// キーボード
	CInputMouse*	GetMouse()	  const;	// マウス
	CInputPad*		GetPad()	  const;	// パッド

private:

	//****************************************************
	// special function
	//****************************************************
	CInputManager();				// デフォルトコンストラクタ
	~CInputManager() override;	// デストラクタ

	//****************************************************
	// function
	//****************************************************

	std::unique_ptr<CInputKeyboard>	m_upKeyboard;	// キーボード
	std::unique_ptr<CInputMouse>	m_upMouse;		// マウス
	std::unique_ptr<CInputPad>		m_upPad;		// パッド
};