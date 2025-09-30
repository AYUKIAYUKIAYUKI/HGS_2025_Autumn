//============================================================================
// 
// �^�C�g�� [title.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "title.h"
#include "sound.h"

// ���͎擾�p
#include "renderer.h"
#include "input.manager.h"

// �V�[���J�ڗp
#include "tutorial.h"
#include "scene_manager.h"
#include "object.manager.h"

#include "object.2D.h"
#include "texture.manager.h"
#include "object_X.h"
#include "object.text.h"
#include"TitleImage.h"

//****************************************************
// �T���v���F2D
//****************************************************
namespace
{

	// ���̃|�C���^�̓N���X�̃����o�ɂ���Ɖ���
	CObject2D* m_p = nullptr;

	// �ǂ������[�J���ɒu�����p�����[�^
	D3DXVECTOR3 PosPos = { 300.0f, 300.0f, 0.0f };
	D3DXVECTOR3 SizeSize = { 100.0f, 100.0f, 0.0f };

	// ���������ɍ��A�����o�Ɏ��T���v��
	auto ffppInit = []() -> void
	{
		// �܂��̓C���X�^���X�쐬�A�|�C���^���󂯎��
		CObject2D* p = CObject2D::Create(
			OBJ::TYPE::NONE,                                               // 1, �^�C�v - OBJ�X�R�[�v���ɂ���܂�
			OBJ::LAYER::DEFAULT,                                           // 2, ���C���[ - OBJ�X�R�[�v��
			CTextureManager::RefInstance().RefRegistry().BindAtKey("Unko") // 3, �e�N�X�`���w��̎��� -  ��{"Unko"�̂Ƃ������ς���܂�
		);

		// �ς������p�����[�^���ASet��ʂ��Đݒ�
		p->SetPos(PosPos);
		p->SetSize(SizeSize);

		/* �Ō�Ƀ����o�Ɏ������Ƃ��� */
		m_p = p;
	};

	// �X�V���ɍ��A�G�f�B�b�g����T���v��
	auto ffppEdit = []() -> void
	{
		if (useful::MIS::MyImGuiShortcut_BeginWindow("ffppEdit", { 300, 100 }))
		{
			useful::MIS::MyImGuiShortcut_DragVector("PosPos", PosPos, 1.0f);
			useful::MIS::MyImGuiShortcut_DragVector("SizeSize", SizeSize, 1.0f);
			ImGui::End();
		}

		m_p->SetPos(PosPos);
		m_p->SetSize(SizeSize);
	};
}

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CTitle::CTitle()
	: CScene()
{}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTitle::~CTitle()
{
	// �I������
	Finalize();
}

//============================================================================
// �X�V����
//============================================================================
void CTitle::Update()
{
#ifdef _DEBUG
	CRenderer::RefInstance().AddText("�|�C�|�C", 1);
#endif // _DEBUG

	// ���ꂪ�X�V�T���v���ł�
	//ffppEdit();

	// ���񂿂Ȃ̐���
	for (int i = 0; i < 5; i++)
	{
		auto p = CObjectText::Create(OpenJsonFile("Data\\JSON\\TEXT\\Title.json"));
		p->SetPos({ GetRandomValue(1000.0f), GetRandomValue(1000.0f) });
		p->SetCol({ GetRandomValue(1.0f), GetRandomValue(1.0f), GetRandomValue(1.0f), 1.0f });
	}


	// ���̃V�[���֑J��
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::START))
	{
		Change();
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CTitle::Draw()
{}

//============================================================================
// ���̃V�[����
//============================================================================
void CTitle::Change()
{
	// �S�I�u�W�F�N�g����\��
	CObjectManager::RefInstance().SetDeathAllObject();

	// �T�E���h by AKR TNK
	CSound::GetInstance()->Stop(CSound::LABEL::BGM_0);

	// �`���[�g���A���V�[���֕ύX
	up<CTutorial> upScene = CreateUniquePtr<CTutorial>();
	CSceneManager::RefInstance().ChangeScene(std::move(upScene));
}

//============================================================================
// ����������
//============================================================================
bool CTitle::Initialize()
{
	// �T�E���h by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Title");

	CObject_X::Create(OBJ::TYPE::NONE, OBJ::LAYER::DEFAULT, nullptr);

	// ���ꂪ�������T���v���ł�
	//ffppInit();

	return true;
}

//============================================================================
// �I������
//============================================================================
void CTitle::Finalize()
{}