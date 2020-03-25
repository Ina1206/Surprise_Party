#ifndef CGHOST_SPEAK_STAGE_H
#define CGHOST_SPEAK_STAGE_H

#include "..\StageBase\CStageBase.h"
#include "..\..\..\FileLoad\FileResource\CFileResource.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\UI\SpeakUI\SpeakBigGhost\CSpeakBigGhost.h"

/*****************************************
*	�������Ƃ̉�b�X�e�[�W�N���X.
*********/
class CGhostSpeakStage
	: public CStageBase
{
public:
	CGhostSpeakStage();
	CGhostSpeakStage(int stagenum);
	~CGhostSpeakStage();

	//========================�萔=============================//.
	const D3DXVECTOR3	INIT_CAMERA_POS				= D3DXVECTOR3(5.0f, 2.5f, -3.5f);		//�J���������ʒu.
	const D3DXVECTOR3	INIT_CAMERA_LOOK			= D3DXVECTOR3(5.0f, 2.5f, 5.0f);		//�J�������������_.
	const D3DXVECTOR3	SPEAK_START_POS				= D3DXVECTOR3(6.0f, 2.7f, 1.3f);		//��b�J�n���̃J�������W.
	const D3DXVECTOR3	SPEAK_START_LOOK			= D3DXVECTOR3(6.0f, 2.2f, 5.0f);		//��b�J�n���̃J���������_.
	const D3DXVECTOR3	CAMERA_POS_DISTANCE			= SPEAK_START_POS - INIT_CAMERA_POS;	//�J�����̍��W����.
	const D3DXVECTOR3	CAMERA_LOOK_DISTANCE		= SPEAK_START_LOOK - INIT_CAMERA_LOOK;	//�J�����̒����_����.
	const int			GET_CLOSER_CAMERA_DIRECT	= 1;									//�J�������ڋ߂������.
	const int			FAR_AWAY_CAMERA_DIRECT		= -1;									//�J���������̂�����.
	const float			CAMER_MOVE_SPEED			= 0.02f;								//�J�����ړ����x.

	//========================�֐�=============================//.
	void UpDate(const bool& ControlFlag);		//�X�V�����֐�.
	void Render();								//�`�揈���֐�.
	void Control();								//���쏈���֐�.

private:
	//========================�֐�=============================//.
	void Init();								//�����������֐�.
	void Release();								//��������֐�.
	void CameraMove();							//�J�����ړ������֐�.
	void DecisionFinishSpeak();					//��b�I�����菈���֐�.

	//========================�֐�=============================//.
	CFontResource*					m_pCFontResource;
	std::vector<std::string>		changestr;
	std::unique_ptr<CFloor>			m_pCFloor;				//��.
	std::unique_ptr<CBigGhost>		m_pCBigGhost;			//�傫��������.
	std::unique_ptr<CSpeakBigGhost>	m_pCSpeakBigGhost;		//�傫����������b�N���X.

	int								m_MoveCameraDirection;	//�J�����ړ�����.
	
};

#endif //#ifndef CGHOST_SPEAK_STAGE_H.