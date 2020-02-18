#include "CGimmickIcon.h"

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
	m_vPos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
}

//======================================.
//		��������֐�.
//======================================.
void CGimmickIcon::Release()
{
	m_pCSpriteUI = nullptr;
}