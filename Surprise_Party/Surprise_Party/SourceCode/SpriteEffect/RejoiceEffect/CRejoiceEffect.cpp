#include "CRejoiceEffect.h"

/*********************************************
*		喜びエフェクト.
*********/
CRejoiceEffect::CRejoiceEffect()
	: m_DispCnt		(0)
	, m_PopCnt		(0)
{
	//初期化処理関数.
	Init();
}

CRejoiceEffect::~CRejoiceEffect()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CRejoiceEffect::Update()
{
	m_DispTime++;
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite) == true) {
				//表示終了.
				//初期値設定.
				SettingDefaultValue(sprite);
				//スプライトの紐づけ.
				LinkSprite(sprite);
			}

			//移動処理関数.
			Move(sprite);
			continue;
		}

		//表示判定処理
		if (m_DispTime >= DISP_TIME_DELIMITER) {
			//番号外のスプライトは飛ばす.
			if (sprite % DISP_DELIMITER_MAX != m_PopCnt) {
				continue;
			}

			AppeartJudgement(sprite);
			
			if (m_DispCnt >= POP_MAX) {
				m_DispTime = 0;
				m_DispCnt = 0;
				m_PopCnt++;

				if (m_PopCnt >= DISP_DELIMITER_MAX) {
					m_PopCnt = 0;
				}
			}
		}
	}

}

//=========================================.
//		エフェクト開始処理関数.
//=========================================.
void CRejoiceEffect::PlayStartInit(const int& num)
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
		m_fDistance[sprite] = 0.0f;
		LinkSprite(sprite);
	}
}

//=========================================.
//		初期化処理関数.
//=========================================.
void CRejoiceEffect::Init()
{
	//要素数設定処理.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	//初期化処理関数.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
		//スプライト紐づけ処理関数.
		LinkSprite(sprite);
	}

	m_fAlphaSpeed	= ALPHA_SPEED;
	m_fScalingSpeed = SCALING_SPEED;
}

//=========================================.
//		解放処理関数.
//=========================================.
void CRejoiceEffect::Release()
{

}

//=========================================.
//		表示判定処理関数.
//=========================================.
void CRejoiceEffect::AppeartJudgement(const int& num)
{
	m_fDistance[num] = 0.0f;

	m_bDispFlag[num] = true;
	m_DispCnt++;
}

//=========================================.
//		移動処理関数.
//=========================================.
void CRejoiceEffect::Move(const int& num)
{

	m_fDistance[num] += MOVE_SPEED;

	//角度.
	const float ANGLE	= START_ANGLE + (num * ANGLE_WIDTH);
	const float RADIAN	= ANGLE / (CIRCLE_HALF_ANGLE * PI);

	m_vPos[num] = m_vCenterPos;
	m_vPos[num].x += cos(RADIAN) * m_fDistance[num];
	m_vPos[num].y += sin(RADIAN) * m_fDistance[num];

	//音符の処理.
	if (num % SPRITE_TYPE_MAX < SPRITE_ATTRIBUTE_MAX) {
		m_fAngle[num] += SWING_SPEED;
		m_vPos[num].x += cos(m_fAngle[num] / (CIRCLE_HALF_ANGLE * PI)) * SWING_WIDHT;
		return;
	}

	//花の処理.
	m_vRot[num].z += ROT_SPEED;
}

//=========================================.
//		スプライト紐づけ処理関数.
//=========================================.
void CRejoiceEffect::LinkSprite(const int& num)
{
	//番号ごとの紐づけ.
	switch (static_cast<enRejoiceSpriteType>(num % SPRITE_TYPE_MAX)) {
	case enRejoiceSpriteType::YellowEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = YELLOW_NOTE;
		break;
	case enRejoiceSpriteType::BlueEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = BLUE_NOTE;
		break;
	case enRejoiceSpriteType::PinkFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = PINK_FLOWER;
		break;
	case enRejoiceSpriteType::RedFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = RED_FLOWER;
		break;
	}
}