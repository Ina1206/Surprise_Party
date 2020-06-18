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
	//初期座標設定処理関数.
	InitPos();
}

CSceneUIBase::~CSceneUIBase()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		更新処理関数.
//==========================================.
void CSceneUIBase::Update()
{
	m_bSelectFinishFlag = false;

	//決定後の処理.
	if (m_ChangeCnt > 0) {
		m_ChangeCnt++;

		//選択終了.
		if (m_ChangeCnt >= CHANGE_CNT_MAX) {
			m_bSelectFinishFlag = true;
			m_vUV[CURSOR_NUM] = NORMAL_UV_POS;
			m_ChangeCnt = 0;
		}
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
		m_vUV[CURSOR_NUM] = ENTER_UV_POS;
		//SE.
		m_ChangeCnt++;
	}


	m_vUIPos[CURSOR_NUM].y = CURSOR_POS.y + (SELECT_STRING_WIDHT * m_SelectNum);

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
//		初期座標設定処理関数.
//==========================================.
void CSceneUIBase::InitPos()
{
	//要素数設定.
	m_pCSpriteUI.resize(UI_MAX);
	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIRot.resize(m_pCSpriteUI.size());
	m_vUV.resize(m_pCSpriteUI.size());

	//初期化.
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		m_vUV[sprite] = INIT_UV;
		m_vUIRot[sprite] = INIT_ROT;

		if (static_cast<int>(sprite) < SELECT_STRING_MAX) {
			m_vUIPos[sprite] = SELECT_STRING_POS;
			m_vUIPos[sprite].y += SELECT_STRING_WIDHT * sprite;
			continue;
		}
		m_vUIPos[sprite] = INIT_POS;
	}
	m_vUIPos[CURSOR_NUM] = CURSOR_POS;
	m_vUIRot[CURSOR_NUM] = CURSOR_ROT;

	//カーソル.
	m_pCSpriteUI[CURSOR_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
}

//===========================================.
//		解放処理関数.
//===========================================.
void CSceneUIBase::Release()
{

}