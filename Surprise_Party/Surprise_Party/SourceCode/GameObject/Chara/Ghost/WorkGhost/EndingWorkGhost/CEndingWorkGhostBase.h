#ifndef CENDING_WORK_GHOST_BASE_H
#define CENDING_WORK_GHOST_BASE_H

#include "..\CWorkGhostBase.h"

/**************************************************
*		�G���f�B���O�������������N���X.
********************/
class CEndingWorkGhostBase
	: public CWorkGhostBase
{
public:
	CEndingWorkGhostBase();
	virtual ~CEndingWorkGhostBase();

	//========================�萔=============================//.
	const unsigned int	FACE_OUTSIDE		= (1 << 0);							//�O��������.
	const unsigned int	MOVE_OUTSIDE		= (1 << 1);							//�O�����ړ�.

	const D3DXVECTOR3	VECTOR_AXIS_Z		= D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//z��.
	const float			LOOK_BACK_SPEED		= 0.05f;							//�U��Ԃ鑬�x.
	const float			LOOK_BACK_ROT_MAX	= 180.0f;							//�U��Ԃ�p�x�ő�l.

	const float			MOVE_SPEED			= 0.01f;							//�ړ����x.

	const float			MOVE_NOTE_ANGLE		= 30.0f;							//�����ړ��p�x.
	const float			PLAY_DISTANCE_MAX	= 6.0f;								//�Đ������ő�.

	const float			MOVE_DISTANCE_MAX	= 8.0f;								//�ړ������ő�l.
	const float			SWING_SPEED			= 0.05f;							//�h��鑬�x.
	const float			SWING_ROTATION_MAX	= 90.0f;							//�h���p�x�ő�l.

	const int			CHANGE_DIRECT		= -1;								//�����ύX.
	
protected:
	//========================�֐�=============================//.
	void Jump();				//�W�����v�����֐�.
	void ChangeEffect();		//�G�t�F�N�g�ύX�����֐�.
	void ActGoodFeeling();		//���@�����̍s�������֐�.
	void PlayEffectManager();	//�G�t�F�N�g�Đ��Ǘ������֐�.

	//========================�ϐ�=============================//.
	std::unique_ptr<CSpriteEffectBase>	m_pCSpriteEffect;		//�X�v���C�g�G�t�F�N�g.
	float								m_fAcc;					//�����x.
	float								m_fAccSpeed;			//�����x���Z���x.
	float								m_fAccMax;				//�����x�ő�l.
	float								m_fGravity;				//�d��.
	D3DXVECTOR3							m_vChangeBeforeRotation;//�ύX�O�̊p�x.
private:
	//========================�֐�=============================//.
	void MoveToOutside();		//�O���Ɉړ����鏈���֐�.
	void FaceOutside();			//�O�������������֐�.

	//========================�ϐ�=============================//.
	int									m_OldEmotionNum;		//�����p�̊���ԍ�.
	unsigned int						m_MoveToOuterFlag;		//�O�����ړ�����t���O.
};

#endif	//#ifndef CENDING_WORK_GHOST_BASE_H.