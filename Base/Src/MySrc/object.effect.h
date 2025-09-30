//============================================================================
// 
// ���ӂ���t�A�w�b�_�[�t�@�C�� [object.2D.h]
// Author : ���c����
// 
//============================================================================

#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.2D.h"


class CObjectEffect : public CObject2D
{
public:

	//****************************************************
	// special function
	//****************************************************
	CObjectEffect(OBJ::TYPE Type, OBJ::LAYER Layer); // �R���X�g���N�^
	~CObjectEffect() override;                       // �f�X�g���N�^

	//****************************************************
	// function
	//****************************************************

	// ����������
	bool Initialize()
	{
		CObject2D::Initialize();
		return true;
	}

	// �I������
	void Finalize()
	{

	}

	// �X�V����
	void Update() override
	{
		CObject2D::Update();

		// �ړ�
		useful::ExponentialDecay(m_Vel, useful::VEC3_ZERO_INIT, 0.15f);
		D3DXVECTOR3 pos = GetPos();
		pos += m_Vel;
		SetPos(pos);

		if (m_nLimit > 0)
		{
			// �\�����Ԃ��J�E���g�_�E��
			--m_nLimit;

			// ������20f�O����
			if (m_nLimit < m_nGhostTime)
			{
				// �A���t�@�l��A�������Ĕ����Ȃ��Ă���
				auto Col = GetCol();
				Col.a = (1.0f / static_cast<float>(m_nGhostTime)) * m_nLimit;
				SetCol(Col);

				D3DXVECTOR3 rot = GetRot();
				rot.z = Col.a;
				SetRot(rot);
			}
		}
		else
		{
			SetDeath();
		}
	}

	// �`�揈��
	void Draw() override
	{
		CObject2D::Draw();
	}

	// <static function>
	static CObjectEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 vel, D3DXVECTOR3 Size, const JSON& json); // ����

	int m_nLimit;
	int m_nGhostTime;
	D3DXVECTOR3 m_Vel;
};