//============================================================================
// 
// オブジェクト(2D)、ヘッダーファイル [object.2D.h]
// Author : 福田歩希
// 
//============================================================================

#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object.h"

//****************************************************
// 2Dオブジェクトクラス
//****************************************************
class CObject2D : public CObject
{
	//****************************************************
	// 静的メンバ定数 (非公開)
	//****************************************************

	// 頂点数
	static constexpr WORD NUM_VTX = 4;

	// プリミティブ数
	static constexpr WORD NUM_PRIM = 2;

public:

	//****************************************************
	// special function
	//****************************************************
	CObject2D(OBJ::TYPE Type, OBJ::LAYER Layer); // コンストラクタ
	~CObject2D() override;                       // デストラクタ

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

	//****************************************************
	// 下記は旧方式のデータ操作用メソッドです
	//****************************************************

	// <setter>
	void BindTex(LPDIRECT3DTEXTURE9 pTex); // テクスチャ割当

	// <getter/setter>
	const D3DXVECTOR3& GetSize() const;	// サイズ取得
	void SetSize(D3DXVECTOR3 Size);		// サイズ設定

	// <getter/setter>
	const D3DXVECTOR3& GetRot() const;	// 向き取得
	void SetRot(D3DXVECTOR3 Rot);		// 向き設定

	// <getter/setter>
	const D3DXVECTOR3& GetPos() const;	// 座標取得
	void SetPos(D3DXVECTOR3 Pos);		// 座標設定

	// <getter/setter>
	const D3DXCOLOR& GetCol() const;	// 色取得
	void SetCol(D3DXCOLOR Col);			// 色設定

	// <getter/setter>
	const float& GetAlpha() const;		// アルファ値取得
	void SetAlpha(const float& fAlpha);	// アルファ値設定

	// <getter>
	const float& GetLength() const;	// 展開用対角線取得

	// <getter/setter>
	const D3DXVECTOR2& GetTexSize() const;	// テクスチャサイズを取得
	void SetTexSize(D3DXVECTOR2 Size);		// テクスチャサイズを設定

	// <setter>
	void SetTexWidth(float fWidth);		// 横テクスチャ分割幅設定
	void SetTexHeight(float fHeight);	// 縦テクスチャ分割幅設定

	// <getter/setter>
	const int& GetNowPatternU() const;		// 現在のテクスチャ横分割幅取得
	void SetNowPatternU(int nNowPatternU);	// 現在のテクスチャ横分割幅設定

	// <getter/setter>
	const int& GetNowPatternV() const;		// 現在のテクスチャ縦分割幅取得
	void SetNowPatternV(int nNowPatternV);	// 現在のテクスチャ縦分割幅設定

	// <static function>
	static CObject2D* Create(OBJ::TYPE Type, OBJ::LAYER Layer, LPDIRECT3DTEXTURE9 pTexture); // 生成

private:

	//****************************************************
	// function
	//****************************************************
	HRESULT CreateVtxBuff(); // 頂点バッファの生成

	//****************************************************
	// data
	//****************************************************
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9		m_pTex;			// テクスチャのポインタ
	D3DXVECTOR3				m_Size;			// サイズ
	D3DXVECTOR3				m_Rot;			// 向き
	D3DXVECTOR3				m_Pos;			// 座標
	D3DXCOLOR				m_Col;			// 色
	float					m_fLength;		// 展開用対角線
	float					m_fAngle;		// 対角線用角度
	D3DXVECTOR2				m_TexSize;		// テクスチャサイズ
	float					m_fTexWidth;	// 横テクスチャ分割幅
	float					m_fTexHeight;	// 縦テクスチャ分縦幅
	int						m_nNowPatternU;	// 現在の横テクスチャ種類
	int						m_nNowPatternV;	// 現在の縦テクスチャ種類
};