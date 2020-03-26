#ifndef CSURPRIES_EFFECT_H
#define CSURPRIES_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
class CSurpriseEffect
	: public CSpriteEffectBase
{
public:
	CSurpriseEffect();
	~CSurpriseEffect();

	//======================�֐�===========================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�Đ��J�n�����������֐�.

private:
	//======================�֐�===========================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.


};

#endif	//#ifndef CSURPRIES_EFFECT_H.