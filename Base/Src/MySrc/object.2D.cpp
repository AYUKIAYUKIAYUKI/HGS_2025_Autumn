//============================================================================
// 
// オブジェクト(2D) [object.2D.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "object.2D.h"
#include "renderer.h"

// クライアント領域のサイズ取得用
#include "window.h"

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// コンストラクタ
//============================================================================
CObject2D::CObject2D(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject(Type, Layer)
	, m_pVtxBuff(nullptr)
	, m_pTex(nullptr)
	, m_Size(VEC3_ZERO_INIT)
	, m_Rot(VEC3_ZERO_INIT)
	, m_Pos(VEC3_ZERO_INIT)
	, m_Col(XCOL_ONE_INIT)
	, m_fLength(0.0f)
	, m_fAngle(0.0f)
	, m_TexSize(VEC2_ZERO_INIT)
	, m_fTexWidth(1.0f)
	, m_fTexHeight(1.0f)
	, m_nNowPatternU(0)
	, m_nNowPatternV(0)
{}

//============================================================================
// デストラクタ
//============================================================================
CObject2D::~CObject2D()
{}

//============================================================================
// 初期化処理
//============================================================================
bool CObject2D::Initialize()
{
	// 頂点バッファの生成
	if (FAILED(CreateVtxBuff()))
	{
		return false;
	}

	// やめよう
	m_Size = { 500.0f, 500.0f, 0.0f };

	return true;
}

//============================================================================
// 終了処理
//============================================================================
void CObject2D::Finalize()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CObject2D::Update()
{
	// 頂点バッファが消失
	if (m_pVtxBuff == nullptr)
	{ 
		std::runtime_error("buffer ga naiyo 2D");
	}

	// 必要な数値を算出
	m_fLength = sqrtf(m_Size.x * m_Size.x + m_Size.y * m_Size.y);
	m_fAngle  = atan2f(m_Size.x, m_Size.y);

	// 現在のクライアント領域のサイズの参照
	const RECT rNowWindowRect = CWindow::RefInstance().GetWindowRect();

	// スケーリング係数
	float fWindowScaleX = static_cast<float>(rNowWindowRect.right) / CWindow::FWINDOW_WIDTH;
	float fWindowScaleY = static_cast<float>(rNowWindowRect.bottom) / CWindow::FWINDOW_HEIGHT;

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx = nullptr;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	// 頂点座標の設定
	pVtx[0].pos = 
	{
		(m_Pos.x + sinf(m_Rot.z - (D3DX_PI - m_fAngle)) * m_fLength) * fWindowScaleX,
		(m_Pos.y + cosf(m_Rot.z - (D3DX_PI - m_fAngle)) * m_fLength) * fWindowScaleY,
		0.0f
	};

	pVtx[1].pos = 
	{
		(m_Pos.x + sinf(m_Rot.z + (D3DX_PI - m_fAngle)) * m_fLength) * fWindowScaleX,
		(m_Pos.y + cosf(m_Rot.z + (D3DX_PI - m_fAngle)) * m_fLength) * fWindowScaleY,
		0.0f
	};

	pVtx[2].pos = 
	{
		(m_Pos.x + sinf(m_Rot.z - m_fAngle) * m_fLength) * fWindowScaleX,
		(m_Pos.y + cosf(m_Rot.z - m_fAngle) * m_fLength) * fWindowScaleY,
		0.0f
	};

	pVtx[3].pos = 
	{
		(m_Pos.x + sinf(m_Rot.z + m_fAngle) * m_fLength) * fWindowScaleX,
		(m_Pos.y + cosf(m_Rot.z + m_fAngle) * m_fLength) * fWindowScaleY,
		0.0f
	};

	// 頂点色の設定
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	// テクスチャ座標の設定
	pVtx[0].tex = { m_fTexWidth * m_nNowPatternU, m_fTexHeight * m_nNowPatternV };
	pVtx[1].tex = { m_fTexWidth * (m_nNowPatternU + 1) - m_TexSize.x, m_fTexHeight * m_nNowPatternV };
	pVtx[2].tex = { m_fTexWidth * (m_nNowPatternU), m_fTexHeight * (m_nNowPatternV + 1) };
	pVtx[3].tex = { m_fTexWidth * (m_nNowPatternU + 1) - m_TexSize.x, m_fTexHeight * (m_nNowPatternV + 1) };

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================================================
// 描画処理
//============================================================================
void CObject2D::Draw()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::RefInstance().GetDevice();

	// 頂点バッファをデータストリームに設定
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDev->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDev->SetTexture(0, m_pTex);

	// ポリゴンの描画
	pDev->DrawPrimitive(
		D3DPT_TRIANGLESTRIP, // プリミティブの種類
		0,                   // 頂点情報の先頭アドレス
		NUM_PRIM);           // プリミティブ数
}

//============================================================================
// テクスチャ割当
//============================================================================
void CObject2D::BindTex(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

//============================================================================
// サイズ取得
//============================================================================
const D3DXVECTOR3& CObject2D::GetSize() const
{
	return m_Size;
}

//============================================================================
// サイズ設定
//============================================================================
void CObject2D::SetSize(D3DXVECTOR3 Size)
{
	m_Size = Size;
}

//============================================================================
// 向き取得
//============================================================================
const D3DXVECTOR3& CObject2D::GetRot()const
{
	return m_Rot;
}

//============================================================================
// 向き設定
//============================================================================
void CObject2D::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot = Rot;
}

//============================================================================
// 座標取得
//============================================================================
const D3DXVECTOR3& CObject2D::GetPos() const
{
	return m_Pos;
}

//============================================================================
// 座標設定
//============================================================================
void CObject2D::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

//============================================================================
// 色を取得
//============================================================================
const D3DXCOLOR& CObject2D::GetCol() const
{
	return m_Col;
}

//============================================================================
// 色を設定
//============================================================================
void CObject2D::SetCol(D3DXCOLOR Col)
{
	m_Col = Col;
}

//============================================================================
// アルファ値を取得
//============================================================================
const float& CObject2D::GetAlpha() const
{
	return m_Col.a;
}

//============================================================================
// アルファ値を設定
//============================================================================
void CObject2D::SetAlpha(const float& fAlpha)
{
	m_Col.a = fAlpha;
}

//============================================================================
// 展開用対角線取得
//============================================================================
const float& CObject2D::GetLength() const
{
	return m_fLength;
}

//============================================================================
// テクスチャサイズを取得
//============================================================================
const D3DXVECTOR2& CObject2D::GetTexSize() const
{
	return m_TexSize;
}

//============================================================================
// テクスチャサイズを設定
//============================================================================
void CObject2D::SetTexSize(D3DXVECTOR2 Size)
{
	m_TexSize = Size;
}

//============================================================================
// 横テクスチャ分割幅設定
//============================================================================
void CObject2D::SetTexWidth(float fWidth)
{
	m_fTexWidth = fWidth;
}

//============================================================================
// 縦テクスチャ分割幅設定
//============================================================================
void CObject2D::SetTexHeight(float fHeight)
{
	m_fTexHeight = fHeight;
}

//============================================================================
// 現在のテクスチャ横分割幅取得
//============================================================================
const int& CObject2D::GetNowPatternU() const
{
	return m_nNowPatternU;
}

//============================================================================
// 現在のテクスチャ横分割幅設定
//============================================================================
void CObject2D::SetNowPatternU(int nNowPatternU)
{
	m_nNowPatternU = nNowPatternU;
}

//============================================================================
// 現在のテクスチャ縦分割幅取得
//============================================================================
const int& CObject2D::GetNowPatternV() const
{
	return m_nNowPatternV;
}

//============================================================================
// 現在のテクスチャ縦分割幅設定
//============================================================================
void CObject2D::SetNowPatternV(int nNowPatternV)
{
	m_nNowPatternV = nNowPatternV;
}

//============================================================================
// 生成
//============================================================================
CObject2D* CObject2D::Create(OBJ::TYPE Type, OBJ::LAYER Layer, LPDIRECT3DTEXTURE9 pTexture)
{
	// インスタンスを生成
	CObject2D* pNewInstance = DBG_NEW CObject2D(Type, Layer);

	// 生成出来ていたら初期設定
	if (pNewInstance == nullptr)
	{
		std::runtime_error("Seisei Situpai 2D");
	}

	// 2Dオブジェクトの初期設定
	pNewInstance->Initialize();

	// テクスチャ指定
	pNewInstance->BindTex(pTexture);

	return pNewInstance;
}

//============================================================================
// 頂点バッファの生成
//============================================================================
HRESULT CObject2D::CreateVtxBuff()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::RefInstance().GetDevice();

	// 頂点バッファの生成
	pDev->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	// 生成失敗
	if (!m_pVtxBuff)
	{
		return E_FAIL;
	}

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx = nullptr;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	for (WORD wNumVtx = 0; wNumVtx < NUM_VTX; ++wNumVtx)
	{
		// 頂点座標の設定
		pVtx[wNumVtx].pos = VEC3_ZERO_INIT;

		// 除算数の設定
		pVtx[wNumVtx].rhw = 1.0f;

		// 頂点色の設定
		pVtx[wNumVtx].col = XCOL_ONE_INIT;

		// テクスチャ座標の設定
		pVtx[wNumVtx].tex = VEC2_ZERO_INIT;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}