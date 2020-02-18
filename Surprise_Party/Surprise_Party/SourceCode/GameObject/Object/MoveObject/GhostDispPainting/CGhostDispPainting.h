#ifndef CGHOST_DISP_PAINTING_H
#define CGHOST_DISP_PAINTING_H

#include "..\CMoveObjectBase.h"

/***********************************************
*		�������������G��N���X.
***************/
class CGhostDispPainting
	: public CMoveObjectBase
{
public:
	CGhostDispPainting();
	~CGhostDispPainting();

	//================�萔===================//.
	const float PAINTING_ALPHA_MIN	= 0.8f;		//�G��̓��ߒl�ŏ��l.
	const float ALPHA_DISTANCE		= 3.0f;		//�������ɂȂ鋗��.
	const float	PAINTING_UP_MAX		= 5.0f;		//�G��オ����.
	
	//================�֐�===================//.
	void UpDate();		//�X�V�����֐�.

private:
	//================�֐�===================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void ObjAlpha();	//�I�u�W�F�N�g���ߏ����֐�.


};

#endif	//#ifndef CGHOST_DISP_PAINTING_H.