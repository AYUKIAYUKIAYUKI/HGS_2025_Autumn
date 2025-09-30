//============================================================================
// 
// �Q�[���V�[���̔w�i�A�w�b�_�[�t�@�C�� [GameBg.h]
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
class CGameBg : public CObject2D
{
public:

	// <special function>
	CGameBg(OBJ::TYPE Type, OBJ::LAYER Layer);
	~CGameBg() override;		// �f�X�g���N�^

	// <function>
	void Update() override;	// �X�V����
	void Draw() override;	// �`�揈��

	// <static function>
	static CGameBg* Create();	// ����

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