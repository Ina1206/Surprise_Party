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

	//=================�萔===================//.
	const int			SPRITE_MAX		= 6;								//�X�v���C�g�ő吔.
	const D3DXVECTOR3	INT_LOCAL_POS	= D3DXVECTOR3(2.0f, 1.6f, 0.0f);	//�����̃��[�J�����W.

	//=================�֐�===================//.
	void Update();		//�X�V�����֐�.
	
private:
	//=================�֐�===================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CHAVE_TROUBLE_EFFECT_H.