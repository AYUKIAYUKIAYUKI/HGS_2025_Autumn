//============================================================================
// 
// ゲーム [game.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "game.h"
#include "sound.h"

// 入力取得用
#include "renderer.h"
#include "input.manager.h"

// シーン遷移用
#include "result.h"
#include "scene_manager.h"
#include "object.manager.h"

#include "object.text.h"
#include "planet.h"
#include "goal.h"
#include"player.h"
#include"GameBg.h"

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CGame::CGame()
	: CScene()
{
}

//============================================================================
// デストラクタ
//============================================================================
CGame::~CGame()
{
	// 終了処理
	Finalize();
}

//============================================================================
// 更新処理
//============================================================================
void CGame::Update()
{
#ifdef _DEBUG
	CRenderer::RefInstance().AddText("ゲーム機に", 1);
#endif // _DEBUG

	// 次のシーンへ遷移
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		Change();
	}

	 // うんちなの生成
	 auto p = CObjectText::Create(OpenJsonFile("Data\\JSON\\TEXT\\Unci.json"));
	 p->SetPos({ GetRandomValue(1000.0f), GetRandomValue(1000.0f) });
	 p->SetCol({ GetRandomValue(1.0f), GetRandomValue(1.0f), GetRandomValue(1.0f), 1.0f });
}

//============================================================================
// 描画処理
//============================================================================
void CGame::Draw()
{
}

//============================================================================
// 次のシーンへ
//============================================================================
void CGame::Change()
{
	// 全オブジェクト解放予約
	CObjectManager::RefInstance().SetDeathAllObject();

	// サウンド by AKR TNK
	CSound::GetInstance()->Stop(CSound::LABEL::BGM_0);

	// リザルシーンへ変更
	up<CResult> upScene = CreateUniquePtr<CResult>();
	CSceneManager::RefInstance().ChangeScene(std::move(upScene));
}

//============================================================================
// 初期化処理
//============================================================================
bool CGame::Initialize()
{
	// サウンド by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Game");

	//無理やり背景を生成
	CGameBg::Create();

	//無理やり惑星を生成
	D3DXVECTOR3 Pos;
	Pos = { 500.0f,700.0f,0.0f };
	CPlanet::Create(Pos);
	Pos = { 1000.0f,200.0f,0.0f };
	CPlanet::Create(Pos);

	//無理やりゴールを生成
	Pos = { 1500.0f,500.0f,0.0f };
	CGoal::Create(Pos);

	//無理やりプレイヤーを生成
	CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));

	return true;
}

//============================================================================
// 終了処理
//============================================================================
void CGame::Finalize()
{
}