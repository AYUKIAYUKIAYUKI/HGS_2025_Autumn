//============================================================================
// 
// Xオブジェクト、ヘッダファイル [object_X.h]
// Author : 福田歩希
// 
//============================================================================

#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object.h"
#include "X_manager.h"

//****************************************************
// Xオブジェクトクラス
//****************************************************
class CObject_X : public CObject
{
public:

	//****************************************************
	// special function
	//****************************************************
	CObject_X(OBJ::TYPE Type, OBJ::LAYER Layer); // コンストラクタ
	~CObject_X() override;                       // デストラクタ

	//****************************************************
	// function
	//****************************************************

	// 初期化処理
	bool Initialize();

	// 終了処理
	void Finalize();

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

	// <getter/setter>
	CX_Manager::MODEL* GetModel();				// モデル取得
	void BindModel(CX_Manager::MODEL* pModel);	// モデル割当

	// <getter/setter>
	const D3DXVECTOR3& GetRot() const;	// 向き取得
	void SetRot(D3DXVECTOR3 Rot);		// 向き設定

	// <getter/setter>
	const D3DXVECTOR3& GetPos() const;	// 座標取得
	void SetPos(D3DXVECTOR3 Pos);		// 座標設定

	// <getter/setter>
	const D3DXVECTOR3& GetScale() const;	// 縮尺取得
	void SetScale(D3DXVECTOR3 Scale);		// 縮尺設定

	// <getter/setter>
	const D3DXCOLOR& GetCol() const;	// 色を取得
	void SetCol(D3DXCOLOR Col);			// 色を設定

	// <getter/setter>
	const bool& GetUseCol() const;	// 色反映を取得
	void SetUseCol(bool Col);		// 色反映を設定

	// <static function>
	static CObject_X* Create(OBJ::TYPE Type, OBJ::LAYER Layer, const JSON& Json);								// 生成

	// ワールド行列を取得
	inline const D3DXMATRIX& GetMtxWorld() const { return m_MtxWorld; };

private:

	/// <summary> アルファ値初期化用 </summary>
	static constexpr float ALPHA_INIT = 1.0f;

	// <function>
	void AdjustRotAngle();	// 向きを調整する
	void SetMtxWorld();		// ワールド行列設定

	// <data>
	CX_Manager::MODEL*	m_pModel;	// モデル情報
	D3DXVECTOR3			m_Rot;		// 向き
	D3DXVECTOR3			m_Pos;		// 座標
	D3DXVECTOR3			m_Scale;	// 縮尺
	D3DXCOLOR			m_Col;		// 色
	bool				m_bUseCol;	// 色反映
	D3DXMATRIX			m_MtxWorld;	// ワールド行列
};