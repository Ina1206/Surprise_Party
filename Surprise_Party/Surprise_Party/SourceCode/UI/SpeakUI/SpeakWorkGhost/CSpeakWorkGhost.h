#ifndef CSPEAK_WORK_GHOST_H
#define CSPEAK_WORK_GHOST_H

#include "..\CSpeakUI.h"

/*************************************
*		働くお化け会話クラス.
************/
class CSpeakWorkGhost
	: public CSpeakUI
{
public:
	CSpeakWorkGhost();
	~CSpeakWorkGhost();

	//==================関数====================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//============情報置換処理関数==============//.
	void SetGhostTypeNum(const int& num) { m_GhostTypeNum = num; }

private:
	//==================関数====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//==================変数====================//.
	CSpriteUI*		m_pCSpriteUI;	//スプライトUI.
	D3DXVECTOR3		m_vPos;			//座標.
	int				m_GhostTypeNum;	//お化けの種類番号.
};

#endif	//#ifndef CSPEAK_WORK_GHOST_H.