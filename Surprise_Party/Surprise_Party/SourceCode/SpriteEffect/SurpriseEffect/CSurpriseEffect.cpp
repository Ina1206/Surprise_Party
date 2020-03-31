#include "CSurpriseEffect.h"

/*****************************************
*		驚きエフェクト.
*******************/
CSurpriseEffect::CSurpriseEffect()
	: m_DispCnt			(0)
	, m_bAllDispFlag	(false)
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


	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bAllDispFlag == false) {
			//表示終了.
			//初期値設定.
			SettingDefaultValue(sprite);
			m_DispCnt = 0;
			continue;
		}

		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite)) {
				m_bAllDispFlag = false;
			}
			//移動処理関数.
			Move(sprite);
			continue;
		}

		//表示判定処理
		if (m_DispCnt <= 3) {
			AppeartJudgement(sprite);
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

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}

	m_fScalingSpeed = 0.08f;
	m_fAlphaSpeed = 0.08f;
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
	m_vRot[num].y = 3.1f;

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
	const float angle = 120.0f + (30.0f * (num % 3));
	//ラジアン.
	const float radian = angle / CIRCLE_HALF_ANGLE * PI;

	m_fDistance[num] += 0.005f;

	m_vPos[num].x += (cos(radian) * m_fDistance[num]) ;
	m_vPos[num].y += (sin(radian) * m_fDistance[num]) ;

}