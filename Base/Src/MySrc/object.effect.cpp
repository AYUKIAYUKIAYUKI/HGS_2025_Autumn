////****************************************************
//// インクルードファイル
////****************************************************
//#include "object.effect.h"
//#include "texture.manager.h"
//
////****************************************************
//// usingディレクティブ
////****************************************************
//using namespace useful;
//
////============================================================================
//// コンストラクタ
////============================================================================
//CObjectEffect::CObjectEffect(OBJ::TYPE Type, OBJ::LAYER Layer)
//	: CObject2D(Type, Layer)
//	, m_nLimit(30)
//	, m_nGhostTime(10)
//	, m_Vel(VEC3_ZERO_INIT)
//{
//
//}
//
////
//CObjectEffect::~CObjectEffect()
//{
//
//}
//
//CObjectEffect* CObjectEffect::Create(D3DXVECTOR3 pos , D3DXVECTOR3 vel, D3DXVECTOR3 Size,  const JSON& json)
//{
//	CObjectEffect* p = DBG_NEW CObjectEffect(OBJ::TYPE::NONE, OBJ::LAYER::UI);
//
//	p->Initialize();
//
//	p->BindTex(CTextureManager::RefInstance().RefRegistry().BindAtKey("Effect"));
//
//	p->m_Vel = vel;
//
//	// 座標を適当にずらす
//	pos += {
//		useful::GetRandomValue<float>(30.0f),
//		useful::GetRandomValue<float>(30.0f),
//		0.0f
//	};
//
//	p->SetSize(Size);
//	p->SetRot(pos);
//	p->SetPos(pos);
//	p->SetCol({ 1.0f, 1.0f, 1.0f, 0.5f });
//
//	return p;
//}