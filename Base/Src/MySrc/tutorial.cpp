//============================================================================
// 
// �`���[�g���A�� [tutorial.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "tutorial.h"
#include "sound.h"

// ���͎擾�p
#include "renderer.h"
#include "input.manager.h"

// �V�[���J�ڗp
#include "game.h"
#include "scene_manager.h"
#include "object.manager.h"

#include "player.h"

// �Q�[���Ɏʂ��p
namespace
{
	// �v���C���[�̃|�C���^
	CPlayer* m_pPlayer = nullptr;

	// �v���C���[�̃Z�b�g�A�b�v
	auto fpInitialize = []() -> void
	{
		m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
	};

	// �v���C���[�����X�V
	auto fpUpdate = []() -> void
	{
		D3DXVECTOR3 PosPos = m_pPlayer->GetPos();
		D3DXVECTOR3 SizeSize = m_pPlayer->GetSize();

		if (useful::MIS::MyImGuiShortcut_BeginWindow("fpUpdate", { 300, 100 }))
		{
			useful::MIS::MyImGuiShortcut_DragVector("PosPos", PosPos, 1.0f);
			useful::MIS::MyImGuiShortcut_DragVector("SizeSize", SizeSize, 1.0f);
			ImGui::End();
		}

		m_pPlayer->SetPos(PosPos);
		m_pPlayer->SetSize(SizeSize);
	};

	// �v���C���[�̃N���[���A�b�v
	auto fpFinalize = []() -> void
	{
		m_pPlayer = nullptr;
	};
}

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CTutorial::CTutorial()
	: CScene()
{}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTutorial::~CTutorial()
{
	// �I������
	Finalize();
}

//============================================================================
// �X�V����
//============================================================================
void CTutorial::Update()
{
	CRenderer::RefInstance().AddText("�X�e�B�b�N���X���ĉ񂵂Ȃ����B������A�œ����Ȃ����B", 1);

	//fpUpdate();

	// ���̃V�[���֑J��
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::START) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
		CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
	{
		Change();
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CTutorial::Draw()
{}

//============================================================================
// ���̃V�[����
//============================================================================
void CTutorial::Change()
{
	// �S�I�u�W�F�N�g����\��
	CObjectManager::RefInstance().SetDeathAllObject();

	// �T�E���h by AKR TNK
	CSound::GetInstance()->Stop(CSound::LABEL::BGM_0);

	// �ްуV�[���֕ύX
	up<CGame> upScene = CreateUniquePtr<CGame>();
	CSceneManager::RefInstance().ChangeScene(std::move(upScene));
}

//============================================================================
// ����������
//============================================================================
bool CTutorial::Initialize()
{
	// �T�E���h by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Tutorial");

	// �v���C���[�̐���
	//fpInitialize();

	return true;
}

//============================================================================
// �I������
//============================================================================
void CTutorial::Finalize()
{
	fpFinalize();
}