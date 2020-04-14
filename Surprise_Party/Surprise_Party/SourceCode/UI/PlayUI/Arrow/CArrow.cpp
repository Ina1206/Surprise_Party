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

}

//=============================================.
//		�����������֐�.
//=============================================.
void CArrow::Init()
{
	for (int arrow = 0; arrow < 2; arrow++) {
		m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Arrow));
	}
	//�����ݒ�֐�.
	SettingInit();

	for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
		m_vUIPos[arrow] = BASE_POS;
		m_vUIPos[arrow].x += arrow * 100.0f;
	}
	m_vUIRot[LEFT_ARROW_NUM].x = 3.5f;
}

//=============================================.
//		��������֐�.
//=============================================.
void CArrow::Release()
{

}