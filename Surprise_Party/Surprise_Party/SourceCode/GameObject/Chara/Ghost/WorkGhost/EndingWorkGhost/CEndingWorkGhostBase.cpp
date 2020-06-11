#include "CEndingWorkGhostBase.h"
#include "..\..\SpriteEffect\RejoiceEffect\CRejoiceEffect.h"

/**************************************************
*		�G���f�B���O�������������N���X.
********************/
CEndingWorkGhostBase::CEndingWorkGhostBase()
	: m_pCSpriteEffect	(nullptr)
	, m_fAcc			(0.0f)
	, m_fAccSpeed		(0.0f)
	, m_fAccMax			(0.0f)
	, m_fGravity		(0.0f)
	, m_OldEmotionNum	(static_cast<int>(enEmotionType::Nothing))
{

}

CEndingWorkGhostBase::~CEndingWorkGhostBase()
{

}

//==========================================.
//		�W�����v�����֐�.
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

//===========================================.
//		�G�t�F�N�g�ύX�����֐�.
//===========================================.
void CEndingWorkGhostBase::ChangeEffect()
{
	if (m_OldEmotionNum == m_EmotionNum) {
		return;
	}

	m_OldEmotionNum = m_EmotionNum;

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		m_pCSpriteEffect.reset(new CRejoiceEffect());
		return;
	}
}