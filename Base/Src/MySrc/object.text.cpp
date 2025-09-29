//============================================================================
// 
// テキストオブジェクト [object.text.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "object.text.h"

#include "renderer.h"
#include "window.h"
#include "font.manager.h"

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// コンストラクタ
//============================================================================
CObjectText::CObjectText(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject(Type, Layer)
	, m_pFont(nullptr)
	, m_sText{}
	, m_sTextTarget{}
	, m_nLimit(0)
	, m_nSpeed(0)
	, m_nStop(0)
	, m_Size(VEC3_ZERO_INIT)
	, m_Pos(VEC3_ZERO_INIT)
	, m_Col(XCOL_ONE_INIT)

	, m_nGhostTime(20)
	, m_bWave(true)
	, m_WavePos(VEC2_ZERO_INIT)
	, m_fWaveCoef(3.0f)
{}

//============================================================================
// デストラクタ
//============================================================================
CObjectText::~CObjectText()
{}

//============================================================================
// 生成
//============================================================================
CObjectText* CObjectText::Create(const JSON& Json)
{
	CObjectText* p = DBG_NEW CObjectText(OBJ::TYPE::NONE, OBJ::LAYER::UI);

	// パラメータぎめ
	p->m_pFont = CFontManager::RefInstance().RefRegistry().BindAtKey(Json["Font"].get<std::string>());
	p->m_sTextTarget = useful::JsonConvertToSJIS(Json["Text"].get<std::string>());
	p->m_nLimit = Json["Limit"].get<int>();
	p->m_nSpeed = Json["Speed"].get<int>();
	p->m_Pos = useful::JsonConvertToVec2(Json["Pos"]);
	//p->m_Size = useful::JsonConvertToVec2(Json["Size"]);
	p->m_Col = useful::JsonConvertToXCol(Json["Col"]);

	return p;
}

//============================================================================
// 更新
//============================================================================
void CObjectText::Update()
{
	// テキストアニメーション
	TextAnimation();

	if (m_nLimit > 0)
	{
		// 表示時間をカウントダウン
		--m_nLimit;

		// 消える20f前から
		if (m_nLimit < m_nGhostTime)
		{
			// アルファ値を連動させて薄くなっていく
			m_Col.a = (1.0f / static_cast<float>(m_nGhostTime)) * m_nLimit;
		}
	}
	else
	{
		// 文章を消去
		SetDeath();
	}
}

//============================================================================
// 描画
//============================================================================
void CObjectText::Draw()
{
	Vec2 Pos = m_Pos + m_WavePos;

	RECT Rect = 
	{ 
		int(Pos.x),
		int(Pos.y),
		CWindow::WWINDOW_WIDTH + int(Pos.x),
		CWindow::WWINDOW_HEIGHT + int(Pos.y)
	};

	// テキストの描画
	m_pFont->DrawText(NULL, m_sText.c_str(), -1, &Rect, DT_CENTER | DT_VCENTER, m_Col);
}

//============================================================================
// テキスト送り
//============================================================================
void CObjectText::TextAnimation()
{
	// テキストが全て表示されていたら処理をしない
	if (m_sText == m_sTextTarget)
	{
		return;
	}

	// テキスト送りカウントをインクリメント
	++m_nStop;

	// テキスト送りカウントが規定値に達したら
	if (m_nStop > m_nSpeed)
	{
		// テキスト送りカウントをリセット
		m_nStop = 0;

		// 目標テキストから1文字切り分ける
		std::string SjisChar = m_sTextTarget.substr(m_sText.size(), 2);

		// 改行シンボルで文字置き換え
		if (SjisChar == "\n#")
		{
			// 改行シンボルの場所をコピー
			WORD wReturnPos = static_cast<WORD>(m_sTextTarget.find("\n#", 0));

			// 正規の改行文字に置換
			m_sTextTarget.replace(wReturnPos, 2, "\n");

			// 切り分けた文字も置換
			SjisChar = "\n";

			// テキスト送りカウントにディレイ
			/*m_nCntDisp = m_nTextDelay;*/
		}

		// テキストを1文字追加
		m_sText += SjisChar;
	}

	// 揺れる設定なら
	if (m_bWave)
	{
		m_WavePos.y = cosf(float(m_nStop)) * m_fWaveCoef;
	}
}