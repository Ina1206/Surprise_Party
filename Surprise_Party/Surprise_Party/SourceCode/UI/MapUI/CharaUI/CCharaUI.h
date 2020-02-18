#ifndef CCHARA_UI_H
#define CCHARA_UI_H

#include "..\CMapUI.h"

/**********************************
*		キャラクターUIクラス.
*******/
class CCharaUI
	: public CMapUI
{
public:
	CCharaUI();
	virtual ~CCharaUI();

	//====================定数=========================//.
	const float		MAP_DISTANCE_MAX = 1280.0f;							//マップの最大値.

	//====================関数=========================//.
	virtual void UpDate() = 0;

	//===========情報置換処理関数==============//.
	//キャラクタの座標取得処理関数.
	void SetCharaPos(const D3DXVECTOR3& vPos) { m_vCharaPos = vPos; }
	//ステージ最大数取得.
	void SetStageMax(const float& fStageMax) { m_fStageMax = fStageMax; }

protected:
	//====================関数==========================//.
	void GameMapConversion();			//ゲーム内からマップ内に座標変換処理関数.

	//=================変数====================//.
	D3DXVECTOR3		m_vCharaPos;		//キャラクタの座標.
	float			m_fStageMax;		//ステージ最大値.

};

#endif	//#ifndef CCHARA_UI_H.