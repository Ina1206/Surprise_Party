#ifndef CSWITCH_BASE_H
#define CSWITCH_BASE_H

#include "..\CMoveObjectBase.h"

/****************************************
*		�X�C�b�`���N���X.
******/
class CSwitchBase
	: public CMoveObjectBase
{
public:
	CSwitchBase();
	virtual ~CSwitchBase();

	//==========================�萔================================//.
	const float	SWITCH_DEPTH_POS = 2.9f;	//�X�C�b�`�̉��s�̍��W.
	
private:

};

#endif	//#ifndef CSWITCH_BASE_H.