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
	//=====================�萔=====================//.
	const int	SELECT_TITLE_NUM = 1;	//�I���^�C�g���ԍ�.

	//=====================�֐�=====================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=====================�֐�=====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=====================�ϐ�=====================//.
	std::unique_ptr<CPauseUI>			m_pCPauseUI;		//�|�[�YUI.
};

#endif	//#ifndef CPAUSE_H.