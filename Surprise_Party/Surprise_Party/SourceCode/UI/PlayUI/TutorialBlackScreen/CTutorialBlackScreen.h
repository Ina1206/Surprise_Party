#ifndef CTUTORIAL_BLACK_SCREEN_H
#define CTUTORIAL_BLACK_SCREEN_H

#include "..\CPlayUI.h"

/******************************************
*		�`���[�g���A�����̍����.
**************/
class CTutorialBlackScreen
	: public CPlayUI
{
public:
	CTutorialBlackScreen();
	~CTutorialBlackScreen();

	//====================�萔======================//.
	const float HALF_SCREEN_SIZE = WND_W / 2.0f;	//�X�N���[���̔����T�C�Y.

	const unsigned int FADE_IN_FLAG		= (1 << 0);	//�t�F�[�h�C���t���O.
	const unsigned int FADE_OUT_FLAG	= (1 << 1);	//�t�F�[�h�A�E�g�t���O.

	//====================�֐�======================//.
	void Update();		//�X�V�����֐�.

	//==============���u�������֐�================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

	

private:
	//====================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void SettingPos();	//���W�ݒ菈���֐�.
	void FadeDecision();//�t�F�[�h���菈���֐�.
	void FadeIn();		//�t�F�[�h�C�������֐�.
	void FadeOut();		//�t�F�[�h�A�E�g�����֐�.

	//====================�ϐ�======================//.
	D3DXVECTOR3		m_vCenterPos;			//���S���W.
	D3DXVECTOR3		m_vOldCenterPos;		//�O��̒��S���W.
	bool			m_bDispFlag;			//�\���t���O.
	unsigned int	m_FadeFlag;				//�t�F�[�h�t���O.
};

#endif	//#ifndef CTUTORIAL_BLACK_SCREEN_H.