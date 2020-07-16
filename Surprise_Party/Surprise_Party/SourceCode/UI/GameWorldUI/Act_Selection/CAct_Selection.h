#ifndef CACT_SELECTION_H
#define CACT_SELECTION_H

#include "..\CGameWorldUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*************************************
*		行動選択クラス.
********/
class CAct_Selection
	: public CGameWorldUI
{
public:
	CAct_Selection();
	~CAct_Selection();

	//====================定数=======================//.
	const int			CHOICE_MAX			= 2;					//選択肢の最大数.
	const int			LEFT_DIRECTION		= -1;					//左方向数値.
	const int			RIGHT_DIRECTION		= 1;					//右方向数値.
	const unsigned int	OPEN_MOVE			= (1 << 0);				//開く移動.
	const unsigned int	CLOSE_MOVE			= (1 << 1);				//閉じる移動.
	const float			MOVE_SPEED			= 0.1f;					//移動速度.
	const float			M0VE_DISTANCE_MAX	= 2.0f;					//移動距離最大.
	const float			MOVE_DISTANCE_MIN	= 0.0f;					//移動距離最小.
	const float			ROTATION_SPEED		= 0.02f;				//回転速度.
	const float			SELECT_SCALE		= 1.3f;					//選択中の大きさ.
	const float			NORMAL_SCALE		= 1.0f;					//通常の大きさ.
	const float			SELECT_ALPHA		= 1.0f;					//選択中の透過値.
	const float			NORMAL_ALPHA		= 0.7f;					//通常の透過値.
	const unsigned int	MOVE_FLAG			= (1 << 0);				//移動フラグ.
	const unsigned int	REST_FLAG			= (1 << 1);				//休憩フラグ.

	//===================列挙体======================//.
	//お化け行動種類.
	enum class enGhostActType {
		Move = 0,	//移動.
		Rest,		//休憩.

		Max,
		Start = Move,
	};

	//====================関数=======================//.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.


	//==============情報置換処理関数=================//.
	//選択フラグ.
	void SetSelectFlag(const bool& flag) { m_bSelectFlag = flag; }
	//チュートリアルフラグ.
	void SetTutorialFlag(const bool& flag) { m_bTutorialFlag = flag; }
	//決定フラグ.
	void SetDecideFlag(const bool& flag) { m_bDecideFlag = flag; }
	//選択肢を閉じるフラグ.
	void SetCloseMoveFlag() { m_MoveFlag = CLOSE_MOVE; }

	//==============情報取得処理関数=================//.
	//選択フラグ.
	bool GetSelectFlag() { return m_bSelectFlag; }
	//お化け行動フラグ.
	int GetGhostActFlag() { return m_GhostActFlag; }

private:
	//====================関数=======================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void BeforeMove();		//動く前の処理関数.
	void OpenMove();		//開く移動処理関数.
	void CloseMove();		//閉じる移動処理関数.
	void Control();			//操作処理関数.

	//====================変数=======================//.
	std::vector<CSprite*>		m_pCSprite;				//スプライトクラス.
	std::vector<D3DXVECTOR3>	m_vSpritePos;			//スプライト座標.
	std::vector<D3DXVECTOR3>	m_vSpriteRot;			//角度.
	std::vector<float>			m_fSpriteAlpha;			//透過値.
	std::vector<float>			m_fSpriteScale;			//大きさ.
	std::vector<float>			m_fMoveDistance;		//移動速度.
	std::vector<int>			m_Direction;			//方向.
	bool						m_bSelectFlag;			//選択フラグ.
	unsigned int				m_MoveFlag;				//移動フラグ.
	int							m_SelectNum;			//選択番号.
	int							m_GhostActFlag;			//お化け行動フラグ.
	bool						m_bTutorialFlag;		//チュートリアルフラグ.
	bool						m_bDecideFlag;			//決定フラグ.
	CPlaySoundManager*			m_pCPlaySoundManager;	//音再生管理クラス.
	bool						m_bOpenSEFlag;			//開くSEフラグ.
};

#endif //#ifndef CACT_SELECTION_H.