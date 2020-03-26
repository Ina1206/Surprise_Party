#ifndef CPAUSE_H
#define CPAUSE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Drawing\Resource\CResourceManager.h"

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
	std::vector<CSpriteUI*>	m_pCSpriteUI;	//�X�v���C�gUI.

};

#endif	//#ifndef CPAUSE_H.