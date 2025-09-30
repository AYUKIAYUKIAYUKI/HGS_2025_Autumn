//============================================================================
// 
// 引力ヘッダーファイル [gravity.h]
// Author : 梅田爽真
// 
//============================================================================
#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object.2D.h"

//****************************************************
// プレイヤークラスの定義
//****************************************************
class CGravity :public CObject2D
{
public:
	// <special function>
	CGravity(OBJ::TYPE Type, OBJ::LAYER Layer);
	~CGravity() override;		// デストラクタ

	// <function>
	void Update() override;	// 更新処理

	// <static function>
	static CGravity* Create(D3DXVECTOR3 pos, float radius);	// 生成

private:

	//****************************************************
	// 静的定数を定義
	//****************************************************
	const float GRAVITY_FORCE = 10.0f;	// 引力の大きさ

	// <function>
	float CalDistance();		// 引力とプレイヤーの距離を計算
	void Efficacy(float dis);	// 引力の効力

	// <Data>
	float m_GravityRadius;	// 引力の届く範囲
	float m_GravityForce;	// 引力の大きさ
};