#include "CChangeSceneCursorUI.h"

/****************************************
*		シーン変更用カーソルUIクラス.
*****************/
CChangeSceneCursorUI::CChangeSceneCursorUI()
	: m_pCSpriteUI			(nullptr)
	, m_vUV					(0.0f, 0.0f)
	, m_bSelectFinishFlag	(false)
	, m_ChangeCnt			(0)
	, m_SelectNum			(0)
{
	//初期化処理関数.
	Init();
}

CChangeSceneCursorUI::~CChangeSceneCursorUI()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CChangeSceneCursorUI::Update()
{
	//操作処理関数.
	Control();
}

//======================================.
//		描画処理関数.
//======================================.
void CChangeSceneCursorUI::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetRotation(m_vRot);
	m_pCSpriteUI->SetPattern(m_vUV);
	m_pCSpriteUI->Render();
}

//======================================.
//		初期化処理関数.
//======================================.
void CChangeSceneCursorUI::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRot = RIGHT_CURSOR_ROT;
	m_vUV = NORMAL_UV_POS;
}

//======================================.
//		解放処理関数.
//======================================.
void CChangeSceneCursorUI::Release()
{

}

//======================================.
//		操作処理関数.
//======================================.
void CChangeSceneCursorUI::Control()
{
	m_bSelectFinishFlag = false;

	//決定後の処理.
	if (m_ChangeCnt > 0) {
		if (m_bChangeWaitFlag == true) {
			m_ChangeCnt++;

			//選択終了.
			if (m_ChangeCnt >= CHANGE_CNT_MAX) {
				m_bSelectFinishFlag = true;
				m_vUV = NORMAL_UV_POS;
				m_ChangeCnt = 0;
			}
			return;
		}

		m_bSelectFinishFlag = true;
		return;
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_SelectNum--;
		if (m_SelectNum < 0) {
			m_SelectNum = 0;
			//SE.

			return;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_SelectNum++;
		if (m_SelectNum >= SELECT_MAX) {
			m_SelectNum = SELECT_MAX - 1;
			//SE.

			return;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_vUV = ENTER_UV_POS;
		//SE.
		m_ChangeCnt++;
	}

	//選択肢の文字の情報取得.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	m_vPos.x = CURSOR_POS.x;
	m_vPos.y = CURSOR_POS.y + (SpriteState.Disp.h * m_SelectNum);

}