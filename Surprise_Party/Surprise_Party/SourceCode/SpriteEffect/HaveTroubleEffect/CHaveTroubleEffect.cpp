#include "CHaveTroubleEffect.h"

/******************************************
*		困りエフェクトクラス.
************/
CHaveTroubleEffect::CHaveTroubleEffect()
	: m_DispCnt	(0)
{
	//初期化処理関数.
	Init();
}

CHaveTroubleEffect::~CHaveTroubleEffect()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		更新処理関数.
//===========================================.
void CHaveTroubleEffect::Update()
{
	m_DispTime++;
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite) == true) {
				//表示終了.
				//初期値設定.
				SettingDefaultValue(sprite);
			}

			//移動処理関数.
			Move(sprite);
			continue;
		}

		if (m_DispTime >= 20) {
			AppeartJudgement(sprite);
			if (m_DispCnt >= 3) {
				m_DispCnt = 0;
				m_DispTime = 0;
			}
		}
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CHaveTroubleEffect::Init()
{
	//要素数設定.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		//初期値設定.
		SettingDefaultValue(sprite);

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
	m_fAlphaSpeed = 0.04f;
	m_fScalingSpeed = 0.04f;
}

//===========================================.
//		解放処理関数.
//===========================================.
void CHaveTroubleEffect::Release()
{

}

//============================================.
//		表示判定処理関数.
//============================================.
void CHaveTroubleEffect::AppeartJudgement(const int& num)
{
	m_vPos[num] = m_vCenterPos + INT_LOCAL_POS;
	m_DispCnt++;
	m_bDispFlag[num] = true;
}

//============================================.
//		移動処理関数.
//============================================.
void CHaveTroubleEffect::Move(const int& num)
{
	const float radian = 120 + (30 * (num % 3)) / 180.0f * PI;
	m_vPos[num].x += cos(radian) * 0.03f;
	m_vPos[num].y += sin(radian) * 0.03f;
}