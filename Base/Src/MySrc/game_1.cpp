//============================================================================
// 
// ゲーム [game.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "game_1.h"
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
#include "window.h"
#include"planet.h"
//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CGame_1::CGame_1()
	: CScene()
	, m_pPlayer(nullptr)
	, m_pGoal(nullptr)
{
}

//============================================================================
// デストラクタ
//============================================================================
CGame_1::~CGame_1()
{
	// 終了処理
	Finalize();
}

//============================================================================
// 更新処理
//============================================================================
void CGame_1::Update()
{
#ifdef _DEBUG
	//CRenderer::RefInstance().AddText("ゲーム機に", 1);
#endif // _DEBUG

	// ① プレイヤーが画面外に
	if (m_pPlayer)
	{
		Vec3 Pos = m_pPlayer->GetPos();

		if (Pos.x < 0.0f || Pos.x > CWindow::FWINDOW_WIDTH ||
			Pos.y < 0.0f || Pos.y > CWindow::FWINDOW_HEIGHT)
		{
			// ② 文字作成
			CObjectText::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\TEXT\\Failed.json"));

			// ③ 今いるプレイヤーを削除
			if (m_pPlayer)
			{
				m_pPlayer->SetDeath();
				m_pPlayer = nullptr;
			}

			// ④ 新しいプレイヤーを作成
			m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
		}
		else if (m_pGoal->Judge())
		{
			Change();
		}
	}


	for (auto obj : m_PlanetList)
	{
		if (obj->Judge())
		{
			// ② 文字作成
			CObjectText::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\TEXT\\Failed.json"));

			// ③ 今いるプレイヤーを削除
			if (m_pPlayer)
			{
				m_pPlayer->SetDeath();
				m_pPlayer = nullptr;
			}

			// ④ 新しいプレイヤーを作成
			m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
			break;
		}
	}

	// 次のシーンへ遷移
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		//Change();
	}

#if 0
	// うんちなの生成
	auto p = CObjectText::Create(OpenJsonFile("Data\\JSON\\TEXT\\Unci.json"));
	p->SetPos({ GetRandomValue(1000.0f), GetRandomValue(1000.0f) });
	p->SetCol({ GetRandomValue(1.0f), GetRandomValue(1.0f), GetRandomValue(1.0f), 1.0f });
#endif
}

//============================================================================
// 描画処理
//============================================================================
void CGame_1::Draw()
{
}

//============================================================================
// 次のシーンへ
//============================================================================
void CGame_1::Change()
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
bool CGame_1::Initialize()
{
	// サウンド by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Game");

	//無理やり背景を生成
	CGameBg::Create();

	//無理やり惑星を生成
	D3DXVECTOR3 Pos;
	Pos = { 1500.0f,720.0f,0.0f };
	m_PlanetList.push_back(CPlanet::Create(Pos));
	Pos = { 1000.0f,100.0f,0.0f };
	m_PlanetList.push_back(CPlanet::Create(Pos));

	//無理やりゴールを生成
	Pos = { 1500.0f,450.0f,0.0f };
	m_pGoal = CGoal::Create(Pos);

	//無理やりプレイヤーを生成
	if (!m_pPlayer)
	{
		m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
	}

	return true;
}

//============================================================================
// 終了処理
//============================================================================
void CGame_1::Finalize()
{
}