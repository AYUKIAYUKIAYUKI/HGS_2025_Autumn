//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.effect.h"
#include "texture.manager.h"

//****************************************************
// using�f�B���N�e�B�u
//****************************************************
using namespace useful;

//============================================================================
// �R���X�g���N�^
//============================================================================
CObjectEffect::CObjectEffect(OBJ::TYPE Type, OBJ::LAYER Layer)
	: CObject2D(Type, Layer)
	, m_nLimit(30)
	, m_nGhostTime(10)
	, m_Vel(VEC3_ZERO_INIT)
{

}

//
CObjectEffect::~CObjectEffect()
{

}

CObjectEffect* CObjectEffect::Create(D3DXVECTOR3 pos , D3DXVECTOR3 vel, const JSON& json)
{
	CObjectEffect* p = DBG_NEW CObjectEffect(OBJ::TYPE::NONE, OBJ::LAYER::UI);

	p->Initialize();

	p->BindTex(CTextureManager::RefInstance().RefRegistry().BindAtKey("Unko"));

	p->m_Vel = vel;

	// ���W��K���ɂ��炷
	pos += {
		useful::GetRandomValue<float>(3.0f),
			useful::GetRandomValue<float>(3.0f),
			useful::GetRandomValue<float>(3.0f),
	};

	p->SetPos(pos);
	p->SetSize({ 10.0f, 10.0f, 0.0f });

	return p;
}