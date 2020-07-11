#include "CSurpriseDegreeManager.h"
#include "..\SurpriseDegreeString\CSurpriesDegreeString.h"

/*********************************************
*		驚かし度の管理クラス.
********************/
CSurpriseDegreeManager::CSurpriseDegreeManager()
	: m_pCSurpriseDegreeBase()
	, m_bAllDispFlag		(false)
	, m_UpdateUINum			(0)
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
	if (m_bAllDispFlag == true) {
		return;
	}
	m_pCSurpriseDegreeBase[m_UpdateUINum]->Update();
}

//=============================================.
//			描画処理関数.
//=============================================.
void CSurpriseDegreeManager::Render()
{
	for (int UI = 0; UI <= m_UpdateUINum; UI++) {
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