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

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CGravity::~CGravity()
{

}

void CGravity::Update()
{
	D3DXVECTOR3 pos = GetPos();

	// �~�Q�̏��
	D3DXVECTOR3 PlayerPos = { 25.0f ,30.0f ,0.0f };
	float PlayerRadius = 8.0f;

	float cal_a = pos.x - PlayerPos.x;	// x �̌v�Z
	float cal_b = pos.y - PlayerPos.y;	// y �̌v�Z

	// �v�Z��������(����)
	float distance = sqrt(cal_a * cal_a + cal_b * cal_b);

	// ��������̉~�̑傫���ȉ��̎�
	if (distance <= m_GravityRadius + PlayerRadius)
	{

	}
}

CGravity* CGravity::Create(D3DXVECTOR3 pos, float radius)
{
	return nullptr;
}
