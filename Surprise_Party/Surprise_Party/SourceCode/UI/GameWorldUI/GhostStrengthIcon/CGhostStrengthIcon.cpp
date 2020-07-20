#include "CGhostStrengthIcon.h"

/************************************************
*		お化けの体力アイコンクラス.
***************/
CGhostStrengthIcon::CGhostStrengthIcon()
{
	//初期化処理関数.
	Init();
}

CGhostStrengthIcon::~CGhostStrengthIcon()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		更新処理関数.
//===========================================.
void CGhostStrengthIcon::UpDate()
{
	//座標設定.
	m_vPos = m_vCharacterPos + ICON_POS_ADJUST;

	//体力アイコンの決定.
	switch (static_cast<enStrengthType>(m_StrengthIcon)) {
	case enStrengthType::Bad:
		m_vPattarn = BAD_STRENGTH;
		break;
	case enStrengthType::Normal:
		m_vPattarn = NORMAL_STRENGTH;
		break;
	case enStrengthType::Good:
		m_vPattarn = GOOD_STRENGTH;
		break;
	case enStrengthType::Great:
		m_vPattarn = GREAT_STRENGTH;
		break;
	}

	//透過値.
	if (m_vPos.z <= ALPHA_CHANGE_POS) {
		m_fAlpha = BEFORE_WALL_ALPHA;
		return;
	}
	m_fAlpha = WALL_BACK_ALPHA;
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CGhostStrengthIcon::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Strenght_Icon);
	m_bDepth = false;
}

//===========================================.
//		解放処理関数.
//===========================================.
void CGhostStrengthIcon::Release()
{
	m_pCSprite = nullptr;
}