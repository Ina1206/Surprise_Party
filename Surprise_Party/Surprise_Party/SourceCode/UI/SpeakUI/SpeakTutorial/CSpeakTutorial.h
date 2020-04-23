#ifndef CSPEAK_TUTORIAL_H
#define CSPEAK_TUTORIAL_H

#include "..\CSpeakUI.h"

//=================定数=======================//.
const unsigned int SELECT_GHOST_FLAG			= (1 << 0);	//お化け選択フラグ.
const unsigned int DECIDE_GHOST_FLAG			= (1 << 1);	//お化け決定フラグ.
const unsigned int DECIDE_ACT_FLAG				= (1 << 2);	//行動決定フラグ.
const unsigned int SELECT_GIMMICK_FLAG			= (1 << 3);	//ギミック選択フラグ.
const unsigned int DECIDE_GIMMICK_FLAG			= (1 << 4);	//ギミック決定フラグ.

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
	const unsigned int MAP_DESCRIPTION_FLAG			= (1 << 0);	//地図の説明フラグ.
	const unsigned int GHOST_DESCRIPTION_FLAG		= (1 << 1);	//お化けの説明フラグ.
	const unsigned int GIMMICK_DESCRIPTION_FLAG		= (1 << 2);	//ギミックの説明フラグ.
	const unsigned int PEOPLE_DESCRIPTION_FLAG		= (1 << 3);	//人々の説明フラグ.
	const unsigned int GAGE_DESCRIPTION_FLAG		= (1 << 4);	//驚きゲージの説明フラグ.
	const unsigned int CLOSE_TIME_DESCRIPTION_FLAG	= (1 << 5);	//閉鎖時間の説明フラグ.

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
	//説明フラグ.
	unsigned int GetDescriptionFlag() const { return m_DescriptionFlag; }

	//============情報置換処理関数=================//.
	//コメント進めるフラグ.
	void SetAdvanceCommentFlag(const bool& bFlag) { m_bAdvanceCommentFlag = bFlag; }


private:
	//==================関数=======================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void FindTutorial();	//チュートリアル見つける処理関数.
	void FindDescription();	//説明内容見つける処理関数.

	//==================変数=======================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;				//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vPos;						//座標.
	unsigned int				m_TutorialFlag;				//チュートリアルフラグ.
	unsigned int				m_DescriptionFlag;			//説明フラグ.
	bool						m_bAdvanceCommentFlag;		//コメント進めるフラグ.
	int							m_SelectMoveCount;			//選択移動カウント.
};

#endif	//#ifndef CSPEAK_TUTORIAL_H.