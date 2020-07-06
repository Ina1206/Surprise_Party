#ifndef CSHOCKING_EFFECT_H
#define CSHOCKING_EFFECT_H

#include "..\CSpriteEffectBase.h"

/************************************
*		�Ռ��G�t�F�N�g�N���X.
**************/
class CShockingEffect
	: public CSpriteEffectBase
{
public:
	CShockingEffect();
	~CShockingEffect();

	//======================�֐�=========================//.
	void Update();			//�X�V�����֐�.
	
private:
	//======================�֐�=========================//.
	void Init();							//�����������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.
};

#endif //#ifndef CSHOCKING_EFFECT_H.