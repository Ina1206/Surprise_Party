#ifndef CSELECT_STRING_UI_H
#define CSELECT_STRING_UI_H

#include "..\..\CUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/***************************************
*		選択肢UIクラス.
********************/
class CSelectStringUI
	: public CUI
{
public:
	CSelectStringUI();
	CSelectStringUI(const bool& bStartFlag);
	~CSelectStringUI();

	//====================定数======================//.
	const D3DXVECTOR3	SELECT_STRING_POS	= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//選択文章座標.

	const int			SELECT_STRING_MAX	= 2;									//選択スプライト.

	const unsigned int FETCH_FLAG			= (1 << 0);								//取りに行くフラグ.
	const unsigned int MOVE_FLAG			= (1 << 1);								//運ぶフラグ.
	const unsigned int CONTROL_FLAG			= (1 << 2);								//操作フラグ.

	//====================関数======================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//==============情報取得処理関数================//.
	//お化けのカーソル座標.
	D3DXVECTOR3 GetGhostCursorPos() const { return m_vGhostCursorPos; }
	//移動停止フラグ.
	bool GetMoveStopFlag() const { return m_bMoveStopFlag; }

	//==============情報置換処理関数================//.
	//移動フラグ.
	void SetMoveFlag(const unsigned int& Flag) { m_MoveFlag = Flag; }
	//移動距離フラグ.
	void SetMoveDistance(const float& fDistance) { m_fMoveDistance = fDistance; }
	//誤差範囲.
	void SetErrorRange(const float& fRange) { m_fErrorRange = fRange; }

private:
	//====================関数======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void Fetch();		//取りに行く処理関数.
	void Move();		//移動処理関数.

	void ControlPos();	//操作時の座標処理関数.

	//====================変数======================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;			//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vStringPos;			//座標.
	std::vector<D3DXVECTOR3>	m_vBeforeMovePos;		//移動前の座標.
	std::vector<D3DXVECTOR3>	m_vLastPos;				//最終座標.

	D3DXVECTOR3					m_vGhostCursorPos;		//お化けのカーソル座標.

	bool						m_bStartFlag;			//ゲーム開始フラグ.
	bool						m_bMoveStopFlag;		//移動停止フラグ.

	unsigned int				m_MoveFlag;				//移動フラグ.

	float						m_fMoveDistance;		//移動距離.
	float						m_fErrorRange;			//誤差範囲.

	CPlaySoundManager*			m_pCPlaySoundManager;	//音再生管理クラス.
};

#endif	//#ifndef CSELECT_STRING_UI_H.