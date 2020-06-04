#ifndef CCAMERA_BASE_H
#define CCAMERA_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"

/**************************************
*		�J�����N���X.
**************/
class CCamera
{
public:
	CCamera();
	~CCamera();

	//=======================�֐�==========================//.
	void Update();		//�X�V�����֐�.

private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=======================�ϐ�==========================//.
	CAMERA	m_Camera;	//�J�������.

};

#endif	//#ifndef CCAMERA_BASE_H.