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
	const float			ANGLE_SPEED		= 0.08f;							//�p�x�ǉ����x.
	const float			ANGLE_MAX		= 360.0f;							//�p�x�ő�l.
	const float			ANGLE_MIN		= 0.0f;								//�p�x�ŏ��l.
	const float			UP_DOWN_SPEED	= 0.01f;							//�㉺�ړ��̑��x.
	const float			VERTICAL_WIDTH	= 2.5f;								//�c�̕�.
	const D3DXVECTOR3	SKY_DIRECT		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//�����.

	//================�񋓑�===================//.
	enum class enEmotionType {
		Sleep = 0,		//�Q��.
		HaveTrounble,	//����.
		Rejoice,		//���.
		Question,		//�^��.
		Nothing,		//����.
		ViewSmartphone,	//�X�}�[�g�t�H��������.

		Max,			//�ő�l.
	};

	//===========���u�������֐�==============//.
	void SetEmotionNum(const int& Num) { m_EmotionNum = Num; }	//����ԍ�.

protected:
	//=======================�֐�==========================//.
	void MoveUpDown();											//���V�����֐�.
	void MoveRotation(const D3DXVECTOR3& vSalfPos, 
					  const D3DXVECTOR3& vTargetPos);			//�ړ��p�x�����֐�.


	//=======================�ϐ�==========================//.
	int				m_EmotionNum;		//����ԍ�.
	bool			m_bUseRotFlag;		//�p�x�g�p�t���O.
	D3DXMATRIX		m_mPoint;			//��]�s��.

private:
	//=======================�ϐ�==========================//.
	float	m_fMoveAngle;		//�ړ��p�x.

};

#endif	//#ifndef CGHOST_BASE_H.