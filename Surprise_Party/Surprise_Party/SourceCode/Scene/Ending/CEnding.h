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

	//========================�֐�===========================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.
private:
	//========================�֐�===========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//========================�ϐ�===========================//.
	std::unique_ptr<CEndingStageBase>	m_pCEndingStageBase;	//�G���f�B���O�X�e�[�W���N���X.

};

#endif	//#ifndef CENDING_H.