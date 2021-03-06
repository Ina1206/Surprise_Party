#ifndef CSPEAK_TUTORIAL_H
#define CSPEAK_TUTORIAL_H

#include "..\CSpeakUI.h"
#include "..\NextSpeakCursor\CNextSpeakCursor.h"

//=================定数=======================//.
const unsigned int SELECT_GHOST_FLAG			= (1 << 0);	//お化け選択フラグ.
const unsigned int DECIDE_GHOST_FLAG			= (1 << 1);	//お化け決定フラグ.
const unsigned int DECIDE_ACT_FLAG				= (1 << 2);	//行動決定フラグ.
const unsigned int SELECT_GIMMICK_FLAG			= (1 << 3);	//ギミック選択フラグ.
const unsigned int DECIDE_GIMMICK_FLAG			= (1 << 4);	//ギミック決定フラグ.

const unsigned int CustomerEnterSE				= (1 << 0);	//客が入ってきたSE.
const unsigned int SeePeople					= (1 << 1);	//客を見る.
const unsigned int DescriptionEnd				= (1 << 2);	//説明終了.

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
	const unsigned int	MAP_DESCRIPTION_FLAG		= (1 << 0);							//地図の説明フラグ.
	const unsigned int	GHOST_DESCRIPTION_FLAG		= (1 << 1);							//お化けの説明フラグ.
	const unsigned int	GIMMICK_DESCRIPTION_FLAG	= (1 << 2);							//ギミックの説明フラグ.
	const unsigned int	PEOPLE_DESCRIPTION_FLAG		= (1 << 3);							//人々の説明フラグ.
	const unsigned int	GAGE_DESCRIPTION_FLAG		= (1 << 4);							//驚きゲージの説明フラグ.
	const unsigned int	CLOSE_TIME_DESCRIPTION_FLAG	= (1 << 5);							//閉鎖時間の説明フラグ.

	const float			DESCRIPTION_ICON_SCALE		= 0.9f;								//説明用アイコン大きさ.	

	const float			DISP_CURSOR_POS_ADJUST		= 40.0f;							//表示カーソル座標微調整.

	const D3DXVECTOR2	BALLOON_UV_POS				= D3DXVECTOR2(1.0f, 1.0f);			//吹き出しUV座標.
	const float			BALLOON_SCALE				= 1.3f;								//吹き出し大きさ.

	const D3DXVECTOR3	BIG_GHOST_ICON_POS			= D3DXVECTOR3(10.0f, 400.0f, 0.0f);	//吹き出しの座標.
	const D3DXVECTOR3	BALLON_POS					= D3DXVECTOR3(20.0f, 150.0f, 0.0f);	//大きいお化けのアイコン座標.
	const D3DXVECTOR3	FONT_START_POS				= D3DXVECTOR3(60.0f, 210.0f, 0.0f);	//フォント開始座標.


	//=================関数=======================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.
	void AdvanceOnceComment();	//一回コメントを進める処理関数.
	void AddSelectMoveCount();	//選択移動カウント追加処理関数.

	//============情報取得処理関数=================//.
	//チュートリアルフラグ.
	unsigned int GetTutorialFlag() const { return m_DefinitiveTutorialFlag; }
	//unsigned int GetTutorialFlag() const { return m_TutorialFlag; }
	//コメント進めるフラグ.
	bool GetAdvanceCommentFlag() const { return m_bAdvanceCommentFlag; }
	//説明フラグ.
	unsigned int GetDescriptionFlag() const { return m_DescriptionFlag; }
	//開始直前フラグ.
	unsigned int GetStartLatestFlag() const { return m_enStartLatestFlag; }
	//終了フラグ.
	bool GetDescriptionEndFlag() const { return m_bDescriptionEnd; }

	//============情報置換処理関数=================//.
	//コメント進めるフラグ.
	void SetAdvanceCommentFlag(const bool& bFlag) { m_bAdvanceCommentFlag = bFlag; }


private:
	//==================関数=======================//.
	void Init();									//初期化処理関数.
	void Release();									//解放処理関数.
	void FindTutorial();							//チュートリアル見つける処理関数.
	void FindDescription();							//説明内容見つける処理関数.
	void SettingDescriptionIcon();					//説明用アイコン設定処理関数.
	void RenderDescriptionIcon();					//説明用アイコン描画処理関数.
	void GhostIconSetting(const int& IconMax);		//お化けアイコン設定処理関数.
	void GimmickIconSetting(const int& IconMax);	//ギミックアイコン設定処理関数.
	void PeopleIconSetting(const int& IconMax);		//人々のアイコン設定処理関数.

	//==================変数=======================//.
	std::vector<CSpriteUI*>				m_pCSpriteUI;				//スプライトUI.
	std::vector<CSpriteUI*>				m_pCDescriptionIcon;		//説明用アイコン.
	std::vector<D3DXVECTOR3>			m_vIconPos;					//アイコン座標.
	std::vector<D3DXVECTOR3>			m_vPos;						//座標.
	std::vector<D3DXVECTOR2>			m_vPattern;					//パターン番号.
	unsigned int						m_TutorialFlag;				//チュートリアルフラグ.
	unsigned int						m_DefinitiveTutorialFlag;	//決定版チュートリアルフラグ.
	unsigned int						m_DescriptionFlag;			//説明フラグ.
	bool								m_bAdvanceCommentFlag;		//コメント進めるフラグ.
	int									m_SelectMoveCount;			//選択移動カウント.
	unsigned int						m_enStartLatestFlag;		//開始直前フラグ.
	bool								m_bDescriptionEnd;			//終了フラグ.

	std::unique_ptr<CNextSpeakCursor>	m_pCNextSpeakCursor;		//次の文章カーソル.
};

#endif	//#ifndef CSPEAK_TUTORIAL_H.