#include "CSurpriesDegreeString.h"

/**********************************************
*		�������x���̓N���X.
*******************/
CSurpriseDegreeString::CSurpriseDegreeString()
{
	//�����������֐�.
	Init();
}

CSurpriseDegreeString::~CSurpriseDegreeString()
{
	//��������֐�.
	Release();
}

//==================================================.
//		�X�V�����֐�.
//==================================================.
void CSurpriseDegreeString::Update()
{

}

//==================================================.
//		�����������֐�.
//==================================================.
void CSurpriseDegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
}

//==================================================.
//		��������֐�.
//==================================================.
void CSurpriseDegreeString::Release()
{

}