#ifndef CSURPRISE_RAGREE_STRING_H
#define CSURPRISE_RAGREE_STRING_H

#include "..\SurpriseRegreeBase\CSurpriseRegreeBase.h"

/**********************************************
*		�������x���̓N���X.
*******************/
class CSurpriseRegreeString
	: public CSurpriseRegreeBase
{
public:
	
	CSurpriseRegreeString();
	~CSurpriseRegreeString();

	//========================�֐�================================//.
	void Update();		//�X�V�����֐�.

private:
	//========================�֐�================================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	
	//========================�ϐ�================================//.


};

#endif	//#ifndef CSURPRISE_RAGREE_STRING_H.