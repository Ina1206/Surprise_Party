#ifndef CSLEEP_EFFECT_H
#define CSLEEP_EFFECT_H

#include "..\CSpriteEffectBase.h"

/********************************************
*		�Q�Ă���G�t�F�N�g�N���X.
****************/
class CSleepEffect
	: public CSpriteEffectBase
{
public:
	CSleepEffect();
	~CSleepEffect();

	//===============�֐�=================//.
	void Update();		//�X�V�����֐�.

private:
	//===============�֐�=================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����f�����֐�.


};

#endif	//#ifndef CSLEEP_EFFECT_H.