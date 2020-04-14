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

	//===================�萔====================//.
	const D3DXVECTOR3	BASE_POS		= D3DXVECTOR3(100.0f, 400.0f, 0.0f);	//��{�ʒu.
	const int			LEFT_ARROW_NUM	= 0;									//�����ԍ�.

	//===================�֐�====================//.
	void Update();		//�X�V�����֐�.

private:
	//===================�֐�====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CARROW_H.