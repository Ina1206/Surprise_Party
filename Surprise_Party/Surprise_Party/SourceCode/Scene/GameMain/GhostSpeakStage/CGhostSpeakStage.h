#ifndef CGHOST_SPEAK_STAGE_H
#define CGHOST_SPEAK_STAGE_H

#include "..\StageBase\CStageBase.h"
#include "..\..\..\FileLoad\FileResource\CFileResource.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Object\StaticObject\Wall\CWall.h"

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
	void LoadString();							//���͓ǂݍ��ݏ����֐�.

	//========================�֐�=============================//.
	CFontResource*					m_pCFontResource;
	std::vector<std::string>		changestr;
	std::unique_ptr<CFloor>			m_pCFloor;			//��.
	std::unique_ptr<CWall>			m_pCWall;			//��.

};

#endif //#ifndef CGHOST_SPEAK_STAGE_H.