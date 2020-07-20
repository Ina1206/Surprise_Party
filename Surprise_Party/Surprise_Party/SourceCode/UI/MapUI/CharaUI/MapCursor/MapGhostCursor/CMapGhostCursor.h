#ifndef CMAP_GHOST_CURSOR_H
#define CMAP_GHOST_CURSOR_H

#include "..\CMapCursor.h"

/************************************
*	�}�b�v��̂������J�[�\���N���X.
**********/
class CMapGhostCursor
	: public CMapCursor
{
public:
	CMapGhostCursor();
	~CMapGhostCursor();

	//===================�萔======================//.
	const float			SCALE = 1.3f;							//�傫��.
	const D3DXVECTOR3	COLOR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	//�F.

	//===================�֐�======================//.
	void UpDate();				//�X�V�����֐�.

private:
	//===================�֐�======================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.


};

#endif	//#ifndef CMAP_GHOST_CURSOR_H.