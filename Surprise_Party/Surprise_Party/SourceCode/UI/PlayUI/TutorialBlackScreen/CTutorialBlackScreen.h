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
	const float HALF_SCREEN_SIZE		= WND_W / 2.0f;	//スクリーンの半分サイズ.
	const float DESCRIPTION_MAP_HEIGHT	= 150.0f;		//初期マップ説明高さ.
	const float	DESCRIPTION_UI_HEIGHT	= -90.0f;		//ゲームメインUIの表示高さ.
	const float	SCALE_BASE				= 1.2f;			//基本大きさ.
	const float	NORMAL_POS_X			= 0.0f;			//通常x座標.
	const float	REVERSE_POS_X			= 1300.0f;		//反転x座標.
	const float	REVERSE_ROT_Y			= 3.1f;			//反転y軸角度.
	const float	FADE_SPEED				= 0.05f;		//フェード速度.

	const unsigned int FADE_IN_FLAG		= (1 << 0);	//フェードインフラグ.
	const unsigned int FADE_OUT_FLAG	= (1 << 1);	//フェードアウトフラグ.

	//====================関数======================//.
	void Update();		//更新処理関数.

	//==============情報置換処理関数================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }
	void SetDescriptionFlag(const bool& Flag) { m_bDescriptionFlag = Flag; }

	//==============情報取得処理関数================//.
	bool GetDispFlag() const { return m_bDispFlag; }

private:
	//====================関数======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void SettingPos();	//座標設定処理関数.
	void FadeDecision();//フェード判定処理関数.
	void FadeIn();		//フェードイン処理関数.
	void FadeOut();		//フェードアウト処理関数.

	//====================変数======================//.
	D3DXVECTOR3		m_vCenterPos;			//中心座標.
	D3DXVECTOR3		m_vOldCenterPos;		//前回の中心座標.
	bool			m_bDispFlag;			//表示フラグ.
	unsigned int	m_FadeFlag;				//フェードフラグ.
	bool			m_bDescriptionFlag;		//説明フラグ.
	bool			m_bOldDescriptionFlag;	//前回の説明フラグ.
};

#endif	//#ifndef CTUTORIAL_BLACK_SCREEN_H.