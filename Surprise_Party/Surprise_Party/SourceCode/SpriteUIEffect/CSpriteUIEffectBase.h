#ifndef CSPRITEUI_EFFECT_BASE_H
#define CSPRITEUI_EFFECT_BASE_H

#include "..\Global.h"

/*****************************************
*	�X�v���C�gUI�G�t�F�N�g���N���X.
******************/
class CSpriteUIEffectBase
{
public:
	CSpriteUIEffectBase();
	virtual ~CSpriteUIEffectBase();

	//====================�֐�========================//.
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	
};

#endif	//#ifndef CSPRITEUI_EFFECT_BASE_H.