#include "CEvaluationUIManager.h"
#include "..\HightEvaluationString\CHightEvaluationString.h"
#include "..\IntermediateEvaluationString\CIntermediateEvaluationString.h"

/*********************************************
*		�]��UI�̊Ǘ��N���X.
********************/
CEvaluationUIManager::CEvaluationUIManager()
{
	
}

CEvaluationUIManager::CEvaluationUIManager(const int& EvaluationNum)
	: m_pCEvaluationUIBase	(nullptr)
	, m_EvaluationNum		(EvaluationNum)
	, m_bFinishedAllDispFlag(false)
	, m_bDisplayAllAtOnce	(false)
{
	//�����������֐�.
	Init();
}

CEvaluationUIManager::~CEvaluationUIManager()
{

}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CEvaluationUIManager::Update()
{
	m_pCEvaluationUIBase->Update();
}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CEvaluationUIManager::Render()
{
	m_pCEvaluationUIBase->Render();
}

//==========================================.
//		�����������֐�.
//==========================================.
void CEvaluationUIManager::Init()
{
	m_pCEvaluationUIBase = DecideEvaluationUIType();
}

//==========================================.
//		�]��UI�̎�ތ��菈���֐�.
//==========================================.
std::unique_ptr<CEvaluationUIBase> CEvaluationUIManager::DecideEvaluationUIType()
{
	if (m_EvaluationNum == 1) {
		return std::make_unique<CIntermediateEvaluationString>();
	}

	return std::make_unique<CHightEvaluationString>();
}