#include "CCharaUI.h"

CCharaUI::CCharaUI()
	: m_vCharaPos	(0.0f, 0.0f, 0.0f)
	, m_fStageMax	(0.0f)
{

}

CCharaUI::~CCharaUI()
{

}

//==============================================.
//	ゲーム内からマップ内に座標変換処理関数
//==============================================.
void CCharaUI::GameMapConversion()
{
	//キャラクタのx座標をマップの方の座標に合わせる.
	m_vPos.x = (MAP_DISTANCE_MAX * m_vCharaPos.x) / m_fStageMax;
}