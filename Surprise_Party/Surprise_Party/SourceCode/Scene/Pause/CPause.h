#ifndef CPAUSE_H
#define CPAUSE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\UI\SceneUI\CPauseUI\CPuaseUI.h"

/****************************************
*		�ꎞ��~�N���X.
************/
class CPause
	: public CSceneBase
{
public:
	CPause();
	~CPause();

	//=====================�֐�=====================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=====================�֐�=====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=====================�萔=====================//.
	std::unique_ptr<CPauseUI>			m_pCPauseUI;		//�|�[�YUI.
};

#endif	//#ifndef CPAUSE_H.