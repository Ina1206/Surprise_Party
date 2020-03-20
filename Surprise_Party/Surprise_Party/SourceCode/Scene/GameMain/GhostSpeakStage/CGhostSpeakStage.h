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

	//========================�֐�=============================//.
	void UpDate(const bool& ControlFlag);		//�X�V�����֐�.
	void Render();								//�`�揈���֐�.
	void Control();								//���쏈���֐�.

private:
	//========================�֐�=============================//.
	void Init();								//�����������֐�.
	void Release();								//��������֐�.
	void LoadSpeakString();						//���͓ǂݍ��ݏ����֐�.

	//========================�֐�=============================//.
	CFontResource*					m_pCFontResource;
	std::vector<std::string>		changestr;
	std::unique_ptr<CFloor>			m_pCFloor;			//��.
	std::unique_ptr<CBigGhost>		m_pCBigGhost;		//�傫��������.
	std::unique_ptr<CSpeakBigGhost>	m_pCSpeakBigGhost;	//�傫����������b�N���X.
	
};

#endif //#ifndef CGHOST_SPEAK_STAGE_H.