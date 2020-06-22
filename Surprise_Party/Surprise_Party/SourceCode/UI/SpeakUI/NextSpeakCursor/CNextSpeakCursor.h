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

	//=================関数====================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.

	//===========情報置換処理関数==============//.
	void SetStartPos(const D3DXVECTOR3& vPos) { m_vStartPos = vPos; }
	void RenderInit(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vPos) { m_mView = mView;  m_mProj = mProj; m_vCameraPos = vPos; }
private:
	//=================関数====================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.

	//==================変数====================//.
	CSprite*	m_pCSprite;		//スプライト.
	D3DXMATRIX	m_mView;		//ビュー行列.
	D3DXMATRIX	m_mProj;		//プロジェクション.
	D3DXVECTOR3 m_vCameraPos;	//カメラ座標.
	D3DXVECTOR3 m_vStartPos;	//初期座標.
	bool		m_bDispFlag;	//表示フラグ.
	float		m_fAcc;			//加速度.
};

#endif	//#ifndef CNEXT_SPEAK_CURSOR_H.