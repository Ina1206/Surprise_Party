#include "CHightEvaluationString.h"

/**********************************************
*		���]�������N���X.
*********************/
CHightEvaluationString::CHightEvaluationString()
{
	//�����������֐�.
	Init();
}

CHightEvaluationString::~CHightEvaluationString()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CHightEvaluationString::Update()
{
	if (m_bFinishedAllDispFlag == true) {
		return;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		for (unsigned int string = 0; string < m_pCEvaluationUI.size(); string++) {
			m_vEvaluationPos[string].y += 0.5f;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		for (unsigned int string = 0; string < m_pCEvaluationUI.size(); string++) {
			m_vEvaluationPos[string].y -= 0.5f;
		}
	}

	Move();
}

//=========================================.
//		�����������֐�.
//=========================================.
void CHightEvaluationString::Init()
{
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
	for (int string = 0; string < SpriteState.Frame.w; string++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::HightEvaluationString));
	}

	//�v�f���̏����������֐�.
	InitElementCount();

	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite] = INIT_POS;
		m_vEvaluationUV[sprite] = D3DXVECTOR2(1.0f * sprite, 0.0f);
	}
}

//=========================================.
//		��������֐�.
//=========================================.
void CHightEvaluationString::Release()
{

}

//=========================================.
//		�ړ������֐�.
//=========================================.
void CHightEvaluationString::Move()
{
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
	const float	FINISH_POS = FINISH_BASE_POS.x + (SpriteState.Disp.w * m_UpdateNum);
	const float RAITO = FINISH_POS / FINISH_BASE_POS.x;

	m_vEvaluationPos[m_UpdateNum].x += 0.3f * RAITO;

	if (m_vEvaluationPos[m_UpdateNum].x >= FINISH_POS) {
		m_vEvaluationPos[m_UpdateNum] = FINISH_BASE_POS;
		m_vEvaluationPos[m_UpdateNum].x += SpriteState.Disp.w * m_UpdateNum;
		m_UpdateNum++;
		if (m_UpdateNum >= static_cast<int>(m_pCEvaluationUI.size())) {
			m_bFinishedAllDispFlag = true;
		}
	}
}

//=========================================.
//		�W�����v�����֐�.
//=========================================.
void CHightEvaluationString::Jump()
{

}

//=========================================.
//		�o�E���h�����֐�.
//=========================================.
void CHightEvaluationString::Bound()
{

}