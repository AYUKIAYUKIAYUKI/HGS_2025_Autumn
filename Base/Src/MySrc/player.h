//============================================================================
// 
// プレイヤー、ヘッダーファイル [player.h]
// Author : 福田歩希
// 
//============================================================================

#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object.2D.h"
#include "input.manager.h"

//****************************************************
// プレイヤークラスの定義
//****************************************************
class CPlayer : public CObject2D
{
public:

	// <special function>
	CPlayer(OBJ::TYPE Type, OBJ::LAYER Layer);
	~CPlayer() override;		// デストラクタ

	// <function>
	void Update() override;	// 更新処理
	void Draw() override;	// 描画処理

	// <static function>
	static CPlayer* Create(const JSON& Json);	// 生成

	inline void SetPosBase(D3DXVECTOR3 PosBase) { m_PosBase = PosBase; };
	inline void SetVelocity(D3DXVECTOR3 velo) { m_Velocity = velo; }
	inline D3DXVECTOR3 GetVelocity() { return m_Velocity; }
private:

	// <function>
	void Swing();    // スイング操作
	void FlyAway();  // 飛んでいく
	void Rotation(); // 見た目の回転

	CInputPad m_OldPad;		// 古いパッド
	D3DXVECTOR3 m_PosBase;	// 基点の座標
	float m_fBaseDistance;	// 基点との距離
	float m_fSwingDistance;	// スイング距離
	float m_fDirection;		// 現在の方角
	float m_fSwingSpeed;	// スイング速度

	bool m_bLaunch;	// 発射した
	D3DXVECTOR3 m_Velocity;	// 加速する方向
};