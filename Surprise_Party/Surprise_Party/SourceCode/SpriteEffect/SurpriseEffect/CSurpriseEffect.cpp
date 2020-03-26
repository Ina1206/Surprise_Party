#include "CSurpriseEffect.h"

/*****************************************
*		驚きエフェクト.
*******************/
CSurpriseEffect::CSurpriseEffect()
{
	//初期化処理関数.
	Init();
}

CSurpriseEffect::~CSurpriseEffect()
{
	//解放処理関数.
	Release();
}

//============================================.
//		更新処理関数.
//============================================.
void CSurpriseEffect::Update()
{

}

//=============================================.
//		再生開始初期化初期化処理関数.
//=============================================.
void CSurpriseEffect::PlayStartInit(const int& num)
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
	}
}

//=============================================.
//		初期化処理関数.
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
//		解放処理関数.
//==============================================.
void CSurpriseEffect::Release()
{

}

//===============================================.
//		表示判定処理関数.
//===============================================.
void CSurpriseEffect::AppeartJudgement(const int& num)
{

}

//================================================.
//		移動処理関数.
//================================================.
void CSurpriseEffect::Move(const int& num)
{

}