#include "CPeopleManager.h"
#include <random>

CPeopleManager::CPeopleManager()
	: m_pCFileResource		(nullptr)
	, m_HumanAppOrder		()
	, m_pCPeopleBase		()
	, m_bDispFlag			()
	, m_vHumanPos			()
	, m_fStageDistanceMax	(0.0f)
	, m_CreateHumanMax		(0)
	, m_bSurpriseFlag		()
	, m_DispCnt				(DISP_TIME)
	, m_AppHumanNum			(0)
	, m_SurpriseHumanNum	()
	, m_AddSurprisePoint	(0)
	, m_pCPeopleIcon		()
	, m_bPauseFlag			(false)
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
void CPeopleManager::Init(int FileNum, int max, float StageMax)
{
	//ファイルの読み込みアドレス取得.
	m_pCFileResource = CFileResource::GetResourceInstance();
	//人のクラスをインスタンス化する最大数.
	m_CreateHumanMax = max;
	
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> IntervalRand(0, 2);
	int m_column = IntervalRand(mt);

	//人の種類番号取得.
	for (int people = 0; people < m_pCFileResource->GetStageMax(FileNum); people++) {
		m_HumanAppOrder.push_back(m_pCFileResource->GetStageNum(FileNum, m_column, people) - 1);
	}

	//人と人のアイコンのインスタンス化.
	for (int people = 0; people < max; people++) {
		m_pCPeopleBase.push_back(nullptr);
		m_bDispFlag.push_back(false);
		m_pCPeopleIcon.push_back(nullptr);

		//偶数：女の子、奇数：男の子.
		if (people % 2 == 0) {
			m_pCPeopleBase[m_pCPeopleBase.size() - 1] = new CGirl();
			m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(StageMax);

			m_pCPeopleIcon[m_pCPeopleIcon.size() - 1].reset(new CGirlIcon());
			
			continue;
		}
		m_pCPeopleBase[m_pCPeopleBase.size() - 1] = new CBoy();
		m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(StageMax);

		m_pCPeopleIcon[m_pCPeopleIcon.size() - 1].reset(new CBoyIcon());
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
	for (unsigned int human = 0; human < m_CreateHumanMax; human++) {
		if (m_bDispFlag[human] == true) {
			//ポーズフラグ.
			m_pCPeopleBase[human]->SetPauseFlag(m_bPauseFlag);
			//描画時に必要な値取得.
			m_pCPeopleBase[human]->SetCameraPos(vCameraPos);
			m_pCPeopleBase[human]->RenderInitSetting(mView, mProj, stLight);
			//描画処理関数.
			m_pCPeopleBase[human]->Render();
		}
	}

	//人のアイコン描画処理.
	for (unsigned int icon = 0; icon < m_pCPeopleIcon.size(); icon++) {
		if (m_bDispFlag[icon] == true) {
			m_pCPeopleIcon[icon]->Render();
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
	for (int human = m_CreateHumanMax - 1; human >= 0; human--) {
		SAFE_DELETE(m_pCPeopleBase[human]);
	}
}

//=======================================.
//		人の表示処理関数.
//=======================================.
void CPeopleManager::HumanApp()
{
	//出現させる処理.
	if (m_DispCnt == DISP_TIME) {
		for (unsigned int human = m_HumanAppOrder[m_AppHumanNum]; human < m_CreateHumanMax; human += 2) {
			//人がいないときは終了.
			if (m_HumanAppOrder[m_AppHumanNum] < 0) {
				break;
			}

			if (m_bDispFlag[human] == false) {
				m_pCPeopleBase[human]->SetPos(INIT_POS);
				m_bDispFlag[human] = true;
				m_pCPeopleBase[human]->SetDispFlag(true);
				break;
			}
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
	for (unsigned int human = 0; human < m_CreateHumanMax; human++) {
		if (m_bDispFlag[human] == true) {

			//更新処理関数.
			m_pCPeopleBase[human]->Update();
			//表示フラグ取得処理.
			m_bDispFlag[human] = m_pCPeopleBase[human]->GetDispFlag();
			//人の座標取得.
			m_vHumanPos[human] = m_pCPeopleBase[human]->GetPos();
		}
	}
}
