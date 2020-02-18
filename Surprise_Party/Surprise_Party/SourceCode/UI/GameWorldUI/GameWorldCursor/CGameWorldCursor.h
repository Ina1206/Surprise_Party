#ifndef CGAME_WORLD_CURSOL_H
#define CGAME_WORLD_CURSOL_H

#include "..\CGameWorldUI.h"

/***********************************
*		�Q�[�����̃J�[�\���N���X.
***********/
class CGameWorldCursor
	: public CGameWorldUI
{
public:
	CGameWorldCursor();
	virtual ~CGameWorldCursor();

	//==================�萔=====================//.
	const float	UNSELECTABLE_ALPHA	= 0.5f;		//�I���ł��Ȃ��Ƃ��̓��ߒl.


protected:
	//==================�֐�=====================//.
	void CursorUpDown();						//�J�[�\�����������֐�.
	void AlphaChange(bool flag);				//���ߒl�ύX�����֐�.

	//==================�ϐ�=====================//.
	float	m_fUpDownDistance;					//�オ�艺���苗��.

private:
	//==================�萔=====================//.
	const float	ADD_SPEED			= -0.003f;	//�������x.
	const float	MOVE_DISTANCE_MIN	= -0.5f;	//�ړ������ŏ��l.
	const float MOVE_DISTANCE_MAX	= 0.0f;		//�ړ������ő�l.
	const int	CHANGE_DIRECTION	= -1;		//�����ύX���l.

	//=================�񋓑�====================//.
	//�㉺�̎��.
	enum class enUpDownType {
		Up,		//�オ��.
		Down,	//������.
	};

	//==================�ϐ�======================//.
	enUpDownType	m_enUpDownType;			//�㉺�̎��.
	float			m_fUpDownSpeed;			//�㉺�ړ��̑��x.
	int				m_Direction;			//����.

};

#endif	//#ifndef CGAME_WORLD_CURSOL_H.