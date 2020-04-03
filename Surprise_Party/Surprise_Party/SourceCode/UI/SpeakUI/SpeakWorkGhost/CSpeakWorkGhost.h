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
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//==================�ϐ�====================//.
	CSpriteUI*		m_pCSpriteUI;	//�X�v���C�gUI.
	D3DXVECTOR3		m_vPos;			//���W.
	int				m_GhostTypeNum;	//�������̎�ޔԍ�.
};

#endif	//#ifndef CSPEAK_WORK_GHOST_H.