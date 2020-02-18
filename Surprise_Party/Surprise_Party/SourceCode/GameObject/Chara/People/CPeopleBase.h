#ifndef CPEOPLE_BASE_H
#define CPEOPLE_BASE_H

#include "..\CCharaBase.h"

class CPeopleBase
	: public CCharaBase
{
public:
	CPeopleBase();
	virtual ~CPeopleBase();

	//=================�萔======================//.
	const unsigned int	SURPRISE_PRE		= (1 << 0);							//��������.
	const unsigned int	SURPRISE_ACT		= (1 << 1);							//�����s��.
	const D3DXVECTOR3	PERSON_ROT			= D3DXVECTOR3(0.0f, -1.5f, 0.0f);	//�l�̊p�x.
	const int			FAR_NUM				= -1;								//�����l�ԍ�.
	const float			ACCELERATION_SPEED	= 0.02f;							//�������x.
	const float			BASE_ANIM_SPEED		= 0.02f;							//��{�A�j���[�V�������x.
	const float			SCALE				= 0.1f;								//�l�̑傫��.
	const int			DECREMENT_POINT		= 1;								//�|�C���g����.
	const float			ADD_ANIM_SPEED		= 0.005f;							//�ǉ��A�j���[�V�������x.

	//================�񋓑�=====================//.
	//�l�̎��.
	enum class enHumanType {
		Girl = 0,		//���̎q.
		Boy,			//�j�̎q.

		Max,			//�ő�l.
		Start = Boy,	//�J�n.
	};
	//�X�e�[�^�X.
	enum class enStatus {
		MoveSpeed = 0,		//�ړ����x.
		Scared,				//�|����x.

		Max,				//�ő�l.
		Start = MoveSpeed,	//�J�n.
	};

	//=================�֐�======================//.
	void Render();		//�`�揈���֐�.

	//============���u�������֐�===============//.
	//�X�e�[�W�̍ő吔.
	void SetStageMax(const float& StageMax) { m_fStageMax = StageMax; }
	//�����t���O.
	void SetSurpriseFlag(const float& bFlag) { m_bSurpriseFlag = bFlag; }
	//�߂Â����Ƃ��̐l�ԍ�.
	void SetHumanNearNum(const int& Num) { m_HumanNearNum = Num; }
	//�������l�ő吔.
	void SetSurpriseHumanMax(const int& Max) { m_SurpriseHumanMax = Max; }

	//=============���l�������֐�==============//.
	//�ǉ��|�C���g��.
	int GetAddPointQuantity(int NearNo);

protected:
	//=================�֐�======================//.
	void DispDecision();							//�\�����菈���֐�.
	void AnimCtrlCreat();							//�A�j���[�V�����R���g���[���쐬�����֐�.
	void HumanMove();								//�l�̈ړ������֐�.
	void SurpriseAnimChange(int surpriseAnimNo);	//�����A�j���[�V�����ύX�����֐�.

	//=================�ϐ�======================//.
	CDX9SkinMesh*				m_pCSkinMesh;		//�X�L�����b�V��.
	float						m_fAnimSpeed;		//�A�j���[�V�������x.
	float						m_fWalkAnimSpeed;	//�����A�j���[�V�������x.
	float						m_fStageMax;		//�X�e�[�W�ő勗��.
	float						m_fMoveSpeed;		//�ړ����x.
	int							m_SurpriseQuantity;	//�����|�C���g��.
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;		//�A�j���[�V�����R���g���[��.
	bool						m_bSurpriseFlag;	//�����t���O.
	int							m_AnimNo;			//�A�j���[�V�����ԍ�.
	int							m_WalkAnimNo;		//�����A�j���[�V�����ԍ�.
	unsigned int				m_SurpriseActFlag;	//�����s���t���O.

	
private:
	//=================�֐�======================//.
	void SpeedAcceleration();						//���x���������֐�.

	//=================�ϐ�======================//.
	double						m_AnimTime;			//�A�j���[�V��������.
	int							m_HumanNearNum;		//�߂Â����Ƃ��̐l�Ԕԍ�.
	int							m_SurpriseHumanMax;	//�������l�ő吔.

};

#endif	//#ifndef CPEOPLE_BASE_H.