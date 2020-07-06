#include "CPeopleManager.h"
#include <random>

CPeopleManager::CPeopleManager()
	: m_pCFileResource		(nullptr)
	, m_HumanAppOrder		()
	, m_pCPeopleBase		()
	, m_bDispFlag			()
	, m_vHumanPos			()
	, m_DisplayableHumanNum	()
	, m_fStageDistanceMax	(0.0f)
	, m_bSurpriseFlag		()
	, m_DispCnt				(DISP_TIME)
	, m_AppHumanNum			(0)
	, m_SurpriseHumanNum	()
	, m_AddSurprisePoint	(0)
	, m_pCPeopleIcon		()
	, m_bPauseFlag			(false)
	, m_bNotRenderIcon		(false)
{

}

CPeopleManager::~CPeopleManager()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CPeopleManager::Init(int FileNum, int StageNum, float StageMax)
{
	//ファイルの読み込みアドレス取得.
	m_pCFileResource = CFileResource::GetResourceInstance();
	//ステージの長さ最大値を設定.
	m_fStageDistanceMax = StageMax;
	
	//人の種類番号取得.
	for (int people = 0; people < m_pCFileResource->GetStageMax(FileNum, StageNum); people++) {
		m_HumanAppOrder.push_back(m_pCFileResource->GetStageNum(FileNum, StageNum, people) - 1);
	}

	//人を作成処理関数.
	for (int people = 0; people < 10; people++) {
		CreatHuman(people);
	}

	//人の座標要素数取得.
	m_vHumanPos.resize(m_pCPeopleBase.size());
	//驚くフラグ要素数取得.
	m_bSurpriseFlag.resize(m_pCPeopleBase.size());

}

//=======================================.
//		更新処理関数.
//=======================================.
void CPeopleManager::Update()
{
	//現れる人間の番号の最大値処理.
	if (m_AppHumanNum >= m_HumanAppOrder.size()) {
		m_AppHumanNum = 0;
	}

	//人の表示処理関数.
	HumanApp();

	//人の移動処理関数.
	HumanMove();

	//人のアイコン更新処理関数.
	for (unsigned int icon = 0; icon < m_pCPeopleIcon.size(); icon++) {
		m_pCPeopleIcon[icon]->SetStageMax(m_fStageDistanceMax);
		m_pCPeopleIcon[icon]->SetCharaPos(m_pCPeopleBase[icon]->GetPos());
		m_pCPeopleIcon[icon]->UpDate();
	}
}

//=======================================.
//		描画処理関数.
//=======================================.
void CPeopleManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos, const LIGHT& stLight)
{
	//人の描画処理.
	for (unsigned int human = 0; human < m_pCPeopleBase.size(); human++) {
		
		if (m_bDispFlag[human] == false) {
			//描画しない.
			continue;
		}

		//ポーズフラグ.
		m_pCPeopleBase[human]->SetPauseFlag(m_bPauseFlag);
		//描画時に必要な値取得.
		m_pCPeopleBase[human]->SetCameraPos(vCameraPos);
		m_pCPeopleBase[human]->RenderInitSetting(mView, mProj, stLight);
		//描画処理関数.
		m_pCPeopleBase[human]->Render();
	}

	//アイコンは描画しないようにする処理.
	if (m_bNotRenderIcon == true) {
		return;
	}

	//人のアイコン描画処理.
	for (unsigned int icon = 0; icon < m_pCPeopleIcon.size(); icon++) {
		if (m_bDispFlag[icon] == true) {
			m_pCPeopleIcon[icon]->Render();
			m_pCPeopleIcon[icon]->RenderEffect();
		}
	}
}

//=======================================.
//情報置換処理関数(驚いている人番号).
//=======================================.
void CPeopleManager::SetNowHumanSurprise(const std::vector<int>& HumanNum)
{
	//追加ポイント初期化.
	m_AddSurprisePoint = 0;

	if (HumanNum.size() <= 0) {
		return;
	}

	for (unsigned int human = 0; human < HumanNum.size(); human++) {
		//追加ポイント量.
		m_AddSurprisePoint += m_pCPeopleBase[HumanNum[human]]->GetAddPointQuantity(human);

		m_bSurpriseFlag[HumanNum[human]] = true;
		//驚いたフラグ取得.
		m_pCPeopleBase[HumanNum[human]]->SetSurpriseFlag(m_bSurpriseFlag[HumanNum[human]]);
		m_pCPeopleIcon[HumanNum[human]]->SetSurpriseFlag(m_bSurpriseFlag[HumanNum[human]]);

		//近くの人番号取得.
		m_pCPeopleBase[HumanNum[human]]->SetHumanNearNum(human);

		//驚いた人の最大数.
		m_pCPeopleBase[HumanNum[human]]->SetSurpriseHumanMax(HumanNum.size());
	}
}

//=======================================.
//		解放処理関数.
//=======================================.
void CPeopleManager::Release()
{

}

//=======================================.
//		人の表示処理関数.
//=======================================.
void CPeopleManager::HumanApp()
{
	if (m_DispCnt == DISP_TIME) {
		//作成フラグ.
		bool m_bCreatFlag = true;

		for (unsigned int people = 0; people < m_pCPeopleBase.size(); people++) {
			if (m_HumanAppOrder[m_AppHumanNum] < 0) {
				//待ち時間なので作成しない.
				m_bCreatFlag = false;
				break;
			}

			if (m_HumanAppOrder[m_AppHumanNum] != m_DisplayableHumanNum[people]) {
				continue;
			}

			//出現させる処理.
			if (m_bDispFlag[people] == false) {
				m_pCPeopleBase[people]->SetPos(INIT_POS);
				m_bDispFlag[people] = true;
				m_pCPeopleBase[people]->SetDispFlag(true);
				m_bCreatFlag = false;
				break;
			}
		}

		//人を作成処理関数.
		if (m_bCreatFlag == true) {
			CreatHuman(m_AppHumanNum);
		}

		m_AppHumanNum++;
		m_DispCnt = 0;
	}

	//カウント処理.
	m_DispCnt++;
}

//=======================================.
//		人の移動処理関数.
//=======================================.
void CPeopleManager::HumanMove()
{
	for (unsigned int human = 0; human < m_pCPeopleBase.size(); human++) {
		
		if (m_bDispFlag[human] == false) {
			//移動させない.
			continue;
		}

		//更新処理関数.
		m_pCPeopleBase[human]->Update();
		//表示フラグ取得処理.
		m_bDispFlag[human] = m_pCPeopleBase[human]->GetDispFlag();
		//人の座標取得.
		m_vHumanPos[human] = m_pCPeopleBase[human]->GetPos();
	}
}

//========================================.
//		人を作成処理関数.
//========================================.
void CPeopleManager::CreatHuman(const int& HumanNum)
{
	m_bDispFlag.push_back(false);
	m_DisplayableHumanNum.push_back(m_HumanAppOrder[HumanNum]);
	//人の座標要素数取得.
	m_vHumanPos.push_back(INIT_POS);
	//驚くフラグ要素数取得.
	m_bSurpriseFlag.push_back(false);

	//女.
	if (m_HumanAppOrder[HumanNum] == 0) {
		m_pCPeopleBase.emplace_back(new CGirl());
		m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(m_fStageDistanceMax);
		m_pCPeopleIcon.emplace_back(new CGirlIcon());
		return;
	}

	//男.
	m_pCPeopleBase.emplace_back(new CBoy());
	m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(m_fStageDistanceMax);
	m_pCPeopleIcon.emplace_back(new CBoyIcon());

}