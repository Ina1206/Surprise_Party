#ifndef CACT_SELECTION_H
#define CACT_SELECTION_H

#include "..\CGameWorldUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*************************************
*		�s���I���N���X.
********/
class CAct_Selection
	: public CGameWorldUI
{
public:
	CAct_Selection();
	~CAct_Selection();

	//====================�萔=======================//.
	const int			CHOICE_MAX			= 2;					//�I�����̍ő吔.
	const int			LEFT_DIRECTION		= -1;					//���������l.
	const int			RIGHT_DIRECTION		= 1;					//�E�������l.
	const unsigned int	OPEN_MOVE			= (1 << 0);				//�J���ړ�.
	const unsigned int	CLOSE_MOVE			= (1 << 1);				//����ړ�.
	const float			MOVE_SPEED			= 0.1f;					//�ړ����x.
	const float			M0VE_DISTANCE_MAX	= 2.0f;					//�ړ������ő�.
	const float			MOVE_DISTANCE_MIN	= 0.0f;					//�ړ������ŏ�.
	const float			ROTATION_SPEED		= 0.02f;				//��]���x.
	const float			SELECT_SCALE		= 1.3f;					//�I�𒆂̑傫��.
	const float			NORMAL_SCALE		= 1.0f;					//�ʏ�̑傫��.
	const float			SELECT_ALPHA		= 1.0f;					//�I�𒆂̓��ߒl.
	const float			NORMAL_ALPHA		= 0.7f;					//�ʏ�̓��ߒl.
	const unsigned int	MOVE_FLAG			= (1 << 0);				//�ړ��t���O.
	const unsigned int	REST_FLAG			= (1 << 1);				//�x�e�t���O.

	//===================�񋓑�======================//.
	//�������s�����.
	enum class enGhostActType {
		Move = 0,	//�ړ�.
		Rest,		//�x�e.

		Max,
		Start = Move,
	};

	//====================�֐�=======================//.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.


	//==============���u�������֐�=================//.
	//�I���t���O.
	void SetSelectFlag(const bool& flag) { m_bSelectFlag = flag; }
	//�`���[�g���A���t���O.
	void SetTutorialFlag(const bool& flag) { m_bTutorialFlag = flag; }
	//����t���O.
	void SetDecideFlag(const bool& flag) { m_bDecideFlag = flag; }
	//�I���������t���O.
	void SetCloseMoveFlag() { m_MoveFlag = CLOSE_MOVE; }

	//==============���擾�����֐�=================//.
	//�I���t���O.
	bool GetSelectFlag() { return m_bSelectFlag; }
	//�������s���t���O.
	int GetGhostActFlag() { return m_GhostActFlag; }

private:
	//====================�֐�=======================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.
	void BeforeMove();		//�����O�̏����֐�.
	void OpenMove();		//�J���ړ������֐�.
	void CloseMove();		//����ړ������֐�.
	void Control();			//���쏈���֐�.

	//====================�ϐ�=======================//.
	std::vector<CSprite*>		m_pCSprite;				//�X�v���C�g�N���X.
	std::vector<D3DXVECTOR3>	m_vSpritePos;			//�X�v���C�g���W.
	std::vector<D3DXVECTOR3>	m_vSpriteRot;			//�p�x.
	std::vector<float>			m_fSpriteAlpha;			//���ߒl.
	std::vector<float>			m_fSpriteScale;			//�傫��.
	std::vector<float>			m_fMoveDistance;		//�ړ����x.
	std::vector<int>			m_Direction;			//����.
	bool						m_bSelectFlag;			//�I���t���O.
	unsigned int				m_MoveFlag;				//�ړ��t���O.
	int							m_SelectNum;			//�I��ԍ�.
	int							m_GhostActFlag;			//�������s���t���O.
	bool						m_bTutorialFlag;		//�`���[�g���A���t���O.
	bool						m_bDecideFlag;			//����t���O.
	CPlaySoundManager*			m_pCPlaySoundManager;	//���Đ��Ǘ��N���X.
	bool						m_bOpenSEFlag;			//�J��SE�t���O.
};

#endif //#ifndef CACT_SELECTION_H.