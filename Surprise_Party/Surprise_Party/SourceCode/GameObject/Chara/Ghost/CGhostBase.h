#ifndef CGHOST_BASE_H
#define CGHOST_BASE_H

#include "..\CCharaBase.h"

class CGhostBase
	: public CCharaBase
{
public:
	CGhostBase();
	virtual ~CGhostBase();

	//=======================�萔==========================//.
	const float	ANGLE_SPEED		= 0.08f;							//�p�x�ǉ����x.
	const float	ANGLE_MAX		= 360.0f;							//�p�x�ő�l.
	const float	ANGLE_MIN		= 0.0f;								//�p�x�ŏ��l.
	const float	UP_DOWN_SPEED	= 0.01f;							//�㉺�ړ��̑��x.
	const float	VERTICAL_WIDTH	= 2.5f;								//�c�̕�.

	//================�񋓑�===================//.
	enum class enEmotionType {
		Sleep = 0,		//�Q��.
		HaveTrounble,	//����.
		Rejoice,		//���.
		Question,		//�^��.
		Nothing,		//����.

		Max,			//�ő�l.
	};

protected:
	//=======================�֐�==========================//.
	void MoveUpDown();		//���V�����֐�.


	//=======================�ϐ�==========================//.
	int		m_EmotionNum;		//����ԍ�.

private:
	//=======================�ϐ�==========================//.
	float	m_fMoveAngle;		//�ړ��p�x.

};

#endif	//#ifndef CGHOST_BASE_H.