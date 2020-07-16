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
	const int			UI_MAX						= 4;		//UI�ő�l.
	const int			LEFT_CURTAIN_NUM			= 0;		//���J�[�e���ԍ�.
	const int			RIHGT_CURTAIN_NUM			= 1;		//�E�J�[�e���ԍ�.
	const int			SIGN_BOARD_NUM				= 2;		//�Ŕԍ�.
	const int			STRING_NUM					= 3;		//�����ԍ�.

	const unsigned int OPENING_FLAG					= (1 << 0);	//�J�X���̃J�[�e���ړ��t���O.
	const unsigned int CLOSE_FLAG					= (1 << 1);	//�X���̃J�[�e���ړ��t���O.
	const unsigned int CHANGE_STAGE_FLAG			= (1 << 2);	//�X�e�[�W�ύX�t���O.
	const unsigned int CLOSE_CURTAIN_FLAG			= (1 << 3);	//���؂����t���O.
	const unsigned int OPEN_CHANG_FLAG				= (1 << 4);	//�ŔύX�t���O.
	const unsigned int SIGN_BOARD_SWING_FLAG		= (1 << 5);	//�Ŕh��t���O.
	const unsigned int OPEN_CURTAIN_FLAG			= (1 << 6);	//�J�[�e���J���t���O.

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