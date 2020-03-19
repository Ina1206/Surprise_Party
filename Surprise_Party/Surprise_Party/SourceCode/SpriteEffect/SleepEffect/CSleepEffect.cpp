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
	m_DispTime++;

	for(unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++){
		if (m_bDispFlag[sprite] == true) {

			//拡縮透過処理.
			if (ScalingTransparent(sprite) == true) {
				//表示終了処理.
				m_bDispFlag[sprite] = false;
				//初期値設定処理関数.
				SettingDefaultValue(sprite);
			}

			//移動処理.
			Move(sprite);
			continue;
		}

		if (m_DispTime >= APPEAR_TIME) {
			//表示判断処理関数.
			AppeartJudgement(sprite);
			m_DispTime = 0;
		}
	}
}

//===================================.
//		初期化処理関数.
//===================================.
void CSleepEffect::Init()
{
	//要素数設定処理.
	m_pCSprite.resize(ALL_SPRITE_MAX);
	SettingElementsCount();

	//初期値設定.
	for (int sprite = 0; sprite < ALL_SPRITE_MAX; sprite++) {
		SettingDefaultValue(sprite);
		m_DispTime = APPEAR_TIME;
		//眠りの睡眠マーク.
		if (sprite % LINE_MAX == SLEEP_Z_NUM) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::SleepZ);
			continue;
		}
		//泡.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Bubble);
	}

	m_fAlphaSpeed = ALPHA_SPEED;
	m_fScalingSpeed = SCALE_SPEED;
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
	//表示開始位置に設定.
	if (m_bDispFlag[num] == false) {
		m_vPos[num] = m_vCenterPos + INIT_LOCAL_POS;
	}

	m_bDispFlag[num] = true;
}

//=======================================.
//		移動処理関数.
//=======================================.
void CSleepEffect::Move(const int& num)
{
	const float angle = START_ANGLE - ((num % LINE_MAX) * ANGLE_WIDTH);	//角度.
	const float rad = (angle) / CIRCLE_HALF_ANGLE * PI;					//ラジアン.
	//移動.
	m_vPos[num].y += sin(rad) * MOVE_SPEED;
	m_vPos[num].x -= cos(rad) * MOVE_SPEED;

	//眠りマークは終了.
	if (num % LINE_MAX == SLEEP_Z_NUM) {
		return;
	}

	//泡のみ揺れる.
	m_fAngle[num] += ANGLE_MOVE_SPEED;
	m_vPos[num].x -= cos(m_fAngle[num] / CIRCLE_HALF_ANGLE * PI) * MOVE_SPEED;

}

