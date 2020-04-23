#ifndef CSPEAK_TUTORIAL_H
#define CSPEAK_TUTORIAL_H

#include "..\CSpeakUI.h"

//=================�萔=======================//.
const unsigned int SELECT_GHOST_FLAG			= (1 << 0);	//�������I���t���O.
const unsigned int DECIDE_GHOST_FLAG			= (1 << 1);	//����������t���O.
const unsigned int DECIDE_ACT_FLAG				= (1 << 2);	//�s������t���O.
const unsigned int SELECT_GIMMICK_FLAG			= (1 << 3);	//�M�~�b�N�I���t���O.
const unsigned int DECIDE_GIMMICK_FLAG			= (1 << 4);	//�M�~�b�N����t���O.

/******************************************
*		�`���[�g���A����b.
***************/
class CSpeakTutorial
	: public CSpeakUI
{
public:
	CSpeakTutorial();
	~CSpeakTutorial();

	//=================�萔=======================//.
	const unsigned int MAP_DESCRIPTION_FLAG			= (1 << 0);	//�n�}�̐����t���O.
	const unsigned int GHOST_DESCRIPTION_FLAG		= (1 << 1);	//�������̐����t���O.
	const unsigned int GIMMICK_DESCRIPTION_FLAG		= (1 << 2);	//�M�~�b�N�̐����t���O.
	const unsigned int PEOPLE_DESCRIPTION_FLAG		= (1 << 3);	//�l�X�̐����t���O.
	const unsigned int GAGE_DESCRIPTION_FLAG		= (1 << 4);	//�����Q�[�W�̐����t���O.
	const unsigned int CLOSE_TIME_DESCRIPTION_FLAG	= (1 << 5);	//�����Ԃ̐����t���O.

	//=================�֐�=======================//.
	void Update();				//�X�V�����֐�.
	void Render();				//�`�揈���֐�.
	void AdvanceOnceComment();	//���R�����g��i�߂鏈���֐�.
	void AddSelectMoveCount();	//�I���ړ��J�E���g�ǉ������֐�.

	//============���擾�����֐�=================//.
	//�`���[�g���A���t���O.
	unsigned int GetTutorialFlag() const { return m_TutorialFlag; }
	//�R�����g�i�߂�t���O.
	bool GetAdvanceCommentFlag() const { return m_bAdvanceCommentFlag; }
	//�����t���O.
	unsigned int GetDescriptionFlag() const { return m_DescriptionFlag; }

	//============���u�������֐�=================//.
	//�R�����g�i�߂�t���O.
	void SetAdvanceCommentFlag(const bool& bFlag) { m_bAdvanceCommentFlag = bFlag; }


private:
	//==================�֐�=======================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.
	void FindTutorial();	//�`���[�g���A�������鏈���֐�.
	void FindDescription();	//�������e�����鏈���֐�.

	//==================�ϐ�=======================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;				//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vPos;						//���W.
	unsigned int				m_TutorialFlag;				//�`���[�g���A���t���O.
	unsigned int				m_DescriptionFlag;			//�����t���O.
	bool						m_bAdvanceCommentFlag;		//�R�����g�i�߂�t���O.
	int							m_SelectMoveCount;			//�I���ړ��J�E���g.
};

#endif	//#ifndef CSPEAK_TUTORIAL_H.