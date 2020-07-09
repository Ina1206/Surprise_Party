#include "CSceneUIBase.h"

/*****************************************
*		シーンUIの基底クラス.
****************/
CSceneUIBase::CSceneUIBase()
	: m_pCSpriteUI			()
	, m_vUIPos				()
	, m_vUV					()
	, m_SelectNum			(0)
	, m_ChangeCnt			(0)
	, m_bSelectFinishFlag	(false)
{

}

CSceneUIBase::~CSceneUIBase()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		描画処理関数.
//==========================================.
void CSceneUIBase::Render()
{
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		//UV座標設定.
		m_pCSpriteUI[sprite]->SetPattern(m_vUV[sprite]);
		//角度.
		m_pCSpriteUI[sprite]->SetRotation(m_vUIRot[sprite]);
		//座標.
		m_pCSpriteUI[sprite]->SetPosition(m_vUIPos[sprite]);
		//描画.
		CDepth_Stencil* m_pCDepthStenceil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepthStenceil->SetDepth(false);
		m_pCSpriteUI[sprite]->Render();
		m_pCDepthStenceil->SetDepth(true);
	}

}

//==========================================.
//		操作処理関数.
//==========================================.
void CSceneUIBase::Control(const bool& bChangeWaitFlag)
{
	m_bSelectFinishFlag = false;

	//カーソル番号.
	const int CursorNum = static_cast<int>(m_pCSpriteUI.size()) - 1;

	//決定後の処理.
	if (m_ChangeCnt > 0) {
		if (bChangeWaitFlag == true) {
			m_ChangeCnt++;

			//選択終了.
			if (m_ChangeCnt >= CHANGE_CNT_MAX) {
				m_bSelectFinishFlag = true;
				m_vUV[CursorNum] = NORMAL_UV_POS;
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
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_SelectNum++;
		if (m_SelectNum >= SELECT_STRING_MAX) {
			m_SelectNum = SELECT_STRING_MAX - 1;
			//SE.
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_vUV[CursorNum] = ENTER_UV_POS;
		//SE.
		m_ChangeCnt++;
	}


	m_vUIPos[CursorNum].y = CURSOR_POS.y + (SELECT_STRING_WIDHT * m_SelectNum);

}

//==========================================.
//		要素数初期化処理関数.
//==========================================.
void CSceneUIBase::InitElementCounts()
{
	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIRot.resize(m_pCSpriteUI.size());
	m_vUV.resize(m_pCSpriteUI.size());

	//初期値設定.
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_vUIPos[ui]	= INIT_POS;
		m_vUIRot[ui]	= INIT_ROT;
		m_vUV[ui]		= INIT_UV;
	}
}

//==========================================.
//		操作時選択文章座標設定処理関数.
//==========================================.
void CSceneUIBase::ControlSelectStringPos()
{
	//初期化.
	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		m_vUIPos[sprite]	= SELECT_STRING_POS;
		m_vUIPos[sprite].y += SELECT_STRING_WIDHT * sprite;
	}

}

//===========================================.
//		カーソル初期設定処理関数.
//===========================================.
void CSceneUIBase::InitCursor()
{
	//カーソル.
	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor));
	m_vUIPos.push_back(INIT_POS);
	m_vUIRot.push_back(RIGHT_CURSOR_ROT);
	m_vUV.push_back(NORMAL_UV_POS);
}

//===========================================.
//		解放処理関数.
//===========================================.
void CSceneUIBase::Release()
{

}