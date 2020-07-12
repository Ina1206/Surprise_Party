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

	//========================�萔================================//.
	const D3DXVECTOR3 INIT_POS		= D3DXVECTOR3(0.0f, 560.0f, 0.0f);	//�������W.
	const D3DXVECTOR3 FINISH_POS	= D3DXVECTOR3(0.0f, 430.0f, 0.0f);	//�ŏI���W.

	//========================�֐�================================//.
	void Update();		//�X�V�����֐�.

private:
	//========================�֐�================================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	
	//========================�ϐ�================================//.


};

#endif	//#ifndef CSURPRISE_RAGREE_STRING_H.