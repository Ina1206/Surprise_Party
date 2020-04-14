#ifndef CSPEAK_TUTORIAL_H
#define CSPEAK_TUTORIAL_H

#include "..\CSpeakUI.h"

/******************************************
*		チュートリアル会話.
***************/
class CSpeakTutorial
	: public CSpeakUI
{
public:
	CSpeakTutorial();
	~CSpeakTutorial();

	//=================定数=======================//.
	const unsigned int SELECT_GHOST_FLAG	= (1 << 0);	//お化け選択フラグ.
	const unsigned int DECIDE_GHOST_FLAG	= (1 << 1);	//お化け決定フラグ.
	const unsigned int DECIDE_ACT_FLAG		= (1 << 2);	//行動決定フラグ.
	const unsigned int SELECT_GIMMICK_FLAG	= (1 << 3);	//ギミック選択フラグ.
	const unsigned int DECIDE_GIMMICK_FLAG	= (1 << 4);	//ギミック決定フラグ.

	//=================関数=======================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.
	void AdvanceOnceComment();	//一回コメントを進める処理関数.
	void AddSelectMoveCount();	//選択移動カウント追加処理関数.

	//============情報取得処理関数=================//.
	//チュートリアルフラグ.
	unsigned int GetTutorialFlag() const { return m_TutorialFlag; }
	//コメント進めるフラグ.
	bool GetAdvanceCommentFlag() const { return m_bAdvanceCommentFlag; }

	//============情報置換処理関数=================//.
	//コメント進めるフラグ.
	void SetAdvanceCommentFlag(const bool& bFlag) { m_bAdvanceCommentFlag = bFlag; }


private:
	//==================関数=======================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void SerchTutorial();	//チュートリアル検索処理関数.

	//==================変数=======================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;				//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vPos;						//座標.
	unsigned int				m_TutorialFlag;				//チュートリアルフラグ.
	bool						m_bAdvanceCommentFlag;		//コメント進めるフラグ.
	int							m_SelectMoveCount;			//選択移動カウント.
};

#endif	//#ifndef CSPEAK_TUTORIAL_H.