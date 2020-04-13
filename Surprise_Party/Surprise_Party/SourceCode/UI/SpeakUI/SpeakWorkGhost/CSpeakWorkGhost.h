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
	D3DXVECTOR3					m_vPos;					//���W.
	int							m_GhostTypeNum;			//�������̎�ޔԍ�.
	std::vector<D3DXVECTOR2>	m_vPatternNum;			//�p�^�[���ԍ�.	
};

#endif	//#ifndef CSPEAK_WORK_GHOST_H.