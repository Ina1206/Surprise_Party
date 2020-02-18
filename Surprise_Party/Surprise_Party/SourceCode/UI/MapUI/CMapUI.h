#ifndef CMAP_UI_H
#define CMAP_UI_H

#include "..\CUI.h"

/******************************************
*		�}�b�vUI�N���X.
**********/
class CMapUI
	: public CUI
{
public:
	CMapUI();
	virtual ~CMapUI();

	//====================�֐�========================//.
	void Render();						//�`�揈���֐�.

protected:
	//====================�ϐ�========================//.
	CSpriteUI*		m_pCSpriteUI;		//SpriteUI�N���X.
	D3DXVECTOR3		m_vColor;			//�F(�A���t�@�l�𔲂�).
	D3DXVECTOR2		m_vPattarn;			//�p�^�[��.

};

#endif	//#ifndef CMAP_UI_H.