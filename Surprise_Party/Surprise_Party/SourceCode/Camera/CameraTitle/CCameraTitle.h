#ifndef CCAMERA_TITLE_H
#define CCAMERA_TITLE_H

#include "..\CCameraBase.h"

/*******************************************
*		�^�C�g���J�����N���X.
*************/
class CCameraTitle
	: public CCameraBase
{
public:
	CCameraTitle();
	~CCameraTitle();

	//=======================�֐�==========================//.
	void Update();		//�X�V�����֐�.
	
private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CCAMERA_TITLE_H.