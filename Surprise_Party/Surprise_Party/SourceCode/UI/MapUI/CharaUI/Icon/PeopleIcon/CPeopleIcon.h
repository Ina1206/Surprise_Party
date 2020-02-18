#ifndef CPEOPLE_ICON_H
#define CPEOPLE_ICON_H

#include "..\CIcon.h"

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
	const D3DXVECTOR3	START_POS			= D3DXVECTOR3(0.0f, 95.0f, 0.0f);	//初期の座標.

	//===================関数=====================//.
	void UpDate();		//更新処理関数.
protected:
};

#endif	//#ifndef CPEOPLE_ICON_H.