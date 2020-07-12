#include "CIntermediateEvaluationString.h"

/***************************************
*		’†ŠÔ•]‰¿‚Ì•¶ÍƒNƒ‰ƒX.
***************/
CIntermediateEvaluationString::CIntermediateEvaluationString()
	: m_ActFinishFlag	(0)
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CIntermediateEvaluationString::~CIntermediateEvaluationString()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//============================================.
//		XVˆ—ŠÖ”.
//============================================.
void CIntermediateEvaluationString::Update()
{
	if (m_bFinishedAllDispFlag == true) {
		return;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
			m_vEvaluationPos[sprite].x -= 0.5f;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
			m_vEvaluationPos[sprite].x += 0.5f;
		}

	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
			m_vEvaluationPos[sprite].y += 0.5f;
		}

	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
			m_vEvaluationPos[sprite].y -= 0.5f;
		}

	}

	m_vEvaluationPos[m_UpdateNum] = BASE_POS;
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::IntermediateEvaluationString);
	m_vEvaluationPos[m_UpdateNum].x += SpriteState.Disp.w * m_UpdateNum;

	//Šg‘åˆ—ŠÖ”.
	Scale();

	//‰ñ“]ˆ—ŠÖ”.
	Rotation();

	const unsigned int ALL_ACT_FLAG = FINISH_ROTATION_FLAG | FINISH_SCALE_FLAG;
	if (m_ActFinishFlag == ALL_ACT_FLAG) {
		m_ActFinishFlag = 0;
		m_UpdateNum++;
		if (m_UpdateNum >= static_cast<int>(m_pCEvaluationUI.size())) {
			m_bFinishedAllDispFlag = true;
		}
	}
}

//============================================.
//		‰Šú‰»ˆ—ŠÖ”.
//============================================.
void CIntermediateEvaluationString::Init()
{
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::IntermediateEvaluationString);
	const float ELEMENT_COUNT_MAX = SpriteState.Frame.w;
	for (int element = 0; element < ELEMENT_COUNT_MAX; element++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::IntermediateEvaluationString));
	}

	//—v‘f”‚Æ‰Šú’l‚Ì‰Šú‰»ˆ—ŠÖ”.
	InitElementCount();
	for (int sprite = 0; sprite < ELEMENT_COUNT_MAX; sprite++) {
		m_vEvaluationPos[sprite] = BASE_POS;
		//‰ñ“]²‚ğ’†S‚É‚·‚é‚½‚ß‚Ìİ’è.
		m_vPrePos = D3DXVECTOR3(-SpriteState.Disp.w / 2.0f, -SpriteState.Disp.h / 2.0f, 0.0f);
		m_vEvaluationScale[sprite] = EATCH_SCALE_MIN;
		m_vEvaluationUV[sprite].x += 1.0f * sprite;
	}
}

//============================================.
//		‰ğ•úˆ—ŠÖ”.
//============================================.
void CIntermediateEvaluationString::Release()
{

}

//============================================.
//		Šg‘åˆ—ŠÖ”.
//============================================.
void CIntermediateEvaluationString::Scale()
{
	m_vEvaluationScale[m_UpdateNum] += SCALE_SPEED;
	
	if (m_vEvaluationScale[m_UpdateNum].x >= EATCH_SCALE_MAX.x) {
		m_vEvaluationScale[m_UpdateNum] = EATCH_SCALE_MAX;
		m_ActFinishFlag = FINISH_SCALE_FLAG;
	}
}

//============================================.
//		‰ñ“]ˆ—ŠÖ”.
//============================================.
void CIntermediateEvaluationString::Rotation()
{
	m_vEvaluationRot[m_UpdateNum].z += ROTATION_SPEED;

	if (m_vEvaluationRot[m_UpdateNum].z >= static_cast<float>(D3DXToRadian(ROT_MAX))) {
		m_vEvaluationRot[m_UpdateNum].z = 0.0f;

		if (m_ActFinishFlag & FINISH_SCALE_FLAG) {
			m_ActFinishFlag |= FINISH_ROTATION_FLAG;
		}
	}
}