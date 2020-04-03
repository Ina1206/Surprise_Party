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

private:
	//==================�֐�====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//==================�ϐ�====================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;
	std::vector<D3DXVECTOR3>	m_vPos;
};

#endif	//#ifndef CSPEAK_WORK_GHOST_H.