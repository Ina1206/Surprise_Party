#ifndef CUI_H
#define CUI_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Sprite\CDepth_Stencil.h"

/*************************************
*		UI�N���X.
*****/
class CUI
{
public:
	CUI();
	virtual ~CUI();

	//=====================�萔=========================//.
	const float	ALPHA_MAX		= 1.0f;			//���ߒl�ő�l.
	const float	UI_INIT_SCALE	= 1.0f;			//�����̑傫��.

	//=====================�֐�=========================//.
	virtual void Render() = 0;		//�`�揈���֐�.

protected:
	//=====================�֐�=========================//.
	virtual void Init() = 0;		//�����������֐�.
	virtual void Release() = 0;		//��������֐�.

	//=====================�ϐ�=========================//.
	CResourceManager*	m_pCResourceManager;//�ǂݍ��݊Ǘ��N���X.
	CDepth_Stencil*		m_pCDepthStencil;	//�f�v�X�X�e���V���N���X.
	D3DXVECTOR3			m_vPos;				//���W.
	D3DXVECTOR3			m_vRot;				//�p�x.
	float				m_fScale;			//�傫��.
	float				m_fAlpha;			//���ߒl.
};

#endif	//#ifndef CUI_H.