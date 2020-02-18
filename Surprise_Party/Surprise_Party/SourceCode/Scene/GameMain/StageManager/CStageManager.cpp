#include "CStageManager.h"

CStageManager::CStageManager()
	: m_pCStageBase			(nullptr)
	, m_StageType			(0)
	, m_StageNum			(0)
	, m_enBeforeEndingType	(CMainStage::enBeforeStageEndigneType::Nothing)
	, m_pCStageFade			(nullptr)
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
	//ステージ初期設定.
	m_StageType = static_cast<int>(enStageType::GhostSpeakStage);
	m_pCStageBase.reset(new CGhostSpeakStage(m_StageNum));

	//ステージフェードインスタンス化.
	m_pCStageFade.reset(new CStageFade());
}

//====================================.
//		更新処理関数.
//====================================.
void CStageManager::UpDate()
{
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
	m_pCStageBase->UpDate(m_bControlFlag);


#ifdef _DEBUG
	//デバッグ用ステージ変更処理関数.
	m_pCStageBase->DebugStageChange();
#endif	//#ifdef _DEBUG.

	if (m_pCStageBase->GetChangeStageFlag() == true) {
		//
		if (m_StageType == static_cast<int>(enStageType::GhostSpeakStage)) {
			m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->OPENING_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
			return;
		}

		m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->CLOSE_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
	}
}

//====================================.
//		描画処理関数.
//====================================.
void CStageManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos)
{
	//ステージの描画初期設定処理関数.
	m_pCStageBase->RenderInitSetting(mView, mProj, vLightPos, vCameraPos);
	//ステージの描画処理関数.
	m_pCStageBase->Render();

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
	//ステージの種類変更.
	switch (static_cast<enStageType>(m_StageType)) {
	case enStageType::GhostSpeakStage:
		//次のステージへ.
		m_StageNum++;
		m_pCStageBase.reset(new CMainStage(m_StageNum, m_enBeforeEndingType));
		break;
	case enStageType::MainStage:
		m_enBeforeEndingType = m_pCStageBase->GetBeforeStageEndingType();
		m_pCStageBase.reset(new CGhostSpeakStage(m_StageNum));
		break;
	}

	m_StageType++;
	if (m_StageType >= static_cast<int>(enStageType::Max)) {
		m_StageType = static_cast<int>(enStageType::Start);
	}
}