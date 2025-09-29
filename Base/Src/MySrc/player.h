////============================================================================
//// 
//// �v���C���[�A�w�b�_�[�t�@�C�� [player.h]
//// Author : ���c����
//// 
////============================================================================
//
//#pragma once
//
////****************************************************
//// �C���N���[�h�t�@�C��
////****************************************************
//#include "object_X.h"
//
//// X���f�����p
//#include "X_manager.h"
//
////****************************************************
//// �v���C���[�N���X�̒�`
////****************************************************
//class CPlayer : public CObject_X
//{
//public:
//
//	// <special function>
//	CPlayer(OBJ::TYPE Type, OBJ::LAYER Layer);
//	~CPlayer() override;		// �f�X�g���N�^
//
//	// <function>
//	void Update() override;	// �X�V����
//	void Draw() override;	// �`�揈��
//
//	// <static function>
//	static CPlayer* Create(const JSON& Json);	// ����
//
//private:
//
//	//****************************************************
//	// �ÓI�萔���`
//	//****************************************************
//	static constexpr float MAX_VELOCITY = 0.5f;		// �����x���
//	static constexpr float JUMP_FORCE = 6.0f;		// �W�����v��
//	static constexpr float BRAKING_FORCE = 0.9f;	// ������
//
//	// <function>
//	void Control();			// ����
//	void Rotation();		// ��]
//	void AdjustRotAngle();	// �����𒲐�����
//	void Braking();			// ��������
//	void GravityFall();		// �d�͉���
//	void AdjustPos();		// �ʒu�𒲐�
//
//	// <Data>
//	int			m_nLeftNumJump;	// �W�����v�\��
//	float		m_fJumpForce;	// �W�����v��
//	D3DXVECTOR3 m_Velocity;		// �����x
//	D3DXVECTOR3 m_PosTarget;	// �ڕW�ʒu
//	D3DXVECTOR3 m_RotTarget;	// �ڕW����
//	D3DXVECTOR3 m_RotTarget;	// �ڕW�T�C�Y
//};