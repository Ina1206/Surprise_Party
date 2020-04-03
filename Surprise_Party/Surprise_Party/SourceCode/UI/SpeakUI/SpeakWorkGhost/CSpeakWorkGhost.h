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

private:
	//==================関数====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//==================変数====================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;
	std::vector<D3DXVECTOR3>	m_vPos;
};

#endif	//#ifndef CSPEAK_WORK_GHOST_H.