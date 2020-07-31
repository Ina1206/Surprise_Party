#include "CSurpriseEffect.h"

/*****************************************
*		驚きエフェクト.
*******************/
CSurpriseEffect::CSurpriseEffect()
	: m_DispCnt			(0)
	, m_bAllDispFlag	(false)
	, m_Direct			(1)
	, m_vOldCenterPos	(0.0f, 0.0f, 0.0f)
	, m_bPlaySound	(false)
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

	const float DIFFERENCE_CENTER_POS = m_vCenterPos.x - m_vOldCenterPos.x;
	if (DIFFERENCE_CENTER_POS != 0.0f) {
		//方向.
		m_Direct = static_cast<int>(DIFFERENCE_CENTER_POS / fabsf(DIFFERENCE_CENTER_POS));
	}
	m_vOldCenterPos = m_vCenterPos;

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
				SettingDefaultValue(sprite);
				m_bAllDispFlag = false;
			}
			//移動処理関数.
			Move(sprite);
			continue;
		}

		//表示判定処理
		if (m_DispCnt <= SPRITE_MAX) {
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
	//要素数設定.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	//初期値設定.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}

	m_fScalingSpeed = SCALE_SPEED;
	m_fAlphaSpeed = ALPHA_SPEED;
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

	m_DispCnt++;
	m_bDispFlag[num] = true;

	if (m_bPlaySound == true) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::Swet);
	}

}

//================================================.
//		移動処理関数.
//================================================.
void CSurpriseEffect::Move(const int& num)
{

	//角度.
	float angle = 0.0f;
	if (m_Direct > 0) {
		angle = static_cast<float>(D3DXToRadian(LEFT_ANGLE + (ANGLE_WIDTH * (num % SPRITE_MAX))));
		//角度.
		m_vRot[num].y = ROT_Y;
	}
	else {
		angle = static_cast<float>(D3DXToRadian(RIGHT_ANGLE + (ANGLE_WIDTH * (num % SPRITE_MAX))));
		m_vRot[num].y = 0.0f;
	}
	m_fDistance[num] += MOVE_SPEED;

	m_vPos[num].x = cos(angle) - (m_fDistance[num] * m_Direct) + m_vCenterPos.x;
	m_vPos[num].y = sin(angle) + m_fDistance[num] + m_vCenterPos.y;

}