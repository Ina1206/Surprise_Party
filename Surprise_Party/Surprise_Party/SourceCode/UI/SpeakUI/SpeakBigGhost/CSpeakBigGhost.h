#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"

/**********************************************
*		ビッグゴーストがしゃべるクラス.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================定数=======================//.
	const float		STRING_WIDTH_MAX	= 950.0f;		//文章の幅最大数.
	const float		ALPHA_MIN			= 0.0f;			//透過値最小値.
	const float		ALPHA_MAX			= 1.0f;			//透過値最大値.
	const float		ALPHA_SPEED			= 0.1f;			//透過値速度.
	const float		FONT_SCALE			= 50.0f;		//文字の大きさ.
	const int		FIRST_CHARACTER_NUM = 0;			//一文字目の文章.


	const int		SELECT_MAX			= 2;			//選択最大数.

	const unsigned int TRANSPARENTING_FLAG	= (1 << 0);	//透過処理中フラグ.
	const unsigned int SELECT_FLAG			= (1 << 1);	//選択フラグ.
	const unsigned int SELECTED_STRING_FLAG = (1 << 2);	//選択した文章フラグ.

	const unsigned int FINISH_NEXT_TITLE	= (1 << 0);	//次がタイトルでの終了.
	const unsigned int FINISH_NEXT_GAME		= (1 << 1);	//次がゲームでの終了.

	//======================関数=======================//.
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.
	void RenderInit(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//描画初期設定処理関数.

	//================情報獲得処理関数==================//.
	int GetEmotionNum() const { return m_EmotionNum[m_SpeakNum]; }
	unsigned int GetFinishFlag() const { return m_FinishFlag; }
	bool GetTutorialFlag() const { return m_bTutorialFlag; }

	//================情報置換処理関数==================//.
	void SetControlFlag(const bool& flag) { m_bControlFlag = flag; }

private:
	//======================関数========================//.
	void Init();									//初期化処理関数.
	void Release();									//解放処理関数.
	void LoadSpeakString();							//会話文章読み込み処理関数.
	void TransparentFont();							//文字透過処理関数.
	void DecisionSelectString();					//選択文章処理関数.
	void FindNextString(const int& NextStringNum);	//次の文章を見つける処理関数.
	void SelectingMove();							//選択中移動処理関数.
	void ChangeString();							//文章変更処理関数.

	//======================変数========================//.
	D3DXMATRIX					m_mView;			//ビュー行列.
	D3DXMATRIX					m_mProj;			//プロジェクション行列.
	D3DXVECTOR3					m_vCameraPos;		//カメラ座標.

	CSpriteUI*					m_pCSpriteUI;		//スプライトUI.
	std::vector<CSprite*>		m_pCSprite;			//スプライトクラス.
	std::vector<D3DXVECTOR3>	m_vSelectPos;		//座標.
	std::vector<D3DXVECTOR3>	m_vSelectRot;		//角度.
	std::vector<float>			m_fSelectAlpha;		//透過値.
	std::vector<float>			m_fSelectScale;		//大きさ.

	std::vector<std::string>	m_stSelectString;	//選択文章.
	std::vector<int>			m_EmotionNum;		//感情番号.
	unsigned int				m_StringFlag;		//文章フラグ.
	int							m_SelectNum;		//選択番号.
	int							m_SelectCnt;		//選択カウント.

	unsigned int				m_FinishFlag;		//終了フラグ.
	bool						m_bTutorialFlag;	//チュートリアルフラグ.

	bool						m_bControlFlag;		//操作フラグ.

};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.