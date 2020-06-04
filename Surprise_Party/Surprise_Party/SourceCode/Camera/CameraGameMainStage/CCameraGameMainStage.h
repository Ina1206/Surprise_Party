#ifndef CCAMERA_GAMEMAIN_STAGE_H
#define CCAMERA_GAMEMAIN_STAGE_H

#include "..\CCameraBase.h"

/**********************************************
*		�Q�[�����C���X�e�[�W�̃J�����N���X.
**********************/
class CCameraGameMainStage
	: public CCameraBase
{
public:
	CCameraGameMainStage();
	~CCameraGameMainStage();

	//==========================�萔=============================//.
	const D3DXVECTOR3	CAMERA_START_POS		= D3DXVECTOR3(11.9f, 7.5f, -19.9f);	//�J�n���̍��W.
	const D3DXVECTOR3	CAMERA_START_LOOK		= D3DXVECTOR3(11.9f, 5.3f, 4.0f);	//�J�n���̒����_���W.
	const D3DXVECTOR3	CAMERA_PEOPLE_SEE_POS	= D3DXVECTOR3(8.8f, 2.0f, -7.0f);	//�J�������l��������W.
	const D3DXVECTOR3	CAMERA_PEOPLE_SEE_LOOK	= D3DXVECTOR3(-4.3f, 4.3f, 0.0f);	//�J�������l�����钍���_.

	//==========================�֐�=============================//.
	void Update();		//�X�V�����֐�.

private:
	//==========================�֐�=============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};


#endif	//#ifndef CCAMERA_GAMEMAIN_STAGE_H.