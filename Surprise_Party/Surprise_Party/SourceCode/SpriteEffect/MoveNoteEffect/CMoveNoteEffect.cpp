#include "CMoveNoteEffect.h"

/*************************************
*	音符移動エフェクトクラス.
*************/
CMoveNoteEffect::CMoveNoteEffect()
{

}

CMoveNoteEffect::~CMoveNoteEffect()
{

}

//========================================.
//		更新処理関数.
//========================================.
void CMoveNoteEffect::Update()
{

}

//========================================.
//		エフェクト開始初期化処理関数.
//========================================.
void CMoveNoteEffect::PlayStartInit(const int& num)
{

}

//========================================.
//		初期化処理関数.
//========================================.
void CMoveNoteEffect::Init()
{
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::eight_part_note));
	SettingElementsCount();
}

//========================================.
//		解放処理関数.
//========================================.
void CMoveNoteEffect::Release()
{

}

//========================================.
//		表示判定処理関数.
//========================================.
void CMoveNoteEffect::AppeartJudgement(const int& num)
{

}

//========================================.
//		移動処理関数.
//========================================.
void CMoveNoteEffect::Move(const int& num)
{

}