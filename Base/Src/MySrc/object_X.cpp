//============================================================================
// 
// X�I�u�W�F�N�g [object_X.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"
#include "renderer.h"
#include "input.manager.h"
#include "camera_manager.h"

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// 
// public�����o
// 
//============================================================================

//============================================================================
// �ϊ��R���X�g���N�^
//============================================================================
CObject_X::CObject_X(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject(Type, Layer),
	m_pModel(nullptr),
	m_Pos(VEC3_ZERO_INIT),
	m_Rot(VEC3_ZERO_INIT),
	m_Scale(VEC3_ONE_INIT),
	m_Col(XCOL_ONE_INIT)
{
	// ���[���h�s���������
	D3DXMatrixIdentity(&m_MtxWorld);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CObject_X::~CObject_X()
{

}

//============================================================================
// ����������
//============================================================================
bool CObject_X::Initialize()
{
	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CObject_X::Finalize()
{}

//============================================================================
// �X�V����
//============================================================================
void CObject_X::Update()
{
	// ���[���h�s��̐ݒ�
	SetMtxWorld();
}

//============================================================================
// �`�揈��
//============================================================================
void CObject_X::Draw()
{
	// ���f�����ݒ肳��Ă��Ȃ�
	if (m_pModel == nullptr)
	{
		std::runtime_error("unko");
	}

	// �}�e���A���̃o�b�t�@���ُ�
	if (m_pModel->pBuffMat == nullptr)
	{
		std::runtime_error("unko");
	}

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::RefInstance().GetDevice();

	// ���_�@���̎������K����L����
	pDev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDev->SetTransform(D3DTS_WORLD, &m_MtxWorld);

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// ���݂̃}�e���A�����擾
	pDev->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pModel->pBuffMat->GetBufferPointer();

	for (WORD wCntMat = 0; wCntMat < static_cast<WORD>(m_pModel->dwNumMat); wCntMat++)
	{
		// �}�e���A���F�̐ݒ�
		m_bUseCol ? pMat[wCntMat].MatD3D.Diffuse = m_Col : pMat[wCntMat].MatD3D.Diffuse = m_pModel->apColMat[wCntMat];

		// �}�e���A���̐ݒ�
		pDev->SetMaterial(&pMat[wCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDev->SetTexture(0, m_pModel->apTex[wCntMat]);

		// �I�u�W�F�N�g�p�[�c�̕`��
		m_pModel->pMesh->DrawSubset(wCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDev->SetMaterial(&matDef);

	// ���_�@���̎������K���𖳌���
	pDev->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//============================================================================
// ���f���擾
//============================================================================
CX_Manager::MODEL* CObject_X::GetModel()
{
	return m_pModel;
}

//============================================================================
// ���f������
//============================================================================
void CObject_X::BindModel(CX_Manager::MODEL* pModel)
{
	m_pModel = pModel;
}

//============================================================================
// �����擾
//============================================================================
const D3DXVECTOR3& CObject_X::GetRot()const
{
	return m_Rot;
}

//============================================================================
// �����ݒ�
//============================================================================
void CObject_X::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot = Rot;
}

//============================================================================
// ���W�擾
//============================================================================
const D3DXVECTOR3& CObject_X::GetPos() const
{
	return m_Pos;
}

//============================================================================
// ���W�ݒ�
//============================================================================
void CObject_X::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

//============================================================================
// �k�ڂ��擾
//============================================================================
const D3DXVECTOR3& CObject_X::GetScale() const
{
	return m_Scale;
}

//============================================================================
// �k�ڂ�ݒ�
//============================================================================
void CObject_X::SetScale(D3DXVECTOR3 Scale)
{
	m_Scale = Scale;
}

//============================================================================
// �F���擾
//============================================================================
const D3DXCOLOR& CObject_X::GetCol() const
{
	return m_Col;
}

//============================================================================
// �F��ݒ�
//============================================================================
void CObject_X::SetCol(D3DXCOLOR Col)
{
	m_Col = Col;
}

//============================================================================
// �F���f���擾
//============================================================================
const bool& CObject_X::GetUseCol() const
{
	return m_bUseCol;
}

//============================================================================
// �F���f��ݒ�
//============================================================================
void CObject_X::SetUseCol(bool bUse)
{
	m_bUseCol = bUse;
}

//============================================================================
// ����
//============================================================================
CObject_X* CObject_X::Create(OBJ::TYPE Type, OBJ::LAYER Layer, const JSON& Json)
{
	// �C���X�^���X�𐶐�
	CObject_X* pObjectX = DBG_NEW CObject_X(Type, Layer);

	// �������s
	if (pObjectX == nullptr)
	{
		assert(false && "X�I�u�W�F�N�g�̐����Ɏ��s���܂���");
	}

	// X�I�u�W�F�N�g�̏����ݒ�
	pObjectX->Initialize();

	if (Json != nullptr)
	{
		// �p�����[�^���R�s�[���Ă���
		const auto& ModelType = static_cast<std::string>(Json["ModelType"]);
		const auto& Rot = JsonConvertToVec3(Json["Rot"]);
		const auto& Pos = JsonConvertToVec3(Json["Pos"]);
		const auto& Scale = JsonConvertToVec3(Json["Scale"]);

		// �e��p�����[�^��ݒ�
		pObjectX->SetRot(Rot);
		pObjectX->SetPos(Pos);
		pObjectX->SetScale(Scale);

		// ���f����ݒ�
		pObjectX->BindModel(CX_Manager::RefInstance().RefRegistry().BindAtKey(ModelType));
	}
	else
	{
		// �e��p�����[�^��ݒ�
		pObjectX->SetRot(VEC3_ZERO_INIT);
		pObjectX->SetPos(VEC3_ZERO_INIT);
		pObjectX->SetScale(VEC3_ONE_INIT);

		// ���f����ݒ�
		pObjectX->BindModel(CX_Manager::RefInstance().RefRegistry().BindAtKey("Unko"));
	}

	return pObjectX;
}

//============================================================================
// 
// private�����o
// 
//============================================================================

//============================================================================
// ���[���h�s��ݒ�
//============================================================================
void CObject_X::SetMtxWorld()
{
	// �v�Z�p�s��
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	// ���[���h�s���������
	D3DXMatrixIdentity(&m_MtxWorld);

	// �g�k�s��쐬
	D3DXMatrixScaling(&mtxScale,
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	// �g�k�s��Ƃ̊|���Z
	D3DXMatrixMultiply(&m_MtxWorld,
		&m_MtxWorld,
		&mtxScale);

	// ��]�s��쐬
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z);

	// ��]�s��Ƃ̊|���Z
	D3DXMatrixMultiply(&m_MtxWorld,
		&m_MtxWorld,
		&mtxRot);

	// ���s�ړ��s��쐬
	D3DXMatrixTranslation(&mtxTrans,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	// ���s�ړ��s��Ƃ̊|���Z
	D3DXMatrixMultiply(&m_MtxWorld,
		&m_MtxWorld,
		&mtxTrans);
}