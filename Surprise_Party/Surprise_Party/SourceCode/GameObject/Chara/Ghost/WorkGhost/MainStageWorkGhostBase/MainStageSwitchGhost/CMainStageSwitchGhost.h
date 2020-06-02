#ifndef CMAIN_STAGE_SWITCH_GHOST_H
#define CMAIN_STAGE_SWITCH_GHOST_H

#include "..\CMainStageWorkGhostBase.h"

/**********************************************
*	���C���X�e�[�W�̃X�C�b�`�������������N���X.
*****************/
class CMainStageSwitchGhost
	: public CMainStageWorkGhostBase
{
public:
	CMainStageSwitchGhost();
	~CMainStageSwitchGhost();

	//=================�萔====================//.
	const unsigned int	PUSH_PREPARATION_FALG	= (1 << 0);								//���������t���O.
	const unsigned int	PUSH_BUTTON_FLAG		= (1 << 1);								//�{�^��������.
	const unsigned int	GO_TO_PUSH_FLAG			= (1 << 2);								//�����ɍs���t���O.
	const unsigned int	PUSH_END_FLAG			= (1 << 3);								//�����I���t���O.
	const unsigned int	PUSH_RETURN_FLAG		= (1 << 4);								//�����Ė߂�t���O.
	const unsigned int	MOVE_ROT_CHANGE_FLAG	= (1 << 5);								//�ړ����p�x�ύX�����֐�.
	const D3DXVECTOR3	GHOST_COLOR				= D3DXVECTOR3(202.0f, 255.0f, 250.0f);	//�������̐F.
	const float			SWITHC_GHOST_SCALE		= 0.1f;									//�X�C�b�`�������̑傫��.
	const float			POS_HEIGHT_MIN			= 0.2f;									//�����̍ŏ��l.
	const float			STANDERD_POS_HIGHT		= 3.5f;									//��{�̍���.
	const float			RETURN_ROTATION			= -1.35f;								//�߂������̊p�x.
	const float			DISTANCE_ADJUSTMENT		= 0.2f;									//�����̔�����.
	const float			MOVE_SPEED				= 0.1f;									//�ړ����x.
	const float			CHANGE_ACT_DISTANCE		= 3.0f;									//�s���ύX����.
	const float			GRAVITY					= 0.007f;								//�d��.
	const int			DOWN_DIRECTION			= -1;									//���̕���.
	const int			CHANGE_DIRECTION		= -1;									//�����ύX.
	const float			PUSH_END_ROT_SPEED		= 0.1f;									//�����I����ĉ�]���x.
	const D3DXVECTOR3	SKY_DIRECT				= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�����.
	const float			CHANGE_UP_DOWN_FLAG_H	= 0.7f;									//�㉺�ړ��t���O�ύX����.

	//=================�֐�====================//.
	void Update();							//�X�V�����֐�.
	void Render();							//�`�揈���֐�.
private:
	//=================�֐�====================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void SurpriseAct();						//�������s�������֐�.
	void ChangeObjectUpDown();				//�㉺�ړ��ύX�����֐�.
	void ReturnMove();						//�߂�ړ������֐�.
	void PushPreparation();					//�������������֐�.
	void PushButton();						//���������֐�.
	void PushEnd();							//�����I����������֐�.
	void MoveRotation();					//�ړ��p�x�����֐�.

	//=================�ϐ�====================//.
	unsigned int	m_PushSwitchActFlag;	//�{�^���������Ƃ��̃t���O.
	float			m_fGravity;				//�d��.
	int				m_UpDownDirection;		//���������.
	D3DXVECTOR3		m_vPointDistance;		//2�_�Ԃ̋���.
	D3DXVECTOR3		m_vUnitVector;			//�P�ʃx�N�g��.
	D3DXVECTOR3		m_vOldPos;				//�O��̍��W.
	D3DXMATRIX		m_mPoint;				
	bool			m_bUseRotFlag;			//�p�x�g�p�t���O.
};

#endif	//#ifndef CMAIN_STAGE_SWITCH_GHOST_H.