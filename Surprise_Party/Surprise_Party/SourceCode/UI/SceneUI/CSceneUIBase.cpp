#include "CSceneUIBase.h"

/*****************************************
*		シーンUIの基底クラス.
****************/
CSceneUIBase::CSceneUIBase()
	: m_pCSpriteUI			()
	, m_pCCursor			(nullptr)
	, m_pCSelectStringUI	(nullptr)
{
	m_pCCursor.reset(new CChangeSceneCursorUI());
}

CSceneUIBase::~CSceneUIBase()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		描画処理関数.
//==========================================.
void CSceneUIBase::Render()
{
	//シーンタイトル描画処理関数.
	RenderSceneTitle();

	//選択文章UI描画処理関数.
	m_pCSelectStringUI->Render();

	//カーソルの描画.
	m_pCCursor->Render();

}

//===========================================.
//		解放処理関数.
//===========================================.
void CSceneUIBase::Release()
{

}