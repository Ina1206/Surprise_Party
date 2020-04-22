#ifndef CTUTORIAL_BLACK_SCREEN_H
#define CTUTORIAL_BLACK_SCREEN_H

#include "..\CPlayUI.h"

/******************************************
*		チュートリアル時の黒画面.
**************/
class CTutorialBlackScreen
	: public CPlayUI
{
public:
	CTutorialBlackScreen();
	~CTutorialBlackScreen();

	//====================定数======================//.
	const float HALF_SCREEN_SIZE = WND_W / 2.0f;	//スクリーンの半分サイズ.

	//====================関数======================//.
	void Update();		//更新処理関数.

	//==============情報置換処理関数================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

private:
	//====================関数======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void SettingPos();	//座標設定処理関数.

	//====================変数======================//.
	D3DXVECTOR3 m_vCenterPos;	//中心座標.
	bool		m_bDispFlag;	//表示フラグ.
};

#endif	//#ifndef CTUTORIAL_BLACK_SCREEN_H.