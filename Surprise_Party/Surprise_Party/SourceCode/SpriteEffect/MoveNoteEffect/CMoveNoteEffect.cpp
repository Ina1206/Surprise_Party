#include "CMoveNoteEffect.h"

/*************************************
*	音符移動エフェクトクラス.
*************/
CMoveNoteEffect::CMoveNoteEffect()
	: m_ScalingFlag	(0)
{
	//初期化処理関数.
	Init();
}

CMoveNoteEffect::~CMoveNoteEffect()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CMoveNoteEffect::Update()
{
	if (m_bPlayFlag == true) {
		for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
			PlayStartInit(Effect);
		}
		m_bRenderFlag = true;
	}

	//描画しなかったら例外処理.
	if (m_bRenderFlag == false) {
		return;
	}

	m_DispTime++;

	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//表示判定処理関数.
		AppeartJudgement(Effect);

		if (m_bDispFlag[Effect] == false) {
			continue;
		}

		//移動処理関数.
		Move(Effect);
		//拡縮処理関数.
		TransparentScaling(Effect);
	}

}

//========================================.
//		エフェクト開始初期化処理関数.
//========================================.
void CMoveNoteEffect::PlayStartInit(const int& num)
{
	SettingDefaultValue(num);
	m_vPos[num] = m_vCenterPos;
	m_ScalingFlag[num] = SCALE_FLAG;
}

//========================================.
//		初期化処理関数.
//========================================.
void CMoveNoteEffect::Init()
{
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::eight_part_note));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Wave));
	//要素数設定処理関数.
	SettingElementsCount();
	m_ScalingFlag.resize(2);
	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//初期値設定処理関数.
		SettingDefaultValue(Effect);
		m_ScalingFlag[Effect] = SCALE_FLAG;

		m_fAlpha[Effect] = 1.0f;
	}
	m_vPart[0] = D3DXVECTOR2(0.0f, 1.0f);
	m_DispTime = 20;
}

//========================================.
//		解放処理関数.
//========================================.
void CMoveNoteEffect::Release()
{

}

//========================================.
//		表示判定処理関数.
//========================================.
void CMoveNoteEffect::AppeartJudgement(const int& num)
{
	if (m_DispTime < 20) {
		return;
	}

	if (m_bDispFlag[num] == false) {
		m_bDispFlag[num] = true;
		m_DispTime = 0;
	}
}

//========================================.
//		移動処理関数.
//========================================.
void CMoveNoteEffect::Move(const int& num)
{
	m_fDistance[num] = 0.06f;

	//ラジアン.
	const float RADIAN = static_cast<float>(D3DXToRadian(m_fAngle[num]));

	m_vPos[num].x += cos(RADIAN) * m_fDistance[num];
	m_vPos[num].y += sin(RADIAN) * m_fDistance[num];

	if (num >= 1) {
		m_vRot[num].z = RADIAN;
	}
}

//========================================.
//		拡縮処理関数.
//========================================.
void CMoveNoteEffect::TransparentScaling(const int& num)
{
	if (m_ScalingFlag[num] & SCALE_FLAG) {
		m_fScale[num] += 0.02f;
		m_fAlpha[num] += 0.02f;
		if (m_fScale[num] > SCALE_MAX) {
			m_fScale[num] = SCALE_MAX;
			m_ScalingFlag[num] = SCALE_DOWN_FLAG;
			m_fAlpha[num] = ALPHA_MAX;
		}

		return;
	}

	m_fScale[num] -= 0.02f;
	m_fAlpha[num] -= 0.02f;
	if (m_fScale[num] < SCALE_MIN) {
		m_fScale[num] = SCALE_MIN;
		m_fAlpha[num] = ALPHA_MIN;
	}
}