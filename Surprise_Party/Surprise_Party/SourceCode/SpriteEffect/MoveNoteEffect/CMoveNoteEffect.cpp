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
		if (ScalingTransparent(Effect) == true) {
			m_bRenderFlag = false;
		}
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
	m_ScalingFlag.resize(m_pCSprite.size());
	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//初期値設定処理関数.
		SettingDefaultValue(Effect);
		m_ScalingFlag[Effect] = SCALE_FLAG;

		m_fAlpha[Effect] = ALPHA_MAX;
	}
	m_vPart[NOTE_NUM] = NOTE_UV_POS;
	m_DispTime = TIME_MAX;
	m_fAlphaSpeed = ALPHA_SPEED;
	m_fScalingSpeed = SCALING_SPEED;
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
	if (m_DispTime < TIME_MAX) {
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
	m_fDistance[num] = DISTANCE;

	//ラジアン.
	const float RADIAN = static_cast<float>(D3DXToRadian(m_fAngle[num]));

	m_vPos[num].x += cos(RADIAN) * m_fDistance[num];
	m_vPos[num].y += sin(RADIAN) * m_fDistance[num];

	if (num >= 1) {
		m_vRot[num].z = RADIAN;
	}
}
