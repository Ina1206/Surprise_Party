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
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//======================�֐�===========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CSURPRIES_EFFECT_H.