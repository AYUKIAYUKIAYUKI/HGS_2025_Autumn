//============================================================================
// 
// タイトル [title.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "title.h"
#include "sound.h"

// 入力取得用
#include "renderer.h"
#include "input.manager.h"

// シーン遷移用
#include "tutorial.h"
#include "scene_manager.h"
#include "object.manager.h"

#include "object.2D.h"
#include "texture.manager.h"
#include "object_X.h"
#include "object.text.h"
#include"TitleImage.h"

//****************************************************
// サンプル：2D
//****************************************************
namespace
{

	// このポインタはクラスのメンバにあると仮定
	CObject2D* m_p = nullptr;

	// どっかローカルに置いたパラメータ
	D3DXVECTOR3 PosPos = { 300.0f, 300.0f, 0.0f };
	D3DXVECTOR3 SizeSize = { 100.0f, 100.0f, 0.0f };

	// 初期化時に作る、メンバに持つサンプル
	auto ffppInit = []() -> void
	{
		// まずはインスタンス作成、ポインタを受け取る
		CObject2D* p = CObject2D::Create(
			OBJ::TYPE::NONE,                                               // 1, タイプ - OBJスコープ内にあるます
			OBJ::LAYER::DEFAULT,                                           // 2, レイヤー - OBJスコープに
			CTextureManager::RefInstance().RefRegistry().BindAtKey("Unko") // 3, テクスチャ指定の呪文 -  基本"Unko"のとこだけ変えるます
		);

		// 変えたいパラメータを、Setを通じて設定
		p->SetPos(PosPos);
		p->SetSize(SizeSize);

		/* 最後にメンバに持ったとする */
		m_p = p;
	};

	// 更新時に作る、エディットするサンプル
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
// usingディレクティブ
//****************************************************
using namespace useful;

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CTitle::CTitle()
	: CScene()
{}

//============================================================================
// デストラクタ
//============================================================================
CTitle::~CTitle()
{
	// 終了処理
	Finalize();
}

//============================================================================
// 更新処理
//============================================================================
void CTitle::Update()
{
#ifdef _DEBUG
	CRenderer::RefInstance().AddText("ポイポイ", 1);
#endif // _DEBUG

	// これが更新サンプルです
	//ffppEdit();

	// うんちなの生成
	for (int i = 0; i < 5; i++)
	{
		auto p = CObjectText::Create(OpenJsonFile("Data\\JSON\\TEXT\\Title.json"));
		p->SetPos({ GetRandomValue(1000.0f), GetRandomValue(1000.0f) });
		p->SetCol({ GetRandomValue(1.0f), GetRandomValue(1.0f), GetRandomValue(1.0f), 1.0f });
	}


	// 次のシーンへ遷移
	if (CInputManager::RefInstance().GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CInputManager::RefInstance().GetPad()->GetTrigger(CInputPad::JOYKEY::START))
	{
		Change();
	}
}

//============================================================================
// 描画処理
//============================================================================
void CTitle::Draw()
{}

//============================================================================
// 次のシーンへ
//============================================================================
void CTitle::Change()
{
	// 全オブジェクト解放予約
	CObjectManager::RefInstance().SetDeathAllObject();

	// サウンド by AKR TNK
	CSound::GetInstance()->Stop(CSound::LABEL::BGM_0);

	// チュートリアルシーンへ変更
	up<CTutorial> upScene = CreateUniquePtr<CTutorial>();
	CSceneManager::RefInstance().ChangeScene(std::move(upScene));
}

//============================================================================
// 初期化処理
//============================================================================
bool CTitle::Initialize()
{
	// サウンド by AKR TNK
	CSound::GetInstance()->Play(CSound::LABEL::BGM_0);

	CCamera_Manager::RefInstance().SetSelectKey("Title");

	CObject_X::Create(OBJ::TYPE::NONE, OBJ::LAYER::DEFAULT, nullptr);

	// これが初期化サンプルです
	//ffppInit();

	return true;
}

//============================================================================
// 終了処理
//============================================================================
void CTitle::Finalize()
{}