#include "CDescriptionUIManager.h"

/*****************************************
*		説明UI管理クラス.
**************/
CDescriptionUIManager::CDescriptionUIManager()
	: m_pCArrow					(nullptr)
	, m_pCTutorialBlackScreen	(nullptr)
	, m_pCSpeakTutorial			(nullptr)
	, m_vCenterPos				(0.0f, 0.0f, 0.0f)
	, m_bRenderArrowFlag		(false)
{
	//初期化処理関数.
	Init();
}

CDescriptionUIManager::~CDescriptionUIManager()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		更新処理関数.
//==========================================.
void CDescriptionUIManager::Update()
{
	//チュートリアル会話.
	if (m_pCTutorialBlackScreen->GetFadeFlag() == 0) {
		m_pCSpeakTutorial->Update();
	}

	//矢印.
	m_pCArrow->SetUsingArrowFlag(SettingArrowFlag());
	if (m_pCArrow->GetUsingArrowFlag() != 0) {
		m_pCArrow->SetCenterPos(SettingArrowPos());
		m_pCArrow->Update();
	}

	//説明用黒画面.
	JudgeDescription();
	m_pCTutorialBlackScreen->SetCenterPos(m_vCenterPos);
	m_pCTutorialBlackScreen->Update();

}

//==========================================.
//		描画処理関数.
//==========================================.
void CDescriptionUIManager::Render()
{
	if (m_pCTutorialBlackScreen->GetDispFlag() == true) {
		//説明用黒画面.
		m_pCTutorialBlackScreen->Render();
	}

	//チュートリアル会話.
	m_pCSpeakTutorial->Render();

	//矢印.
	if (m_pCArrow->GetUsingArrowFlag() != 0) {
		m_pCArrow->Render();
	}
	
}

//===========================================.
//		中心座標設定処理関数.
//===========================================.
void CDescriptionUIManager::SetCenterPos(const D3DXVECTOR3& vGagePos, const D3DXVECTOR3& vTimePos)
{
	//説明フラグ.
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
//		初期化処理関数.
//===========================================.
void CDescriptionUIManager::Init()
{
	m_pCArrow.reset(new CArrow());
	m_pCTutorialBlackScreen.reset(new CTutorialBlackScreen());
	m_pCSpeakTutorial.reset(new CSpeakTutorial());

}

//===========================================.
//		解放処理関数.
//===========================================.
void CDescriptionUIManager::Release()
{

}

//===========================================.
//		矢印座標設定処理関数.
//===========================================.
D3DXVECTOR3 CDescriptionUIManager::SettingArrowPos()
{
	//説明フラグ.
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
//		矢印フラグ設定処理関数.
//============================================.
unsigned int CDescriptionUIManager::SettingArrowFlag()
{
	//説明フラグ.
	const unsigned int DESCIPTION_FLAG = m_pCSpeakTutorial->GetDescriptionFlag();

	//ゲージ.
	if (DESCIPTION_FLAG == m_pCSpeakTutorial->GAGE_DESCRIPTION_FLAG) {
		return m_pCArrow->USING_LEFT_FLAG;
	}

	//タイム.
	if (DESCIPTION_FLAG == m_pCSpeakTutorial->CLOSE_TIME_DESCRIPTION_FLAG) {
		return m_pCArrow->USING_RIGHT_FLAG;
	}

	//移動時.
	const unsigned int ALL_SELECT_FLAG = SELECT_GHOST_FLAG | SELECT_GIMMICK_FLAG;
	if (m_pCSpeakTutorial->GetTutorialFlag() & ALL_SELECT_FLAG) {
		return m_pCArrow->USING_LEFT_FLAG | m_pCArrow->USING_RIGHT_FLAG;
	}


	return 0;
}

//=============================================.
//		説明判定処理関数.
//=============================================.
void CDescriptionUIManager::JudgeDescription()
{
	if (m_pCSpeakTutorial->GetDescriptionFlag() == 0) {
		m_pCTutorialBlackScreen->SetDescriptionFlag(false);
		return;
	}

	m_pCTutorialBlackScreen->SetDescriptionFlag(true);
}