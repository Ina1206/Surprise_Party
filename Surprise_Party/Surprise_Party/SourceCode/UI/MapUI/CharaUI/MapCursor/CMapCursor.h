#ifndef CMAP_CURSOR_H
#define CMAP_CURSOR_H

#include "..\CCharaUI.h"

/********************************************
*		�}�b�v�̃J�[�\���N���X.
*********/
class CMapCursor
	: public CCharaUI
{
public:
	CMapCursor();
	virtual ~CMapCursor();

	//======================�萔===========================//.
	const D3DXVECTOR3 CURSOR_UI_ADJUSTMENT = D3DXVECTOR3(7.0f, 7.0f, 0.0f);

protected:

};

#endif	//#ifndef CMAP_CURSOR_H.