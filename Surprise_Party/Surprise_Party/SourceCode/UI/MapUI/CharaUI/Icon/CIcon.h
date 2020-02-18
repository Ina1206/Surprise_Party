#ifndef CICON_H
#define CICON_H

#include "..\CCharaUI.h"

/**********************************
*		アイコンクラス.
*******/
class CIcon
	: public CCharaUI
{
public:
	CIcon();
	virtual ~CIcon();

	//================定数====================//.
	const float	SELECTING_SCALE		= 1.1f;		//選択中の大きさ.
	const float SELECTION_ALPHA		= 1.0f;		//選択中の透過値.
	const float BASIC_SCALE			= 1.0f;		//基本的な大きさ.
	const float BASIC_ALPHA			= 0.75f;	//基本的な透過値.

	//===========情報置換処理関数=============//.
	//UIの色置換処理関数.
	void SetColor(const D3DXVECTOR3& vColor) { m_vColor = vColor; }
	//選択フラグ.
	void SetSelectingFlag() { m_bSelectingFlag = true; }
	//決定フラグ.
	void SetSelectedFlag(const bool& flag) { m_bSelectedFlag = flag; }
protected:
	//================関数====================//.
	void SelectingDisplay();		//選択中の表示処理関数.

	//================変数====================//.
	bool	m_bSelectingFlag;		//選択中フラグ.
	bool	m_bSelectedFlag;		//選ばれたフラグ.

};

#endif	//#ifndef CICON_H.