#include "CMoveNoteEffect.h"

/*************************************
*	音符移動エフェクトクラス.
*************/
CMoveNoteEffect::CMoveNoteEffect()
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
			m_vPos[Effect] = m_vCenterPos;
		}
		m_bRenderFlag = true;
	}

	if (m_bRenderFlag == false) {
		return;
	}

	m_DispTime++;

	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//表示判定処理関数.
		AppeartJudgement(Effect);
		//移動処理関数.
		Move(Effect);
	}
}

//========================================.
//		エフェクト開始初期化処理関数.
//========================================.
void CMoveNoteEffect::PlayStartInit(const int& num)
{

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
	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//初期値設定処理関数.
		SettingDefaultValue(Effect);

		m_fAlpha[Effect] = 1.0f;
		m_fScale[Effect] = 2.0f;
	}
	m_vPart[0] = D3DXVECTOR2(0.0f, 1.0f);
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
	if (m_DispTime < 10) {
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
	if (m_bDispFlag[num] == false) {
		return;
	}

	m_vPos[num].y -= 0.05f;
	m_vPos[num].x -= 0.05f;
}