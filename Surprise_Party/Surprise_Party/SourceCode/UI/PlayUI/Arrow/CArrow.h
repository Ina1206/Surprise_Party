#ifndef CARROW_H
#define CARROW_H

#include "..\CPlayUI.h"

/**********************************************
*			���N���X.
*****************/
class CArrow
	: public CPlayUI
{
public:
	CArrow();
	~CArrow();

	//===================�֐�====================//.
	void UpDate();		//�X�V�����֐�.

private:
	//===================�֐�====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CARROW_H.