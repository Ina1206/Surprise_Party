#ifndef CBOY_ICON_H
#define CBOY_ICON_H

#include "..\CPeopleIcon.h"

/*************************************
*		�j�̎q�A�C�R���N���X.
******/
class CBoyIcon
	: public CPeopleIcon
{
public:
	CBoyIcon();
	~CBoyIcon();
	
private:
	//======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CBOY_ICON_H.