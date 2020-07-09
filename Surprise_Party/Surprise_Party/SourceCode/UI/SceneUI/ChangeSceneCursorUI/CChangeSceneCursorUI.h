#ifndef CCHANGE_SCENE_CURSOR_H
#define CCHANGE_SCENE_CURSOR_H

#include "..\..\CUI.h"

/****************************************
*		�V�[���ύX�p�J�[�\��UI�N���X.
*****************/
class CChangeSceneCursorUI
	: public CUI
{
public:
	CChangeSceneCursorUI();
	~CChangeSceneCursorUI();

	//===================�萔======================//.	
	const D3DXVECTOR3	CONTROL_CURSOR_POS		= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//�J�[�\�����W.
						
	const D3DXVECTOR3	RIGHT_CURSOR_ROT		= D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//�J�[�\���p�x.
	const D3DXVECTOR3	LEFT_CURSOR_ROT			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�J�[�\���p�x.
	const D3DXVECTOR2	NORMAL_UV_POS			= D3DXVECTOR2(0.0f, 0.0f);				//�ʏ�UV���W.
	const D3DXVECTOR2	ENTER_UV_POS			= D3DXVECTOR2(0.0f, 1.0f);				//���莞��UV���W.
	const D3DXVECTOR2	HAVE_TROUBLE_UV_POS		= D3DXVECTOR2(1.0f, 0.0f);				//������UV���W.
	const D3DXVECTOR2	SURPRISE_UV_POS			= D3DXVECTOR2(1.0f, 1.0f);				//����UV���W.

	const int			CHANGE_CNT_MAX			= 10;									//�ύX�J�E���g�ő吔.
	const int			SELECT_MAX				= 2;									//�I�����ő吔.
						
	const float			ANGLE_MAX				= 360.0f;								//�p�x�ő�l.
	const float			FLOATING_SPEED			= 0.1f;									//���V���x.
	const float			FLOATING_DISTANCE		= 1.5f;									//���V����.
						
	const float			ADD_ACC_SPEED			= 0.5f;									//�����x���Z���x.
	const float			GRAVITY					= 5.0f;									//�d��.
						
	const int			RIGHT_DIRECT_NUM		= 1;									//�E�Ɉړ������ԍ�.
	const int			CHANGE_DIRECT			= -1;									//�����ύX.
	const float			ROTATION_SPEED			= 0.1f;									//��]���x.

	//m_CarryFlag.
	const unsigned int	LEFT_TITLE_CARRY_FLAG	= (1 << 0);								//���̃^�C�g���^�ԃt���O.
	const unsigned int	RIGHT_TITLE_CARRY_FLAG	= (1 << 1);								//�E�̃^�C�g���^�ԃt���O.
	const unsigned int	SELECT_CARRY_FLAG		= (1 << 2);								//�I�����^�ԃt���O.

	//m_FetchFlag.
	const unsigned int	LEFT_TITLE_FETCH_FLAG	= (1 << 0);								//���̃^�C�g�������ɍs���t���O.
	const unsigned int	RIGHT_TITLE_FETCH_FLAG	= (1 << 1);								//�E�̃^�C�g�������ɍs���t���O.
	const unsigned int	SELECT_FEATCH_FLAG		= (1 << 2);								//�I���������ɍs���t���O.

	//==================�񋓑�=====================//.
	//�ړ����.
	enum class enMoveType {
		StartMove = 0,		//�J�n���̈ړ�.
		Surprise,			//�����t���O.
		LeftTitleFetch,		//���̃^�C�g�������ɍs��.
		LeftTitleCarry,		//���̃^�C�g�����^��.
		RightTitleFetch,	//�E�̃^�C�g�������ɍs��.
		RightTitleCarry,	//�E�̃^�C�g�����^��.
		Rejoice,			//���.
		SelectFetch,		//�I�������ɍs��.
		SelectCarry,		//�I�����^��.
		BecomeCursor,		//�J�[�\���ɂȂ�.
	};

	//===================�֐�======================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//=============���u�������֐�================//.
	//�ύX�ҋ@�t���O.
	void SetChangeWaitFlag(const bool& bFlag) { m_bChangeWaitFlag = bFlag; }
	//����t���O.
	void SetControlFlag(const bool& bFlag) { m_bControlFlag = bFlag; }
	//�^�C�g���^�я��߂̍��W.
	void SetCarryStartPos(const D3DXVECTOR3& vPos) { m_vCarryStartPos = vPos; }
	//�^�ԍs���I��.
	void SetFinishCarry() { m_CarryFlag = 0; }

	//=============���擾�����֐�================//.
	//�I���I���t���O.
	bool GetSelectFinishFlag() const { return m_bSelectFinishFlag; }
	//�I��ԍ�.
	int	GetSelectNum()const { return m_SelectNum; }
	//�^�ԃt���O.
	unsigned int GetCarryFlag() const { return m_CarryFlag; }
	//���ɍs���t���O.
	unsigned int GetFetchFlag() const { return m_FetchFlag; }
	//�^��ł��鎞�̋���.
	float GetCarryDistance() const { return m_fCarryDisntace; }

private:
	//===================�֐�======================//.
	void Init();											//�����������֐�.
	void Release();											//��������֐�.
	void Act();												//�s�������֐�.
	void Control();											//���쏈���֐�.
	bool Move(const float& MoveDistanceMax);				//�ړ������֐�.
	bool MoveToDestination(const D3DXVECTOR3& vTargetPos);	//�ړI�n�ւ̈ړ������֐�.
	void UpDownFloat();										//�㉺���V�����֐�.
	bool Jump();											//�W�����v�����֐�.
	bool ChangeMoveDirect();								//�ړ������ύX�����֐�.

	//===================�ϐ�======================//.
	CSpriteUI*		m_pCSpriteUI;				//�X�v���C�gUI.
	D3DXVECTOR2		m_vUV;						//UV���W.
	D3DXVECTOR3		m_vPrePos;					//���O�̍��W.
	bool			m_bChangeWaitFlag;			//�ύX�ҋ@�t���O.
	bool			m_bSelectFinishFlag;		//�I���I���t���O.
	bool			m_bControlFlag;				//����t���O.
	int				m_ChangeCnt;				//�ύX�J�E���g.
	int				m_SelectNum;				//�I��ԍ�.
	
	float			m_fAngle;					//�p�x.

	float			m_fAcc;						//�����x.
	D3DXVECTOR3		m_vJumpBeforePos;			//�W�����v�O�̍��W.
	int				m_MaxJump;					//�W�����v�ő�l.
	int				m_JumpCnt;					//�W�����v�J�E���g.

	int				m_MoveDirect;				//�ړ�����.
	bool			m_bChangeDirect;			//�����ύX�t���O.
	D3DXVECTOR3		m_vChangeDirectBeforeRot;	//�����ύX�O�̊p�x.
	int				m_MoveWaitCnt;				//�ړ��ҋ@�t���O.
	bool			m_bArrivalFlga;				//�����t���O.
	
	D3DXVECTOR3		m_vCarryStartPos;			//�^�C�g���^�т͂��߂̍��W.
	unsigned int	m_CarryFlag;				//�^�ԃt���O.
	unsigned int	m_FetchFlag;				//���ɍs���t���O.
	float			m_fCarryDisntace;			//�^�ԋ���.
	
	int				m_MoveType;					//�ړ��t���O.

	float			m_OutSidePos;				//��ʊO��x���W.
};

#endif	//#ifndef CCHANGE_SCENE_CURSOR_H