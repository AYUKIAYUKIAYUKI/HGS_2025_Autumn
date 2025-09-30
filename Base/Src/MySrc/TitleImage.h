//============================================================================
// 
// タイトルで表示する画像、ヘッダーファイル [TitleImage.h]
// Author : 後藤優輝
// 
//============================================================================

#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object.2D.h"

//****************************************************
// 惑星クラスの定義
//****************************************************
class CTitleImage : public CObject2D
{
public:

	// <special function>
	CTitleImage(OBJ::TYPE Type, OBJ::LAYER Layer);
	~CTitleImage() override;		// デストラクタ

	// <function>
	void Update() override;	// 更新処理
	void Draw() override;	// 描画処理

	// <static function>
	static CTitleImage* Create(/*const JSON& Json*/);	// 生成

private:

	//****************************************************
	// 静的定数を定義
	//****************************************************
	//static constexpr float MAX_VELOCITY = 0.5f;		// 加速度上限
	//static constexpr float JUMP_FORCE = 6.0f;		// ジャンプ力
	//static constexpr float BRAKING_FORCE = 0.9f;	// 制動力

	// <function>
	void Control();			// 操作
	void Rotation();		// 回転
	void AdjustRotAngle();	// 向きを調整する
	void Braking();			// 制動調整
	void GravityFall();		// 重力加速
	void AdjustPos();		// 位置を調整

	// <Data>
};