#ifndef CSPRITE_EFFECT_BASE_H
#define CSPRITE_EFFECT_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\..\Global.h"

/*********************************************
*		�X�v���C�g�̃G�t�F�N�g���N���X.
********/
class CSpriteEffectBase
{
public:
	CSpriteEffectBase();
	virtual ~CSpriteEffectBase();

	//================�֐�====================//.
	virtual void Update() = 0;																				//�X�V�����֐�.
	void	Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//�`�揈���֐�.

	//==========���u�������֐�==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }		//�������W.

protected:
	//================�֐�====================//.
	virtual void Init() = 0;		//�����������֐�.
	virtual void Release() = 0;		//��������֐�.

	//================�ϐ�====================//.
	std::vector<CSprite*>		m_pCSprite;		//�X�v���C�g�N���X.
	std::vector<D3DXVECTOR3>	m_vPos;			//���W.
	std::vector<D3DXVECTOR3>	m_vRot;			//�p�x.
	std::vector<D3DXVECTOR3>	m_vScale;		//�傫��.
	D3DXVECTOR3					m_vCenterPos;	//�������W.

private:

};

#endif	//#ifndef CSPRITE_EFFECT_BASE_H.