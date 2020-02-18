#ifndef CSWITCH_BASE_H
#define CSWITCH_BASE_H

#include "..\CMoveObjectBase.h"

/****************************************
*		スイッチ基底クラス.
******/
class CSwitchBase
	: public CMoveObjectBase
{
public:
	CSwitchBase();
	virtual ~CSwitchBase();

	//==========================定数================================//.
	const float	SWITCH_DEPTH_POS = 2.9f;	//スイッチの奥行の座標.
	
private:

};

#endif	//#ifndef CSWITCH_BASE_H.