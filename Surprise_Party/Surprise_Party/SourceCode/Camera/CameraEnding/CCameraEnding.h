#ifndef CCAMERA_ENDING_H
#define CCAMERA_ENDING_H

#include "..\CCameraBase.h"

/******************************************
*		�G���f�B���O�J�����N���X.
***************/
class CCameraEnding
	: public CCameraBase
{
public:
	CCameraEnding();
	~CCameraEnding();

	//===========================�֐�===============================//.
	void Update();	//�X�V�����֐�.

private:
	//===========================�֐�===============================//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.


};

#endif	//#ifndef CCAMERA_ENDING_H.