#ifndef COBJECT_BASE_H
#define COBJECT_BASE_H

#include "..\CGameObject.h"
#include "..\..\Drawing\Sprite\CDepth_Stencil.h"

/********************************************
*		オブジェクト基底クラス.
******************/
class CObjectBase
	: public CGameObject
{
public:
	CObjectBase();
	virtual ~CObjectBase();

	//====================定数===================//.
	const float		ALPHA_MAX	= 1.0f;		//透過値最大値.
	const float		ALPHA_MIN	= 0.51f;	//透過値最小値.

	//====================関数===================//.
	void Render();		//描画処理関数.


protected:
	//====================変数===================//.
	CDX9Mesh*			m_pCMesh;			//メッシュ.
	float				m_fAlpha;			//透過値.
	
private:
	//====================変数===================//.
	CDepth_Stencil*		m_pCDepthStenceil;	//デプスステンシル.
};

#endif	//#ifndef COBJECT_BASE_H.