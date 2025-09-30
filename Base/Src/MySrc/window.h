//============================================================================
// 
// ウィンドウ、ヘッダーファイル [window.h]
// Author : 福田歩希
// 
//============================================================================

#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "singleton.h"

//****************************************************
// ウィンドウクラスの定義
//****************************************************
class CWindow final : public CSingleton<CWindow>
{
	//****************************************************
	// フレンド宣言
	//****************************************************
	friend struct std::default_delete<CWindow>;
	friend CWindow& CSingleton<CWindow>::RefInstance();

	//****************************************************
	// 静的メンバ定数の定義 (非公開)
	//****************************************************

	// ウィンドウクラスの名前
	static constexpr const char* s_pClassName = "Window Class";

	// ウィンドウの名前
	static constexpr const char* s_pWindowName = "Base";

public:

	//****************************************************
	// 静的メンバ変数の定義 (公開)
	//****************************************************

	// ウィンドウ横幅
	static const WORD  WWINDOW_WIDTH;
	static const float FWINDOW_WIDTH;

	// ウィンドウ縦幅
	static const WORD  WWINDOW_HEIGHT;
	static const float FWINDOW_HEIGHT;

	//****************************************************
	// function
	//****************************************************

	// 初期化処理
	bool Initialize(HINSTANCE hInstance);
	bool Initialize() { return true; }

	// 終了処理
	void Finalize();

	// メッセージループ
	// fp -> 更新処理
	template <typename T>
	void MessageLoop(T&& fpMainLoop);

	//****************************************************
	// inline function
	//***************************************************

	// クライアント領域のサイズの取得
	inline RECT GetWindowRect() const { return m_Rect; }

	// ウィンドウハンドルの取得
	inline HWND GetWindowHandle() const { return m_hWnd; }

private:

	//****************************************************
	// special function
	//****************************************************
	CWindow();           // デフォルトコンストラクタ
	~CWindow() override; // デストラクタ

	//****************************************************
	// function
	//****************************************************
	void InitializeWindowClass(HINSTANCE hInstance); // ウィンドウクラスの初期化処理
	void InitializeWindowRect();					 // クライアント領域の初期化処理
	void MyCreateWindow(HINSTANCE hInstance);		 // ウィンドウの生成
	
	void ChangeMode(); // モード変更

	// ウインドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//****************************************************
	// data
	//****************************************************
	WNDCLASSEX m_Wcex;	  // ウィンドウクラス
	RECT	   m_Rect;	  // クライアント領域のサイズ
	DWORD	   m_dwStyle; // ウィンドウの表示スタイル
	HWND	   m_hWnd;	  // ウィンドウハンドル
	MSG		   m_Msg;	  // メッセージを格納する変数
};

//============================================================================
// メッセージループ
//============================================================================
template <typename T>
void CWindow::MessageLoop(T&& fpMainLoop)
{
	// FPS計測用
	int   nCountFPS = 0;					// 現在のFPS
	DWORD dwCurrentTime = 0;				// 現在時刻用
	DWORD dwFrameCount = 0;					// 最後に処理した時間
	DWORD dwExecLastTime = timeGetTime();	// フレームカウント格納
	DWORD dwFPSLastTime = timeGetTime();	// 最後にFPSを計測した時刻格納

	while (true)
	{
		// メッセージを確認
		if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUITのメッセージを受け取ると、メッセージループを抜ける
			if (m_Msg.message == WM_QUIT)
			{
				break;
			}

			// メッセージの設定
			TranslateMessage(&m_Msg); // 仮想キーメッセージを文字メッセージへ変換
			DispatchMessage(&m_Msg);  // ウィンドウプロシージャへメッセージを送出
		}
		else
		{
			// 現在時刻を取得
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				// FPSを計測
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				// FPSを計測した時間を保存
				dwFPSLastTime = dwCurrentTime;

				// フレームカウントをクリア
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				// 現在時刻を保存
				dwExecLastTime = dwCurrentTime;

				fpMainLoop();

				// フレームカウントを加算
				++dwFrameCount;
			}
		}
	}
}