#ifndef CMAIN_STAGE_WORK_GHOST_BASE_H
#define CMAIN_STAGE_WORK_GHOST_BASE_H

#include "..\CWorkGhostBase.h"

/**********************************************
*	���C���X�e�[�W�̓������������N���X.
****************/
class CMainStageWorkGhostBase
	: public CWorkGhostBase
{
public:
	CMainStageWorkGhostBase();
	virtual ~CMainStageWorkGhostBase();

	//==============�萔=================//.
	//m_MoveFlag.
	const unsigned int	SURPRISE_FLAG		= (1 << 0);							//�������Ă���t���O.
	const unsigned int	SELECT_FLAG			= (1 << 1);							//�I���t���O.
	const unsigned int	SELECT_ACT_FLAG		= (1 << 2);							//�I���s���t���O.
	const unsigned int	MOVE_FLAG			= (1 << 3);							//�ړ��t���O.
	const unsigned int	REST_FLAG			= (1 << 4);							//�x�e�t���O.
	const unsigned int	SELECT_STOP_FLAG	= (1 << 5);							//�I��߂�t���O.
	//m_SurpriseFlag.
	const unsigned int	GIMMICK_TOP_FLAG	= (1 << 0);							//�M�~�b�N�̏�ɂ��邩�t���O.	
	const unsigned int	HUMAN_NEAR_FLAG		= (1 << 1);							//�l���߂Â��Ă��邩�t���O.
	const unsigned int	SURPRISE_ACT_FLAG	= (1 << 2);							//�l���������Ă��邩�ǂ����t���O.
	const unsigned int	SURPRISE_REST_FLAG	= (1 << 3);							//�����x�e�t���O.
	//m_RestFlag.
	const unsigned int	REST_PREPARAT_FLAG	= (1 << 0);							//�x�e�����t���O.
	const unsigned int	IN_REST_FLAG		= (1 << 1);							//�x�e���t���O.
	const unsigned int	RESURRECTION_FLAG	= (1 << 2);							//�����t���O.
	//m_UpDownObjectFlag.
	const unsigned int	DOWN_FLAG			= (1 << 0);							//������t���O.
	const unsigned int	UP_FLAG				= (1 << 1);							//�グ��t���O.

	const float			COLOR_MAX			= 255.0f;							//�F�̍ő�l.
	const float			ADJUSTMENT_WIDTH	= 0.2f;								//������.
	const float			NEAR_SENTER_ADJUST	= 5.0f;								//�߂Â����蒆������.
	//const float			GIMMICK_UP_DECISION = 0.1f;								//�M�~�b�N�̏�ɏ���Ă��邩�̔��荷��.
	const float			SURPRISE_POS_ADJUST = 2.5f;								//�����ꏊ�̍���.
	const int			NOT_SURPRISE_NUM	= -1;								//�N�������Ă��Ȃ��Ƃ��̔ԍ�.
	const float			HUMAN_HIT_SCALE		= 1.0f;								//�l�����������蔻��傫��.
	const float			SURPRISE_HIT_SCALE	= 0.5f;								//�l�������ꏊ�̓����蔻��傫��.
	const D3DXVECTOR3	REST_ROTATION_SPEED = D3DXVECTOR3(0.02f, 0.03f, 0.0f);	//�񕜉�]���x.
	const float			REST_MOVE_SPEED		= 0.02f;							//�񕜈ړ����x.
	const float			REST_SCALE_SPEED	= 0.002f;							//�񕜑傫�����x.
	const D3DXVECTOR3	REST_ROTATION_MAX	= D3DXVECTOR3(1.5f, 2.5f, 0.0f);	//�񕜉�]�ő吔.
	const float			REST_MOVE_MAX		= 1.5f;								//�񕜈ړ��ő吔.
	const float			REST_SCALE_MIN		= 0.0f;								//�񕜑傫���ŏ�.
	const float			BASIC_REDUCE_SPEED	= 0.01f;							//��{�̗͌��炷���x.
	const float			MOVE_REDUCE_SPEED	= 0.015f;							//�ړ����̗̑͌��鑬�x.
	const float			CAMERA_DISP_RANGE	= 15.0f;							//�\���J�����͈�.
	const float			ROT_SPEED			= 0.1f;								//�p�x�̑��x.
	const float			ROT_MAX				= 1.35f;							//�p�x�̍ő�l.
	const float			ROT_MIN				= 0.0f;								//�p�x�̍ŏ��l.
	const float			ROT_MIN_ADJUST		= 0.1f;								//�p�x�ŏ��l������.
	const int			SURPRISE_REST_MAX	= 120;								//�������x�e�ő厞��.
	//�X�e�[�^�X.
	enum class enStatus {
		Strength,			//�̗�.
		MoveSpeed,			//�ړ����x.
		RecoverySpeed,		//�񕜑��x.
		SurprisePoint,		//�����|�C���g.
	};

	//===============�֐�=================//.
	void SelectRender();								//�s���I��`�揈���֐�.
	void StrengthIconRender();							//�̗̓A�C�R���`�揈���֐�.

	//=========���u�������֐�===========//.
	//�I���t���O.
	void SetSelectFlag(const bool& flag) { m_bSelectFlag = flag; }
	//�X�e�[�W�ő勗��.
	void SetStageDistanceMax(const float& fDistance) { m_fStageMaxDistance = fDistance; }
	//�������A�C�R���I�΂�Ă���t���O.
	void SetGhostSelectIcon(const bool& bFlag) { m_bGhostSelectIcon = bFlag; }
	//�ړI�M�~�b�N���W�擾.
	void SetObjectiveGimmickPos(const D3DXVECTOR3& vPos) { m_vObjectiveGimmickPos = vPos; }
	//�M�~�b�N�I��ύX�t���O.
	void SetChangeGimmickSelect(const bool& flag) { m_bChangeGimmickSelect = flag; }
	//���������߂̍��W���擾.
	void SetSurprisePosInfo(const std::vector<D3DXVECTOR3>& vGimmickPos, const std::vector<D3DXVECTOR3>& vHumanPos) {
		m_vGimmickPos = vGimmickPos;
		m_vHumanPos = vHumanPos;
	}
	//���߂̈ʒu�ݒ�.
	void SetInitMovePos() { m_vMovePos = m_vPos; }
	//�������I�u�W�F�N�g�ݒ�.
	void SetSurpriseObjectType(const CGameObject::enSurpriseObjectType& enType) {
		m_enSurpriseObjectType = enType;
	}
	//�I�𒆎~�ݒ�.
	void SetSelectStop() { m_MoveFlag |= SELECT_STOP_FLAG; }
	//�`���[�g���A���t���O.
	void SetTutorialFlag(const bool& Flag) { m_pCAct_Selection->SetTutorialFlag(Flag); }
	//�I������t���O.
	void SetDecideSelectFlag(const bool& Flag) { m_pCAct_Selection->SetDecideFlag(Flag); }
	//�g�p�M�~�b�N�ԍ�.
	void SetUseGimmickNum(const int& Num) { m_UseGimmickNum = Num; }
	//�J�[�\������ɂ���t���O.
	void SetUpCursorFlag(const bool& bFlag) { m_bUpCursorFlag = bFlag; }

	//=========���l�������֐�===========//.
	//�I���t���O.
	bool GetSelectFlag() { return m_bSelectFlag; }
	//�M�~�b�N�I��ύX�t���O.
	bool GetChangeGimmickSelect() { return m_bChangeGimmickSelect; }
	//�������I�u�W�F�N�g���.
	enSurpriseObjectType GetSurpriseObjectType() { return m_enSurpriseObjectType; }
	//�l���������t���O.
	bool GetHumanSurpriseFlag() { return m_bHumanSurpriseFlag; }
	//�������l�ԍ�.
	int	GetSurpriseHumanNum() { return m_SurpriseHumanNum; }
	//�g���M�~�b�N�ԍ�.
	int GetUseGimmickNum() { return m_UseGimmickNum; }
	//�ړ��t���O.
	unsigned int GetMoveFlag() { return m_MoveFlag; }
	//�㉺�I�u�W�F�N�g�t���O.
	unsigned int GetUpDownFlag() { return m_UpDownObjectFlag; }
	//�߂��ɂ���l�̔ԍ�.
	std::vector<int> GetNearHumanNum() { return m_NearHumanNum; }
	//�`���[�g���A�����̃R�����g����₷�t���O.
	bool GetTutorialAddCommentFlag() const { return m_bTutorialCommentAddFlag; }

protected:
	//===============�֐�=================//.
	void	SelectUpdate();										//�I���X�V�����֐�.
	void	GhostIconUpdate();									//�������A�C�R���X�V�����֐�.
	void	SurpriseActDecide();								//�������s�������߂鏈���֐�.
	HRESULT SurpriseHit();										//�����������蔻�菈���֐�.
	void	StrengthIconUpdate();								//�̗̓A�C�R���X�V�����֐�.
	void	MoveSpeedChange();									//�ړ����x�ύX�����֐�.
	void	MovePosReference();									//�ړ��X�V�����֐�.
	void	UpdateFutigueEffect();								//��J�G�t�F�N�g�X�V�����֐�.

	virtual void SurpriseAct() = 0;								//�������s�������֐�.
	virtual void ChangeObjectUpDown() = 0;						//�㉺�ړ��ύX�����֐�.
	virtual void ReturnMove() = 0;								//�߂�ړ������֐�.

	//===============�ϐ�=================//.
	std::unique_ptr<CAct_Selection>		m_pCAct_Selection;		//�s���I���N���X.
	unsigned int						m_MoveFlag;				//�s���t���O.
	bool								m_bSelectFlag;			//�I���t���O.
	unsigned int						m_ActType;				//�I����e�t���O.
	float								m_fStageMaxDistance;	//�X�e�[�W�ő勗��.
	std::unique_ptr<CGhostIcon>			m_pCGhostIcon;			//�������A�C�R��.
	bool								m_bGhostSelectIcon;		//���������I�΂�Ă��邩�ǂ���.
	D3DXVECTOR3							m_vObjectiveGimmickPos;	//�ړI�M�~�b�N���W.
	bool								m_bChangeGimmickSelect;	//�M�~�b�N�I��ύX�t���O.
	enSurpriseObjectType				m_enSurpriseObjectType;	//�������I�u�W�F�N�g���.
	float								m_fStrength;			//�̗�.
	float								m_fStrengthMax;			//�̗͍ő吔.
	float								m_fMoveSpeed;			//�ړ����x.
	float								m_fMoveSpeedMax;		//�ړ����x�ő吔.
	float								m_fRecoverySpeed;		//�x�e����.
	unsigned int						m_SurpriseFlag;			//�������Ă���t���O.
	unsigned int						m_RestFlag;				//�x�e�t���O.
	float								m_fScaleMax;			//�傫���ő吔.
	std::unique_ptr<CGhostStrengthIcon>	m_pCGhostStrengthIcon;	//�������̗̑̓A�C�R��.
	unsigned int						m_UpDownObjectFlag;		//�㉺�I�u�W�F�N�g�t���O.
	D3DXVECTOR3							m_vMovePos;				//�ړ����Ă�����W.
	D3DXVECTOR3							m_vSurpriseBeforePos;	//�������O�̍��W.
	D3DXVECTOR3							m_vStrengthIconPos;		//�̗̓A�C�R�����W.
	float								m_fMoveFinishHight;		//�ړ��I����̍���.
	bool								m_bNowHumanSurprise;	//���ݐl�������t���O.
	std::vector<int>					m_NearHumanNum;			//�߂��ɂ���l�̔ԍ�.
	D3DXVECTOR3							m_vEffectCenterPos;		//�G�t�F�N�g���S���W.

	std::unique_ptr<CSurpriseEffect>	m_pCFatigue;			//��J�G�t�F�N�g.

	int									m_GhostType;			//�������̃^�C�v.

private:
	//===============�֐�===================//.
	void  SelectAfterActivity();								//�I����̍s�������֐�.
	void  RestAct();											//�x�e�����֐�.
	void  MoveGimmick();										//�M�~�b�N�ړ������֐�.
	void  RestMove(float* pfVar, float fSpped, float fMax);		//�x�e�ړ������֐�.
	void  Resurrection(float* pfVar, float fSpeed, float fMin);	//�񕜏����֐�.
	void  ClearNearHumanOfGhost();								//�������̋߂��ɂ���l�ԍ����폜�����֐�.

	//===============�ϐ�===================//.
	int									m_MoveDirection;			//�ړ�����.
	std::vector<D3DXVECTOR3>			m_vGimmickPos;				//�M�~�b�N���W.
	std::vector<D3DXVECTOR3>			m_vHumanPos;				//�l�̍��W.
	D3DXVECTOR3							m_vSurprisePos;				//�����ꏊ.
	std::vector<CDX9Mesh*>				m_pCHitSphere;				//�����蔻��p�X�t�B�A.
	bool								m_bHumanSurpriseFlag;		//�l�������t���O.
	int									m_SurpriseHumanNum;			//�������l�ԍ�.
	int									m_UseGimmickNum;			//�g���M�~�b�N�ԍ�.
	int									m_OldStrengthType;			//�̗͎��.
	int									m_SurpriseRestTime;			//�����x�e����.
	bool								m_bUpCursorFlag;			//�J�[�\������ɂ���t���O.

	bool								m_bLimitationRest;			//���E�x�e�t���O.
	bool								m_bTutorialCommentAddFlag;	//�`���[�g���A���R�����g�i�߂�t���O.

};


#endif	//#ifndef CMAIN_STAGE_WORK_GHOST_BASE_H.