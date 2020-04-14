#include "CArrow.h"

/**********************************************
*			���N���X.
*****************/
CArrow::CArrow()
{
	//�����������֐�.
	Init();
}

CArrow::~CArrow()
{
	//��������֐�.
	Release();
}

//=============================================.
//		�X�V�����֐�.
//=============================================.
void CArrow::Update()
{
	for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
		m_vUIPos[arrow] = BASE_POS;
		m_vUIPos[arrow].x += 100.0f * arrow;
	}
}

//=============================================.
//		�����������֐�.
//=============================================.
void CArrow::Init()
{
	for (int arrow = 0; arrow < ARROW_MAX; arrow++) {
		m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Arrow));
	}
	//�����ݒ�֐�.
	SettingInit();

	//for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
	//	m_vUIPos[arrow] = BASE_POS;
	//	m_vUIPos[arrow].x += arrow * ARROW_WIDTH;
	//}
	m_vUIRot[LEFT_ARROW_NUM].y = LEFT_ARROW_ROT_Y;
}

//=============================================.
//		��������֐�.
//=============================================.
void CArrow::Release()
{

}