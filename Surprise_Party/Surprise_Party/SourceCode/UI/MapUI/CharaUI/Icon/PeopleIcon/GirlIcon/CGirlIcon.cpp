#include "CGirlIcon.h"

CGirlIcon::CGirlIcon()
{
	//�����������֐�.
	Init();
}

CGirlIcon::~CGirlIcon()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�����������֐�.
//=====================================.
void CGirlIcon::Init()
{
	//���̎q�̃A�C�R��UI�ǂݍ��݊Ǘ�����A�h���X�擾.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Girl_Icon);
	//�����̍��W.
	m_vPos = START_POS;

	m_bShoutWoman = true;
}

//=====================================.
//		��������֐�.
//=====================================.
void CGirlIcon::Release()
{
	m_pCSpriteUI = nullptr;
}