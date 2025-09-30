//============================================================================
// 
// チュートリアル [tutorial.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "tutorial.h"
#include "sound.h"

// 入力取得用
#include "renderer.h"
#include "input.manager.h"

// シーン遷移用
#include "game.h"
#include "scene_manager.h"
#include "object.manager.h"

#include "player.h"

// ゲームに写す用
namespace
{
	// プレイヤーのポインタ
	CPlayer* m_pPlayer = nullptr;

	// プレイヤーのセットアップ
	auto fpInitialize = []() -> void
	{
		m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
	};

	// プレイヤー向け更新
	auto fpUpdate = []() -> void
	{
		D3DXVECTOR3 PosPos = m_pPlayer->GetPos();
		D3DXVECTOR3 SizeSize = m_pPlayer->GetSize();

		if (useful::MIS::MyImGuiShortcut_BeginWindow("fpUpdate", { 300, 100 }))
		{
			useful::MIS::MyImGuiShortcut_DragVector("PosPos", PosPos, 1.0f);
			useful::MIS::MyImGuiShortcut_DragVector("SizeSize", SizeSize, 1.0f);
			ImGui::End();
		}

		m_pPlayer->SetPos(PosPos);
		m_pPlayer->SetSize(SizeSize);
	};

	// プレイヤーのクリーンアップ
	auto fpFinalize = []() -> void
	{
		m_pPlayer = nullptr;
	};
}

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CTutorial::CTutorial()
	: CScene()
{}

//============================================================================
// デストラクタ
//============================================================================
CTutorial::~CTutorial()
{
	// 終了処理
	Finalize();
}

//============================================================================
// 更新処理
//============================================================================
void CTutorial::Update()
{
	CRenderer::RefInstance().AddText("スティックを傾けて回しなさい。そしてAで投げなさい。", 1);

	//fpUpdate();

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
void CTutorial::Draw()
{}

//============================================================================
// 次のシーンへ
//============================================================================
void CTutorial::Change()
{
	// 全オブジェクト解放予約
	CObjectManager::RefInstance().SetDeathAllObject();

	// サウンド by AKR TNK
	CSound::GetInstance()->Stop(CSound::LABEL::BGM_0);

	// ｹﾞｰﾑシーンへ変更
	up<CGame> upScene = CreateUniquePtr<CGame>();
	CSceneManager::RefInstance().ChangeScene(std::move(upScene));
}

//============================================================================
// 初期化処理
//============================================================================
bool CTutorial::Initialize()
{
	// サウンド by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Tutorial");

	// プレイヤーの生成
	//fpInitialize();

	return true;
}

//============================================================================
// 終了処理
//============================================================================
void CTutorial::Finalize()
{
	fpFinalize();
}