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
	//========================関数=============================//.
	void Jump();		//ジャンプ処理関数.

	//========================変数=============================//.
	float	m_fAcc;		//加速度.
	float	m_fAccSpeed;//加速度加算速度.
	float	m_fAccMax;	//加速度最大値.
	float	m_fGravity;	//重力.

private:

};

#endif	//#ifndef CENDING_WORK_GHOST_BASE_H.