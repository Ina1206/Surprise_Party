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

	//=======================�萔==========================//.
	const unsigned int MOVE_FLAG		= (1 << 0);		//�ړ��t���O.
	const unsigned int STOP_FLAG		= (1 << 1);		//��~�t���O.
	const unsigned int MOVE_FINISH_FLAG = (1 << 2);		//�ړ��I���t���O.
	const unsigned int PEOPLE_LOOK_FLAG = (1 << 3);		//�l������t���O.
	const unsigned int GHOST_LOOK_FLAG	= (1 << 4);		//������������t���O.

	//=======================�֐�==========================//.
	virtual void Update() = 0;		//�X�V�����֐�.
	void AcquisitionDifference();	//�����擾�����֐�.

	//=================���擾�����֐�====================//.
	//�J�������W.
	D3DXVECTOR3 GetPos() const { return m_Camera.vPos; }
	//�J���������_.
	D3DXVECTOR3 GetLook() const { return m_Camera.vLook; }
	//�J�����ړ��I��.	
	//bool GetFinishMoveCamera() const { return m_bFinishMoveCamera; }
	//�ړ��t���O.
	unsigned int GetMoveFlag() const { return m_MoveFlag; }


	//=================���u�������֐�====================//.
	//�ړ��t���O.
	void SetMoveFlag(const unsigned int& Flag) { m_MoveFlag = Flag; }
	//����̍��W.
	void SetTargetPos(const D3DXVECTOR3& vPos) { m_vTargetPos = vPos; }

protected:
	//=======================�֐�==========================//.
	virtual void Init() = 0;		//�����������֐�.
	virtual void Release() = 0;		//��������֐�.

	//=======================�ϐ�==========================//.
	CAMERA	m_Camera;				//�J�������.
	//bool	m_bFinishMoveCamera;	//�J�����ړ��I��.
	unsigned int m_MoveFlag;		//�ړ��t���O.
	D3DXVECTOR3		m_vTargetPos;	//����̍��W.
	CAMERA			m_OldCamera;	//�����p�ϐ�.
};

#endif	//#ifndef CCAMERA_BASE_H.