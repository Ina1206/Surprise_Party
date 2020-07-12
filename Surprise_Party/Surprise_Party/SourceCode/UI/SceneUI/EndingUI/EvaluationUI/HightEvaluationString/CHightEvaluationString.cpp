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
}

//=========================================.
//		��������֐�.
//=========================================.
void CHightEvaluationString::Release()
{

}