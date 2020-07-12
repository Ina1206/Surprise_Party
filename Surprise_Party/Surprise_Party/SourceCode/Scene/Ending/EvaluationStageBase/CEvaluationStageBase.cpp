#include "CEvaluationStageBase.h"

/**********************************************
*		�]���X�e�[�W���N���X.
************************/
CEvaluationStageBase::CEvaluationStageBase()
{

}

CEvaluationStageBase::CEvaluationStageBase(const int& EvaluationNum)
	: CEndingStageBase				(EvaluationNum)
	, m_pCSurpriseDegreeManager		(nullptr)
	, m_pCEvaluationUIManager		(nullptr)
	, m_pCPushEnterUI				(nullptr)
	, m_fPushEnterUIAlpha			(0.0f)
	, m_AlphaAddDecDirect			(1)
{
	//UI�̏����������֐�.
	InitUI();
}

CEvaluationStageBase::~CEvaluationStageBase()
{

}

//========================================.
//				�X�V�����֐�.		  
//========================================.
void CEvaluationStageBase::Update()
{
	//�J�����̍X�V�����֐�.
	m_pCCameraEnding->Update();

	if (m_UpdateFlag == 0) {
		//�t�F�[�h�X�V�����֐�.
		m_pCWhiteScreenFade->Update();

		//�t�F�[�h�I����ɋ������xUI�̏����J�n.
		if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
			m_UpdateFlag = SURPRISE_DEGREE_FLAG;
		}
		return;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_bDisplayAllAtOnce = true;
	}

	//���ʂ�UI�̍X�V�����֐�.
	UpdateCommonUI();
	
	if (m_UpdateFlag & GHOST_FLAG) {
		//�������̍X�V����.
		for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
			m_pCGhost[ghost]->Update();
		}
	}


}

//=========================================.
//				�`�揈���֐�.
//=========================================.
void CEvaluationStageBase::Render()
{
	//���̕`�揈���֐�.
	RenderFloor();

	//�������`�揈���֐�.
	RenderGhost();

	//����ʂ̃t�F�[�h�`��.
	if (!(m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG)) {
		m_pCWhiteScreenFade->Render();
		return;
	}

	//���ʂ�UI�̕`�揈���֐�.
	RenderCommonUI();

	//PushEnter�`�揈���֐�.
	RenderPushEnter();

}

//=========================================.
//		UI�̏����������֐�.
//=========================================.
void CEvaluationStageBase::InitUI()
{
	m_pCSurpriseDegreeManager = std::make_unique<CSurpriseDegreeManager>(m_Evaluation);
	m_pCEvaluationUIManager = std::make_unique<CEvaluationUIManager>(m_Evaluation);
}

//=========================================.
//		���ʂ�UI�̍X�V�����֐�.
//=========================================.
void CEvaluationStageBase::UpdateCommonUI()
{
	if (m_UpdateFlag & SURPRISE_DEGREE_FLAG) {

		m_pCSurpriseDegreeManager->SetDisplayAllAtOnce(m_bDisplayAllAtOnce);

		//�������x��UI�X�V�����֐�.
		m_pCSurpriseDegreeManager->Update();

		if (m_pCSurpriseDegreeManager->GetAllDispFlag() == true) {
			//�������ƕ]�������X�V�����t���O.
			m_UpdateFlag = EVALUATION_STRING_FLAG | GHOST_FLAG;
		}
		return;
	}

	if (m_UpdateFlag & EVALUATION_STRING_FLAG) {

		m_pCEvaluationUIManager->SetDispAllAtOnce(m_bDisplayAllAtOnce);

		//�]��UI�X�V�����֐�.
		m_pCEvaluationUIManager->Update();

		if(m_pCEvaluationUIManager->GetFinishedAllDispFlag() == true){
			//PushEnter�\���t���O.
			m_UpdateFlag = GHOST_FLAG | PUSH_ENTER_FLAG;
		}

	}
}

//=========================================.
//		���ʂ�UI�̕`�揈���֐�.
//=========================================.
void CEvaluationStageBase::RenderCommonUI()
{
	m_pCSurpriseDegreeManager->Render();
	m_pCEvaluationUIManager->Render();
}


//=========================================.
//		PushEnter�̍X�V�����֐�.
//=========================================.
void CEvaluationStageBase::UpdatePushEnter()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		m_bChangeStage = true;
	}

	m_fPushEnterUIAlpha += 0.05f * m_AlphaAddDecDirect;

	if (m_fPushEnterUIAlpha > ALPHA_MAX) {
		m_fPushEnterUIAlpha = ALPHA_MAX;
		m_AlphaAddDecDirect *= -1;
		return;
	}

	if (m_fPushEnterUIAlpha < ALPHA_MIN) {
		m_fPushEnterUIAlpha = ALPHA_MIN;
		m_AlphaAddDecDirect *= -1;
	}

}

//=========================================.
//		PushEnter�̕`�揈���֐�.
//=========================================.
void CEvaluationStageBase::RenderPushEnter()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCPushEnterUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::PushEnterString);
	m_pCPushEnterUI->SetAlpha(m_fPushEnterUIAlpha);
	m_pCPushEnterUI->SetScale(PUSH_ENTER_SCALE_MAX);
	m_pCPushEnterUI->SetPosition(PUSH_ENTER_POS);

	CDepth_Stencil* m_pCDeptshStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDeptshStencil->SetDepth(false);
	m_pCPushEnterUI->Render();
	m_pCDeptshStencil->SetDepth(true);

}
