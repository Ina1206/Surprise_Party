#ifndef CFRONTSTAGE_LIGHT_H
#define CFRONTSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*********************************
*		�\����̃��C�g�N���X.
*************/
class CFrontstageLight
	: public CLightBase
{
public:
	CFrontstageLight();
	~CFrontstageLight();

	//======================�֐�========================//.
	void Update();		//�X�V�����֐�.

private:
	//======================�֐�========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CFRONTSTAGE_LIGHT_H.