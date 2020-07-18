#ifndef COBJECT_BASE_H
#define COBJECT_BASE_H

#include "..\CGameObject.h"
#include "..\..\Drawing\Sprite\CDepth_Stencil.h"

/********************************************
*		�I�u�W�F�N�g���N���X.
******************/
class CObjectBase
	: public CGameObject
{
public:
	CObjectBase();
	virtual ~CObjectBase();

	//====================�萔===================//.
	const float		ALPHA_MAX	= 1.0f;		//���ߒl�ő�l.
	const float		ALPHA_MIN	= 0.51f;	//���ߒl�ŏ��l.

	//====================�֐�===================//.
	void Render();		//�`�揈���֐�.


protected:
	//====================�ϐ�===================//.
	CDX9Mesh*			m_pCMesh;			//���b�V��.
	float				m_fAlpha;			//���ߒl.
	
private:
	//====================�ϐ�===================//.
	CDepth_Stencil*		m_pCDepthStenceil;	//�f�v�X�X�e���V��.
};

#endif	//#ifndef COBJECT_BASE_H.