#ifndef CGAME_MAIN_H
#define CGAME_MAIN_H

#include "..\SceneBase\CSceneBase.h"
#include "StageManager/CStageManager.h"

/***************************************
*		�Q�[�����C���N���X.
***********/
class CGameMain
	: public CSceneBase
{
public:
	CGameMain();
	~CGameMain();


	//=========================�֐�===========================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=========================�֐�===========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//===================�ϐ�=======================//.
	std::unique_ptr<CStageManager>	m_pCStageManager;	//�X�e�[�W�Ǘ��N���X.
							
};

#endif	//#ifndef CGAME_MAIN_H.