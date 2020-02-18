#ifndef CGHOST_SPEAK_STAGE_H
#define CGHOST_SPEAK_STAGE_H

#include "..\StageBase\CStageBase.h"
#include "..\..\..\FileLoad\FileResource\CFileResource.h"

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

	//========================�֐�=============================//.
	void UpDate(const bool& ControlFlag);		//�X�V�����֐�.
	void Render();								//�`�揈���֐�.
	void Control();								//���쏈���֐�.

private:
	//========================�֐�=============================//.
	void Init();								//�����������֐�.
	void Release();								//��������֐�.

	//========================�֐�=============================//.
	CFontResource*					m_pCFontResource;
	std::vector<std::string>		changestr;


};

#endif //#ifndef CGHOST_SPEAK_STAGE_H.