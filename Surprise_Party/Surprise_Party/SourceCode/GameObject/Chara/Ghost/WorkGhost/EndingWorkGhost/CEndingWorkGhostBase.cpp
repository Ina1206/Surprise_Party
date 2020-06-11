#include "CEndingWorkGhostBase.h"

/**************************************************
*		エンディング働くお化け基底クラス.
********************/
CEndingWorkGhostBase::CEndingWorkGhostBase()
	: m_fAcc	(0.0f)
{

}

CEndingWorkGhostBase::~CEndingWorkGhostBase()
{

}

//==========================================.
//		ジャンプ処理関数.
//==========================================.
void CEndingWorkGhostBase::Jump()
{
	m_fAcc -= m_fAccSpeed;
	m_vPos.y += m_fAcc - m_fGravity;


	if (m_vPos.y < m_vChangeBeforePos.y) {
		m_vPos.y = m_vChangeBeforePos.y;
		m_fAcc = m_fAccMax;
	}
}