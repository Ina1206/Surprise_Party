#include "CStageManager.h"

/**************************************************
*		ステージ管理クラス.
********/
CStageManager::CStageManager()
	: m_pCStageBase			()
	, m_StageType			(0)
	, m_StageNum			(0)
	, m_enBeforeEndingType	(CMainStage::enBeforeStageEndigneType::Nothing)
	, m_pCStageFade			(nullptr)
	, m_FinishFlag			(0)
	, m_bOldTutorialFlag	(false)
	, m_AllEndingType		(0)
	, m_bPauseFlag			(false)
	, m_pCPlaySoundManager	(nullptr)
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
	m_StageType = static_cast<int>(CStageBase::enStageType::GhostSpeakStage);
	m_pCStageBase[NORMAL_STAGE_NUM].reset(new CGhostSpeakStage(m_StageNum, m_enBeforeEndingType));

	//ステージフェードインスタンス化.
	m_pCStageFade.reset(new CStageFade());

	//曲.
	m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();
}

//====================================.
//		更新処理関数.
//====================================.
void CStageManager::UpDate()
{

	//ステージフェード更新処理関数.
	m_pCStageFade->Update();

	//BGMの音量調整処理.
	if (m_FinishFlag == 0) {
		const int BGM_VOLUME = static_cast<int>(m_pCPlaySoundManager->VOLUME_MAX * m_pCStageFade->GetDistanceRatio());
		m_pCPlaySoundManager->SetPlayingBGMVolume(BGM_VOLUME);
	}

	if (m_pCStageFade->GetCurtainMoveFlag() & m_pCStageFade->CHANGE_STAGE_FLAG) {
		//ステージ変更処理関数.
		ChangeStage();
	}
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

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
		m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() != m_bOldTutorialFlag) {
		if (m_StageType == static_cast<int>(CStageBase::enStageType::GhostSpeakStage)){
			if (m_bOldTutorialFlag == 0 || m_bOldTutorialFlag & m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_FINISH) {
				//開店時のカーテンの動き.
				m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->OPENING_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
				return;
			}
		}
		//閉店時のカーテンの動き.
		m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->CLOSE_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
	}

	//終了処理.
	if (m_pCStageBase[STAGE_TYPE_NUM]->GetFinishFlag() & m_pCStageBase[STAGE_TYPE_NUM]->FINISH_NEXT_ENDING) {
		m_FinishFlag = FINISH_NEXT_ENDING;
	}
	if (m_pCStageBase[STAGE_TYPE_NUM]->GetFinishFlag() & m_pCStageBase[STAGE_TYPE_NUM]->FINISH_NEXT_TITLE) {
		m_FinishFlag = FINISH_NEXT_TITLE;
	}
}

//====================================.
//		描画処理関数.
//====================================.
void CStageManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj)
{
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

	//ポーズフラグ.
	m_pCStageBase[STAGE_TYPE_NUM]->SetPauseFlag(m_bPauseFlag);

	//ステージの描画初期設定処理関数.
	m_pCStageBase[STAGE_TYPE_NUM]->RenderInitSetting(mView, mProj);
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

	if (m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() & m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_START) {
		//チュートリアルステージ番号.
		const int TUTORIAL_STAGE_NUM = 5;
		m_pCStageBase.emplace_back(new CMainStage(TUTORIAL_STAGE_NUM, CStageBase::enStageType::Tutorial, m_enBeforeEndingType));
		m_StageType = static_cast<int>(CStageBase::enStageType::Tutorial);
		m_bOldTutorialFlag = m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_START;

		//曲設定.
		m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::GameMain);
		return;
	}

	if (m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() & m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_FINISH) {
		if (m_pCStageBase.size() >= NORMAL_STAGE_MAX) {
			m_pCStageBase.pop_back();
			m_bOldTutorialFlag = m_pCStageBase[NORMAL_STAGE_NUM]->TUTORIAL_FINISH;
			m_StageType = static_cast<int>(CStageBase::enStageType::GhostSpeakStage);
			m_pCStageBase[NORMAL_STAGE_NUM]->SetTutorialFlag(m_pCStageBase[NORMAL_STAGE_NUM]->TUTORIAL_FINISH);

			//曲設定.
			m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::GhostSpeakStage);
			return;
		}
	}
	if (m_StageType == static_cast<int>(CStageBase::enStageType::Tutorial)) {
		return;
	}

	//3ステージ以上の場合は終了処理.
	if (m_StageNum >= ALL_STAGE_MAX) {
		m_FinishFlag = FINISH_NEXT_ENDING;
		return;
	}

	//ステージの種類変更.
	switch (static_cast<CStageBase::enStageType>(m_StageType)) {
	case CStageBase::enStageType::GhostSpeakStage:
		//次のステージへ.
		m_pCStageBase[STAGE_TYPE_NUM].reset(new CMainStage(m_AllEndingType, CStageBase::enStageType::GhostSpeakStage , m_enBeforeEndingType));
		m_bOldTutorialFlag = 0;
		//曲設定.
		m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::GameMain);
		break;
	case CStageBase::enStageType::MainStage:
		m_enBeforeEndingType = m_pCStageBase[STAGE_TYPE_NUM]->GetBeforeStageEndingType();
		//ゲームエンディング加算.
		m_AllEndingType += static_cast<int>(m_enBeforeEndingType);
		m_StageNum++;
		m_pCStageBase[STAGE_TYPE_NUM].reset(new CGhostSpeakStage(m_StageNum, m_enBeforeEndingType));
		//曲設定.
		m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::GhostSpeakStage);
		break;
	}

	m_StageType++;
	if (m_StageType >= static_cast<int>(CStageBase::enStageType::NormalStageMax)) {
		m_StageType = static_cast<int>(CStageBase::enStageType::Start);
	}
}