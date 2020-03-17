#include "CSleepEffect.h"

/********************************************
*		寝ているエフェクトクラス.
****************/
CSleepEffect::CSleepEffect()
{
	//初期化処理関数.
	Init();
}

CSleepEffect::~CSleepEffect()
{
	//解放処理関数.
	Release();
}

//===================================.
//		更新処理関数.
//===================================.
void CSleepEffect::Update()
{
	m_DispCnt++;

	for(unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++){
		if (m_bDispFlag[sprite] == true) {
			m_vPos[sprite].y += 0.05f;
			m_vPos[sprite].x -= 0.05f;
			continue;
		}

		if (m_DispCnt >= 30) {
			AppeartJudgement(sprite);
			m_DispCnt = 0;
		}
	}
}

//===================================.
//		初期化処理関数.
//===================================.
void CSleepEffect::Init()
{
	//要素数設定.
	m_pCSprite.resize(ALL_SPRITE_MAX);
	m_vPos.resize(m_pCSprite.size());
	m_vScale.resize(m_pCSprite.size());
	m_vRot.resize(m_pCSprite.size());
	m_fAlpha.resize(m_pCSprite.size());
	m_bDispFlag.resize(m_pCSprite.size());

	//初期値設定.
	for (int sprite = 0; sprite < ALL_SPRITE_MAX; sprite++) {
		//m_vScale[sprite] = SCALE_MIN;
		//m_fAlpha[sprite] = ALPHA_MIN;
		m_bDispFlag[sprite] = false;
		m_vScale[sprite] = SCALE_MAX;
		m_fAlpha[sprite] = ALPHA_MAX;
		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//泡.
		if (sprite < BUBBLE_MAX) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Bubble);
			continue;
		}
		//眠りの睡眠マーク.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::SleepZ);
	}
}

//====================================.
//		解放処理関数.
//====================================.
void CSleepEffect::Release()
{
	for (unsigned int sprite = m_pCSprite.size() - 1; ; sprite--) {
		m_pCSprite[sprite] = nullptr;

		//抜ける処理.
		if(sprite == 0){
			break;
		}
	}
}

//======================================.
//		表示判断処理関数.
//======================================.
void CSleepEffect::AppeartJudgement(const int& num)
{
	if (m_bDispFlag[num] == false) {
		m_vPos[num] = m_vCenterPos + INIT_LOCAL_POS;
	}

	m_bDispFlag[num] = true;
}