#ifndef CSPEAK_WORK_GHOST_H
#define CSPEAK_WORK_GHOST_H

#include "..\CSpeakUI.h"

/*************************************
*		������������b�N���X.
************/
class CSpeakWorkGhost
	: public CSpeakUI
{
public:
	CSpeakWorkGhost();
	~CSpeakWorkGhost();

	//==================�萔====================//.
	const D3DXVECTOR3	BALLOON_POS				= D3DXVECTOR3(650.0f, 150.0f, 0.0f);	//�����o�����W.
	const D3DXVECTOR3	COMMENT_POS				= D3DXVECTOR3(690.0f, 250.0f, 0.0f);	//�R�����g���W.
	const D3DXVECTOR2	DISP_GHOST_BALLOON		= D3DXVECTOR2(0.0f, 0.0f);				//����邨���������o���̃p�^�[��.
	const D3DXVECTOR2	SWITCH_GHOST_BALLOON	= D3DXVECTOR2(1.0f, 0.0f);				//�X�C�b�`�����������o���p�^�[��.


	//==================�֐�====================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//============���u�������֐�==============//.
	void SetGhostTypeNum(const int& num) { m_GhostTypeNum = num; }

private:
	//==================�֐�====================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.
	void RenderBalloon();	//�����o���`�揈���֐�.
	void RenderComment();	//�R�����g�`�揈���֐�.

	//==================�ϐ�====================//.
	CSpriteUI*					m_pCBalloonSpriteUI;	//�X�v���C�gUI.
	std::vector<CSpriteUI*>		m_pCCommentSpriteUI;	//�R�����g�X�v���C�gUI.
	int							m_GhostTypeNum;			//�������̎�ޔԍ�.
	std::vector<D3DXVECTOR2>	m_vPatternNum;			//�p�^�[���ԍ�.	
};

#endif	//#ifndef CSPEAK_WORK_GHOST_H.