#include "CDescriptionUIManager.h"

/*****************************************
*		����UI�Ǘ��N���X.
**************/
CDescriptionUIManager::CDescriptionUIManager()
	: m_pCArrow					(nullptr)
	, m_pCTutorialBlackScreen	(nullptr)
	, m_pCSpeakTutorial			(nullptr)
	, m_vCenterPos				(0.0f, 0.0f, 0.0f)
	, m_bRenderArrowFlag		(false)
{
	//�����������֐�.
	Init();
}

CDescriptionUIManager::~CDescriptionUIManager()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CDescriptionUIManager::Update()
{
	//�`���[�g���A����b.
	if (m_pCTutorialBlackScreen->GetFadeFlag() == 0) {
		m_pCSpeakTutorial->Update();
	}

	//���.
	m_pCArrow->SetUsingArrowFlag(SettingArrowFlag());
	if (m_pCArrow->GetUsingArrowFlag() != 0) {
		m_pCArrow->SetCenterPos(SettingArrowPos());
		m_pCArrow->Update();
	}

	//�����p�����.
	JudgeDescription();
	m_pCTutorialBlackScreen->SetCenterPos(m_vCenterPos);
	m_pCTutorialBlackScreen->Update();

}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CDescriptionUIManager::Render()
{
	if (m_pCTutorialBlackScreen->GetDispFlag() == true) {
		//�����p�����.
		m_pCTutorialBlackScreen->Render();
	}

	//�`���[�g���A����b.
	m_pCSpeakTutorial->Render();

	//���.
	if (m_pCArrow->GetUsingArrowFlag() != 0) {
		m_pCArrow->Render();
	}
	
}

//===========================================.
//		���S���W�ݒ菈���֐�.
//===========================================.
void CDescriptionUIManager::SetCenterPos(const D3DXVECTOR3& vGagePos, const D3DXVECTOR3& vTimePos)
{
	//�����t���O.
	const unsigned int DESCRIPTION_FLAG = m_pCSpeakTutorial->GetDescriptionFlag();

	if (DESCRIPTION_FLAG == m_pCSpeakTutorial->GAGE_DESCRIPTION_FLAG) {
		m_vCenterPos = vGagePos;
		return;
	}

	if (DESCRIPTION_FLAG == m_pCSpeakTutorial->CLOSE_TIME_DESCRIPTION_FLAG) {
		m_vCenterPos = vTimePos;
		return;
	}

	m_vCenterPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================================.
//		�����������֐�.
//===========================================.
void CDescriptionUIManager::Init()
{
	m_pCArrow.reset(new CArrow());
	m_pCTutorialBlackScreen.reset(new CTutorialBlackScreen());
	m_pCSpeakTutorial.reset(new CSpeakTutorial());

}

//===========================================.
//		��������֐�.
//===========================================.
void CDescriptionUIManager::Release()
{

}

//===========================================.
//		�����W�ݒ菈���֐�.
//===========================================.
D3DXVECTOR3 CDescriptionUIManager::SettingArrowPos()
{
	//�����t���O.
	const unsigned int DESCIPTION_FLAG = m_pCSpeakTutorial->GetDescriptionFlag();

	if (DESCIPTION_FLAG == m_pCSpeakTutorial->GAGE_DESCRIPTION_FLAG) {
		return GAGE_ARROW_POS + m_vCenterPos;
		//return D3DXVECTOR3(m_vCenterPos.x + 500.0f, m_vCenterPos.y - 30.0f, m_vCenterPos.z);
	}

	if (DESCIPTION_FLAG == m_pCSpeakTutorial->CLOSE_TIME_DESCRIPTION_FLAG) {
		return CLOSE_ARROW_POS + m_vCenterPos;
		//return D3DXVECTOR3(m_vCenterPos.x - 100.0f, m_vCenterPos.y, m_vCenterPos.z);
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================================.
//		���t���O�ݒ菈���֐�.
//============================================.
unsigned int CDescriptionUIManager::SettingArrowFlag()
{
	//�����t���O.
	const unsigned int DESCIPTION_FLAG = m_pCSpeakTutorial->GetDescriptionFlag();

	//�Q�[�W.
	if (DESCIPTION_FLAG == m_pCSpeakTutorial->GAGE_DESCRIPTION_FLAG) {
		return m_pCArrow->USING_LEFT_FLAG;
	}

	//�^�C��.
	if (DESCIPTION_FLAG == m_pCSpeakTutorial->CLOSE_TIME_DESCRIPTION_FLAG) {
		return m_pCArrow->USING_RIGHT_FLAG;
	}

	//�ړ���.
	const unsigned int ALL_SELECT_FLAG = SELECT_GHOST_FLAG | SELECT_GIMMICK_FLAG;
	if (m_pCSpeakTutorial->GetTutorialFlag() & ALL_SELECT_FLAG) {
		return m_pCArrow->USING_LEFT_FLAG | m_pCArrow->USING_RIGHT_FLAG;
	}


	return 0;
}

//=============================================.
//		�������菈���֐�.
//=============================================.
void CDescriptionUIManager::JudgeDescription()
{
	if (m_pCSpeakTutorial->GetDescriptionFlag() == 0) {
		m_pCTutorialBlackScreen->SetDescriptionFlag(false);
		return;
	}

	m_pCTutorialBlackScreen->SetDescriptionFlag(true);
}