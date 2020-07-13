#include "CIntermediateEvaluationString.h"

/***************************************
*		���ԕ]���̕��̓N���X.
***************/
CIntermediateEvaluationString::CIntermediateEvaluationString()
	: m_ActFinishFlag	(0)
{
	//�����������֐�.
	Init();
}

CIntermediateEvaluationString::~CIntermediateEvaluationString()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CIntermediateEvaluationString::Update()
{
	if (m_bFinishedAllDispFlag == true) {
		return;
	}

	if (m_bDisplayAllAtOnce == true) {
		//��C�ɕ\�����鏈���֐�.
		DisplayAllAtOnce();
		return;
	}

	m_vEvaluationPos[m_UpdateNum] = BASE_POS;
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::IntermediateEvaluationString);
	m_vEvaluationPos[m_UpdateNum].x += SpriteState.Disp.w * m_UpdateNum;

	//�g�又���֐�.
	Scale();

	//��]�����֐�.
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
//		�����������֐�.
//============================================.
void CIntermediateEvaluationString::Init()
{
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::IntermediateEvaluationString);
	const float ELEMENT_COUNT_MAX = SpriteState.Frame.w;
	for (int element = 0; element < ELEMENT_COUNT_MAX; element++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::IntermediateEvaluationString));
	}

	//�v�f���Ə����l�̏����������֐�.
	InitElementCount();
	for (int sprite = 0; sprite < ELEMENT_COUNT_MAX; sprite++) {
		m_vEvaluationPos[sprite] = BASE_POS;
		//��]���𒆐S�ɂ��邽�߂̐ݒ�.
		m_vPrePos = D3DXVECTOR3(-SpriteState.Disp.w / 2.0f, -SpriteState.Disp.h / 2.0f, 0.0f);
		m_vEvaluationScale[sprite] = EATCH_SCALE_MIN;
		m_vEvaluationUV[sprite].x += 1.0f * sprite;
	}
}

//============================================.
//		��������֐�.
//============================================.
void CIntermediateEvaluationString::Release()
{

}

//============================================.
//		�g�又���֐�.
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
//		��]�����֐�.
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

//=============================================.
//		��C�ɕ\�������֐�.
//=============================================.
void CIntermediateEvaluationString::DisplayAllAtOnce()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::IntermediateEvaluationString);
	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationRot[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vEvaluationScale[sprite] = EATCH_SCALE_MAX;
		m_vEvaluationPos[sprite] = BASE_POS;
		m_vEvaluationPos[sprite].x += sprite * SpriteState.Disp.w;
	}

	m_bFinishedAllDispFlag = true;
}