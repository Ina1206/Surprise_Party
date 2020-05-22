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

	//=================�萔====================//.
	const unsigned int SCALE_FLAG		= (1 << 0);	//�g��t���O.
	const unsigned int SCALE_DOWN_FLAG	= (1 << 1);	//�k���t���O.

	//=================�֐�====================//.
	void Update();									//�X�V�����֐�.
	void PlayStartInit(const int& num);				//�G�t�F�N�g�J�n�����������֐�.

private:
	//=================�֐�====================//.
	void Init();									//�����������֐�.
	void Release();									//��������֐�.
	void AppeartJudgement(const int& num);			//�\�����菈���֐�.
	void Move(const int& num);						//�ړ������֐�.

	//=================�ϐ�====================//.
	std::vector<unsigned int> m_ScalingFlag;		//�g��k���t���O.
};


#endif	//#ifndef CMOVE_NOTE_EFFECT_H.