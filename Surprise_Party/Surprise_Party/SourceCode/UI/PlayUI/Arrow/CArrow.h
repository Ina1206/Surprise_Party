#ifndef CARROW_H
#define CARROW_H

#include "..\CPlayUI.h"

/**********************************************
*			���N���X.
*****************/
class CArrow
	: public CPlayUI
{
public:
	CArrow();
	~CArrow();

	//===================�萔====================//.
	const D3DXVECTOR3	BASE_POS			= D3DXVECTOR3(600.0f, 500.0f, 0.0f);	//��{�ʒu.
	const int			ARROW_MAX			= 2;									//���ő�l.
	const int			LEFT_ARROW_NUM		= 0;									//�����ԍ�.
	const int			RIGHT_ARROW_NUM		= 1;									//�E���ԍ�.
	const float			ARROW_WIDTH			= 100.0f;								//���.
	const float			LEFT_ARROW_ROT_Y	= 2.9f;									//�����y�p�x.
	const float			ACCELERATION_SPEED	= 0.1f;									//�������x.
	const float			MOVE_DISTANCE_MAX	= 30.0f;								//�ړ������ő�l.
	const float			MOVE_DISTANCE_MIN	= 0.0f;									//�ړ������ŏ��l.
	const int			CHANGE_DIRECT		= -1;									//�����ύX���l.
	const int			MOVE_LEFT_DIRECT	= -1;									//���ړ�����.
	const int			MOVE_OUTSIDE_DIRECT = 1;									//�O���ֈړ�����.

	const unsigned int	USING_LEFT_FLAG		= (1 << 0);								//���̖��g�p�t���O.
	const unsigned int	USING_RIGHT_FLAG	= (1 << 1);								//�E�̖��g�p�t���O.

	//===================�֐�====================//.
	void Update();		//�X�V�����֐�.

	//=============���u�������֐�==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }
	void SetUsingArrowFlag(const unsigned int& Flag) { m_UsingArrowFlag = Flag; }

	//=============���擾�����֐�==============//.
	unsigned int GetUsingArrowFlag() const { return m_UsingArrowFlag; }

private:
	//===================�֐�====================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.
	void MoveArrow();		//���ړ������֐�.
	void SettingPos();		//���W�ݒ菈���֐�.			

	//===================�ϐ�====================//.
	D3DXVECTOR3		m_vCenterPos;		//���S���W.
	unsigned int	m_UsingArrowFlag;	//�g�p���̖��t���O.
	float			m_fDistance;		//�ړ�����.
	int				m_fDirect;			//����.
	float			m_fMoveSpeed;
};

#endif	//#ifndef CARROW_H.