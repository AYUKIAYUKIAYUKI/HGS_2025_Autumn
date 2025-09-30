//============================================================================
// 
// �v���C���[�A�w�b�_�[�t�@�C�� [player.h]
// Author : ���c����
// 
//============================================================================

#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.2D.h"
#include "input.manager.h"

//****************************************************
// �v���C���[�N���X�̒�`
//****************************************************
class CPlayer : public CObject2D
{
public:

	// <special function>
	CPlayer(OBJ::TYPE Type, OBJ::LAYER Layer);
	~CPlayer() override;		// �f�X�g���N�^

	// <function>
	void Update() override;	// �X�V����
	void Draw() override;	// �`�揈��

	// <static function>
	static CPlayer* Create(const JSON& Json);	// ����

	inline void SetPosBase(D3DXVECTOR3 PosBase) { m_PosBase = PosBase; };
	inline void SetVelocity(D3DXVECTOR3 velo) { m_Velocity = velo; }
	inline D3DXVECTOR3 GetVelocity() { return m_Velocity; }
private:

	// <function>
	void Swing();    // �X�C���O����
	void FlyAway();  // ���ł���
	void Rotation(); // �����ڂ̉�]

	CInputPad m_OldPad;		// �Â��p�b�h
	D3DXVECTOR3 m_PosBase;	// ��_�̍��W
	float m_fBaseDistance;	// ��_�Ƃ̋���
	float m_fSwingDistance;	// �X�C���O����
	float m_fDirection;		// ���݂̕��p
	float m_fSwingSpeed;	// �X�C���O���x

	bool m_bLaunch;	// ���˂���
	D3DXVECTOR3 m_Velocity;	// �����������
};