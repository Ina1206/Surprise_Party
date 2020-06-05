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

	//===========================�萔===============================//.
	const unsigned int	APPROCH_GHOST_HEAD_FLAG	= (1 << 0);							//�������̓��ɐڋ߃t���O.
	const unsigned int	APPROCH_SMARTPHONE_FLAG = (1 << 1);							//�X�}�[�g�t�H���̐ڋ߃t���O.
	
	const D3DXVECTOR3	INIT_CAMERA_POS			= D3DXVECTOR3(23.9f, 5.0f, -3.5f);	//�J�����������W.
	const D3DXVECTOR3	INIT_CAMERA_LOOK		= D3DXVECTOR3(5.0f, 2.5f, 5.0f);	//�J�������������_.
	const D3DXVECTOR3	INTERMEDIATE_POINT_POS	= D3DXVECTOR3(5.1f, 21.8f, 3.9f);	//���Ԓn�_���W.
	const D3DXVECTOR3	INTERMEDIATE_POINT_LOOK	= D3DXVECTOR3(5.7f, -5.0, 5.0f);	//���Ԓn�_�����_.

	const float			MOVE_SPEED				= 0.15f;								//�ړ����x.
	const float			ANGLE_MIN				= -123.0f;							//�p�x�ŏ��l.
	const float			ANGLE_MAX				= -18.0f;							//�p�x�ő�l.
	//===========================�֐�===============================//.
	void Update();	//�X�V�����֐�.

private:
	//===========================�֐�===============================//.
	void Init();											//�����������֐�.
	void Release();											//��������֐�.
	void MoveToIntermediatePoint();							//���Ԓn�_�܂ňړ������֐�.
	void MoveUp();											//�㏸�ړ������֐�.
	void MoveApproching();									//�ڋ߈ړ������֐�.
	void RotateSurrunding(	const float& fCriteriaRange,
							const float& fCenterRange);		//���ӂ���鏈���֐�.
	void MoveLook();										//�����_�ړ������֐�.
	void MoveDown();										//���~�ړ������֐�.

	//===========================�ϐ�===============================//.
	float			m_fAngle;				//�p�x.
	float			m_fApprochDistance;		//�߂Â�����.
	unsigned int	m_ApprochFlag;			//�ڋ߃t���O.

};

#endif	//#ifndef CCAMERA_ENDING_H.