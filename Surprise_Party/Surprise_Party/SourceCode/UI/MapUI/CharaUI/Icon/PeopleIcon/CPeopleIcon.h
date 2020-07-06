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
	const D3DXVECTOR3	START_POS	= D3DXVECTOR3(0.0f, 95.0f, 0.0f);	//�����̍��W.
	const float			ACC_SPEED	= 0.1f;								//�����x���x.
	const float			GRAVITY		= 2.0f;								//�d��.

	//=============���u�������֐�===============//.
	//�����t���O.
	void SetSurpriseFlag(const bool& bFlag) { m_bSurpriseFlag = bFlag; }

	//===================�֐�=====================//.
	void UpDate();			//�X�V�����֐�.
	void SurpriseAct();		//�����s�������֐�.

protected:
	//===================�ϐ�=====================//.
	bool m_bSurpriseFlag;	//�����t���O.

private:
	//===================�ϐ�=====================//.
	float		m_fAcc;		//�����x.
};

#endif	//#ifndef CPEOPLE_ICON_H.