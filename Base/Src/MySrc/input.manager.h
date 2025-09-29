//============================================================================
// 
// �}�l�[�W���[�A�w�b�_�t�@�C�� [managaer.h]
// Author : ���c����
// 
//============================================================================

// �C���N���[�h�K�[�h
#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "singleton.h"

#include "input_keyboard.h"
#include "input_mouse.h"
#include "input_pad.h"

//****************************************************
// �}�l�[�W���[�N���X���`
//****************************************************
class CInputManager final : public CSingleton<CInputManager>
{
	//****************************************************
	// �t�����h�錾
	//****************************************************
	friend struct std::default_delete<CInputManager>;
	friend CInputManager& CSingleton<CInputManager>::RefInstance();

public:

	//****************************************************
	// function
	//****************************************************
	
	//
	bool Initialize(HINSTANCE hi);
	bool Initialize() { return true; }
	void Finalize();

	/**
	 * ���C���ƂȂ�X�V�����ł�
	 */
	void Update();

	CInputKeyboard* GetKeyboard() const;	// �L�[�{�[�h
	CInputMouse*	GetMouse()	  const;	// �}�E�X
	CInputPad*		GetPad()	  const;	// �p�b�h

private:

	//****************************************************
	// special function
	//****************************************************
	CInputManager();				// �f�t�H���g�R���X�g���N�^
	~CInputManager() override;	// �f�X�g���N�^

	//****************************************************
	// function
	//****************************************************

	std::unique_ptr<CInputKeyboard>	m_upKeyboard;	// �L�[�{�[�h
	std::unique_ptr<CInputMouse>	m_upMouse;		// �}�E�X
	std::unique_ptr<CInputPad>		m_upPad;		// �p�b�h
};