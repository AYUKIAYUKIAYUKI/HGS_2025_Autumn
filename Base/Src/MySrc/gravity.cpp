//============================================================================
// 
// ����[gravity.cpp]
// Author : �~�c�u�^
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "gravity.h"
#include "object.manager.h"
#include "player.h"

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �R���X�g���N�^
//============================================================================
CGravity::CGravity(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject2D(Type, Layer)
{
	m_GravityForce = 0.0f;
	m_GravityRadius = 0.0f;
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CGravity::~CGravity()
{

}

//===========================================================================================================
// �X�V
//===========================================================================================================
void CGravity::Update()
{
	float dis = CalDistance();

	Efficacy(dis);
}

//===========================================================================================================
// ����
//===========================================================================================================
CGravity* CGravity::Create(D3DXVECTOR3 pos, float radius)
{
	// �C���X�^���X�𐶐�
	CGravity* pGravity = DBG_NEW CGravity(OBJ::TYPE::GRAVITY, OBJ::LAYER::DEFAULT);

	// 2D�I�u�W�F�N�g�̏����ݒ�
	pGravity->Initialize();

	pGravity->SetPos(pos);
	pGravity->SetSize({ radius,radius,0.0f });
	pGravity->m_GravityRadius = radius * 2.0f;
	
	return pGravity;
}

//===========================================================================================================
// ���͂ƃv���C���[�̋������v�Z
//===========================================================================================================
float CGravity::CalDistance()
{
	// �v���C���[�̌���
	std::list<CObject*>ol = CObjectManager::RefInstance().RefObjList(OBJ::TYPE::PLAYER);	// �v���C���[�̃��X�g���擾
	CObject* pobj = ol.front();	// �擪����
	CPlayer* pPlayer = DownCast<CPlayer, CObject>(pobj);	// �_�E���L���X�g

	// �f���̒��S
	D3DXVECTOR3 pos = GetPos();

	// �v���C���[�̏��
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	
	float cal_a = pos.x - PlayerPos.x;	// x �̌v�Z
	float cal_b = pos.y - PlayerPos.y;	// y �̌v�Z

	// �v�Z��������(����)
	float distance = sqrt(cal_a * cal_a + cal_b * cal_b);

	return distance;
}

//===========================================================================================================
// ���͂̌���
//===========================================================================================================
void CGravity::Efficacy(float dis)
{
	// �v���C���[�̌���
	std::list<CObject*>ol = CObjectManager::RefInstance().RefObjList(OBJ::TYPE::PLAYER);	// �v���C���[�̃��X�g���擾
	CObject* pobj = ol.front();	// �擪����
	CPlayer* pPlayer = DownCast<CPlayer, CObject>(pobj);	// �_�E���L���X�g

	// �v���C���[�̏��
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	float PlayerRadius = pPlayer->GetSize().x;

	// �f���̒��S
	D3DXVECTOR3 pos = GetPos();

	float DirectionMove = atan2f(pos.x - PlayerPos.x, pos.y - PlayerPos.y);	// ���݂̈ړ�����

	float length = pPlayer->GetLength();

	D3DXVECTOR3 velo = pPlayer->GetVelocity();

	float a = 0.001f;

	if (dis>=400)
	{
		m_GravityForce = 0.0f;
	}
	else if (dis < 400 && dis >= 300)
	{
		m_GravityForce = 0.001f+ a;
	}
	else if (dis < 300 && dis >= 200)
	{
		m_GravityForce = 0.0035f+ a;
	}
	else if (dis < 200 && dis >= 50)
	{
		m_GravityForce = 0.005f+ a;
	}
	else
	{
		m_GravityForce = 0.1f+ a;
	}

	// ��������̉~�̑傫���ȉ��̎�
	if (dis <= m_GravityRadius + PlayerRadius)
	{
		// �ړ��l�̐ݒ�
		velo = (velo + (D3DXVECTOR3(sinf(DirectionMove) * pPlayer->GetLength() * m_GravityForce/*+(dis*0.0001f)*/, cosf(DirectionMove) * pPlayer->GetLength() * m_GravityForce/*+ (dis * 0.0001f)*/, 0.0f)));
		pPlayer->SetVelocity(velo);
	}

#if _DEBUG
	/* ���p�̑���Ɗp�x�̏o�� */
	if (useful::MIS::MyImGuiShortcut_BeginWindow("aaaaaaaaaa"))
	{
		ImGui::Text("distance: %f", dis);
		ImGui::Text("velo: %f , %f", velo.x, velo.y);
	}
	ImGui::End();
#endif
}
