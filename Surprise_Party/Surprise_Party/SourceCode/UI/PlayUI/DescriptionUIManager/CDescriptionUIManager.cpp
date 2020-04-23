#include "CDescriptionUIManager.h"

/*****************************************
*		説明UI管理クラス.
**************/
CDescriptionUIManager::CDescriptionUIManager()
	: m_pCArrow					(nullptr)
	, m_pCTutorialBlackScreen	(nullptr)
	, m_pCSpeakTutorial			(nullptr)
	, m_vCenterPos				(0.0f, 0.0f, 0.0f)
	, m_bRenderBothArrowFlag	(false)
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
	//チュートリアル会話更新処理関数.
	m_pCSpeakTutorial->Update();

	//矢印.
	m_pCArrow->SetUsingArrowFlag(SettingArrowFlag());
	m_pCArrow->SetCenterPos(SettingArrowPos());
	m_pCArrow->Update();

	//説明用黒画面.
	m_pCTutorialBlackScreen->SetCenterPos(m_vCenterPos);
	m_pCTutorialBlackScreen->Update();

}

//==========================================.
//		描画処理関数.
//==========================================.
void CDescriptionUIManager::Render()
{
	if (m_pCTutorialBlackScreen != nullptr) {
		m_pCTutorialBlackScreen->Render();
	}

	//チュートリアル会話描画処理.
	if (m_pCSpeakTutorial != nullptr) {
		m_pCSpeakTutorial->Render();
	}
	//矢印クラス.
	if (m_pCArrow != nullptr) {
		//描画フラグ.
		bool ArrowRenderFlag = false;

		//ゲームUI説明時に描画.
		const unsigned int NECESSARY_ARROW = m_pCSpeakTutorial->GAGE_DESCRIPTION_FLAG | m_pCSpeakTutorial->CLOSE_TIME_DESCRIPTION_FLAG;
		if (m_pCSpeakTutorial->GetDescriptionFlag() & NECESSARY_ARROW) {
			ArrowRenderFlag = true;
		}

		//会話文を進めるときは例外処理.
		if (m_pCSpeakTutorial->GetAdvanceCommentFlag() == true) {
			if (ArrowRenderFlag == false) {
				return;
			}
		}

		//選択時の描画.
		if (m_bRenderBothArrowFlag == true) {

			const unsigned int SELECT_ALL_TUTORIAL_FLAG = SELECT_GHOST_FLAG | SELECT_GIMMICK_FLAG;
			if (m_pCSpeakTutorial->GetTutorialFlag() & SELECT_ALL_TUTORIAL_FLAG) {
				ArrowRenderFlag = true;
			}
		}

		if (ArrowRenderFlag == true) {
			m_pCArrow->Render();
		}
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
		return D3DXVECTOR3(m_vCenterPos.x + 500.0f, m_vCenterPos.y - 30.0f, m_vCenterPos.z);
	}

	if (DESCIPTION_FLAG == m_pCSpeakTutorial->CLOSE_TIME_DESCRIPTION_FLAG) {
		return D3DXVECTOR3(m_vCenterPos.x - 100.0f, m_vCenterPos.y, m_vCenterPos.z);
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
	if (m_bRenderBothArrowFlag == true) {
		if (m_pCSpeakTutorial->GetAdvanceCommentFlag() == false) {
			return m_pCArrow->USING_LEFT_FLAG | m_pCArrow->USING_RIGHT_FLAG;
		}
	}

	return 0;
}