#ifndef CBACKSTAGE_LIGHT_H
#define CBACKSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*******************************************
*		���䗠�̃��C�g�N���X.
************/
class CBackstageLight
	: public CLightBase
{
public:
	CBackstageLight();
	~CBackstageLight();

	//=======================�֐�==========================//.
	void Update();		//�X�V�����֐�.

private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CBACKSTAGE_LIGHT_H.