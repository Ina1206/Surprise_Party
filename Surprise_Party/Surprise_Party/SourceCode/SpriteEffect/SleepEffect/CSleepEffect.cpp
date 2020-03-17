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
			//拡縮処理.
			m_fScale[sprite] += SCALE_SPEED * m_ChangeAddSub[sprite];
			
			//透過処理.
			if (Transparent(sprite) == true) {
				//表示終了処理.
				m_bDispFlag[sprite] = false;
				//初期値設定処理関数.
				SettingDefaultValue(sprite);
			}

			//移動処理.
			Move(sprite);
			continue;
		}

		if (m_DispCnt >= APPEAR_TIME) {
			//表示判断処理関数.
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
	m_fScale.resize(m_pCSprite.size());
	m_vRot.resize(m_pCSprite.size());
	m_fAlpha.resize(m_pCSprite.size());
	m_fAngle.resize(m_pCSprite.size());
	m_bDispFlag.resize(m_pCSprite.size());
	m_ChangeAddSub.resize(m_pCSprite.size());

	//初期値設定.
	for (int sprite = 0; sprite < ALL_SPRITE_MAX; sprite++) {
		SettingDefaultValue(sprite);

		//眠りの睡眠マーク.
		if (sprite % LINE_MAX == SLEEP_Z_NUM) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::SleepZ);
			continue;
		}
		//泡.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Bubble);
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

//==========================================.
//		透過処理関数.
//==========================================.
bool CSleepEffect::Transparent(const int& num) 
{
	//透過値と大きさ.
	m_fAlpha[num] += ALPHA_SPEED * m_ChangeAddSub[num];

	//加算減少変更処理.
	if (m_fAlpha[num] >= ALPHA_MAX) {
		m_ChangeAddSub[num] *= CHANGE_ADD_SUB;
		return false;
	}

	//表示終了.
	if (m_fAlpha[num] <= ALPHA_MIN) {
		return true;
	}
	return false;
}

//===========================================.
//		初期値設定処理関数.
//===========================================.
void CSleepEffect::SettingDefaultValue(const int& num)
{
	m_bDispFlag[num]	= false;
	m_vPos[num]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale[num]		= SCALE_MIN;
	m_fAlpha[num]		= ALPHA_MIN;
	m_ChangeAddSub[num] = ADDITION_NUM;
}