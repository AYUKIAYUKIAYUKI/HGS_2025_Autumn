//============================================================================
// 
// �I�u�W�F�N�g(2D) [object.2D.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.2D.h"
#include "renderer.h"

// �N���C�A���g�̈�̃T�C�Y�擾�p
#include "window.h"

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//============================================================================
CObject2D::~CObject2D()
{}

//============================================================================
// ����������
//============================================================================
bool CObject2D::Initialize()
{
	// ���_�o�b�t�@�̐���
	if (FAILED(CreateVtxBuff()))
	{
		return false;
	}

	// ��߂悤
	m_Size = { 500.0f, 500.0f, 0.0f };

	return true;
}

//============================================================================
// �I������
//============================================================================
void CObject2D::Finalize()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================================================================
// �X�V����
//============================================================================
void CObject2D::Update()
{
	// ���_�o�b�t�@������
	if (m_pVtxBuff == nullptr)
	{ 
		std::runtime_error("buffer ga naiyo 2D");
	}

	// �K�v�Ȑ��l���Z�o
	m_fLength = sqrtf(m_Size.x * m_Size.x + m_Size.y * m_Size.y);
	m_fAngle  = atan2f(m_Size.x, m_Size.y);

	// ���݂̃N���C�A���g�̈�̃T�C�Y�̎Q��
	const RECT rNowWindowRect = CWindow::RefInstance().GetWindowRect();

	// �X�P�[�����O�W��
	float fWindowScaleX = static_cast<float>(rNowWindowRect.right) / CWindow::FWINDOW_WIDTH;
	float fWindowScaleY = static_cast<float>(rNowWindowRect.bottom) / CWindow::FWINDOW_HEIGHT;

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	// ���_���W�̐ݒ�
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

	// ���_�F�̐ݒ�
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = { m_fTexWidth * m_nNowPatternU, m_fTexHeight * m_nNowPatternV };
	pVtx[1].tex = { m_fTexWidth * (m_nNowPatternU + 1) - m_TexSize.x, m_fTexHeight * m_nNowPatternV };
	pVtx[2].tex = { m_fTexWidth * (m_nNowPatternU), m_fTexHeight * (m_nNowPatternV + 1) };
	pVtx[3].tex = { m_fTexWidth * (m_nNowPatternU + 1) - m_TexSize.x, m_fTexHeight * (m_nNowPatternV + 1) };

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================================
// �`�揈��
//============================================================================
void CObject2D::Draw()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::RefInstance().GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDev->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDev->SetTexture(0, m_pTex);

	// �|���S���̕`��
	pDev->DrawPrimitive(
		D3DPT_TRIANGLESTRIP, // �v���~�e�B�u�̎��
		0,                   // ���_���̐擪�A�h���X
		NUM_PRIM);           // �v���~�e�B�u��
}

//============================================================================
// �e�N�X�`������
//============================================================================
void CObject2D::BindTex(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

//============================================================================
// �T�C�Y�擾
//============================================================================
const D3DXVECTOR3& CObject2D::GetSize() const
{
	return m_Size;
}

//============================================================================
// �T�C�Y�ݒ�
//============================================================================
void CObject2D::SetSize(D3DXVECTOR3 Size)
{
	m_Size = Size;
}

//============================================================================
// �����擾
//============================================================================
const D3DXVECTOR3& CObject2D::GetRot()const
{
	return m_Rot;
}

//============================================================================
// �����ݒ�
//============================================================================
void CObject2D::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot = Rot;
}

//============================================================================
// ���W�擾
//============================================================================
const D3DXVECTOR3& CObject2D::GetPos() const
{
	return m_Pos;
}

//============================================================================
// ���W�ݒ�
//============================================================================
void CObject2D::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

//============================================================================
// �F���擾
//============================================================================
const D3DXCOLOR& CObject2D::GetCol() const
{
	return m_Col;
}

//============================================================================
// �F��ݒ�
//============================================================================
void CObject2D::SetCol(D3DXCOLOR Col)
{
	m_Col = Col;
}

//============================================================================
// �A���t�@�l���擾
//============================================================================
const float& CObject2D::GetAlpha() const
{
	return m_Col.a;
}

//============================================================================
// �A���t�@�l��ݒ�
//============================================================================
void CObject2D::SetAlpha(const float& fAlpha)
{
	m_Col.a = fAlpha;
}

//============================================================================
// �W�J�p�Ίp���擾
//============================================================================
const float& CObject2D::GetLength() const
{
	return m_fLength;
}

//============================================================================
// �e�N�X�`���T�C�Y���擾
//============================================================================
const D3DXVECTOR2& CObject2D::GetTexSize() const
{
	return m_TexSize;
}

//============================================================================
// �e�N�X�`���T�C�Y��ݒ�
//============================================================================
void CObject2D::SetTexSize(D3DXVECTOR2 Size)
{
	m_TexSize = Size;
}

//============================================================================
// ���e�N�X�`���������ݒ�
//============================================================================
void CObject2D::SetTexWidth(float fWidth)
{
	m_fTexWidth = fWidth;
}

//============================================================================
// �c�e�N�X�`���������ݒ�
//============================================================================
void CObject2D::SetTexHeight(float fHeight)
{
	m_fTexHeight = fHeight;
}

//============================================================================
// ���݂̃e�N�X�`�����������擾
//============================================================================
const int& CObject2D::GetNowPatternU() const
{
	return m_nNowPatternU;
}

//============================================================================
// ���݂̃e�N�X�`�����������ݒ�
//============================================================================
void CObject2D::SetNowPatternU(int nNowPatternU)
{
	m_nNowPatternU = nNowPatternU;
}

//============================================================================
// ���݂̃e�N�X�`���c�������擾
//============================================================================
const int& CObject2D::GetNowPatternV() const
{
	return m_nNowPatternV;
}

//============================================================================
// ���݂̃e�N�X�`���c�������ݒ�
//============================================================================
void CObject2D::SetNowPatternV(int nNowPatternV)
{
	m_nNowPatternV = nNowPatternV;
}

//============================================================================
// ����
//============================================================================
CObject2D* CObject2D::Create(OBJ::TYPE Type, OBJ::LAYER Layer, LPDIRECT3DTEXTURE9 pTexture)
{
	// �C���X�^���X�𐶐�
	CObject2D* pNewInstance = DBG_NEW CObject2D(Type, Layer);

	// �����o���Ă����珉���ݒ�
	if (pNewInstance == nullptr)
	{
		std::runtime_error("Seisei Situpai 2D");
	}

	// 2D�I�u�W�F�N�g�̏����ݒ�
	pNewInstance->Initialize();

	// �e�N�X�`���w��
	pNewInstance->BindTex(pTexture);

	return pNewInstance;
}

//============================================================================
// ���_�o�b�t�@�̐���
//============================================================================
HRESULT CObject2D::CreateVtxBuff()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::RefInstance().GetDevice();

	// ���_�o�b�t�@�̐���
	pDev->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	// �������s
	if (!m_pVtxBuff)
	{
		return E_FAIL;
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	for (WORD wNumVtx = 0; wNumVtx < NUM_VTX; ++wNumVtx)
	{
		// ���_���W�̐ݒ�
		pVtx[wNumVtx].pos = VEC3_ZERO_INIT;

		// ���Z���̐ݒ�
		pVtx[wNumVtx].rhw = 1.0f;

		// ���_�F�̐ݒ�
		pVtx[wNumVtx].col = XCOL_ONE_INIT;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[wNumVtx].tex = VEC2_ZERO_INIT;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}