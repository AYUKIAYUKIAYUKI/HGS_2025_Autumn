//============================================================================
// 
// �S�[���A�w�b�_�[�t�@�C�� [goal.h]
// Author : �㓡�D�P
// 
//============================================================================

#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.2D.h"

//****************************************************
// �f���N���X�̒�`
//****************************************************
class CGoal : public CObject2D
{
public:

	// <special function>
	CGoal(OBJ::TYPE Type, OBJ::LAYER Layer);
	~CGoal() override;		// �f�X�g���N�^

	// <function>
	void Update() override;	// �X�V����
	void Draw() override;	// �`�揈��

	// <static function>
	static CGoal* Create(D3DXVECTOR3 Pos);	// ����

private:

	//****************************************************
	// �ÓI�萔���`
	//****************************************************
	//static constexpr float MAX_VELOCITY = 0.5f;		// �����x���
	//static constexpr float JUMP_FORCE = 6.0f;		// �W�����v��
	//static constexpr float BRAKING_FORCE = 0.9f;	// ������

	// <function>
	void Control();			// ����
	void Rotation();		// ��]
	void AdjustRotAngle();	// �����𒲐�����
	void Braking();			// ��������
	void GravityFall();		// �d�͉���
	void AdjustPos();		// �ʒu�𒲐�

	// <Data>
};