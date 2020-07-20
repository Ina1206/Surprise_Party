#ifndef CENDING_H
#define CENDING_H

#include "..\SceneBase\CSceneBase.h"

#include "BeforeResultStage\CBeforeResultStage.h"


/************************************************
*		�G���f�B���O�N���X.
***********/
class CEnding
	: public CSceneBase
{
public:
	CEnding();
	~CEnding();

	//========================�萔===========================//.
	const int LOW_EVALUATION_NUM			= 0;	//��]���̔ԍ�.
	const int INTERMEDIATE_EVALUATION_NUM	= 1;	//���ԕ]���̔ԍ�.

	//========================�֐�===========================//.
	void UpDate();						//�X�V�����֐�.
	void Render();						//�`�揈���֐�.
private:
	//========================�֐�===========================//.
	void Init();						//�����������֐�.
	void Release();						//��������֐�.
	void ChangeStage();					//�X�e�[�W�ύX�����֐�.
	CEndingStageBase* DecideStage();	//�X�e�[�W���菈���֐�.

	//========================�ϐ�===========================//.
	std::unique_ptr<CEndingStageBase>	m_pCEndingStageBase;	//�G���f�B���O�X�e�[�W���N���X.
	int									m_ChangeStageCnt;		//�X�e�[�W�ύX�J�E���g.
};

#endif	//#ifndef CENDING_H.