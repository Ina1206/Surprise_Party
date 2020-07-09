#ifndef CTITLE_UI_H
#define CTITLE_UI_H

#include "..\CSceneUIBase.h"

/*************************************
*		�^�C�g��UI�N���X.
****************/
class CTitleUI
	: public CSceneUIBase
{
public:
	CTitleUI();
	~CTitleUI();
	//======================�萔=======================//.
	//m_SelectTypeFlag.
	const unsigned int	GAME_START_FLAG		= (1 << 0);							//�Q�[���X�^�[�g�t���O.
	const unsigned int	GAME_FINISH_FLAG	= (1 << 1);							//�Q�[���I���t���O.	
	//m_ControlFlag.
	const unsigned int	CONTROL_WAIT_FLAG	= (1 << 0);							//����ҋ@�t���O.
	const unsigned int	CONTROL_FLAG		= (1 << 1);							//����t���O.

	const D3DXVECTOR3	TITLE_POS			= D3DXVECTOR3(40.5f, 90.8f, 0.0f);	//�^�C�g�����W.

	const int			TITLE_MAX			= 2;								//�^�C�g���ő�l.



	//======================�֐�=======================//.
	void Update();							//�X�V�����֐�.

	//================���擾�����֐�=================//.
	unsigned int GetSelectTypeFlag() const;	//�I����ނ̃t���O���擾�����֐�.
	
private:
	//======================�֐�=======================//.
	void Init();							//�����������֐�.
	void InitTitlePos();					//�^�C�g�����W�̏����������֐�.
	void ControlTitlePos();					//���쎞�^�C�g�����W�ݒ菈���֐�.

	//======================�ϐ�=======================//.
	unsigned int				m_SelectTypeFlag;			//�I����ރt���O.
	unsigned int				m_ControlFlag;				//����t���O.
	std::vector<D3DXVECTOR3>	m_vTitleLastPos;			//�^�C�g���ŏI���W.

};

#endif	//#ifndef CTITLE_UI_H.