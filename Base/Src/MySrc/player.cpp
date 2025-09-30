//============================================================================
// 
// プレイヤー [player.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "player.h"
#include "texture.manager.h"
#include "input.manager.h"

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject2D(Type, Layer)
	, m_OldPad{}
	, m_PosBase(VEC3_ZERO_INIT)
	, m_fBaseDistance(60.0f)
	, m_fSwingDistance(0.0f)
	, m_fDirection(0.0f)
	, m_fSwingSpeed(0.0f)
	, m_bLaunch(false)
	, m_Velocity(VEC3_ZERO_INIT)
{}

//============================================================================
// デストラクタ
//============================================================================
CPlayer::~CPlayer()
{}

//============================================================================
// 更新
//============================================================================
void CPlayer::Update()
{
	// 基底クラスの更新処理
	CObject2D::Update();

	// 発射されていなければスイング操作
	if (!m_bLaunch)
	{
		Swing();
	}
	else
	{
		// 発射後は飛行動作
		FlyAway();
	}

	// 見た目の回転
	Rotation();
}

//============================================================================
// 描画
//============================================================================
void CPlayer::Draw()
{
	// 基底クラスの描画処理
	CObject2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CPlayer* CPlayer::Create(const JSON& Json)
{
	// 生成
	CPlayer* p = DBG_NEW CPlayer(OBJ::TYPE::PLAYER, OBJ::LAYER::DEFAULT);

	// 頂点生成
	p->Initialize();

	// テクスチャの設定
	p->BindTex(CTextureManager::RefInstance().RefRegistry().BindAtKey("Sphere"));

	// パラメータの設定
	p->SetPosBase(useful::JsonConvertToVec3(Json["InitPos"]));
	p->SetSize(useful::JsonConvertToVec3(Json["Size"]));
	
	{
		CObject2D* pp = DBG_NEW CObject2D(OBJ::TYPE::NONE, OBJ::LAYER::DEFAULT);
		pp->BindTex(CTextureManager::RefInstance().RefRegistry().BindAtKey("Sphere"));
		pp->Initialize();
		pp->SetPos(useful::JsonConvertToVec3(Json["InitPos"]));
		pp->SetSize({ p->m_fBaseDistance, p->m_fBaseDistance, 0.0f });
		pp->SetCol({ 0.0f, 0.0f, 1.0f, 1.0f });
	}

	return p;
}

//============================================================================
// スイング操作
//============================================================================
void CPlayer::Swing()
{
	// 上昇・減少の強度
	const float fSpeedCoef = 0.005f;
	const float fDistanceCoef = 0.025f;

#if 0
	// 過去のスティック傾きとの差
	int saX = CInputManager::RefInstance().GetPad()->GetJoyStickL().X - m_OldPad.GetJoyStickL().X;
	int saY = CInputManager::RefInstance().GetPad()->GetJoyStickL().Y - m_OldPad.GetJoyStickL().Y;

	// 許容する差
	const int nKyoou = 1;

	// 左スティックをガチャガチャしてると、方角が周り、スイング距離が加算されていく
	if (abs(saX) > nKyoou && abs(saY) > nKyoou)
	{
		m_fSwingDistance = (m_fSwingDistance + fCoef * 2.0f) * (1.0f + fCoef);
	}
	else
	{
		// スイング距離は常に減少
		m_fSwingDistance = (m_fSwingDistance + fCoef * 0.5f) * (1.0f - fCoef);
	}
#endif

	// 一旦左スティックを倒していると、方角が周り、スイング距離が加算されていく
	if (CInputManager::RefInstance().GetPad()->GetJoyStickL().X != 0 ||
		CInputManager::RefInstance().GetPad()->GetJoyStickL().Y != 0)
	{
		m_fSwingSpeed = (m_fSwingSpeed + fSpeedCoef * 0.1f) * (1.0f + fSpeedCoef);
		m_fSwingDistance = (m_fSwingDistance + fDistanceCoef * 0.1f) * (1.0f + fDistanceCoef);
	}
	else
	{
		// スイング距離は常に減少
		m_fSwingSpeed = (m_fSwingSpeed - fSpeedCoef * 0.1f) * (1.0f - fSpeedCoef);
		m_fSwingDistance = (m_fSwingDistance - fDistanceCoef * 0.1f) * (1.0f - fDistanceCoef);
	}

	// スイング速度の下限・上限を設定
	if (m_fSwingSpeed < 0.0f)
	{
		m_fSwingSpeed = 0.0f;
	}
	else if (m_fSwingSpeed > 0.25f)
	{
		m_fSwingSpeed = 0.25f;
	}

	// スイング距離の下限・上限を設定
	if (m_fSwingDistance < 0.0f)
	{
		m_fSwingDistance = 0.0f;
	}
	else if (m_fSwingDistance > 40.0f)
	{
		m_fSwingDistance = 40.0f;
	}

	// 最終的なスイング速度分、プレイヤーが周回
	m_fDirection += m_fSwingSpeed;

	// 現在の座標取得
	Vec3 Pos = GetPos();

	// 発射時に、速度や進行方向を保つために位置を保持
	Vec3 PosOld = Pos;

	// 基点の座標を元に、現在の方角分、基点距離 + 速度距離分離す
	Pos =
	{
		m_PosBase.x + sinf(m_fDirection) * (m_fBaseDistance + m_fSwingDistance),
		m_PosBase.y + cosf(m_fDirection) * (m_fBaseDistance + m_fSwingDistance),
		m_PosBase.z,
	};

	/* 方角の操作と角度の出力 */
	if (useful::MIS::MyImGuiShortcut_BeginWindow("Player Swing"))
	{
		ImGui::DragFloat("BaseDistance", &m_fBaseDistance, 0.1f);

		ImGui::Text("Pos.X: %f", Pos.x);
		ImGui::Text("Pos.Y: %f", Pos.y);
		ImGui::Text("Distance: %f", m_fDirection);
		ImGui::Text("SwingDistance: %f", m_fSwingDistance);
		ImGui::Text("SwingSpeed: %f", m_fSwingSpeed);
	}
	ImGui::End();

	// 計算後の角度を -π ～ π の範囲に抑える
	useful::WrapAngleToRange(m_fDirection);

	// 位置を反映
	SetPos(Pos);

	// パッドの情報をコピー
	m_OldPad = *CInputManager::RefInstance().GetPad();

	// 発射
	if (CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
	{
		// もうスイング処理はしない
		m_bLaunch = true;

	    // ガチで飛行する方向を決める
		m_Velocity = 
		{
			(Pos.x - PosOld.x),
			(Pos.y - PosOld.y),
			0.0f
		};
	}
}

//============================================================================
// 飛行
//============================================================================
void CPlayer::FlyAway()
{
	// 現在の座標取得
	Vec3 Pos = GetPos();

	// 飛行方向に移動
	Pos += m_Velocity;

	// 加算されている座標を設定
	SetPos(Pos);
}

//============================================================================
// 見た目の回転
//============================================================================
void CPlayer::Rotation()
{

}