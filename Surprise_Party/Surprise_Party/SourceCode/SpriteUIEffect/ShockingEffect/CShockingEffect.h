#ifndef CSHOCKING_EFFECT_H
#define CSHOCKING_EFFECT_H

#include "..\CSpriteUIEffectBase.h"

/*************************************
*		�Ռ��G�t�F�N�g�N���X.
****************/
class CShockingEffect
	: public CSpriteUIEffectBase
{
public:
	CShockingEffect();
	~CShockingEffect();

	//======================�֐�============================//.
	void Update();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.

private:
	//======================�ϐ�============================//.
	

};

#endif	//#ifndef CSHOCKING_EFFECT_H.