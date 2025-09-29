//============================================================================
// 
// テキストオブジェクト、ヘッダーファイル [object.text.h]
// Author : 福田歩希
// 
//============================================================================

#pragma once

//****************************************************
// インクルードファイル
//****************************************************
#include "object.h"

//****************************************************
// テキストオブジェクトクラスの定義
//****************************************************
class CObjectText : public CObject
{
public:

	//****************************************************
	// special function
	//****************************************************
	CObjectText(OBJ::TYPE Type, OBJ::LAYER Layer); // コンストラクタ
	~CObjectText() override;                       // デストラクタ

	//****************************************************
	// function
	//****************************************************

	// 初期化処理
	bool Initialize() {};

	// 終了処理
	void Finalize() {};

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

	// <static function>
	static CObjectText* Create(const JSON& Json); // 生成

	inline void SetPos(D3DXVECTOR2 Pos) { m_Pos = Pos; }
	inline void SetCol(D3DXCOLOR Col) { m_Col = Col; }

private:

	//****************************************************
	// function
	//****************************************************
	void TextAnimation(); // テキスト送りのアニメーション

	//****************************************************
	// data
	//****************************************************
	LPD3DXFONT  m_pFont;       // フォントのポインタ
	std::string m_sText;       // 文章
	std::string m_sTextTarget; // 目標文章
	int         m_nLimit;      // 表示時間
	int         m_nSpeed;      // 表示速度
	int         m_nStop;       // 遅延カウンター
	D3DXVECTOR2 m_Pos;         // 位置
	D3DXVECTOR2 m_Size;        // サイズ
	D3DXCOLOR   m_Col;         // 色

	int m_nGhostTime;
	bool m_bWave;
	D3DXVECTOR2 m_WavePos;
	float m_fWaveCoef;
};