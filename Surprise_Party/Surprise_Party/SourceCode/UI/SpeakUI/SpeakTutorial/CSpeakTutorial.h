#ifndef CSPEAK_TUTORIAL_H
#define CSPEAK_TUTORIAL_H

#include "..\CSpeakUI.h"

//=================�萔=======================//.
const unsigned int SELECT_GHOST_FLAG			= (1 << 0);	//�������I���t���O.
const unsigned int DECIDE_GHOST_FLAG			= (1 << 1);	//����������t���O.
const unsigned int DECIDE_ACT_FLAG				= (1 << 2);	//�s������t���O.
const unsigned int SELECT_GIMMICK_FLAG			= (1 << 3);	//�M�~�b�N�I���t���O.
const unsigned int DECIDE_GIMMICK_FLAG			= (1 << 4);	//�M�~�b�N����t���O.

const unsigned int CustomerEnterSE				= (1 << 0);	//�q�������Ă���SE.
const unsigned int SeePeople					= (1 << 1);	//�q������.
const unsigned int DescriptionEnd				= (1 << 2);	//�����I��.

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
	const unsigned int	MAP_DESCRIPTION_FLAG		= (1 << 0);	//�n�}�̐����t���O.
	const unsigned int	GHOST_DESCRIPTION_FLAG		= (1 << 1);	//�������̐����t���O.
	const unsigned int	GIMMICK_DESCRIPTION_FLAG	= (1 << 2);	//�M�~�b�N�̐����t���O.
	const unsigned int	PEOPLE_DESCRIPTION_FLAG		= (1 << 3);	//�l�X�̐����t���O.
	const unsigned int	GAGE_DESCRIPTION_FLAG		= (1 << 4);	//�����Q�[�W�̐����t���O.
	const unsigned int	CLOSE_TIME_DESCRIPTION_FLAG	= (1 << 5);	//�����Ԃ̐����t���O.

	const float			DESCRIPTION_ICON_SCALE		= 0.9f;		//�����p�A�C�R���傫��.	

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
	//�J�n���O�t���O.
	unsigned int GetStartLatestFlag() const { return m_enStartLatestFlag; }
	//�I���t���O.
	bool GetDescriptionEndFlag() const { return m_bDescriptionEnd; }
	//============���u�������֐�=================//.
	//�R�����g�i�߂�t���O.
	void SetAdvanceCommentFlag(const bool& bFlag) { m_bAdvanceCommentFlag = bFlag; }


private:
	//==================�֐�=======================//.
	void Init();									//�����������֐�.
	void Release();									//��������֐�.
	void FindTutorial();							//�`���[�g���A�������鏈���֐�.
	void FindDescription();							//�������e�����鏈���֐�.
	void SettingDescriptionIcon();					//�����p�A�C�R���ݒ菈���֐�.
	void RenderDescriptionIcon();					//�����p�A�C�R���`�揈���֐�.
	void GhostIconSetting(const int& IconMax);		//�������A�C�R���ݒ菈���֐�.
	void GimmickIconSetting(const int& IconMax);	//�M�~�b�N�A�C�R���ݒ菈���֐�.
	void PeopleIconSetting(const int& IconMax);		//�l�X�̃A�C�R���ݒ菈���֐�.

	//==================�ϐ�=======================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;				//�X�v���C�gUI.
	std::vector<CSpriteUI*>		m_pCDescriptionIcon;		//�����p�A�C�R��.
	std::vector<D3DXVECTOR3>	m_vIconPos;					//�A�C�R�����W.
	std::vector<D3DXVECTOR3>	m_vPos;						//���W.
	std::vector<D3DXVECTOR2>	m_vPattern;					//�p�^�[���ԍ�.
	unsigned int				m_TutorialFlag;				//�`���[�g���A���t���O.
	unsigned int				m_DescriptionFlag;			//�����t���O.
	bool						m_bAdvanceCommentFlag;		//�R�����g�i�߂�t���O.
	int							m_SelectMoveCount;			//�I���ړ��J�E���g.
	unsigned int				m_enStartLatestFlag;		//�J�n���O�t���O.
	bool						m_bDescriptionEnd;			//�I���t���O.
};

#endif	//#ifndef CSPEAK_TUTORIAL_H.