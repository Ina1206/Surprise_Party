#ifndef CCAMERA_GHOST_SPEAK_STAGE_H
#define CCAMERA_GHOST_SPEAK_STAGE_H

#include "..\CCameraBase.h"

/**********************************************
*		���������b���X�e�[�W�̃J�����N���X.
**************/
class CCameraGhostSpeakStage
	: public CCameraBase
{
public:
	CCameraGhostSpeakStage();
	~CCameraGhostSpeakStage();

	//========================�֐�==========================//.
	void Update();		//�X�V�����֐�.
private:
	//========================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CCAMERA_GHOST_SPEAK_STAGE_H.