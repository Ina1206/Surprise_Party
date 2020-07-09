#ifndef CCHANGE_SCENE_CURSOR_H
#define CCHANGE_SCENE_CURSOR_H

#include "..\..\CUI.h"

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
	const D3DXVECTOR3	CONTROL_CURSOR_POS	= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//カーソル座標.
	
	const D3DXVECTOR3	RIGHT_CURSOR_ROT	= D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//カーソル角度.
	const D3DXVECTOR3	LEFT_CURSOR_ROT		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//カーソル角度.
	const D3DXVECTOR2	NORMAL_UV_POS		= D3DXVECTOR2(0.0f, 0.0f);				//通常UV座標.
	const D3DXVECTOR2	ENTER_UV_POS		= D3DXVECTOR2(0.0f, 1.0f);				//決定時のUV座標.

	const int			CHANGE_CNT_MAX		= 10;									//変更カウント最大数.
	const int			SELECT_MAX			= 2;									//選択肢最大数.

	const float			ANGLE_MAX			= 360.0f;								//角度最大値.
	const float			FLOATING_SPEED		= 0.1f;									//浮遊速度.
	const float			FLOATING_DISTANCE	= 1.5f;									//浮遊距離.

	const float			ADD_ACC_SPEED		= 0.5f;									//加速度加算速度.
	const float			GRAVITY				= 5.0f;									//重力.

	//===================関数======================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//=============情報置換処理関数================//.
	//変更待機フラグ.
	void SetChangeWaitFlag(const bool& bFlag) { m_bChangeWaitFlag = bFlag; }
	//操作フラグ.
	void SetControlFlag(const bool& bFlag) { m_bControlFlag = bFlag; }

	//=============情報取得処理関数================//.
	//選択終了フラグ.
	bool GetSelectFinishFlag() const { return m_bSelectFinishFlag; }
	//選択番号.
	int	GetSelectNum()const { return m_SelectNum; }

private:
	//===================関数======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void Control();		//操作処理関数.
	void UpDownFloat();	//上下浮遊処理関数.
	void Jump();		//ジャンプ処理関数.

	//===================変数======================//.
	CSpriteUI*	m_pCSpriteUI;			//スプライトUI.
	D3DXVECTOR2 m_vUV;					//UV座標.
	bool		m_bChangeWaitFlag;		//変更待機フラグ.
	bool		m_bSelectFinishFlag;	//選択終了フラグ.
	bool		m_bControlFlag;			//操作フラグ.
	int			m_ChangeCnt;			//変更カウント.
	int			m_SelectNum;			//選択番号.
	float		m_fAngle;				//角度.
	float		m_fAcc;					//加速度.
	D3DXVECTOR3 m_vJumpBeforePos;		//ジャンプ前の座標.
};

#endif	//#ifndef CCHANGE_SCENE_CURSOR_H