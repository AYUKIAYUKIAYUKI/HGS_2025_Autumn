//============================================================================
// 
// �Q�[�� [game.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "game_1.h"
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
#include "window.h"
#include"planet.h"
//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CGame_1::CGame_1()
	: CScene()
	, m_pPlayer(nullptr)
	, m_pGoal(nullptr)
{
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CGame_1::~CGame_1()
{
	// �I������
	Finalize();
}

//============================================================================
// �X�V����
//============================================================================
void CGame_1::Update()
{
#ifdef _DEBUG
	//CRenderer::RefInstance().AddText("�Q�[���@��", 1);
#endif // _DEBUG

	// �@ �v���C���[����ʊO��
	if (m_pPlayer)
	{
		Vec3 Pos = m_pPlayer->GetPos();

		if (Pos.x < 0.0f || Pos.x > CWindow::FWINDOW_WIDTH ||
			Pos.y < 0.0f || Pos.y > CWindow::FWINDOW_HEIGHT)
		{
			// �A �����쐬
			CObjectText::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\TEXT\\Failed.json"));

			// �B ������v���C���[���폜
			if (m_pPlayer)
			{
				m_pPlayer->SetDeath();
				m_pPlayer = nullptr;
			}

			// �C �V�����v���C���[���쐬
			m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
		}
		else if (m_pGoal->Judge())
		{
			Change();
		}
	}


	for (auto obj : m_PlanetList)
	{
		if (obj->Judge())
		{
			// �A �����쐬
			CObjectText::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\TEXT\\Failed.json"));

			// �B ������v���C���[���폜
			if (m_pPlayer)
			{
				m_pPlayer->SetDeath();
				m_pPlayer = nullptr;
			}

			// �C �V�����v���C���[���쐬
			m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
			break;
		}
	}

	// ���̃V�[���֑J��
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		//Change();
	}

#if 0
	// ���񂿂Ȃ̐���
	auto p = CObjectText::Create(OpenJsonFile("Data\\JSON\\TEXT\\Unci.json"));
	p->SetPos({ GetRandomValue(1000.0f), GetRandomValue(1000.0f) });
	p->SetCol({ GetRandomValue(1.0f), GetRandomValue(1.0f), GetRandomValue(1.0f), 1.0f });
#endif
}

//============================================================================
// �`�揈��
//============================================================================
void CGame_1::Draw()
{
}

//============================================================================
// ���̃V�[����
//============================================================================
void CGame_1::Change()
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
bool CGame_1::Initialize()
{
	// �T�E���h by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Game");

	//�������w�i�𐶐�
	CGameBg::Create();

	//�������f���𐶐�
	D3DXVECTOR3 Pos;
	Pos = { 1500.0f,720.0f,0.0f };
	m_PlanetList.push_back(CPlanet::Create(Pos));
	Pos = { 1000.0f,100.0f,0.0f };
	m_PlanetList.push_back(CPlanet::Create(Pos));

	//�������S�[���𐶐�
	Pos = { 1500.0f,450.0f,0.0f };
	m_pGoal = CGoal::Create(Pos);

	//�������v���C���[�𐶐�
	if (!m_pPlayer)
	{
		m_pPlayer = CPlayer::Create(useful::OpenJsonFileMaybeThrow("Data\\JSON\\PLAYER\\Player.json"));
	}

	return true;
}

//============================================================================
// �I������
//============================================================================
void CGame_1::Finalize()
{
}