#include "CSurpriseEffect.h"

/*****************************************
*		驚きエフェクト.
*******************/
CSurpriseEffect::CSurpriseEffect()
	: m_DispCnt	(0)
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
	if (m_bAllDispFlag == false) {
		return;
	}

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite)) {
				//表示終了.
				//初期値設定.
				SettingDefaultValue(sprite);
				m_bAllDispFlag = false;
				m_DispCnt = 0;
			}
			//移動処理関数.
			Move(sprite);
			continue;
		}

		//表示判定処理
		if (m_DispCnt <= 3) {
			AppeartJudgement(sprite);
			//if (m_DispCnt >= 3) {
			//	m_DispCnt = 0;
			//	m_DispTime = 0;
			//}
		}

	}
}

//=============================================.
//		再生開始初期化初期化処理関数.
//=============================================.
void CSurpriseEffect::PlayStartInit(const int& num)
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
		m_fDistance[sprite] = 0.0f;
	}
}

//=============================================.
//		初期化処理関数.
//=============================================.
void CSurpriseEffect::Init()
{
	m_pCSprite.resize(3);
	m_fDistance.resize(m_pCSprite.size());
	SettingElementsCount();

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);

		if (sprite % 2 == 1) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Shock);
			continue;
		}

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
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
	//初期位置.
	m_vPos[num] = m_vCenterPos;
	//角度.
	m_vRot[num].z = -60.0f + ((num % 3)* 60.0f);

	m_fDistance[num] = 0.0f;

	m_DispCnt++;
	m_bDispFlag[num] = true;

}

//================================================.
//		移動処理関数.
//================================================.
void CSurpriseEffect::Move(const int& num)
{
	//角度.
	const float angle = 60.0f + (30.0f * (num % 3));
	//ラジアン.
	const float radian = angle / CIRCLE_HALF_ANGLE * PI;

	m_fDistance[num] += 0.02f;

	m_vPos[num].x = cos(radian) + m_fDistance[num] + m_vCenterPos.x;
	m_vPos[num].y = sin(radian) + m_fDistance[num] + m_vCenterPos.y;

}