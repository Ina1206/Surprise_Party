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

	//==================定数====================//.
	const D3DXVECTOR3	BALLOON_POS				= D3DXVECTOR3(650.0f, 150.0f, 0.0f);	//吹き出し座標.
	const D3DXVECTOR3	COMMENT_POS				= D3DXVECTOR3(690.0f, 250.0f, 0.0f);	//コメント座標.
	const D3DXVECTOR2	DISP_GHOST_BALLOON		= D3DXVECTOR2(0.0f, 0.0f);				//現れるお化け吹き出しのパターン.
	const D3DXVECTOR2	SWITCH_GHOST_BALLOON	= D3DXVECTOR2(1.0f, 0.0f);				//スイッチお化け吹き出しパターン.


	//==================関数====================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//============情報置換処理関数==============//.
	void SetGhostTypeNum(const int& num) { m_GhostTypeNum = num; }

private:
	//==================関数====================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void RenderBalloon();	//吹き出し描画処理関数.
	void RenderComment();	//コメント描画処理関数.

	//==================変数====================//.
	CSpriteUI*					m_pCBalloonSpriteUI;	//スプライトUI.
	std::vector<CSpriteUI*>		m_pCCommentSpriteUI;	//コメントスプライトUI.
	int							m_GhostTypeNum;			//お化けの種類番号.
	std::vector<D3DXVECTOR2>	m_vPatternNum;			//パターン番号.	
};

#endif	//#ifndef CSPEAK_WORK_GHOST_H.