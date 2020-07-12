#include "CHightEvaluationString.h"

/**********************************************
*		高評価文字クラス.
*********************/
CHightEvaluationString::CHightEvaluationString()
{
	//初期化処理関数.
	Init();
}

CHightEvaluationString::~CHightEvaluationString()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
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
//		初期化処理関数.
//=========================================.
void CHightEvaluationString::Init()
{
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
	for (int string = 0; string < SpriteState.Frame.w; string++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::HightEvaluationString));
	}

	//要素数の初期化処理関数.
	InitElementCount();
}

//=========================================.
//		解放処理関数.
//=========================================.
void CHightEvaluationString::Release()
{

}