#ifndef CAUTO_UI_H
#define CAUTO_UI_H

#include "..\..\CUI.h"

/**********************************
*		�����Đ�����UI�N���X.
************/
class CAutoUI
	: public CUI
{
public:
	CAutoUI();
	~CAutoUI();

	//=======================�֐�==========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=======================�ϐ�==========================//.
	CSpriteUI*	m_pCSpriteUI;	//�X�v���C�gUI.


};

#endif	//#ifndef CAUTO_UI_H.