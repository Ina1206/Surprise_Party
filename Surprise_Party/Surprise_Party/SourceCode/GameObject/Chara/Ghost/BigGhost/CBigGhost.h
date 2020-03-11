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
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void WakeUp();				//�N�������֐�.
	void HaveTroubleEmotion();	//���銴����֐�.
	void RejoiceEmotion();		//��Ԋ�����֐�.
	void Sleep();				//�Q�鏈���֐�.

};


#endif	//#ifndef CBIG_GHOST_H.