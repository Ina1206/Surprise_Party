#ifndef CBIG_GHOST_H
#define CBIG_GHOST_H

#include "..\CGhostBase.h"

/******************************************
*		�傫���������N���X.
**********/
class CBigGhost
	: public CGhostBase
{
public:
	CBigGhost();
	~CBigGhost();

	//=================�֐�====================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���Ȑ�.

private:
	//=================�֐�====================//.
	void Init();		//�����������֐�.
	void Release();		//�����������֐�.


};


#endif	//#ifndef CBIG_GHOST_H.