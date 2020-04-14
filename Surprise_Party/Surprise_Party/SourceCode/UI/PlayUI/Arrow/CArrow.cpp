#include "CArrow.h"

/**********************************************
*			矢印クラス.
*****************/
CArrow::CArrow()
{
	//初期化処理関数.
	Init();
}

CArrow::~CArrow()
{
	//解放処理関数.
	Release();
}

//=============================================.
//		更新処理関数.
//=============================================.
void CArrow::Update()
{
	for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
		m_vUIPos[arrow] = BASE_POS;
		m_vUIPos[arrow].x += 100.0f * arrow;
	}
}

//=============================================.
//		初期化処理関数.
//=============================================.
void CArrow::Init()
{
	for (int arrow = 0; arrow < ARROW_MAX; arrow++) {
		m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Arrow));
	}
	//初期設定関数.
	SettingInit();

	//for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
	//	m_vUIPos[arrow] = BASE_POS;
	//	m_vUIPos[arrow].x += arrow * ARROW_WIDTH;
	//}
	m_vUIRot[LEFT_ARROW_NUM].y = LEFT_ARROW_ROT_Y;
}

//=============================================.
//		解放処理関数.
//=============================================.
void CArrow::Release()
{

}