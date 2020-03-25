#include "CStageManager.h"

CStageManager::CStageManager()
	: m_pCStageBase			()
	, m_StageType			(0)
	, m_StageNum			(0)
	, m_enBeforeEndingType	(CMainStage::enBeforeStageEndigneType::Nothing)
	, m_pCStageFade			(nullptr)
	, m_FinishFlag			(0)
	, m_bOldTutorialFlag	(false)
{

}

CStageManager::~CStageManager()
{

}

//====================================.
//		初期化処理関数.
//====================================.
void CStageManager::Init()
{
	m_pCStageBase.resize(1);
	//ステージ初期設定.
	m_StageType = static_cast<int>(enStageType::GhostSpeakStage);
	m_pCStageBase[NORMAL_STAGE_NUM].reset(new CGhostSpeakStage(m_StageNum));

	//ステージフェードインスタンス化.
	m_pCStageFade.reset(new CStageFade());
}

//====================================.
//		更新処理関数.
//====================================.
void CStageManager::UpDate()
{
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

	//ステージフェード更新処理関数.
	m_pCStageFade->UpDate();

	if (m_pCStageFade->GetCurtainMoveFlag() & m_pCStageFade->CHANGE_STAGE_FLAG) {
		//ステージ変更処理関数.
		ChangeStage();
	}

	bool m_bControlFlag = true;
	//フェード中はステージ系処理をしない.
	if (m_pCStageFade->GetCurtainMoveFlag() != 0) {
		m_bControlFlag = false;
	}
	//ステージの更新処理関数.
	m_pCStageBase[STAGE_TYPE_NUM]->UpDate(m_bControlFlag);


#ifdef _DEBUG
	//デバッグ用ステージ変更処理関数.
	m_pCStageBase[STAGE_TYPE_NUM]->DebugStageChange();
#endif	//#ifdef _DEBUG.

	if (m_pCStageBase[STAGE_TYPE_NUM]->GetChangeStageFlag() == true ||
		m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() == true) {
		//
		if (m_StageType == static_cast<int>(enStageType::GhostSpeakStage)){
			if (m_bOldTutorialFlag == false) {
				m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->OPENING_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
				return;
			}
		}

		m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->CLOSE_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
	}

	//終了処理.
	if (m_pCStageBase[STAGE_TYPE_NUM]->GetFinishFlag() & m_pCStageBase[STAGE_TYPE_NUM]->FINISH_NEXT_ENDING) {
		m_FinishFlag = FINISH_NEXT_ENDING;
	}
}

//====================================.
//		描画処理関数.
//====================================.
void CStageManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos)
{
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

	//ステージの描画初期設定処理関数.
	m_pCStageBase[STAGE_TYPE_NUM]->RenderInitSetting(mView, mProj, vCameraPos);
	//ステージの描画処理関数.
	m_pCStageBase[STAGE_TYPE_NUM]->Render();

	//ステージフェード描画処理関数.
	m_pCStageFade->Render();
}

//====================================.
//		解放処理関数.
//====================================.
void CStageManager::Release()
{
	
}

//====================================.
//		ステージ変更処理関数.
//====================================.
void CStageManager::ChangeStage()
{
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

	if (m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() == true) {
		m_pCStageBase.emplace_back(new CTutorial());
		m_StageType = static_cast<int>(enStageType::Tutorial);
		return;
	}

	//ステージの種類変更.
	switch (static_cast<enStageType>(m_StageType)) {
	case enStageType::GhostSpeakStage:
		//次のステージへ.
		m_pCStageBase[STAGE_TYPE_NUM].reset(new CMainStage(m_StageNum, m_enBeforeEndingType));
		break;
	case enStageType::MainStage:
		m_enBeforeEndingType = m_pCStageBase[STAGE_TYPE_NUM]->GetBeforeStageEndingType();
		m_pCStageBase[STAGE_TYPE_NUM].reset(new CGhostSpeakStage(m_StageNum));
		m_StageNum++;
		break;
	}

	m_StageType++;
	if (m_StageType >= static_cast<int>(enStageType::NormalStageMax)) {
		m_StageType = static_cast<int>(enStageType::Start);
	}
}