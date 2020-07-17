#ifndef CMAIN_STAGE_DISP_GHOST_H
#define CMAIN_STAGE_DISP_GHOST_H

#include "..\CMainStageWorkGhostBase.h"

/***********************************************
*		���C���X�e�[�W�̌���邨�����N���X.
******************/
class CMainStageDispGhost
	: public CMainStageWorkGhostBase
{
public:
	CMainStageDispGhost();
	~CMainStageDispGhost();

	//===============�萔===================//.
	const unsigned int	APPEAR_FLAG					= (1 << 0);	//�����t���O.
	const unsigned int  APPEAR_SURPRISE_FLAG		= (1 << 1);	//����ċ������t���O.
	const unsigned int	RETURN_FLAG					= (1 << 2);	//�߂�t���O.
	const float			WAIT_SURPRISE_ANIM_SPEED	= 0.0f;		//�������҂��̃A�j���[�V�������x.
	const float			SURPRISE_ANIM_SPEED			= 0.008f;	//�������Ƃ��̃A�j���[�V�������x.
	const double		RETURN_ANIM_TIME			= 1.1;		//�߂�A�j���[�V��������.
	const double		WAIT_ANIM_TIME				= 1.5;		//�ҋ@�A�j���[�V��������.
	const float			APPEAR_SPEED				= 0.15f;	//����鑬�x.
	const float			APPEAR_POS_MAX				= -0.3f;	//�����ꏊ�̍ő�l.
	const float			RETURN_SPEED				= 0.2f;		//�߂鑬�x.
	const float			RETURN_POS_MAX				= 3.5f;		//�߂�ꏊ�̍ő�l.
	const float			GHOST_POS_Z					= 3.5f;		//�������̂������W.
	const float			OBJECT_DOWN_POS				= 3.4f;		//�I�u�W�F�N�g���Ƃ��������̍��W.
	const float			HIGHT_MIN					= 0.0f;		//�����̍ŏ��l.
	const float			EFFECT_DISP_HIGHT			= 4.5f;		//�G�t�F�N�g�`�捂��.

	//===============�֐�===================//.
	void Update();									//�X�V�����֐�.
	void Render();									//�`�揈���֐�.

private:
	//===============�֐�===================//.
	void Init();									//�����������֐�.
	void Release();									//��������֐�.
	void SurpriseAct();								//�������s�������֐�.
	void ChangeObjectUpDown();						//�㉺�ړ��ύX�����֐�.
	void ReturnMove();								//�߂�ړ������֐�.

	//===============�ϐ�===================//.
	float						m_fAnimSpeed;		//�A�j���[�V�������x.
	unsigned int				m_SurpriseActFlag;	//�������s���t���O.
	double						m_dAnimTime;		//�A�j���[�V��������.
};

#endif	//#ifndef CMAIN_STAGE_DISP_GHOST_H.	