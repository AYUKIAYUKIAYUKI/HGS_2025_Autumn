//============================================================================
// 
// �E�B���h�E�A�w�b�_�[�t�@�C�� [window.h]
// Author : ���c����
// 
//============================================================================

#pragma once

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "singleton.h"

//****************************************************
// �E�B���h�E�N���X�̒�`
//****************************************************
class CWindow final : public CSingleton<CWindow>
{
	//****************************************************
	// �t�����h�錾
	//****************************************************
	friend struct std::default_delete<CWindow>;
	friend CWindow& CSingleton<CWindow>::RefInstance();

	//****************************************************
	// �ÓI�����o�萔�̒�` (����J)
	//****************************************************

	// �E�B���h�E�N���X�̖��O
	static constexpr const char* s_pClassName = "Window Class";

	// �E�B���h�E�̖��O
	static constexpr const char* s_pWindowName = "Base";

public:

	//****************************************************
	// �ÓI�����o�ϐ��̒�` (���J)
	//****************************************************

	// �E�B���h�E����
	static const WORD  WWINDOW_WIDTH;
	static const float FWINDOW_WIDTH;

	// �E�B���h�E�c��
	static const WORD  WWINDOW_HEIGHT;
	static const float FWINDOW_HEIGHT;

	//****************************************************
	// function
	//****************************************************

	// ����������
	bool Initialize(HINSTANCE hInstance);
	bool Initialize() { return true; }

	// �I������
	void Finalize();

	// ���b�Z�[�W���[�v
	// fp -> �X�V����
	template <typename T>
	void MessageLoop(T&& fpMainLoop);

	//****************************************************
	// inline function
	//***************************************************

	// �N���C�A���g�̈�̃T�C�Y�̎擾
	inline RECT GetWindowRect() const { return m_Rect; }

	// �E�B���h�E�n���h���̎擾
	inline HWND GetWindowHandle() const { return m_hWnd; }

private:

	//****************************************************
	// special function
	//****************************************************
	CWindow();           // �f�t�H���g�R���X�g���N�^
	~CWindow() override; // �f�X�g���N�^

	//****************************************************
	// function
	//****************************************************
	void InitializeWindowClass(HINSTANCE hInstance); // �E�B���h�E�N���X�̏���������
	void InitializeWindowRect();					 // �N���C�A���g�̈�̏���������
	void MyCreateWindow(HINSTANCE hInstance);		 // �E�B���h�E�̐���
	
	void ChangeMode(); // ���[�h�ύX

	// �E�C���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//****************************************************
	// data
	//****************************************************
	WNDCLASSEX m_Wcex;	  // �E�B���h�E�N���X
	RECT	   m_Rect;	  // �N���C�A���g�̈�̃T�C�Y
	DWORD	   m_dwStyle; // �E�B���h�E�̕\���X�^�C��
	HWND	   m_hWnd;	  // �E�B���h�E�n���h��
	MSG		   m_Msg;	  // ���b�Z�[�W���i�[����ϐ�
};

//============================================================================
// ���b�Z�[�W���[�v
//============================================================================
template <typename T>
void CWindow::MessageLoop(T&& fpMainLoop)
{
	while (true)
	{
		// ���b�Z�[�W���m�F
		if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUIT�̃��b�Z�[�W���󂯎��ƁA���b�Z�[�W���[�v�𔲂���
			if (m_Msg.message == WM_QUIT)
			{
				break;
			}

			// ���b�Z�[�W�̐ݒ�
			TranslateMessage(&m_Msg); // ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
			DispatchMessage(&m_Msg);  // �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
		}
		else
		{
			// ���C�����[�v���s
			fpMainLoop();
		}
	}
}