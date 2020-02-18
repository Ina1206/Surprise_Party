#ifndef CGAME_GHOST_CURSOL_H
#define CGAME_GHOST_CURSOL_H

#include "..\CGameWorldCursor.h"

/*********************************************
*	�Q�[�����̂������̃J�[�\���N���X.
*************/
class CGameGhostCursor
	: public CGameWorldCursor
{
public:
	CGameGhostCursor();
	~CGameGhostCursor();

	//=====================�萔==========================//.
	const float	CURSOL_BASE_HIGHT	= 7.0f;	//�J�[�\����{����.
	const float	SCALE				= 2.5f;	//�傫��.

	//=====================�֐�==========================//.
	void UpDate();			//�X�V�����֐�.

	//===============���l����������====================//.
	//�x�e�t���O.
	void SetRestFlag(const bool& flag) { m_bRestFlag = flag; }
	
private:
	//=====================�֐�==========================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.

	//=====================�ϐ�==========================//.
	bool	m_bRestFlag;	//�x�e�t���O.

	

};

#endif //#ifndef CGAME_GHOST_CURSOL_H.