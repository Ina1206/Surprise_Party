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