#ifndef CSURPRISE_RAGREE_STRING_H
#define CSURPRISE_RAGREE_STRING_H

#include "..\SurpriseDegreeBase\CSurpriseDegreeBase.h"

/**********************************************
*		�������x���̓N���X.
*******************/
class CSurpriseDegreeString
	: public CSurpriseDegreeBase
{
public:
	
	CSurpriseDegreeString();
	~CSurpriseDegreeString();

	//========================�֐�================================//.
	void Update();		//�X�V�����֐�.

private:
	//========================�֐�================================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	
	//========================�ϐ�================================//.


};

#endif	//#ifndef CSURPRISE_RAGREE_STRING_H.