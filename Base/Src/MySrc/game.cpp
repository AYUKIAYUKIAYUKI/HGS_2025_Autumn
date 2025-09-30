//============================================================================
// 
// �Q�[�� [game.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "game.h"
#include "sound.h"

// ���͎擾�p
#include "renderer.h"
#include "input.manager.h"

// �V�[���J�ڗp
#include "result.h"
#include "scene_manager.h"
#include "object.manager.h"

#include "object.text.h"
#include "planet.h"
#include "goal.h"
#include"player.h"
#include"GameBg.h"

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CGame::CGame()
	: CScene()
{
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CGame::~CGame()
{
	// �I������
	Finalize();
}

//============================================================================
// �X�V����
//============================================================================
void CGame::Update()
{
#ifdef _DEBUG
	CRenderer::RefInstance().AddText("�Q�[���@��", 1);
#endif // _DEBUG

	// ���̃V�[���֑J��
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		Change();
	}

	 // ���񂿂Ȃ̐���
	 auto p = CObjectText::Create(OpenJsonFile("Data\\JSON\\TEXT\\Unci.json"));
	 p->SetPos({ GetRandomValue(1000.0f), GetRandomValue(1000.0f) });
	 p->SetCol({ GetRandomValue(1.0f), GetRandomValue(1.0f), GetRandomValue(1.0f), 1.0f });
}

//============================================================================
// �`�揈��
//============================================================================
void CGame::Draw()
{
}

//============================================================================
// ���̃V�[����
//============================================================================
void CGame::Change()
{
	// �S�I�u�W�F�N�g����\��
	CObjectManager::RefInstance().SetDeathAllObject();

	// �T�E���h by AKR TNK
	CSound::GetInstance()->Stop(CSound::LABEL::BGM_0);

	// ���U���V�[���֕ύX
	up<CResult> upScene = CreateUniquePtr<CResult>();
	CSceneManager::RefInstance().ChangeScene(std::move(upScene));
}

//============================================================================
// ����������
//============================================================================
bool CGame::Initialize()
{
	// �T�E���h by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Game");

	//�������w�i�𐶐�
	CGameBg::Create();

	//�������f���𐶐�
	D3DXVECTOR3 Pos;
	Pos = { 500.0f,700.0f,0.0f };
	CPlanet::Create(Pos);
	Pos = { 1000.0f,200.0f,0.0f };
	CPlanet::Create(Pos);

	//�������S�[���𐶐�
	Pos = { 1500.0f,500.0f,0.0f };
	CGoal::Create(Pos);

	//�������v���C���[�𐶐�
	CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));

	return true;
}

//============================================================================
// �I������
//============================================================================
void CGame::Finalize()
{
}