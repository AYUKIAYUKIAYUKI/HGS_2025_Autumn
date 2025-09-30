//============================================================================
// 
// ���̓w�b�_�[�t�@�C�� [gravity.h]
// Author : �~�c�u�^
// 
//============================================================================
#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.2D.h"

//****************************************************
// �v���C���[�N���X�̒�`
//****************************************************
class CGravity :public CObject2D
{
public:
	// <special function>
	CGravity(OBJ::TYPE Type, OBJ::LAYER Layer);
	~CGravity() override;		// �f�X�g���N�^

	// <function>
	void Update() override;	// �X�V����

	// <static function>
	static CGravity* Create(D3DXVECTOR3 pos, float radius);	// ����

private:

	//****************************************************
	// �ÓI�萔���`
	//****************************************************
	const float GRAVITY_FORCE = 10.0f;	// ���͂̑傫��

	// <function>
	float CalDistance();		// ���͂ƃv���C���[�̋������v�Z
	void Efficacy(float dis);	// ���͂̌���

	// <Data>
	float m_GravityRadius;	// ���͂̓͂��͈�
	float m_GravityForce;	// ���͂̑傫��
};