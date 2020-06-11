#ifndef CENDIGN_SWITCH_GHOST_H
#define CENDIGN_SWITCH_GHOST_H

#include "..\CEndingWorkGhostBase.h"

/*******************************************
*		�G���f�B���O�X�C�b�`�������N���X.
******************/
class CEndingSwitchGhost
	: public CEndingWorkGhostBase
{
public:
	CEndingSwitchGhost();
	~CEndingSwitchGhost();

	//====================�萔======================//.
	const float	SCALE		= 0.05f;	//�傫��.
	const float	PRE_POS_Y	= -10.0f;	//�����p�x���������l.
	
	const float	ACC_MAX		= 0.5f;		//�����x�ő�l.
	const float	ACC_SPEED	= 0.01f;	//�����x���Z���x.
	const float	GRAVITY		= 0.25f;	//�d��.

	const float	MOVE_SPEED	= 0.02f;	//�ړ����x.

	//====================�֐�======================//.
	void Update();				//�X�V�����֐�.
	void Render();				//�`�揈���֐�.

private:
	//====================�֐�======================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void ActRejoiceEmotion();	//��ъ���s�������֐�.
	void SettingInitDirect();	//���������ݒ菈���֐�.

	//====================�ϐ�======================//.
	int		m_MoveDirect;		//�ړ�����.
	bool	m_bSetDirect;		//������ݒ肵���t���O.


};

#endif	//#ifndef CENDIGN_SWITCH_GHOST_H.