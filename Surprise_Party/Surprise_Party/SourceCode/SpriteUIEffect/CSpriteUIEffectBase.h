#ifndef CSPRITEUI_EFFECT_BASE_H
#define CSPRITEUI_EFFECT_BASE_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Sprite\CDepth_Stencil.h"

/*****************************************
*	�X�v���C�gUI�G�t�F�N�g���N���X.
******************/
class CSpriteUIEffectBase
{
public:
	CSpriteUIEffectBase();
	virtual ~CSpriteUIEffectBase();

	//====================�萔========================//.
	const float	SCALE_MAX = 1.0f;	//�傫���ő�l.
	const float SCALE_MIN = 0.0f;	//�傫���ŏ��l.
	const float	ALPHA_MAX = 1.0f;	//���ߒl�ő�l.
	const float ALPHA_MIN = 0.0f;	//���ߒl�ŏ��l.

	//====================�֐�========================//.
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	//====================�ϐ�========================//.
	CResourceManager*	m_pCResourceManager;	//�ǂݍ��݊Ǘ��N���X.
	CDepth_Stencil*		m_pCDepthStencil;		//�f�v�X�X�e���V��.
};

#endif	//#ifndef CSPRITEUI_EFFECT_BASE_H.