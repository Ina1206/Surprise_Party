#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"

/**********************************************
*		�r�b�O�S�[�X�g������ׂ�N���X.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================�֐�=======================//.
	void Update();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.

private:
	//======================�֐�========================//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.

	
};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.