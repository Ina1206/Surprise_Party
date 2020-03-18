#include "CHaveTroubleEffect.h"

/******************************************
*		困りエフェクトクラス.
************/
CHaveTroubleEffect::CHaveTroubleEffect()
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
	m_DispCnt++;
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {

			//移動処理関数.
			Move(sprite);
			continue;
		}

		if (m_DispCnt <= 50) {
			AppeartJudgement(sprite);
			m_DispCnt = 0;
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
		m_fAlpha[sprite] = ALPHA_MAX;
		m_fScale[sprite] = SCALE_MAX;
		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDispFlag[sprite] = false;
		
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
	m_bDispFlag[num] = true;
}

//============================================.
//		移動処理関数.
//============================================.
void CHaveTroubleEffect::Move(const int& num)
{
	m_vPos[num].x += cos(60 / 180.0f * PI) * 0.01f;
	m_vPos[num].y += cos(60 / 180.0f * PI) * 0.01f;
}