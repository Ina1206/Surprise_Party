#ifndef CNEXT_SPEAK_CURSOR_H
#define CNEXT_SPEAK_CURSOR_H

#include "..\..\CUI.h"

/*****************************************
*		次の会話のカーソルクラス.
*****************/
class CNextSpeakCursor
	: public CUI
{
public:
	CNextSpeakCursor();
	~CNextSpeakCursor();

	//=================定数====================//.
	const float	ACC_MAX		= 1.5f;		//加速度最大値.
	const float	ACC_SPEED	= 0.05f;	//加速度減速速度.
	const float GRAVITY		= 0.5f;		//重力.
	const float SCALE_MAX	= 1.0f;		//大きさ最大値.

	//=================関数====================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.

	//===========情報置換処理関数==============//.
	//初期座標.
	void SetStartPos(const D3DXVECTOR3& vPos) { m_vStartPos = vPos; }
	//表示フラグ.
	void SetDispFlag(const bool& bFlag) { m_bDispFlag = bFlag; }

private:
	//=================関数====================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.

	//==================変数====================//.
	CSpriteUI*	m_pCSpriteUI;	//スプライトUI.
	D3DXVECTOR3 m_vStartPos;	//初期座標.
	bool		m_bDispFlag;	//表示フラグ.
	float		m_fAcc;			//加速度.
};

#endif	//#ifndef CNEXT_SPEAK_CURSOR_H.