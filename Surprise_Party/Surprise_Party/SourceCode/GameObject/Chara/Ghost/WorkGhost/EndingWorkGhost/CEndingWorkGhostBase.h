#ifndef CENDING_WORK_GHOST_BASE_H
#define CENDING_WORK_GHOST_BASE_H

#include "..\CWorkGhostBase.h"

/**************************************************
*		�G���f�B���O�������������N���X.
********************/
class CEndingWorkGhostBase
	: public CWorkGhostBase
{
public:
	CEndingWorkGhostBase();
	virtual ~CEndingWorkGhostBase();

	
protected:
	//========================�ϐ�=============================//.
	float	m_fAcc;		//�����x.
private:

};

#endif	//#ifndef CENDING_WORK_GHOST_BASE_H.