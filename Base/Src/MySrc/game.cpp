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
#include "game_1.h"
#include "scene_manager.h"
#include "object.manager.h"

#include "object.text.h"
#include "planet.h"
#include "goal.h"
#include"player.h"
#include"GameBg.h"
#include "window.h"
#include"planet.h"
namespace {
	D3DXVECTOR3 n_PosOld = useful::VEC3_ZERO_INIT;
}

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CGame::CGame()
	: CScene()
	, m_pPlayer(nullptr)
	, m_pGoal(nullptr)
	, m_nCounter(0)
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
	static bool clear = false;
	static int num = 60;
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
			if (m_pPlayer)
			{
				m_pPlayer->SetDeath();
				m_pPlayer = nullptr;
			}
			// ④ 新しいプレイヤーを作成
			m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));

			clear = true;
			// ② 文字作成
			CObjectText::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\TEXT\\clear.json"));
		}
	}

	// プレイヤーが止まっていて、発射フラグが立っていたら
	if (n_PosOld == m_pPlayer->GetPos() && m_pPlayer->GetLaunch())
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

	if (m_pPlayer)
	{
		if (m_pPlayer->GetLaunch())
		{
			++m_nCounter;

			if (m_nCounter > 180)
			{
				m_nCounter = 0;

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
		}
	}

	if (m_pPlayer)
	{
		for (auto obj : m_PlanetList)
		{
			if (obj->Judge())
			{
				// ② 文字作成
				CObjectText::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\TEXT\\Failed.json"));

				// ③ 今いるプレイヤーを削除
				m_pPlayer->SetDeath();
				m_pPlayer = nullptr;

				// ④ 新しいプレイヤーを作成
				m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
				break;
			}
		}
	}

	// 次のシーンへ遷移
	if (clear)
	{
		num--;
		if (num < 0)
		{
			Change();
		}
	}

#if 0
	// うんちなの生成
	auto p = CObjectText::Create(OpenJsonFile("Data\\JSON\\TEXT\\Unci.json"));
	p->SetPos({ GetRandomValue(1000.0f), GetRandomValue(1000.0f) });
	p->SetCol({ GetRandomValue(1.0f), GetRandomValue(1.0f), GetRandomValue(1.0f), 1.0f });
#endif

	// 過去の位置保存
	if (m_pPlayer)
	{
		n_PosOld = m_pPlayer->GetPos();
	}
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
	up<CGame_1> upScene = CreateUniquePtr<CGame_1>();
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
	Pos = { 500.0f,820.0f,0.0f };
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
void CGame::Finalize()
{
}