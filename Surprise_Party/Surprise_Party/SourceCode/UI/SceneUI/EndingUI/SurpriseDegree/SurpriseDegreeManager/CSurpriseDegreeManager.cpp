#include "CSurpriseDegreeManager.h"
#include "..\SurpriseDegreeString\CSurpriesDegreeString.h"

/*********************************************
*		驚かし度の管理クラス.
********************/
CSurpriseDegreeManager::CSurpriseDegreeManager()
	: m_pCSurpriseDegreeBase()
	, m_bAllDispFlag		(false)
	, m_UpdateUINum			(0)
	, m_bDisplayAllAtOnce	(false)
{
	//初期化処理関数.
	Init();
}

CSurpriseDegreeManager::~CSurpriseDegreeManager()
{

}

//=============================================.
//			更新処理関数.
//=============================================.
void CSurpriseDegreeManager::Update()
{
	//全ての更新処理をしたら処理を終了.
	if (m_bAllDispFlag == true) {
		return;
	}

	if (m_bDisplayAllAtOnce == true) {
		for (unsigned int UI = 0; UI < m_pCSurpriseDegreeBase.size(); UI++) {
			m_pCSurpriseDegreeBase[UI]->SetDisplayAllAtOnce(m_bDisplayAllAtOnce);
			m_pCSurpriseDegreeBase[UI]->Update();
			m_bAllDispFlag = true;
			return;
		}
	}

	//更新処理関数.
	m_pCSurpriseDegreeBase[m_UpdateUINum]->Update();

	//次の処理へ.
	if (m_pCSurpriseDegreeBase[m_UpdateUINum]->GetDispFlag() == true) {
		m_UpdateUINum++;
	}

	if (m_UpdateUINum >= static_cast<int>(m_pCSurpriseDegreeBase.size())) {
		m_bAllDispFlag = true;
	}
}

//=============================================.
//			描画処理関数.
//=============================================.
void CSurpriseDegreeManager::Render()
{
	for (unsigned int UI = 0; UI < m_pCSurpriseDegreeBase.size(); UI++) {
		m_pCSurpriseDegreeBase[UI]->Render();
	}
}

//=============================================.
//			初期化処理関数.
//=============================================.
void CSurpriseDegreeManager::Init()
{
	//驚かし度の文章UI構築.
	m_pCSurpriseDegreeBase.emplace_back(std::make_unique<CSurpriseDegreeString>());
}