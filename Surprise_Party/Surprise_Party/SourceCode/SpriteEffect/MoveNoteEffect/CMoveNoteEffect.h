#ifndef CMOVE_NOTE_EFFECT_H
#define CMOVE_NOTE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*************************************
*	�����ړ��G�t�F�N�g�N���X.
*************/
class CMoveNoteEffect
	: public CSpriteEffectBase
{
public:
	CMoveNoteEffect();
	~CMoveNoteEffect();

	//=================�֐�====================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�G�t�F�N�g�J�n�����������֐�.

private:
	//=================�֐�====================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.


};


#endif	//#ifndef CMOVE_NOTE_EFFECT_H.