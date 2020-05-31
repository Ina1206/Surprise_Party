#ifndef CQUESTION_EFFECT_H
#define CQUESTION_EFFECT_H

#include "..\CSpriteEffectBase.h"

/************************************
*		�^��G�t�F�N�g�N���X.
***************/
class CQuestionEffect
	: public CSpriteEffectBase
{
public:
	CQuestionEffect();
	~CQuestionEffect();

	//====================�֐�========================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�G�t�F�N�g�J�n�����������֐�.

private:
	//====================�֐�========================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.

};

#endif	//#ifndef CQUESTION_EFFECT_H.