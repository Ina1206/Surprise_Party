#ifndef CPEOPLE_ICON_H
#define CPEOPLE_ICON_H

#include "..\CIcon.h"
#include "..\..\SpriteUIEffect\ShockingEffect\CShockingEffect.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*********************************
*		人のアイコンクラス.
*****/
class CPeopleIcon
	: public CIcon
{
public:
	CPeopleIcon();
	virtual ~CPeopleIcon();

	//===================定数=====================//.
	const D3DXVECTOR3	START_POS	= D3DXVECTOR3(0.0f, 95.0f, 0.0f);	//初期の座標.
	const float			ACC_SPEED	= 0.1f;								//加速度速度.
	const float			GRAVITY		= 2.0f;								//重力.

	//=============情報置換処理関数===============//.
	//驚くフラグ.
	void SetSurpriseFlag(const bool& bFlag) { m_bSurpriseFlag = bFlag; }
	//叫び声可能フラグ.
	void SetShoutPossibleFlag(const bool& bFlag) { m_bShoutPossibleFlag = bFlag; }

	//===================関数=====================//.
	void UpDate();												//更新処理関数.
	void RenderEffect();										//エフェクト描画処理関数.

protected:
	//===================関数=====================//.
	void SurpriseAct();											//驚き行動処理関数.
	bool DecisionSurpriseJump();								//驚きジャンプ判定処理関数.

	//===================変数=====================//.
	bool m_bSurpriseFlag;										//驚きフラグ.
	bool m_bShoutWoman;											//女性の叫び声フラグ.

private:
	//===================変数=====================//.
	float								m_fAcc;					//加速度.

	std::unique_ptr<CShockingEffect>	m_pCShockingEffect;		//衝撃クラス.
	bool								m_bJumpFlag;			//ジャンプフラグ.
	bool								m_bShoutFlag;			//叫び声フラグ.
	bool								m_bShoutPossibleFlag;	//叫び声可能フラグ.
	CPlaySoundManager*					m_pCSoundPlayManager;	//音再生管理クラス.
};

#endif	//#ifndef CPEOPLE_ICON_H.