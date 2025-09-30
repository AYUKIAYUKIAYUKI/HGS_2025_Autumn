//============================================================================
// 
// 引力[gravity.cpp]
// Author : 梅田爽真
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "gravity.h"
#include "object.manager.h"
#include "player.h"

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// コンストラクタ
//============================================================================
CGravity::CGravity(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject2D(Type, Layer)
{
	m_GravityForce = 0.0f;
	m_GravityRadius = 0.0f;
}

//============================================================================
// デストラクタ
//============================================================================
CGravity::~CGravity()
{

}

//===========================================================================================================
// 更新
//===========================================================================================================
void CGravity::Update()
{
	float dis = CalDistance();

	Efficacy(dis);
}

//===========================================================================================================
// 生成
//===========================================================================================================
CGravity* CGravity::Create(D3DXVECTOR3 pos, float radius)
{
	// インスタンスを生成
	CGravity* pGravity = DBG_NEW CGravity(OBJ::TYPE::GRAVITY, OBJ::LAYER::DEFAULT);

	// 2Dオブジェクトの初期設定
	pGravity->Initialize();

	pGravity->SetPos(pos);
	pGravity->SetSize({ radius,radius,0.0f });
	pGravity->m_GravityRadius = radius * 2.0f;
	
	return pGravity;
}

//===========================================================================================================
// 引力とプレイヤーの距離を計算
//===========================================================================================================
float CGravity::CalDistance()
{
	// プレイヤーの検索
	std::list<CObject*>ol = CObjectManager::RefInstance().RefObjList(OBJ::TYPE::PLAYER);	// プレイヤーのリストを取得
	CObject* pobj = ol.front();	// 先頭を代入
	CPlayer* pPlayer = DownCast<CPlayer, CObject>(pobj);	// ダウンキャスト

	// 惑星の中心
	D3DXVECTOR3 pos = GetPos();

	// プレイヤーの情報
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	
	float cal_a = pos.x - PlayerPos.x;	// x の計算
	float cal_b = pos.y - PlayerPos.y;	// y の計算

	// 計算した結果(距離)
	float distance = sqrt(cal_a * cal_a + cal_b * cal_b);

	return distance;
}

//===========================================================================================================
// 引力の効力
//===========================================================================================================
void CGravity::Efficacy(float dis)
{
	// プレイヤーの検索
	std::list<CObject*>ol = CObjectManager::RefInstance().RefObjList(OBJ::TYPE::PLAYER);	// プレイヤーのリストを取得
	CObject* pobj = ol.front();	// 先頭を代入
	CPlayer* pPlayer = DownCast<CPlayer, CObject>(pobj);	// ダウンキャスト

	// プレイヤーの情報
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	float PlayerRadius = pPlayer->GetSize().x;

	// 惑星の中心
	D3DXVECTOR3 pos = GetPos();

	float DirectionMove = atan2f(pos.x - PlayerPos.x, pos.y - PlayerPos.y);	// 現在の移動方向

	float length = pPlayer->GetLength();

	D3DXVECTOR3 velo = pPlayer->GetVelocity();

	float a = 0.001f;

	if (dis>=400)
	{
		m_GravityForce = 0.0f;
	}
	else if (dis < 400 && dis >= 300)
	{
		m_GravityForce = 0.001f+ a;
	}
	else if (dis < 300 && dis >= 200)
	{
		m_GravityForce = 0.0035f+ a;
	}
	else if (dis < 200 && dis >= 50)
	{
		m_GravityForce = 0.005f+ a;
	}
	else
	{
		m_GravityForce = 0.1f+ a;
	}

	// 距離が二つの円の大きさ以下の時
	if (dis <= m_GravityRadius + PlayerRadius)
	{
		// 移動値の設定
		velo = (velo + (D3DXVECTOR3(sinf(DirectionMove) * pPlayer->GetLength() * m_GravityForce/*+(dis*0.0001f)*/, cosf(DirectionMove) * pPlayer->GetLength() * m_GravityForce/*+ (dis * 0.0001f)*/, 0.0f)));
		pPlayer->SetVelocity(velo);
	}

#if _DEBUG
	/* 方角の操作と角度の出力 */
	if (useful::MIS::MyImGuiShortcut_BeginWindow("aaaaaaaaaa"))
	{
		ImGui::Text("distance: %f", dis);
		ImGui::Text("velo: %f , %f", velo.x, velo.y);
	}
	ImGui::End();
#endif
}
