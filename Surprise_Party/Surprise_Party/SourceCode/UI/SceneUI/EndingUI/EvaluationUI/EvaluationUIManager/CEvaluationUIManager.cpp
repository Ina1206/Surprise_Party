#include "CEvaluationUIManager.h"
#include "..\HightEvaluationString\CHightEvaluationString.h"
#include "..\IntermediateEvaluationString\CIntermediateEvaluationString.h"
#include "..\LowEvaluationString\CLowEvaluationString.h"

/*********************************************
*		評価UIの管理クラス.
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
	//初期化処理関数.
	Init();
}

CEvaluationUIManager::~CEvaluationUIManager()
{

}

//==========================================.
//		更新処理関数.
//==========================================.
void CEvaluationUIManager::Update()
{
	//すべてを表示するクラス.
	m_pCEvaluationUIBase->SetDisplayAllAtOnce(m_bDisplayAllAtOnce);
	//更新処理関数.
	m_pCEvaluationUIBase->Update();
	m_bFinishedAllDispFlag = m_pCEvaluationUIBase->GetFinishedAllDispFlag();
}

//==========================================.
//		描画処理関数.
//==========================================.
void CEvaluationUIManager::Render()
{
	m_pCEvaluationUIBase->Render();
}

//==========================================.
//		初期化処理関数.
//==========================================.
void CEvaluationUIManager::Init()
{
	//評価UIの種類決定.
	m_pCEvaluationUIBase = DecideEvaluationUIType();
}

//==========================================.
//		評価UIの種類決定処理関数.
//==========================================.
std::unique_ptr<CEvaluationUIBase> CEvaluationUIManager::DecideEvaluationUIType()
{
	if (m_EvaluationNum == LOW_EVALUATION_NUM) {
		return std::make_unique<CLowEvaluationString>();
	}

	if (m_EvaluationNum == INTERMEDIATE_EVALUATION_NUM) {
		return std::make_unique<CIntermediateEvaluationString>();
	}

	return std::make_unique<CHightEvaluationString>();
}