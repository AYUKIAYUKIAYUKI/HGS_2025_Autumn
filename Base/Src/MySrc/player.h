////============================================================================
//// 
//// プレイヤー、ヘッダーファイル [player.h]
//// Author : 福田歩希
//// 
////============================================================================
//
//#pragma once
//
////****************************************************
//// インクルードファイル
////****************************************************
//#include "object_X.h"
//
//// Xモデル情報用
//#include "X_manager.h"
//
////****************************************************
//// プレイヤークラスの定義
////****************************************************
//class CPlayer : public CObject_X
//{
//public:
//
//	// <special function>
//	CPlayer(OBJ::TYPE Type, OBJ::LAYER Layer);
//	~CPlayer() override;		// デストラクタ
//
//	// <function>
//	void Update() override;	// 更新処理
//	void Draw() override;	// 描画処理
//
//	// <static function>
//	static CPlayer* Create(const JSON& Json);	// 生成
//
//private:
//
//	//****************************************************
//	// 静的定数を定義
//	//****************************************************
//	static constexpr float MAX_VELOCITY = 0.5f;		// 加速度上限
//	static constexpr float JUMP_FORCE = 6.0f;		// ジャンプ力
//	static constexpr float BRAKING_FORCE = 0.9f;	// 制動力
//
//	// <function>
//	void Control();			// 操作
//	void Rotation();		// 回転
//	void AdjustRotAngle();	// 向きを調整する
//	void Braking();			// 制動調整
//	void GravityFall();		// 重力加速
//	void AdjustPos();		// 位置を調整
//
//	// <Data>
//	int			m_nLeftNumJump;	// ジャンプ可能回数
//	float		m_fJumpForce;	// ジャンプ力
//	D3DXVECTOR3 m_Velocity;		// 加速度
//	D3DXVECTOR3 m_PosTarget;	// 目標位置
//	D3DXVECTOR3 m_RotTarget;	// 目標向き
//	D3DXVECTOR3 m_RotTarget;	// 目標サイズ
//};