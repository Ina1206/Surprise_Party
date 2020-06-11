#include "CHightEvaluationStage.h"

/**********************************************
*			高評価ステージクラス.
*******************/
CHightEvaluationStage::CHightEvaluationStage()
{
	//初期化処理関数.
	Init();
}

CHightEvaluationStage::~CHightEvaluationStage()
{
	//解放処理関数.
	Release();
}

//=============================================.
//			更新処理関数.
//=============================================.
void CHightEvaluationStage::Update()
{
	m_pCCameraEnding->Update();

	//static D3DXVECTOR3 avPos = D3DXVECTOR3(5.0f, 0.0f, 5.0f);
	//if (GetAsyncKeyState(VK_UP) & 0x8000) {
	//	avPos.z += 0.3f;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
	//	avPos.z -= 0.3f;
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	//	avPos.x += 0.3f;
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
	//	avPos.x -= 0.3f;
	//}


	//お化けの更新処理.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
		//const float			RADIAN = static_cast<float>(D3DXToRadian(-7.0f + (ghost * 55.0f)));
		//const D3DXVECTOR3	vPos = (D3DXVECTOR3(cos(RADIAN), 0.0f, sin(RADIAN)) * 2.5f) + D3DXVECTOR3(5.0f, 1.5f + ((ghost % 2) * 0.5f), 8.0f);

		//////if (ghost != 2) {
		//m_pCGhost[ghost]->SetPos(vPos);
		////}

	}



	//白画面のフェード.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
		return;
	}
	m_pCWhiteScreenFade->Update();
}

//=============================================.
//			描画処理関数.
//=============================================.
void CHightEvaluationStage::Render()
{
	//床の描画処理関数.
	RenderFloor();

	//お化け描画処理関数.
	RenderGhost();

	//白画面のフェード描画.
	if (!(m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG)) {
		m_pCWhiteScreenFade->Render();
	}
}

//=============================================.
//			初期化処理関数.
//=============================================.
void CHightEvaluationStage::Init()
{
	//フェードアウトで設定.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	//お化け感情設定.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::Rejoice));
	}

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);
	
}

//=============================================.
//			解放処理関数.
//=============================================.
void CHightEvaluationStage::Release()
{

}