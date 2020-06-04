#ifndef CCAMERA_BASE_H
#define CCAMERA_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"

/**************************************
*		�J�������N���X.
**************/
class CCameraBase
{
public:
	CCameraBase();
	virtual ~CCameraBase();

	//=======================�֐�==========================//.
	virtual void Update() = 0;		//�X�V�����֐�.

	//=================���擾�����֐�====================//.
	//�J�������W.
	D3DXVECTOR3 GetCameraPos() const { return m_Camera.vPos; }

protected:
	//=======================�֐�==========================//.
	virtual void Init() = 0;		//�����������֐�.
	virtual void Release() = 0;		//��������֐�.

	//=======================�ϐ�==========================//.
	CAMERA	m_Camera;	//�J�������.

};

#endif	//#ifndef CCAMERA_BASE_H.