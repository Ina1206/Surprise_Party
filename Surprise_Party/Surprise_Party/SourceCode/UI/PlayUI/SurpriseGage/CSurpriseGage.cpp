#include "CSurpriseGage.h"

CSurpriseGage::CSurpriseGage()
	: CSurpriseGage(0)
{

}

CSurpriseGage::CSurpriseGage(const int& StageNum)
	: m_pCFileResource		(CFileResource::GetResourceInstance())
	, m_SurprisePoint		(0)
	, m_SurprisePointMax	(0)
	, m_bSurprisePointMax	(false)
	, m_bBorusGetFlag		(false)
	, m_EvalutionFlag		(0)
	, m_StageNum			(StageNum)
	, m_bStumpSE			(false)
	, m_bExtensionSE		(false)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
{
	//初期化処理関数.
	Init();
}

CSurpriseGage::~CSurpriseGage()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CSurpriseGage::Update()
{
	if (m_SurprisePoint >= m_SurprisePointMax) {
		m_SurprisePoint = m_SurprisePointMax;
		m_bSurprisePointMax = true;

		//スタンプ表示処理関数.
		StampDisp();
	}

	const int FileNum = static_cast<int>(CFileResource::enStatusCharaType::Stage);
	const int Status = static_cast<int>(enScoreType::BornasTime);
	const int BornasTimeIndication = static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, m_StageNum, Status));
	if (m_SurprisePoint >= BornasTimeIndication) {
		//通知移動処理関数.
		InfomMove();
		
		m_bBorusGetFlag = true;
	}

	//驚きポイント評価処理関数.
	EvalutionSurprisePoint();

	m_vUIScale[GAGE_NUM].x = static_cast<float>(m_SurprisePoint) / static_cast<float>(m_SurprisePointMax);
}

//======================================.
//		驚きポイント追加処理関数.
//======================================.
void CSurpriseGage::AddSurprisePoint(int Point)
{
	m_SurprisePoint += Point;
}

//======================================.
//		初期化処理関数.
//======================================.
void CSurpriseGage::Init()
{
	//サイズ.
	m_pCSpriteUI.resize(UI_MAX);
	//初期設定処理関数.
	SettingInit();

	//初期化処理.
	m_vUIScale[STAMP_NUM]	= SCALE_MIN;

	m_fUIAlpha[INFOM_NUM]	= ALPHA_MIN;

	m_vUIPos[GAGE_GROUND_NUM]	= GAGE_GROUND_POS;
	m_vUIPos[GAGE_NUM]			= GAGE_POS;
	m_vUIPos[STAMP_NUM]			= STAMP_POS;
	m_vUIPos[INFOM_NUM]			= INFOM_POS;

	//アドレス取得処理.
	m_pCSpriteUI[GAGE_GROUND_NUM]	= m_pCResourceManager->GetSpriteUI(enSpriteUI::GageGround);
	m_pCSpriteUI[GAGE_NUM]			= m_pCResourceManager->GetSpriteUI(enSpriteUI::Gage);
	m_pCSpriteUI[STAMP_NUM]			= m_pCResourceManager->GetSpriteUI(enSpriteUI::ThankYouStamp);
	m_pCSpriteUI[INFOM_NUM]			= m_pCResourceManager->GetSpriteUI(enSpriteUI::ExtendedNotification);

	//驚かしポイント最大値の設定処理.
	const int FileNum		= static_cast<int>(CFileResource::enStatusCharaType::Stage);	//ファイル番号.
	const int StatusTypeNum = static_cast<int>(enScoreType::GageMax);															//ステータスタイプの番号.
	m_SurprisePointMax = static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, m_StageNum, StatusTypeNum));
}

//======================================.
//		解放処理関数.
//======================================.
void CSurpriseGage::Release()
{
	for (int ui = UI_MAX - 1; ui >= 0; ui--) {
		m_pCSpriteUI[ui] = nullptr;
	}
}

//=====================================.
//		スタンプ表示処理関数.
//=====================================.
void CSurpriseGage::StampDisp()
{
	
	if (m_bStumpSE == false) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::Stump);
		m_bStumpSE = true;
	}

	if (m_vUIScale[STAMP_NUM].x <= SCALE_MIN.x) {
		m_vUIScale[STAMP_NUM] = SCALE_MAX;
		return;
	}

	//規定値まで小さくなると終了.
	if (m_vUIScale[STAMP_NUM].x <= SHRINK_STOP_SCALE.x) {
		m_vUIScale[STAMP_NUM] = SHRINK_STOP_SCALE;
		return;
	}

	m_vUIScale[STAMP_NUM] -= SHRINK_SPEED;
}

//==========================================.
//		通知移動処理関数.
//==========================================.
void CSurpriseGage::InfomMove()
{
	m_vUIPos[INFOM_NUM].y += INFOM_MOVE_SPEED;

	if (m_bExtensionSE == false) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::ExtensionCheers);
		m_bExtensionSE = true;
	}

	//透過値を上げる処理.
	if (m_vUIPos[INFOM_NUM].y <= CHANGE_ALPHA_HEIGHT) {
		m_fUIAlpha[INFOM_NUM] += INFOM_ALPHA_SPEED;
		if (m_fUIAlpha[INFOM_NUM] >= ALPHA_MAX) {
			m_fUIAlpha[INFOM_NUM] = ALPHA_MAX;
		}
		return;
	}

	//透過値下げる処理.
	m_fUIAlpha[INFOM_NUM] -= INFOM_ALPHA_SPEED;
	if (m_fUIAlpha[INFOM_NUM] <= ALPHA_MIN) {
		m_fUIAlpha[INFOM_NUM] = ALPHA_MIN;
	}

}

//==========================================.
//		驚きポイント評価処理関数.
//==========================================.
void CSurpriseGage::EvalutionSurprisePoint()
{
	const int FileNum = static_cast<int>(CFileResource::enStatusCharaType::Stage);
	const int LowScore = static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, m_StageNum, static_cast<int>(enScoreType::LowScore)));
	if (m_SurprisePoint < LowScore) {
		m_EvalutionFlag = BAD_FLAG;
		return;
	}

	const int MediumScore = static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, m_StageNum, static_cast<int>(enScoreType::MediumScore)));
	if (m_SurprisePoint < MediumScore) {
		m_EvalutionFlag = GOOD_FLAG;
		return;
	}

	m_EvalutionFlag = GREAT_FLAG;
}