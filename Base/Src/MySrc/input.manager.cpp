//============================================================================
// 
// �}�l�[�W���[ [manager.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "input.manager.h"
#include "window.h"

//****************************************************
// �������O��Ԃ��` 
//****************************************************
namespace
{
	/* ���̖��O��Ԃ��폜���Ă������� */

	// �����t��������
	template <typename T> std::unique_ptr<T> DedicatedInitialize(HINSTANCE hInstance, HWND hWnd)
	{
		useful::up<T> upInstance = std::make_unique<T>();

		if (!upInstance)
		{
			return nullptr;
		}

		if (FAILED(upInstance->Init(hInstance, hWnd)))
		{
			return nullptr;
		}

		return upInstance;
	}

	// �����t�����
	template <typename T> void DedicatedRelease(T* pInstance)
	{
		if (pInstance)
		{
			pInstance->Uninit();
		}
	}
};

//============================================================================
// �X�V����
//============================================================================
void CInputManager::Update()
{
	// �L�[�{�[�h�̍X�V
	m_upKeyboard->Update();

	// �}�E�X�̍X�V
	m_upMouse->Update();

	// �p�b�h�̍X�V
	m_upPad->Update();
}

//============================================================================
// �L�[�{�[�h�̎擾
//============================================================================
CInputKeyboard* CInputManager::GetKeyboard() const
{
	return m_upKeyboard.get();
}

//============================================================================
// �}�E�X�̎擾
//============================================================================
CInputMouse* CInputManager::GetMouse() const
{
	return m_upMouse.get();
}

//============================================================================
// �p�b�h�̎擾
//============================================================================
CInputPad* CInputManager::GetPad() const
{
	return m_upPad.get();
}

// �R���X�g���N�^
//============================================================================
CInputManager::CInputManager() :
	m_upKeyboard(nullptr),
	m_upMouse(nullptr),
	m_upPad(nullptr)
{}

//============================================================================
// �f�X�g���N�^
//============================================================================
CInputManager::~CInputManager()
{
	// �I������
	Finalize();
}

//============================================================================
// ����������
//============================================================================
bool CInputManager::Initialize(HINSTANCE hInstance)
{
	HWND hWnd = CWindow::RefInstance().GetWindowHandle();

	// �L�[�{�[�h�̐���
	m_upKeyboard = DedicatedInitialize<CInputKeyboard>(hInstance, hWnd);

	// �}�E�X�̐���
	m_upMouse = DedicatedInitialize<CInputMouse>(hInstance, hWnd);

	// �p�b�h�̐���
	m_upPad = DedicatedInitialize<CInputPad>(hInstance, hWnd);

	return true;
}

// �I������
//============================================================================
void CInputManager::Finalize()
{
	// �p�b�h�̏I������
	DedicatedRelease<CInputPad>(m_upPad.get());

	// �}�E�X�̏I������
	DedicatedRelease<CInputMouse>(m_upMouse.get());

	// �L�[�{�[�h�̏I������
	DedicatedRelease<CInputKeyboard>(m_upKeyboard.get());
}