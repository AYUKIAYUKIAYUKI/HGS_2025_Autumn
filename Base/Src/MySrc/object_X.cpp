//============================================================================
// 
// Xオブジェクト [object_X.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"
#include "renderer.h"
#include "input.manager.h"
#include "camera_manager.h"

//****************************************************
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// 
// publicメンバ
// 
//============================================================================

//============================================================================
// 変換コンストラクタ
//============================================================================
CObject_X::CObject_X(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject(Type, Layer),
	m_pModel(nullptr),
	m_Pos(VEC3_ZERO_INIT),
	m_Rot(VEC3_ZERO_INIT),
	m_Scale(VEC3_ONE_INIT),
	m_Col(XCOL_ONE_INIT)
{
	// ワールド行列を初期化
	D3DXMatrixIdentity(&m_MtxWorld);
}

//============================================================================
// デストラクタ
//============================================================================
CObject_X::~CObject_X()
{

}

//============================================================================
// 初期化処理
//============================================================================
bool CObject_X::Initialize()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CObject_X::Finalize()
{}

//============================================================================
// 更新処理
//============================================================================
void CObject_X::Update()
{
	// ワールド行列の設定
	SetMtxWorld();
}

//============================================================================
// 描画処理
//============================================================================
void CObject_X::Draw()
{
	// モデルが設定されていない
	if (m_pModel == nullptr)
	{
		std::runtime_error("unko");
	}

	// マテリアルのバッファが異常
	if (m_pModel->pBuffMat == nullptr)
	{
		std::runtime_error("unko");
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::RefInstance().GetDevice();

	// 頂点法線の自動正規化を有効に
	pDev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ワールドマトリックスの設定
	pDev->SetTransform(D3DTS_WORLD, &m_MtxWorld);

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// 現在のマテリアルを取得
	pDev->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pModel->pBuffMat->GetBufferPointer();

	for (WORD wCntMat = 0; wCntMat < static_cast<WORD>(m_pModel->dwNumMat); wCntMat++)
	{
		// マテリアル色の設定
		m_bUseCol ? pMat[wCntMat].MatD3D.Diffuse = m_Col : pMat[wCntMat].MatD3D.Diffuse = m_pModel->apColMat[wCntMat];

		// マテリアルの設定
		pDev->SetMaterial(&pMat[wCntMat].MatD3D);

		// テクスチャの設定
		pDev->SetTexture(0, m_pModel->apTex[wCntMat]);

		// オブジェクトパーツの描画
		m_pModel->pMesh->DrawSubset(wCntMat);
	}

	// 保存していたマテリアルを戻す
	pDev->SetMaterial(&matDef);

	// 頂点法線の自動正規化を無効に
	pDev->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//============================================================================
// モデル取得
//============================================================================
CX_Manager::MODEL* CObject_X::GetModel()
{
	return m_pModel;
}

//============================================================================
// モデル割当
//============================================================================
void CObject_X::BindModel(CX_Manager::MODEL* pModel)
{
	m_pModel = pModel;
}

//============================================================================
// 向き取得
//============================================================================
const D3DXVECTOR3& CObject_X::GetRot()const
{
	return m_Rot;
}

//============================================================================
// 向き設定
//============================================================================
void CObject_X::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot = Rot;
}

//============================================================================
// 座標取得
//============================================================================
const D3DXVECTOR3& CObject_X::GetPos() const
{
	return m_Pos;
}

//============================================================================
// 座標設定
//============================================================================
void CObject_X::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

//============================================================================
// 縮尺を取得
//============================================================================
const D3DXVECTOR3& CObject_X::GetScale() const
{
	return m_Scale;
}

//============================================================================
// 縮尺を設定
//============================================================================
void CObject_X::SetScale(D3DXVECTOR3 Scale)
{
	m_Scale = Scale;
}

//============================================================================
// 色を取得
//============================================================================
const D3DXCOLOR& CObject_X::GetCol() const
{
	return m_Col;
}

//============================================================================
// 色を設定
//============================================================================
void CObject_X::SetCol(D3DXCOLOR Col)
{
	m_Col = Col;
}

//============================================================================
// 色反映を取得
//============================================================================
const bool& CObject_X::GetUseCol() const
{
	return m_bUseCol;
}

//============================================================================
// 色反映を設定
//============================================================================
void CObject_X::SetUseCol(bool bUse)
{
	m_bUseCol = bUse;
}

//============================================================================
// 生成
//============================================================================
CObject_X* CObject_X::Create(OBJ::TYPE Type, OBJ::LAYER Layer, const JSON& Json)
{
	// インスタンスを生成
	CObject_X* pObjectX = DBG_NEW CObject_X(Type, Layer);

	// 生成失敗
	if (pObjectX == nullptr)
	{
		assert(false && "Xオブジェクトの生成に失敗しました");
	}

	// Xオブジェクトの初期設定
	pObjectX->Initialize();

	if (Json != nullptr)
	{
		// パラメータをコピーしていく
		const auto& ModelType = static_cast<std::string>(Json["ModelType"]);
		const auto& Rot = JsonConvertToVec3(Json["Rot"]);
		const auto& Pos = JsonConvertToVec3(Json["Pos"]);
		const auto& Scale = JsonConvertToVec3(Json["Scale"]);

		// 各種パラメータを設定
		pObjectX->SetRot(Rot);
		pObjectX->SetPos(Pos);
		pObjectX->SetScale(Scale);

		// モデルを設定
		pObjectX->BindModel(CX_Manager::RefInstance().RefRegistry().BindAtKey(ModelType));
	}
	else
	{
		// 各種パラメータを設定
		pObjectX->SetRot(VEC3_ZERO_INIT);
		pObjectX->SetPos(VEC3_ZERO_INIT);
		pObjectX->SetScale(VEC3_ONE_INIT);

		// モデルを設定
		pObjectX->BindModel(CX_Manager::RefInstance().RefRegistry().BindAtKey("Unko"));
	}

	return pObjectX;
}

//============================================================================
// 
// privateメンバ
// 
//============================================================================

//============================================================================
// ワールド行列設定
//============================================================================
void CObject_X::SetMtxWorld()
{
	// 計算用行列
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	// ワールド行列を初期化
	D3DXMatrixIdentity(&m_MtxWorld);

	// 拡縮行列作成
	D3DXMatrixScaling(&mtxScale,
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	// 拡縮行列との掛け算
	D3DXMatrixMultiply(&m_MtxWorld,
		&m_MtxWorld,
		&mtxScale);

	// 回転行列作成
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z);

	// 回転行列との掛け算
	D3DXMatrixMultiply(&m_MtxWorld,
		&m_MtxWorld,
		&mtxRot);

	// 平行移動行列作成
	D3DXMatrixTranslation(&mtxTrans,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// 平行移動行列との掛け算
	D3DXMatrixMultiply(&m_MtxWorld,
		&m_MtxWorld,
		&mtxTrans);
}