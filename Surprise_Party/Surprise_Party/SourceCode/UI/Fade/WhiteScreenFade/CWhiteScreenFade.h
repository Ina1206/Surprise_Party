#ifndef CWHITE_SCREEN_FADE_H
#define CWHITE_SCREEN_FADE_H

#include "..\CFade.h"

/******************************************
*		���X�N���[���t�F�[�h�N���X.
************/
class CWhiteScreenFade
	: public CFade
{
public:
	CWhiteScreenFade();
	~CWhiteScreenFade();

	//========================�֐�=========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//========================�֐�=========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CWHITE_SCREEN_FADE_H.