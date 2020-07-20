#ifndef CSTAGE_FADE_H
#define CSTAGE_FADE_H

#include "..\CFade.h"

/******************************************
*		�X�e�[�W�t�F�[�h�N���X.
**************/
class CStageFade
	: public CFade
{
public:
	CStageFade();
	~CStageFade();

	//=================�萔=====================//.
	const int			UI_MAX						= 4;									//UI�ő�l.
	const int			LEFT_CURTAIN_NUM			= 0;									//���J�[�e���ԍ�.
	const int			RIHGT_CURTAIN_NUM			= 1;									//�E�J�[�e���ԍ�.
	const int			SIGN_BOARD_NUM				= 2;									//�Ŕԍ�.
	const int			STRING_NUM					= 3;									//�����ԍ�.

	const unsigned int	OPENING_FLAG				= (1 << 0);								//�J�X���̃J�[�e���ړ��t���O.
	const unsigned int	CLOSE_FLAG					= (1 << 1);								//�X���̃J�[�e���ړ��t���O.
	const unsigned int	CHANGE_STAGE_FLAG			= (1 << 2);								//�X�e�[�W�ύX�t���O.
	const unsigned int	CLOSE_CURTAIN_FLAG			= (1 << 3);								//���؂����t���O.
	const unsigned int	OPEN_CHANG_FLAG				= (1 << 4);								//�ŔύX�t���O.
	const unsigned int	SIGN_BOARD_SWING_FLAG		= (1 << 5);								//�Ŕh��t���O.
	const unsigned int	OPEN_CURTAIN_FLAG			= (1 << 6);								//�J�[�e���J���t���O.

	const float			SCALE_MAX					= 1.0f;									//�傫���ő�l.
	const float			ROT_MAX						= 3.1f;									//�p�x�ő�l.
	const float			HALF_ROT_ANGLE				= 1.6f;									//����]�p�x.
	const float			CURTAIN_ROT_MIN				= -3.1f;								//�J�[�e���p�x�ŏ��l.
	const D3DXVECTOR3	BOARD_PRE_POS				= D3DXVECTOR3(-320.0f, -10.0f, 0.0f);	//�̌덷���W.
	const D3DXVECTOR3	SIGN_BOARD_INIT_POS			= D3DXVECTOR3(650.0f, -500.0f, 0.0f);	//�Ŕ̏������W.
	const D3DXVECTOR3	STRING_PRE_POS				= D3DXVECTOR3(-150.0f, 300.0f, 0.0f);	//���͌덷���W.

	const float			SIGN_BOARD_HEIGHT_MAX		= 80.0f;								//�Ŕ����ő�l.

	const int			OPEN_DIRECT					= -1;									//�J������.
	const int			CLOSE_DIRECT				= 1;									//�������.

	const float			CURTAIN_ROT_SPEED			= 0.03f;								//�J�[�e���p�x���x.
	const float			SIGN_BOARD_MOVE_SPEED		= 6.0f;									//�Ŕړ����x.
	const float			SIGN_BOARD_ROT_SPEED		= 0.1f;									//�Ŕ�]���x.
	const float			SIGN_BOARD_SCALE_SPEED		= 0.02f;								//�Ŕg�k���x.

	const int			CHANGE_DIRECT				= -1;									//�����ύX.
	const float			SWING_ROT_MAX_SPEED			= 0.3f;									//�h���p�x�ő呬�x.
	const float			SWING_SPEED					= 0.01f;								//�h��鑬�x.

	const float			SWING_ROT_LIMIT_MIN			= 0.1f;									//�h���p�x����ŏ�.
	const float			SWING_ROT_MIN				= 0.05f;								//�h���p�x�ŏ��l.
	const float			SWING_SPEED_MAX				= 0.04f;								//�h��鑬�x�ő�l.
	const float			SWING_ROT_MAX				= 0.6f;									//�h���p�x�ő�l.

	//================�񋓑�====================//.
	//�Ŕh��^�C�v.
	enum class enSwingSignBoard {
		LeftSwing,	//��.
		RightSwing,	//�E.
	};

	//=================�֐�=====================//.
	void Update();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.

	//============���u�������֐�==============//.
	//�J�[�e���ړ��t���O.
	void SetCurtainMoveFlag(const unsigned int& flag) { m_CurtainMoveFlag = flag; }

	//============���l�������֐�==============//.
	//�J�[�e���ړ��t���O.
	unsigned int GetCurtainMoveFlag() { return m_CurtainMoveFlag; }
	//�����̊���.
	float GetDistanceRatio() const { return m_fDistanceRatio; }

private:
	//=================�֐�=====================//.
	void Init();												//�����������֐�.
	void Release();												//��������֐�.
	void OpeningCurtainMove();									//�J�X���̃J�[�e���ړ������֐�.
	void CloseCurtainMove();									//�X���̃J�[�e���ړ������֐�.
	bool CurtainMove();											//�J�[�e���ړ������֐�(���Ŕ��ړ�����).
	bool RotationSignBoard(CSpriteUI*	ChangeStringSpriteUI);	//�Ŕ�]�����֐�.
	bool SwingSignBoard();										//�Ŕh��鏈���֐�.

	//=================�ϐ�=====================//.
	std::vector<CSpriteUI*>		m_pCUI;				//�X�v���C�gUI�N���X.
	std::vector<D3DXVECTOR3>	m_vUIPos;			//���W.
	std::vector<float>			m_fUIScale;			//�傫��.
	std::vector<D3DXVECTOR3>	m_vUIRot;			//�p�x.
	std::vector<D3DXVECTOR3>	m_vPrePos;			//�����p�x.

	unsigned int				m_CurtainMoveFlag;	//�J�[�e���ړ��t���O.
	enSwingSignBoard			m_enSwingSignBoard;	//�Ŕ̗h��^�C�v.
	int							m_SwingRotDirect;	//�h��̊p�x����.
	float						m_SwingRotMax;		//�h��̊p�x�ő吔.
	float						m_fSwingSpeed;		//�h��̑��x.
	CSpriteUI*					m_pCOldSpriteUI;	//�O�̃X�v���C�gUI�N���X.
	float						m_fDistanceRatio;	//�����̊���.
	bool						m_bPlayCurtainSE;	//�J�[�e���Đ��t���O.
	bool						m_bPlayOpneBell;	//�J����.
};

#endif	//#ifndef CSTAGE_FADE_H.