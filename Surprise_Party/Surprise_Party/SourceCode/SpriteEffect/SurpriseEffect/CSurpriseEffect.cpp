#include "CSurpriseEffect.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
CSurpriseEffect::CSurpriseEffect()
{
	//�����������֐�.
	Init();
}

CSurpriseEffect::~CSurpriseEffect()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CSurpriseEffect::Update()
{

}

//=============================================.
//		�Đ��J�n�����������������֐�.
//=============================================.
void CSurpriseEffect::PlayStartInit(const int& num)
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
	}
}

//=============================================.
//		�����������֐�.
//=============================================.
void CSurpriseEffect::Init()
{
	m_pCSprite.resize(2);
	SettingElementsCount();

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);

		if (sprite == 0) {

		}

	}
}

//==============================================.
//		��������֐�.
//==============================================.
void CSurpriseEffect::Release()
{

}

//===============================================.
//		�\�����菈���֐�.
//===============================================.
void CSurpriseEffect::AppeartJudgement(const int& num)
{

}

//================================================.
//		�ړ������֐�.
//================================================.
void CSurpriseEffect::Move(const int& num)
{

}