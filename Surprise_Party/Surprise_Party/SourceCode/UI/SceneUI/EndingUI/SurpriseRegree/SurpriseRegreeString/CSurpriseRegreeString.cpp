#include "CSurpriesRagreeString.h"

/**********************************************
*		�������x���̓N���X.
*******************/
CSurpriseRegreeString::CSurpriseRegreeString()
{
	//�����������֐�.
	Init();
}

CSurpriseRegreeString::~CSurpriseRegreeString()
{
	//��������֐�.
	Release();
}

//==================================================.
//		�X�V�����֐�.
//==================================================.
void CSurpriseRegreeString::Update()
{

}

//==================================================.
//		�����������֐�.
//==================================================.
void CSurpriseRegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
}

//==================================================.
//		��������֐�.
//==================================================.
void CSurpriseRegreeString::Release()
{

}