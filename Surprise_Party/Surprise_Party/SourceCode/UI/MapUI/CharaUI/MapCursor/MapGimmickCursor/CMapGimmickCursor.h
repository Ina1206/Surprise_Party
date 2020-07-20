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

	//========================�萔=============================//.
	const float			CURSOR_HEIGHT	= 60.0f;							//�J�[�\������.
	const float			SCALE			= 1.3f;								//�傫��.
	const D3DXVECTOR3	COLOR			= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//�F.

	//========================�֐�=============================//.
	void UpDate();		//�X�V�����֐�.

private:
	//========================�֐�=============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CMAP_GIMMICK_CUROSR_H.