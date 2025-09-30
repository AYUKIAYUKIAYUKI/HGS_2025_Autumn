//============================================================================
// 
// �v���C���[ [player.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "player.h"
#include "texture.manager.h"
#include "input.manager.h"

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject2D(Type, Layer)
	, m_OldPad{}
	, m_PosBase(VEC3_ZERO_INIT)
	, m_fBaseDistance(60.0f)
	, m_fSwingDistance(0.0f)
	, m_fDirection(0.0f)
	, m_fSwingSpeed(0.0f)
	, m_bLaunch(false)
	, m_Velocity(VEC3_ZERO_INIT)
{}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayer::~CPlayer()
{}

//============================================================================
// �X�V
//============================================================================
void CPlayer::Update()
{
	// ���N���X�̍X�V����
	CObject2D::Update();

	// ���˂���Ă��Ȃ���΃X�C���O����
	if (!m_bLaunch)
	{
		Swing();
	}
	else
	{
		// ���ˌ�͔�s����
		FlyAway();
	}

	// �����ڂ̉�]
	Rotation();
}

//============================================================================
// �`��
//============================================================================
void CPlayer::Draw()
{
	// ���N���X�̕`�揈��
	CObject2D::Draw();
}

//============================================================================
// ����
//============================================================================
CPlayer* CPlayer::Create(const JSON& Json)
{
	// ����
	CPlayer* p = DBG_NEW CPlayer(OBJ::TYPE::PLAYER, OBJ::LAYER::DEFAULT);

	// ���_����
	p->Initialize();

	// �e�N�X�`���̐ݒ�
	p->BindTex(CTextureManager::RefInstance().RefRegistry().BindAtKey("Sphere"));

	// �p�����[�^�̐ݒ�
	p->SetPosBase(useful::JsonConvertToVec3(Json["InitPos"]));
	p->SetSize(useful::JsonConvertToVec3(Json["Size"]));
	
	{
		CObject2D* pp = DBG_NEW CObject2D(OBJ::TYPE::NONE, OBJ::LAYER::DEFAULT);
		pp->BindTex(CTextureManager::RefInstance().RefRegistry().BindAtKey("Sphere"));
		pp->Initialize();
		pp->SetPos(useful::JsonConvertToVec3(Json["InitPos"]));
		pp->SetSize({ p->m_fBaseDistance, p->m_fBaseDistance, 0.0f });
		pp->SetCol({ 0.0f, 0.0f, 1.0f, 1.0f });
	}

	return p;
}

//============================================================================
// �X�C���O����
//============================================================================
void CPlayer::Swing()
{
	// �㏸�E�����̋��x
	const float fSpeedCoef = 0.005f;
	const float fDistanceCoef = 0.025f;

#if 0
	// �ߋ��̃X�e�B�b�N�X���Ƃ̍�
	int saX = CInputManager::RefInstance().GetPad()->GetJoyStickL().X - m_OldPad.GetJoyStickL().X;
	int saY = CInputManager::RefInstance().GetPad()->GetJoyStickL().Y - m_OldPad.GetJoyStickL().Y;

	// ���e���鍷
	const int nKyoou = 1;

	// ���X�e�B�b�N���K�`���K�`�����Ă�ƁA���p������A�X�C���O���������Z����Ă���
	if (abs(saX) > nKyoou && abs(saY) > nKyoou)
	{
		m_fSwingDistance = (m_fSwingDistance + fCoef * 2.0f) * (1.0f + fCoef);
	}
	else
	{
		// �X�C���O�����͏�Ɍ���
		m_fSwingDistance = (m_fSwingDistance + fCoef * 0.5f) * (1.0f - fCoef);
	}
#endif

	// ��U���X�e�B�b�N��|���Ă���ƁA���p������A�X�C���O���������Z����Ă���
	if (CInputManager::RefInstance().GetPad()->GetJoyStickL().X != 0 ||
		CInputManager::RefInstance().GetPad()->GetJoyStickL().Y != 0)
	{
		m_fSwingSpeed = (m_fSwingSpeed + fSpeedCoef * 0.1f) * (1.0f + fSpeedCoef);
		m_fSwingDistance = (m_fSwingDistance + fDistanceCoef * 0.1f) * (1.0f + fDistanceCoef);
	}
	else
	{
		// �X�C���O�����͏�Ɍ���
		m_fSwingSpeed = (m_fSwingSpeed - fSpeedCoef * 0.1f) * (1.0f - fSpeedCoef);
		m_fSwingDistance = (m_fSwingDistance - fDistanceCoef * 0.1f) * (1.0f - fDistanceCoef);
	}

	// �X�C���O���x�̉����E�����ݒ�
	if (m_fSwingSpeed < 0.0f)
	{
		m_fSwingSpeed = 0.0f;
	}
	else if (m_fSwingSpeed > 0.25f)
	{
		m_fSwingSpeed = 0.25f;
	}

	// �X�C���O�����̉����E�����ݒ�
	if (m_fSwingDistance < 0.0f)
	{
		m_fSwingDistance = 0.0f;
	}
	else if (m_fSwingDistance > 40.0f)
	{
		m_fSwingDistance = 40.0f;
	}

	// �ŏI�I�ȃX�C���O���x���A�v���C���[������
	m_fDirection += m_fSwingSpeed;

	// ���݂̍��W�擾
	Vec3 Pos = GetPos();

	// ���ˎ��ɁA���x��i�s������ۂ��߂Ɉʒu��ێ�
	Vec3 PosOld = Pos;

	// ��_�̍��W�����ɁA���݂̕��p���A��_���� + ���x����������
	Pos =
	{
		m_PosBase.x + sinf(m_fDirection) * (m_fBaseDistance + m_fSwingDistance),
		m_PosBase.y + cosf(m_fDirection) * (m_fBaseDistance + m_fSwingDistance),
		m_PosBase.z,
	};

	/* ���p�̑���Ɗp�x�̏o�� */
	if (useful::MIS::MyImGuiShortcut_BeginWindow("Player Swing"))
	{
		ImGui::DragFloat("BaseDistance", &m_fBaseDistance, 0.1f);

		ImGui::Text("Pos.X: %f", Pos.x);
		ImGui::Text("Pos.Y: %f", Pos.y);
		ImGui::Text("Distance: %f", m_fDirection);
		ImGui::Text("SwingDistance: %f", m_fSwingDistance);
		ImGui::Text("SwingSpeed: %f", m_fSwingSpeed);
	}
	ImGui::End();

	// �v�Z��̊p�x�� -�� �` �� �͈̔͂ɗ}����
	useful::WrapAngleToRange(m_fDirection);

	// �ʒu�𔽉f
	SetPos(Pos);

	// �p�b�h�̏����R�s�[
	m_OldPad = *CInputManager::RefInstance().GetPad();

	// ����
	if (CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
	{
		// �����X�C���O�����͂��Ȃ�
		m_bLaunch = true;

	    // �K�`�Ŕ�s������������߂�
		m_Velocity = 
		{
			(Pos.x - PosOld.x),
			(Pos.y - PosOld.y),
			0.0f
		};
	}
}

//============================================================================
// ��s
//============================================================================
void CPlayer::FlyAway()
{
	// ���݂̍��W�擾
	Vec3 Pos = GetPos();

	// ��s�����Ɉړ�
	Pos += m_Velocity;

	// ���Z����Ă�����W��ݒ�
	SetPos(Pos);
}

//============================================================================
// �����ڂ̉�]
//============================================================================
void CPlayer::Rotation()
{

}