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
	const unsigned int SELECT_GHOST_FLAG = (1 << 0);	//お化け選択フラグ.
	const unsigned int DECIDE_GHOST_FLAG = (1 << 1);	//お化け決定フラグ.
	const unsigned int SELECT_GIMMICK_FLAG = (1 << 2);	//ギミック選択フラグ.
	const unsigned int DECIDE_GIMMICK_FLAG = (1 << 3);	//ギミック決定フラグ.

	//=================関数=======================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//============情報取得処理関数=================//.
	//チュートリアルフラグ.
	unsigned int GetTutorialFlag() const { return m_TutorialFlag; }



private:
	//==================関数=======================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void SerchTutorial();	//チュートリアル検索処理関数.

	//==================変数=======================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vPos;			//座標.
	unsigned int				m_TutorialFlag;	//チュートリアルフラグ.
};

#endif	//#ifndef CSPEAK_TUTORIAL_H.