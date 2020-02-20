#ifndef _CDX9BASE_H
#define _CDX9BASE_H

#include "..\..\Global.h"

/***************************************
*	DirectX9Draw基底クラス.
***************/
class CDX9Base
{
public:
	CDX9Base();
	virtual ~CDX9Base();

	//ﾗｲﾄ情報.
	struct LIGHT
	{
		D3DXVECTOR3	vPos;			//位置.
		D3DXVECTOR3	vDir;			//方向.
		D3DXMATRIX	mRot;			//回転行列.
		float		fIntensity;		//強度(明るさ).
		float		m_fLightWidth;	//光の広さ.
	};

protected:

};

#endif	//#ifndef _CDX9BASE_H.