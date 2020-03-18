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
			ScalingTransparent(sprite);

			//移動処理関数.
			Move(sprite);
			continue;
		}

		if (m_DispTime >= 50) {
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
		//m_fAlpha[sprite] = ALPHA_MAX;
		//m_fScale[sprite] = SCALE_MAX;
		//m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//m_bDispFlag[sprite] = false;
		SettingDefaultValue(sprite);

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
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
	m_vPos[num].x += cos(120 + ( 20 * (num % 3)) / 180.0f * PI) * 0.03f;
	m_vPos[num].y += sin(120 + ( 20 * (num % 3)) / 180.0f * PI) * 0.03f;
}