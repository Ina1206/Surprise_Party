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

	//================���u�������֐�======================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

private:
	//======================�֐�============================//.
	void Init();	//�����������֐�.

	//======================�ϐ�============================//.
	CSpriteUI*	m_pCSpriteUI;	//�X�v���C�gUI.
	D3DXVECTOR3 m_vPos;			//���W.
	D3DXVECTOR3 m_vCenterPos;	//�����̍��W.
	float		m_fAlpha;		//���ߒl.
	float		m_fScale;		//�傫��.

};

#endif	//#ifndef CSHOCKING_EFFECT_H.