#ifndef CHAVE_TROUBLE_EFFECT_H
#define CHAVE_TROUBLE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/******************************************
*		����G�t�F�N�g�N���X.
************/
class CHaveTroubleEffect
	: public CSpriteEffectBase
{
public:
	CHaveTroubleEffect();
	~CHaveTroubleEffect();

	//=================�֐�===================//.
	void Update();		//�X�V�����֐�.
	
private:
	//=================�֐�===================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CHAVE_TROUBLE_EFFECT_H.