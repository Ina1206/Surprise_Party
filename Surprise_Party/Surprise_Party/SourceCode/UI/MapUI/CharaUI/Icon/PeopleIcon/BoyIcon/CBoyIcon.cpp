#include "CBoyIcon.h"

/*************************************
*		�j�̎q�A�C�R���N���X.
******/
CBoyIcon::CBoyIcon()
{
	//�����������֐�.
	Init();
}

CBoyIcon::~CBoyIcon()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�����������֐�.
//=====================================.
void CBoyIcon::Init()
{
	//�ǂݍ��݊Ǘ��N���X����A�h���X�擾.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Boy_Icon);

	//���W�����ݒ�.
	m_vPos = START_POS;

	m_bShoutWoman = false;
}

//=====================================.
//		��������֐�.
//=====================================.
void CBoyIcon::Release()
{
	m_pCSpriteUI = nullptr;	
}