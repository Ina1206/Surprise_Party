#ifndef CGAME_WORLD_UI_H
#define CGAME_WORLD_UI_H

#include "..\CUI.h"

/***************************************
*		ゲーム内でのUIクラス.
************/
class CGameWorldUI
	: public CUI
{
public:
	CGameWorldUI();
	virtual ~CGameWorldUI();

	//======================関数============================//.
	void RenderSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//描画設定処理関数.
	void Render();																							//描画処理関数.

	//================情報置換処理関数======================//.
	//キャラクタの座標.
	void SetCharacterPos(const D3DXVECTOR3& vCharaPos) { m_vCharacterPos = vCharaPos; }

protected:
	//======================変数============================//.
	CSprite*	m_pCSprite;			//スプライトクラス.
	D3DXMATRIX	m_mView;			//ビュー行列.
	D3DXMATRIX	m_mProj;			//プロジェクション行列.
	D3DXVECTOR3	m_vCameraPos;		//カメラ座標.
	D3DXVECTOR3	m_vCharacterPos;	//キャラクタ座標.
	D3DXVECTOR3 m_vColor;			//色.
	D3DXVECTOR2	m_vPattarn;			//パターン.
	bool		m_bDepth;			//デプス.

};

#endif //#ifndef CGAME_WORLD_UI_H.