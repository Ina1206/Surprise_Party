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

	//====================�֐�======================//.
	void Update();		//�X�V�����֐�.

	//==============���u�������֐�================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

private:
	//====================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void SettingPos();	//���W�ݒ菈���֐�.

	//====================�ϐ�======================//.
	D3DXVECTOR3 m_vCenterPos;	//���S���W.
	bool		m_bDispFlag;	//�\���t���O.
};

#endif	//#ifndef CTUTORIAL_BLACK_SCREEN_H.