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
		GoodFeeling,	//���@��.
		ViewSmartphone,	//�X�}�[�g�t�H��������.

		Max,			//�ő�l.
	};

	//===========���u�������֐�==============//.
	void SetEmotionNum(const int& Num) { m_EmotionNum = Num; }			//����ԍ�.
	void SetLookAtPos(const D3DXVECTOR3& vPos) { m_vLookAtPos = vPos; }	//������W.
	void SetRot(const D3DXVECTOR3& vRot) { m_vRot = vRot; }
	void SetChangeBeforePos(const D3DXVECTOR3& vPos) { m_vChangeBeforePos = vPos; }
protected:
	//=======================�֐�==========================//.
	void MoveUpDown();											//���V�����֐�.
	void MoveRotation(const D3DXVECTOR3& vSalfPos, 
					  const D3DXVECTOR3& vTargetPos);			//�ړ��p�x�����֐�.

	//=======================�ϐ�==========================//.
	int				m_EmotionNum;			//����ԍ�.
	D3DXVECTOR3		m_vLookAtPos;			//������W.
	D3DXVECTOR3		m_vPrePos;				//���W�C��.
	D3DXVECTOR3		m_vChangeBeforePos;		//�ύX�O�̍��W.		

private:
	//=======================�֐�==========================//.
	void ConvertRotationMatrixToRadian(const D3DXMATRIX& mMat);	//��]�s�񂩂�N�E�H�[�^�j�I���ɕϊ������֐�.

	//=======================�ϐ�==========================//.
	float	m_fMoveAngle;		//�ړ��p�x.

};

#endif	//#ifndef CGHOST_BASE_H.