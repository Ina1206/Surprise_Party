#ifndef CPEOPLE_ICON_H
#define CPEOPLE_ICON_H

#include "..\CIcon.h"

/*********************************
*		�l�̃A�C�R���N���X.
*****/
class CPeopleIcon
	: public CIcon
{
public:
	CPeopleIcon();
	virtual ~CPeopleIcon();

	//===================�萔=====================//.
	const D3DXVECTOR3	START_POS			= D3DXVECTOR3(0.0f, 95.0f, 0.0f);	//�����̍��W.

	//===================�֐�=====================//.
	void UpDate();		//�X�V�����֐�.
protected:
};

#endif	//#ifndef CPEOPLE_ICON_H.