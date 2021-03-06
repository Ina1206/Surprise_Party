#ifndef CCHANGE_SCENE_CURSOR_H
#define CCHANGE_SCENE_CURSOR_H

#include "..\..\CUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/****************************************
*		シーン変更用カーソルUIクラス.
*****************/
class CChangeSceneCursorUI
	: public CUI
{
public:
	CChangeSceneCursorUI();
	~CChangeSceneCursorUI();

	//===================定数======================//.	
	const D3DXVECTOR3	CONTROL_CURSOR_POS		= D3DXVECTOR3(750.0f, 450.0f, 0.0f);		//カーソル座標.
						
	const D3DXVECTOR3	SCREEN_CENTER_POS		= D3DXVECTOR3(WND_W, WND_H, 0.0f) / 2.0f;	//画面中央の座標.

	const D3DXVECTOR3	RIGHT_CURSOR_ROT		= D3DXVECTOR3(0.0f, 3.0f, 0.0f);			//カーソル角度.
	const D3DXVECTOR3	LEFT_CURSOR_ROT			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//カーソル角度.
	const D3DXVECTOR2	NORMAL_UV_POS			= D3DXVECTOR2(0.0f, 0.0f);					//通常UV座標.
	const D3DXVECTOR2	ENTER_UV_POS			= D3DXVECTOR2(0.0f, 1.0f);					//決定時のUV座標.
	const D3DXVECTOR2	HAVE_TROUBLE_UV_POS		= D3DXVECTOR2(1.0f, 0.0f);					//困ったUV座標.
	const D3DXVECTOR2	SURPRISE_UV_POS			= D3DXVECTOR2(1.0f, 1.0f);					//驚きUV座標.

	const int			CHANGE_CNT_MAX			= 10;										//変更カウント最大数.
	const int			SELECT_MAX				= 2;										//選択肢最大数.
						
	const float			ANGLE_MAX				= 360.0f;									//角度最大値.
	const float			FLOATING_SPEED			= 0.1f;										//浮遊速度.
	const float			FLOATING_DISTANCE		= 1.5f;										//浮遊距離.
						
	const float			ADD_ACC_SPEED			= 0.5f;										//加速度加算速度.
	const float			GRAVITY					= 5.0f;										//重力.
	const int			MOVE_WAIT_MAX			= 30;										//移動待機カウント最大.

	const int			RIGHT_DIRECT_NUM		= 1;										//右に移動方向番号.
	const int			CHANGE_DIRECT			= -1;										//方向変更.
	const float			ROTATION_SPEED			= 0.1f;										//回転速度.

	const float			MOVE_SPEED				= 5.0f;										//移動速度.

	//m_CarryFlag.
	const unsigned int	LEFT_TITLE_CARRY_FLAG	= (1 << 0);									//左のタイトル運ぶフラグ.
	const unsigned int	RIGHT_TITLE_CARRY_FLAG	= (1 << 1);									//右のタイトル運ぶフラグ.
	const unsigned int	SELECT_CARRY_FLAG		= (1 << 2);									//選択肢運ぶフラグ.

	//m_FetchFlag.
	const unsigned int	LEFT_TITLE_FETCH_FLAG	= (1 << 0);									//左のタイトルを取りに行くフラグ.
	const unsigned int	RIGHT_TITLE_FETCH_FLAG	= (1 << 1);									//右のタイトルを取りに行くフラグ.
	const unsigned int	SELECT_FEATCH_FLAG		= (1 << 2);									//選択肢を取りに行くフラグ.

	//==================列挙体=====================//.
	//移動種類.
	enum class enMoveType {
		StartMove = 0,		//開始時の移動.
		Surprise,			//驚くフラグ.
		LeftTitleFetch,		//左のタイトルを取りに行く.
		LeftTitleCarry,		//左のタイトルを運ぶ.
		RightTitleFetch,	//右のタイトルを取りに行く.
		RightTitleCarry,	//右のタイトルを運ぶ.
		Rejoice,			//喜ぶ.
		SelectFetch,		//選択肢取りに行く.
		SelectCarry,		//選択肢運ぶ.
		BecomeCursor,		//カーソルになる.
	};

	//===================関数======================//.
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.

	//=============情報置換処理関数================//.
	//変更待機フラグ.
	void SetChangeWaitFlag(const bool& bFlag) { m_bChangeWaitFlag = bFlag; }
	//操作フラグ.
	void SetControlFlag(const bool& bFlag) { m_bControlFlag = bFlag; }
	//タイトル運び初めの座標.
	void SetCarryStartPos(const D3DXVECTOR3& vPos) { m_vCarryStartPos = vPos; }
	//運ぶ行動終了.
	void SetFinishCarry() { m_CarryFlag = 0; }

	//=============情報取得処理関数================//.
	//選択終了フラグ.
	bool GetSelectFinishFlag() const { return m_bSelectFinishFlag; }
	//選択番号.
	int	GetSelectNum()const { return m_SelectNum; }
	//運ぶフラグ.
	unsigned int GetCarryFlag() const { return m_CarryFlag; }
	//取りに行くフラグ.
	unsigned int GetFetchFlag() const { return m_FetchFlag; }
	//運んでいる時の距離.
	float GetCarryDistance() const { return m_fCarryDisntace; }

private:
	//===================関数======================//.
	void Init();											//初期化処理関数.
	void Release();											//解放処理関数.
	inline void Act();										//行動処理関数.
	inline void Control();									//操作処理関数.
	bool Move(const float& MoveDistanceMax);				//移動処理関数.
	bool MoveToDestination(const D3DXVECTOR3& vTargetPos);	//目的地への移動処理関数.
	void UpDownFloat();										//上下浮遊処理関数.
	bool Jump();											//ジャンプ処理関数.
	bool ChangeMoveDirect();								//移動方向変更処理関数.
	void CarryMove();										//運び移動処理関数.
	bool FetchString(const float& MoveDistanceMax);			//文章を取りに行く処理関数.
	void MoveStart();										//開始時の移動処理関数.
	void Surprise();										//驚き処理関数.
	void LeftTitleFetch();									//左タイトル文章取りに行く処理関数.
	void LeftTitleCarry();									//左タイトル文章運ぶ処理関数.
	void RightTitleFetch();									//右タイトル文章取りに行く処理関数.
	void RightTitleCarry();									//右タイトル文章取りに行く処理関数.
	void Rejoice();											//喜び処理関数.
	void SelectFetch();										//選択肢を取りに行く処理関数.
	void SelectCarry();										//選択肢を運ぶ処理関数.
	void BecomeCursor();									//カーソルになる処理関数.

	//===================変数======================//.
	CSpriteUI*			m_pCSpriteUI;						//スプライトUI.
	D3DXVECTOR2			m_vUV;								//UV座標.
	D3DXVECTOR3			m_vPrePos;							//事前の座標.
	bool				m_bChangeWaitFlag;					//変更待機フラグ.
	bool				m_bSelectFinishFlag;				//選択終了フラグ.
	bool				m_bControlFlag;						//操作フラグ.
	int					m_ChangeCnt;						//変更カウント.
	int					m_SelectNum;						//選択番号.

	float				m_fAngle;							//角度.

	float				m_fAcc;								//加速度.
	D3DXVECTOR3			m_vJumpBeforePos;					//ジャンプ前の座標.
	int					m_MaxJump;							//ジャンプ最大値.
	int					m_JumpCnt;							//ジャンプカウント.

	int					m_MoveDirect;						//移動方向.
	bool				m_bChangeDirect;					//方向変更フラグ.
	D3DXVECTOR3			m_vChangeDirectBeforeRot;			//方向変更前の角度.
	int					m_MoveWaitCnt;						//移動待機フラグ.
	bool				m_bArrivalFlga;						//到着フラグ.

	D3DXVECTOR3			m_vCarryStartPos;					//タイトル運びはじめの座標.
	unsigned int		m_CarryFlag;						//運ぶフラグ.
	unsigned int		m_FetchFlag;						//取りに行くフラグ.
	float				m_fCarryDisntace;					//運ぶ距離.

	int					m_MoveType;							//移動フラグ.

	float				m_OutSidePos;						//画面外のx座標.

	CPlaySoundManager*	m_pCPlaySoundManager;				//音再生管理クラス.
	bool				m_bPlayJumpSE;						//ジャンプ再生フラグ.
	bool				m_bPlayTurnSE;						//回転再生フラグ.
	bool				m_bPlayFloationSE;					//浮遊SE再生フラグ.
};

#endif	//#ifndef CCHANGE_SCENE_CURSOR_H