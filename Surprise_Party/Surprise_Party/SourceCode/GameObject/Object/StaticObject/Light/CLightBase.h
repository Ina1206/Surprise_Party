#ifndef CLIGHT_BASE_H
#define CLIGHT_BASE_H

#include "..\CStaticObjectBase.h"
#include "..\..\Drawing\Resource\CResourceManager.h"	

/**********************************
*		���C�g���N���X.
*********/
class CLightBase
	: public CStaticObjectBase
{
public:
	CLightBase();
	virtual ~CLightBase();

	//====================�֐�=======================//.
	void Render();		//�`�揈���֐�.

	//==============���擾�����֐�=================//.
	LIGHT	GetLight() const { return m_stLight; }

protected:
	//====================�ϐ�=======================//.
	LIGHT	m_stLight;	//���C�g.

private:
};


#endif	//#ifndef CLIGHT_BASE_H.