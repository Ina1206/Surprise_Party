#ifndef CENDING_WORK_GHOST_BASE_H
#define CENDING_WORK_GHOST_BASE_H

#include "..\CWorkGhostBase.h"

/**************************************************
*		エンディング働くお化け基底クラス.
********************/
class CEndingWorkGhostBase
	: public CWorkGhostBase
{
public:
	CEndingWorkGhostBase();
	virtual ~CEndingWorkGhostBase();

	
protected:
	//========================変数=============================//.
	float	m_fAcc;		//加速度.
private:

};

#endif	//#ifndef CENDING_WORK_GHOST_BASE_H.