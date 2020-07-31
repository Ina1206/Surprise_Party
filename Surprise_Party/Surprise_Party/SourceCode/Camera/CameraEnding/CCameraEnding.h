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
	
	const D3DXVECTOR3	INIT_CAMERA_POS			= D3DXVECTOR3(7.3f, 3.0f, -19.1f);	//�J�����������W.
	const D3DXVECTOR3	INIT_CAMERA_LOOK		= D3DXVECTOR3(6.0f, 2.2f, 5.0f);	//�J�������������_.
	const D3DXVECTOR3	INTERMEDIATE_POINT_POS	= D3DXVECTOR3(3.7f, 19.4f, 10.9f);	//���Ԓn�_���W.
	const D3DXVECTOR3	INTERMEDIATE_POINT_LOOK	= D3DXVECTOR3(6.0f, -20.0f, 1.4f);	//���Ԓn�_�����_.

	const D3DXVECTOR3	FINISH_CMAERA_POS		= D3DXVECTOR3(5.1f, 1.6f, 8.0f);	//�ŏI�J�����ʒu���W.

	const D3DXVECTOR3	LOOK_AT_GHOSTS_POS		= D3DXVECTOR3(5.8f, 2.3f, -2.3f);	//�������B������ʒu���W.
	const D3DXVECTOR3	LOOK_AT_GHOSTS_LOOK		= D3DXVECTOR3(5.2f, 2.7f, 5.1f);	//�������B�����钍���_���W.

	const float			MOVE_SPEED				= 0.1f;								//�ړ����x.
	const float			MOVE_DOWN_SPEED			= 0.2f;								//���~�ړ����x.
	const float			ANGLE_MIN				= 110.0f;							//�p�x�ŏ��l.
	const float			ANGLE_MAX				= 281.0f;							//�p�x�ő�l.
	//===========================�֐�===============================//.
	void Update();											//�X�V�����֐�.

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