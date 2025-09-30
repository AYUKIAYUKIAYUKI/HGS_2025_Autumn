//============================================================================
// 
// リザルト [result.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "result.h"
#include "sound.h"

// 入力取得用
#include "renderer.h"
#include "input.manager.h"

// シーン遷移用
#include "title.h"
#include "scene_manager.h"
#include "object.manager.h"

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CResult::CResult()
	: CScene()
{
}

//============================================================================
// デストラクタ
//============================================================================
CResult::~CResult()
{
	// 終了処理
	Finalize();
}

//============================================================================
// 更新処理
//============================================================================
void CResult::Update()
{
#ifdef _DEBUG
	CRenderer::RefInstance().AddText("お前は成功したよ", 1);
#endif // _DEBUG

	// 次のシーンへ遷移
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::START) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
	{
		Change();
	}
}

//============================================================================
// 描画処理
//============================================================================
void CResult::Draw()
{
}

//============================================================================
// 次のシーンへ
//============================================================================
void CResult::Change()
{
	// 全オブジェクト解放予約
	CObjectManager::RefInstance().SetDeathAllObject();

	// サウンド by AKR TNK
	CSound::GetInstance()->Stop(CSound::LABEL::BGM_0);

	// nuigujvhjbijjidojrgdシーンへ変更
	up<CTitle> upScene = CreateUniquePtr<CTitle>();
	CSceneManager::RefInstance().ChangeScene(std::move(upScene));
}

//============================================================================
// 初期化処理
//============================================================================
bool CResult::Initialize()
{
	// サウンド by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Result");

	return true;
}

//============================================================================
// 終了処理
//============================================================================
void CResult::Finalize()
{
}