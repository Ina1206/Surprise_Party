#include "CGimmickIcon.h"

/******************************************
*		�M�~�b�N�A�C�R���N���X.
*********/
CGimmickIcon::CGimmickIcon()
	: CGimmickIcon(0)
{

}

CGimmickIcon::CGimmickIcon(int GimmickNum)
	: m_GimmickType	(0)
{
	m_GimmickType = GimmickNum;
	//�����������֐�.
	Init();
}

CGimmickIcon::~CGimmickIcon()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CGimmickIcon::UpDate()
{
	//�Q�[��������}�b�v���ɍ��W�ϊ������֐�.
	GameMapConversion();

	//�I�𒆂̕\�������֐�.
	SelectingDisplay();
}

//=====================================.
//		�����������֐�.
//=====================================.
void CGimmickIcon::Init()
{
	switch (static_cast<enGimmickType>(m_GimmickType)) {
	case enGimmickType::DispGhost:
		m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::DispGimmick_Iccon);
		break;
	default:
		m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Switch_Icon);
		break;
	}
	m_vPos = INIT_POS;
}

//======================================.
//		��������֐�.
//======================================.
void CGimmickIcon::Release()
{
	m_pCSpriteUI = nullptr;
}