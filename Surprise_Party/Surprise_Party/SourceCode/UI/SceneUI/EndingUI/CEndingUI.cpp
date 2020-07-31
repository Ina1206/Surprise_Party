#include "CEndingUI.h"

/*******************************************
*		�G���f�B���OUI�N���X.
********************/
CEndingUI::CEndingUI()
	: CEndingUI	(0)
{

}

CEndingUI::CEndingUI(const int& EvaluationNum)
	: m_pCSurpriseDegreeManager	(nullptr)
	, m_pCEvaluationManager		(nullptr)
	, m_pCPushEnter				(nullptr)
	, m_UpdateUIFlag			(0)
	, m_bFinishEvaluationFlag	(false)
	, m_EvaluationNum			(EvaluationNum)
	, m_bDisplayAllAtOnce		(false)
	, m_bChangeSceneFlag		(false)
{
	//�����������֐�.
	Init();
}

CEndingUI::~CEndingUI()
{
	//��������֐�.
	Release();
}

//==============================================.
//		�X�V�����֐�.
//==============================================.
void CEndingUI::Update()
{
	if (m_UpdateUIFlag & PUSH_ENTER_FLAG) {
		//PushEnter�X�V�����֐�.
		UpdatePushEnter();
	}

	if (m_bDisplayAllAtOnce == false) {
		//��C�ɕ`�悷��t���O����.
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//�X�L�b�v���Đ�.
			if (m_bDisplayAllAtOnce == false) {
				m_pCPlaySoundManager->SetPlaySE(enSEType::Skip);
			}
			m_bDisplayAllAtOnce = true;
		}
	}

	if (m_UpdateUIFlag & SURPRISE_DEGREE_FLAG) {
		//�������x�X�V�����֐�.
		UpdateSurpriseDegree();
	}

	if (m_UpdateUIFlag & EVALUATION_FLAG) {
		//�]���X�V�����֐�.
		UpdateEvaluation();
	}
}

//==============================================.
//		�`�揈���֐�.
//==============================================.
void CEndingUI::Render()
{
	//�������x�`�揈���֐�.
	m_pCSurpriseDegreeManager->Render();
	//�]���`�揈���֐�.
	m_pCEvaluationManager->Render();
	//PushEnter�`�揈���֐�.
	m_pCPushEnter->Render();
}

//==============================================.
//		�����������֐�.
//==============================================.
void CEndingUI::Init()
{
	//�������x.
	m_pCSurpriseDegreeManager = std::make_unique<CSurpriseDegreeManager>(m_EvaluationNum);
	//�]��.
	m_pCEvaluationManager = std::make_unique<CEvaluationUIManager>(m_EvaluationNum);
	//PushEnter.
	m_pCPushEnter = std::make_unique<CPushEnter>();

	m_UpdateUIFlag = SURPRISE_DEGREE_FLAG;
}

//==============================================.
//		��������֐�.
//==============================================.
void CEndingUI::Release()
{

}

//===============================================.
//		�������x�X�V�����֐�.
//===============================================.
void CEndingUI::UpdateSurpriseDegree()
{
	//��C�ɕ`�悷��t���O.
	m_pCSurpriseDegreeManager->SetDisplayAllAtOnce(m_bDisplayAllAtOnce);
	//�X�V�����֐�.
	m_pCSurpriseDegreeManager->Update();
	if (m_pCSurpriseDegreeManager->GetAllDispFlag() == true) {
		m_UpdateUIFlag = EVALUATION_FLAG;
	}

}

//================================================.
//		�]���X�V�����֐�.
//================================================.
void CEndingUI::UpdateEvaluation()
{
	//��C�ɕ`�悷��t���O.
	m_pCEvaluationManager->SetDispAllAtOnce(m_bDisplayAllAtOnce);
	//�X�V�����֐�.
	m_pCEvaluationManager->Update();

	if (m_pCEvaluationManager->GetFinishedAllDispFlag() == true) {
		m_bFinishEvaluationFlag = true;
		m_UpdateUIFlag = PUSH_ENTER_FLAG;
	}
}

//==================================================.
//		PushEnter�X�V�����֐�.
//==================================================.
void CEndingUI::UpdatePushEnter()
{
	//�X�V�����֐�.
	m_pCPushEnter->Update();

	//���菈��.
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_bChangeSceneFlag = true;
		m_pCPlaySoundManager->SetPlaySE(enSEType::SelectDecide);
	}
}