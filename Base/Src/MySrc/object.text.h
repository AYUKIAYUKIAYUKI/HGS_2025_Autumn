//============================================================================
// 
// �e�L�X�g�I�u�W�F�N�g�A�w�b�_�[�t�@�C�� [object.text.h]
// Author : ���c����
// 
//============================================================================

#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.h"

//****************************************************
// �e�L�X�g�I�u�W�F�N�g�N���X�̒�`
//****************************************************
class CObjectText : public CObject
{
public:

	//****************************************************
	// special function
	//****************************************************
	CObjectText(OBJ::TYPE Type, OBJ::LAYER Layer); // �R���X�g���N�^
	~CObjectText() override;                       // �f�X�g���N�^

	//****************************************************
	// function
	//****************************************************

	// ����������
	bool Initialize() {};

	// �I������
	void Finalize() {};

	// �X�V����
	void Update() override;

	// �`�揈��
	void Draw() override;

	// <static function>
	static CObjectText* Create(const JSON& Json); // ����

	inline void SetPos(D3DXVECTOR2 Pos) { m_Pos = Pos; }
	inline void SetCol(D3DXCOLOR Col) { m_Col = Col; }

private:

	//****************************************************
	// function
	//****************************************************
	void TextAnimation(); // �e�L�X�g����̃A�j���[�V����

	//****************************************************
	// data
	//****************************************************
	LPD3DXFONT  m_pFont;       // �t�H���g�̃|�C���^
	std::string m_sText;       // ����
	std::string m_sTextTarget; // �ڕW����
	int         m_nLimit;      // �\������
	int         m_nSpeed;      // �\�����x
	int         m_nStop;       // �x���J�E���^�[
	D3DXVECTOR2 m_Pos;         // �ʒu
	D3DXVECTOR2 m_Size;        // �T�C�Y
	D3DXCOLOR   m_Col;         // �F

	int m_nGhostTime;
	bool m_bWave;
	D3DXVECTOR2 m_WavePos;
	float m_fWaveCoef;
};