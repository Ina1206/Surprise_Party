#ifndef _CDX9BASE_H
#define _CDX9BASE_H

#include "..\..\Global.h"

/***************************************
*	DirectX9Draw���N���X.
***************/
class CDX9Base
{
public:
	CDX9Base();
	virtual ~CDX9Base();

	//ײď��.
	struct LIGHT
	{
		D3DXVECTOR3	vPos;			//�ʒu.
		D3DXVECTOR3	vDir;			//����.
		D3DXMATRIX	mRot;			//��]�s��.
		float		fIntensity;		//���x(���邳).
		float		m_fLightWidth;	//���̍L��.
	};

protected:

};

#endif	//#ifndef _CDX9BASE_H.