#ifndef CENDING_DISP_GHOST_H
#define CENDING_DISP_GHOST_H

#include "..\CEndingWorkGhostBase.h"

/******************************************
*		�G���f�B���O�̌���邨�����N���X.
**************/
class CEndingDispGhost
	: public CEndingWorkGhostBase
{
public:
	CEndingDispGhost();
	~CEndingDispGhost();

	//======================�֐�=======================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//======================�֐�=======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.



};

#endif	//#ifndef CENDING_DISP_GHOST_H.