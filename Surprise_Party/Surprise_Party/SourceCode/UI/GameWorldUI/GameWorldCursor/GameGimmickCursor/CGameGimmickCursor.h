#ifndef CGAME_GIMMICK_CURSOR_H
#define CGAME_GIMMICK_CURSOR_H

#include "..\CGameWorldCursor.h"

/***********************************
*		�M�~�b�N�J�[�\���N���X.
********/
class CGameGimmickCursor
	: public CGameWorldCursor
{
public:
	CGameGimmickCursor();
	~CGameGimmickCursor();

	//====================�萔======================//.
	const float			ADJUST_HEIGHT	= -3.0f;						//��������.
	const float			ADJUST_WIDTH	= 4.0f;							//������.
	const float			SCALE			= 2.5f;							//�傫��.
	const D3DXVECTOR3	COLOR			= D3DXVECTOR3(0.5f, 1.0f, 0.5f);//�F.

	//====================�֐�======================//.
	void UpDate();					//�X�V�����֐�.

	//==============���u�������֐�================//.
	//�I���ł���t���O.
	void SetUnSelectableFlag(const bool& flag) { m_bUnSelectableFlag = flag; }

private:
	//====================�֐�======================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.

	//====================�ϐ�======================//.
	bool	m_bUnSelectableFlag;	//�I���ł�t���O.

};

#endif	//#ifndef CGAME_GIMMICK_CURSOR_H.