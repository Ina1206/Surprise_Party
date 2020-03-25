#ifndef CTUTORIAL_H
#define CTUTORIAL_H

#include "..\SceneBase\CSceneBase.h"
#include "..\GameMain\StageBase\CStageBase.h"

/************************************
*	�`���[�g���A���N���X.
*********/
class CTutorial
	: public CStageBase
{
public:
	CTutorial();
	~CTutorial();

	//======================�֐�============================//.
	void UpDate(const bool& ControlFlag);	//�X�V�����֐�.
	void Render();							//�`�揈���֐�.

private:
	//======================�֐�============================//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.
	void Control();	//���쏈���֐�.

};

#endif	//#ifndef CTUTORIAL_H.