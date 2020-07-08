#include "CMainStageWorkGhostManager.h"

/*************************************************
*		メインステージの働くお化け管理クラス.
*******************/
CMainStageWorkGhostManager::CMainStageWorkGhostManager()
	: m_pCWorkGhost			()
	, m_vGimmickPos			()
	, m_vPeoplePos			()
	, m_UpDownFlag			()
	, m_fStageDistanceMax	(0.0f)
	, m_TutorialFlag		(0)
	, m_SelectNum			(0)
	, m_bPauseFlag			(false)
{
}

CMainStageWorkGhostManager::~CMainStageWorkGhostManager()
{
	//解放処理関数.
	Release();
}

//================================================.
//		初期化処理関数.
//================================================.
void CMainStageWorkGhostManager::Init(const int& StageType, const int& StageNum, const float& PosWidth)
{
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();

	for (int stage = 0; stage < m_pCFileResource->GetStageMax(StageType, 0); stage++) {
		const int CharaPosNum = m_pCFileResource->GetStageNum(StageType, StageNum, stage) - 1;
		if (CharaPosNum < 0 || CharaPosNum > 1) {
			continue;
		}

		switch (CharaPosNum) {
		case 0:
			//初期設定.
			m_pCWorkGhost.emplace_back(new CMainStageDispGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 0.0f, 3.5f));
			break;
		case 1:
			m_pCWorkGhost.emplace_back(new CMainStageSwitchGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 3.5f, 3.5f));
			break;
		}
		//要素数.
		const int ElementNum = static_cast<int>(m_pCWorkGhost.size() - 1);
		m_pCWorkGhost[ElementNum]->SetPos(m_vWorkGhostPos[ElementNum]);
		m_pCWorkGhost[ElementNum]->SetInitMovePos();
	}

	m_UpDownFlag.resize(m_pCWorkGhost.size());

}

//================================================.
//		更新処理関数.
//================================================.
void CMainStageWorkGhostManager::Update()
{
	//お化け.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {

		//お化けの座標取得.
		m_vWorkGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();

		//ステージ全体の距離取得.
		m_pCWorkGhost[ghost]->SetStageDistanceMax(m_fStageDistanceMax);

		//ギミックと人の座標取得.
		m_pCWorkGhost[ghost]->SetSurprisePosInfo(m_vGimmickPos, m_vPeoplePos);

		//チュートリアル処理関数(trueがかえってくれば処理終了).
		if (m_TutorialFlag & TUTORIAL_STAGE_FLAG) {
			if (Tutorial(ghost)) break;
		}

		//お化け更新処理関数.
		m_pCWorkGhost[ghost]->Update();

		//お化けの座標取得.
		m_vWorkGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();

		//要素数変更処理関数.
		ChangeElementNum(ghost);

		//オブジェクト上下処理関数.
		UpDownObuject(ghost);
	}

	//お化けアイコンが選ばれているフラグ.
	m_pCWorkGhost[m_SelectNum]->SetGhostSelectIcon(true);

}

//================================================.
//		描画処理関数.
//================================================.
void CMainStageWorkGhostManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& Light, const D3DXVECTOR3& vCameraPos)
{
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//ポーズフラグ.
		m_pCWorkGhost[ghost]->SetPauseFlag(m_bPauseFlag);
		//お化け本体の描画処理関数.
		m_pCWorkGhost[ghost]->SetCameraPos(vCameraPos);
		m_pCWorkGhost[ghost]->RenderInitSetting(mView, mProj, Light);
		m_pCWorkGhost[ghost]->Render();
	}

}

//================================================.
//		アイコン描画処理関数.
//================================================.
void CMainStageWorkGhostManager::RenderIcon()
{
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		m_pCWorkGhost[ghost]->StrengthIconRender();
	}
}

//================================================.
//		選択UI描画処理関数.
//================================================.
void CMainStageWorkGhostManager::RenderSelectUI()
{
	m_pCWorkGhost[m_SelectNum]->SelectRender();
}

//================================================.
//		選択お化けの休憩判定処理関数.
//================================================.
bool CMainStageWorkGhostManager::DecisionSelectRest()
{
	//休憩判定.
	if (m_pCWorkGhost[m_SelectNum]->GetMoveFlag() & m_pCWorkGhost[m_SelectNum]->REST_FLAG) {
		return true;
	}

	return false;
}

//================================================.
//		選択お化けの驚かす判定処理関数.
//================================================.
bool CMainStageWorkGhostManager::DecisionSelectSurprise()
{
	if (m_pCWorkGhost[m_SelectNum]->GetMoveFlag() &	m_pCWorkGhost[m_SelectNum]->SURPRISE_FLAG) {
		return true;
	}

	return false;
}

//================================================.
//		お化け選択処理関数.
//================================================.
bool CMainStageWorkGhostManager::SelectGhost()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum++;

		if (m_SelectNum >= static_cast<int>(m_pCWorkGhost.size())) {
			m_SelectNum = m_pCWorkGhost.size() - 1;
		}
		return true;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum--;

		if (m_SelectNum < 0) {
			m_SelectNum = 0;
		}
		return true;
	}

	return false;
}

