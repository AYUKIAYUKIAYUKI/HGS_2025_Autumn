//============================================================================
// 
// えふぇ区t、ヘッダーファイル [object.2D.h]
// Author : 福田歩希
// 
//============================================================================

#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object.2D.h"


class CObjectEffect : public CObject2D
{
public:

	//****************************************************
	// special function
	//****************************************************
	CObjectEffect(OBJ::TYPE Type, OBJ::LAYER Layer); // コンストラクタ
	~CObjectEffect() override;                       // デストラクタ

	//****************************************************
	// function
	//****************************************************

	// 初期化処理
	bool Initialize()
	{
		CObject2D::Initialize();
		return true;
	}

	// 終了処理
	void Finalize()
	{

	}

	// 更新処理
	void Update() override
	{
		CObject2D::Update();

		// 移動
		useful::ExponentialDecay(m_Vel, useful::VEC3_ZERO_INIT, 0.15f);
		D3DXVECTOR3 pos = GetPos();
		pos += m_Vel;
		SetPos(pos);

		if (m_nLimit > 0)
		{
			// 表示時間をカウントダウン
			--m_nLimit;

			// 消える20f前から
			if (m_nLimit < m_nGhostTime)
			{
				// アルファ値を連動させて薄くなっていく
				auto Col = GetCol();
				Col.a = (1.0f / static_cast<float>(m_nGhostTime)) * m_nLimit;
				SetCol(Col);

				D3DXVECTOR3 rot = GetRot();
				rot.z = Col.a;
				SetRot(rot);
			}
		}
		else
		{
			SetDeath();
		}
	}

	// 描画処理
	void Draw() override
	{
		CObject2D::Draw();
	}

	// <static function>
	static CObjectEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 vel, D3DXVECTOR3 Size, const JSON& json); // 生成

	int m_nLimit;
	int m_nGhostTime;
	D3DXVECTOR3 m_Vel;
};