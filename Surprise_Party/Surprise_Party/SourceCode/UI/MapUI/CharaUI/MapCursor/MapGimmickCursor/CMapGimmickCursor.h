#ifndef CMAP_GIMMICK_CUROSR_H
#define CMAP_GIMMICK_CUROSR_H

#include "..\CMapCursor.h"

/****************************************
*	�}�b�v��̃M�~�b�N�p�J�[�\���N���X.
********/
class CMapGimmickCursor
	: public CMapCursor
{
public:
	CMapGimmickCursor();
	~CMapGimmickCursor();

	//========================�֐�=============================//.
	void UpDate();		//�X�V�����֐�.

private:
	//========================�֐�=============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CMAP_GIMMICK_CUROSR_H.