//================================================.
//	選択しているお化けの休憩フラグ取得処理関数.
//================================================.
bool CMainStageWorkGhostManager::GetRestSelectGhostFlag() const
{
	if (m_pCWorkGhost[m_SelectNum]->GetMoveFlag() & m_pCWorkGhost[m_SelectNum]->REST_FLAG) {
		return true;
	}
	return false;
}

//================================================.
//		チュートリアル処理関数.
//================================================.
bool CMainStageWorkGhostManager::Tutorial(const int& GhostNum)
{
	//選択待機時は処理を終了させる.
	if (m_TutorialFlag & SELECT_WAIT_FLAG) {
		return true;
	}

	if (m_TutorialFlag & EXPLAINING_FLAG) {
		//チュートリアルフラグ.
		m_pCWorkGhost[GhostNum]->SetTutorialFlag(true);

		//選択決定フラグ設定.
		if (m_TutorialFlag & GHOST_DECIDE_FLAG) {
			m_pCWorkGhost[GhostNum]->SetDecideSelectFlag(true);
			return false;
		}
		m_pCWorkGhost[GhostNum]->SetDecideSelectFlag(false);
		
		return false;
	}

	//説明終了後.
	m_pCWorkGhost[GhostNum]->SetTutorialFlag(false);
	m_pCWorkGhost[GhostNum]->SetDecideSelectFlag(true);

	return false;
}

//================================================.
//		要素数変換処理関数.
//================================================.
void CMainStageWorkGhostManager::ChangeElementNum(const int& GhostNum) 
{
		
	D3DXVECTOR3 vTargetPos;							//目標座標.
	std::unique_ptr<CMainStageWorkGhostBase> pTmp;	//変更用変数.


	const int GHOST_MAX_NUM = m_pCWorkGhost.size() - 1;
	if (GhostNum < GHOST_MAX_NUM) {
		
		//右のお化けの番号.
		const int RightGhostNum = GhostNum + 1;

		//左から右.
		vTargetPos = m_pCWorkGhost[RightGhostNum]->GetPos();
		if (m_vWorkGhostPos[GhostNum].x > vTargetPos.x) {
			//お化けの変更.
			pTmp.swap(m_pCWorkGhost[GhostNum]);
			m_pCWorkGhost[GhostNum].swap(m_pCWorkGhost[RightGhostNum]);
			m_pCWorkGhost[RightGhostNum].swap(pTmp);
	
			//カーソルがある時は番号を移動させる.
			if (m_SelectNum == GhostNum) {
				m_SelectNum = RightGhostNum;
				return;
			}

			if (fabs(m_SelectNum - RightGhostNum) != 0) {
				return;
			}
			//右にカーソルがある場合は選択番号変更.
			if (m_SelectNum == RightGhostNum) {
				m_SelectNum = GhostNum;
			}
		}
	}

	if (GhostNum > 0) {
	
		//左のお化けの番号.
		const int LeftGhostNum = GhostNum - 1;
		
		//右から左.
		vTargetPos = m_pCWorkGhost[LeftGhostNum]->GetPos();
		if (m_vWorkGhostPos[GhostNum].x < vTargetPos.x) {
			pTmp.swap(m_pCWorkGhost[GhostNum]);
			m_pCWorkGhost[GhostNum].swap(m_pCWorkGhost[LeftGhostNum]);
			m_pCWorkGhost[LeftGhostNum].swap(pTmp);
	
			if (m_SelectNum == GhostNum) {
				m_SelectNum = LeftGhostNum;
				return;
			}
			if (fabs(m_SelectNum - LeftGhostNum) != 0) {
				return;
			}
			//左にカーソルがある場合は選択番号変更.
			if (m_SelectNum == LeftGhostNum) {
				m_SelectNum = GhostNum;
			}
		}
	}

}

//================================================.
//		オブジェクト上下処理関数.
//================================================.
void CMainStageWorkGhostManager::UpDownObuject(const int& GhostNum)
{
	//ギミックの移動フラグ設定.
	int UseGimmickNum = m_pCWorkGhost[GhostNum]->GetUseGimmickNum();

	if (UseGimmickNum < 0) {
		m_UpDownFlag[GhostNum] = 0;
		return;
	}

	//オブジェクト下げる処理.
	if (m_pCWorkGhost[GhostNum]->GetUpDownFlag() & m_pCWorkGhost[GhostNum]->DOWN_FLAG) {
		m_UpDownFlag[GhostNum] = OBJ_DOWN_FLAG;
		return;
	}

	//オブジェクト上げる処理.
	if (m_pCWorkGhost[GhostNum]->GetUpDownFlag() & m_pCWorkGhost[GhostNum]->UP_FLAG) {
		m_UpDownFlag[GhostNum] = OBJ_UP_FLAG;
	}

}

//================================================.
//		解放処理関数.
//================================================.
void CMainStageWorkGhostManager::Release()
{

}