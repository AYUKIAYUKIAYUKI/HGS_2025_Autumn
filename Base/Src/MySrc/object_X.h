//============================================================================
// 
// X�I�u�W�F�N�g�A�w�b�_�t�@�C�� [object_X.h]
// Author : ���c����
// 
//============================================================================

#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.h"
#include "X_manager.h"

//****************************************************
// X�I�u�W�F�N�g�N���X
//****************************************************
class CObject_X : public CObject
{
public:

	//****************************************************
	// special function
	//****************************************************
	CObject_X(OBJ::TYPE Type, OBJ::LAYER Layer); // �R���X�g���N�^
	~CObject_X() override;                       // �f�X�g���N�^

	//****************************************************
	// function
	//****************************************************

	// ����������
	bool Initialize();

	// �I������
	void Finalize();

	// �X�V����
	void Update() override;

	// �`�揈��
	void Draw() override;

	// <getter/setter>
	CX_Manager::MODEL* GetModel();				// ���f���擾
	void BindModel(CX_Manager::MODEL* pModel);	// ���f������

	// <getter/setter>
	const D3DXVECTOR3& GetRot() const;	// �����擾
	void SetRot(D3DXVECTOR3 Rot);		// �����ݒ�

	// <getter/setter>
	const D3DXVECTOR3& GetPos() const;	// ���W�擾
	void SetPos(D3DXVECTOR3 Pos);		// ���W�ݒ�

	// <getter/setter>
	const D3DXVECTOR3& GetScale() const;	// �k�ڎ擾
	void SetScale(D3DXVECTOR3 Scale);		// �k�ڐݒ�

	// <getter/setter>
	const D3DXCOLOR& GetCol() const;	// �F���擾
	void SetCol(D3DXCOLOR Col);			// �F��ݒ�

	// <getter/setter>
	const bool& GetUseCol() const;	// �F���f���擾
	void SetUseCol(bool Col);		// �F���f��ݒ�

	// <static function>
	static CObject_X* Create(OBJ::TYPE Type, OBJ::LAYER Layer, const JSON& Json);								// ����

	// ���[���h�s����擾
	inline const D3DXMATRIX& GetMtxWorld() const { return m_MtxWorld; };

private:

	/// <summary> �A���t�@�l�������p </summary>
	static constexpr float ALPHA_INIT = 1.0f;

	// <function>
	void AdjustRotAngle();	// �����𒲐�����
	void SetMtxWorld();		// ���[���h�s��ݒ�

	// <data>
	CX_Manager::MODEL*	m_pModel;	// ���f�����
	D3DXVECTOR3			m_Rot;		// ����
	D3DXVECTOR3			m_Pos;		// ���W
	D3DXVECTOR3			m_Scale;	// �k��
	D3DXCOLOR			m_Col;		// �F
	bool				m_bUseCol;	// �F���f
	D3DXMATRIX			m_MtxWorld;	// ���[���h�s��
};