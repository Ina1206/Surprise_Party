#ifndef CLIGHT_BASE_H
#define CLIGHT_BASE_H

#include "..\CStaticObjectBase.h"
#include "..\..\Drawing\Resource\CResourceManager.h"	

/**********************************
*		ライト基底クラス.
*********/
class CLightBase
	: public CStaticObjectBase
{
public:
	CLightBase();
	virtual ~CLightBase();

	//====================関数=======================//.
	void Render();		//描画処理関数.

	//==============情報取得処理関数=================//.
	LIGHT	GetLight() const { return m_stLight; }

protected:
	//====================変数=======================//.
	LIGHT	m_stLight;	//ライト.

private:
};


#endif	//#ifndef CLIGHT_BASE_H.