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

	//===================�֐�======================//.
	void UpDate();			//�X�V�����֐�.

private:
	//===================�֐�======================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.


};

#endif	//#ifndef CMAP_GHOST_CURSOR_H.