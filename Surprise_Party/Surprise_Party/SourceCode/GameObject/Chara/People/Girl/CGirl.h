#ifndef CGIRL_H
#define CGIRL_H

#include "..\CPeopleBase.h"

/*******************************************************
*			���̎q�N���X.
************************/
class CGirl
	: public CPeopleBase
{
public:
	CGirl();
	~CGirl();

	//=================�萔====================//.
	const int	SUSPEND_INTERVAL_TIME_MIN	= 2;	//�ꎞ��~���ԍŏ��l.
	const int	SUSPEND_INRERVAL_TIME_MAX	= 5;	//�ꎞ��~���ԍő�l.
	const int	SECONDS_DELIMITER			= 60;	//�b��؂�.
	const float DEPTH_POS					= -3.5f;//���s���̍��W.

	//================�񋓑�===================//.
	enum class enGirlAnimType {
		FallDown,	//�|���.
		Stand,		//����.
		Walk,		//����.
		Search,		//�T��.
		Rejoice,	//���.
	};

	//=================�֐�====================//.
	void Update();				//�X�V�����֐�.
	
private:
	//=================�֐�====================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void SearchMotion();		//�T�������֐�.
	void SearchAnimChange();	//�T���A�j���[�V�����ύX�����֐�.

	//=================�ϐ�=====================//.
	int		m_SuspendTime;		//�ꎞ��~����J�E���g.
	double	m_dAnimTime;		//�A�j���[�V�����^�C��.
	int		m_SuspendInterval;	//�ꎞ��~�Ԋu.
	float	m_fOldPosX;			//X���W�̑O�̍��W.
};

#endif	//#ifndef CGIRL_H.