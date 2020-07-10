#ifndef CTITLE_STRING_UI_H
#define CTITLE_STRING_UI_H

#include "..\..\..\CUI.h"

/*********************************************
*		タイトル文章UIクラス.
*******************/
class CTitleStringUI
	: public CUI
{
public:
	CTitleStringUI();
	~CTitleStringUI();

	//====================定数==========================//.
	const D3DXVECTOR3	TITLE_POS			= D3DXVECTOR3(40.5f, 90.8f, 0.0f);	//タイトル座標.
	const int			TITLE_STRING_MAX	= 2;								//タイトルの文章最大値.	

	const unsigned int	FETCH_FLAG			= (1 << 0);							//取りに行くフラグ.
	const unsigned int  MOVE_FLAG			= (1 << 1);							//移動フラグ.
	const unsigned int  CONTROL_FLAG		= (1 << 2);							//操作フラグ.

	//====================関数==========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//==============情報取得処理関数====================//.
	//取りに行くお化けの座標.
	D3DXVECTOR3 GetFetchGhostPos() const { return m_vFetchGhostPos; }
	//移動停止フラグ.
	bool GetStopMoveFlag() const { return m_bStopFlag[m_FetchStringNum]; }

	//==============情報置換処理関数====================//.
	//移動距離.
	void SetMoveDistance(const float& fDistance) { m_fMoveDistance = fDistance; }
	//誤差範囲.
	void SetErrorRange(const float& ErrorRange) { m_fErrorRange = ErrorRange; }
	//移動フラグ.
	void SetMoveFlag(const unsigned int& Flag) { m_MoveFlag = Flag; }
	//次の文章に番号変更.
	void SetChangeNextStringNum() { m_FetchStringNum++; }

private:
	//====================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void ControlPos();	//操作時の座標処理関数.
	void FetchPos();	//取りに行く座標処理関数.
	void Move();		//移動処理関数.

	//====================変数==========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;		//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vTitlePos;		//座標.
	std::vector<D3DXVECTOR2>	m_vTitleUV;			//UV.
	std::vector<D3DXVECTOR3>	m_vBeforeMovePos;	//移動前の座標.
	std::vector<D3DXVECTOR3>	m_vLastPos;			//最終的な座標.
	D3DXVECTOR3					m_vFetchGhostPos;	//取りに行くお化けの座標.
	int							m_FetchStringNum;	//取りに行く文章番号.
	float						m_fMoveDistance;	//移動距離.
	std::vector<bool>			m_bStopFlag;		//停止フラグ.
	float						m_fErrorRange;		//誤差範囲.
	unsigned int				m_MoveFlag;			//移動フラグ.
};

#endif	//#ifndef CTITLE_STRING_UI_H.