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

		//表示判定処理
		if (m_DispTime >= DISP_TIME_MAX) {
			AppeartJudgement(sprite);
			if (m_DispCnt >= LINE_MAX) {
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
		//汗画像.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
	m_fAlphaSpeed	= ALPHA_SPEED;
	m_fScalingSpeed = SCALING_SPEED;
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
	//初期位置.
	m_vPos[num] = m_vCenterPos + INT_LOCAL_POS;
	//角度.
	m_vRot[num].z = -ROT_WIDTH + ((num % LINE_MAX)* ROT_WIDTH);

	m_DispCnt++;
	m_bDispFlag[num] = true;
}

//============================================.
//		移動処理関数.
//============================================.
void CHaveTroubleEffect::Move(const int& num)
{
	//角度.
	const float angle = START_ANGLE + (ANGLE_WIDTH * (num % LINE_MAX));
	//ラジアン.
	const float radian = angle / CIRCLE_HALF_ANGLE * PI;
	m_vPos[num].x += cos(radian) * MOVE_SPEED;
	m_vPos[num].y += sin(radian) * MOVE_SPEED;
}