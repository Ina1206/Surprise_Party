#ifndef CENDING_DISP_GHOST_H
#define CENDING_DISP_GHOST_H

#include "..\CEndingWorkGhostBase.h"

/******************************************
*		�G���f�B���O�̌���邨�����N���X.
**************/
class CEndingDispGhost
	: public CEndingWorkGhostBase
{
public:
	CEndingDispGhost();
	~CEndingDispGhost();

	//======================�萔=======================//.
	const float	SCALE			= 0.07f;	//�傫��.
	const float PRE_POS_Y		= -20.0f;	//�ŏ��̒��������W.

	const float	ACC_MAX			= 0.25f;	//�����ő�l.
	const float	ACC_SPEED		= 0.005f;	//�����x���Z���x.
	const float GRAVITY			= 0.1f;		//�d��.
	const float	ROTATION_SPEED	= 0.02f;	//��]���x.

	//======================�֐�=======================//.
	void Update();				//�X�V�����֐�.
	void Render();				//�`�揈���֐�.

private:
	//======================�֐�=======================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void ActRejoiceEmotion();	//��ъ���s�������֐�.
	void Rotation();			//��]�����֐�.
	void ActHaveTrouble();		//����������s�������֐�.

	//======================�ϐ�=======================//.
	int			m_RotationDirect;		//��]����.
	bool		m_bChangeRotationDirect;//��]�����ύX�t���O.
	bool		m_bStartHaveTrouble;	//����̊J�n�t���O.
};

#endif	//#ifndef CENDING_DISP_GHOST_H.