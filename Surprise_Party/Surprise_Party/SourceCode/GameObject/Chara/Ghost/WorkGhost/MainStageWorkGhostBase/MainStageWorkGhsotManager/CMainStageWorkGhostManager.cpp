#include "CMainStageWorkGhostManager.h"

/*************************************************
*		メインステージの働くお化け管理クラス.
*******************/
CMainStageWorkGhostManager::CMainStageWorkGhostManager()
	: m_pCWorkGhost			()
	, m_vGimmickPos			()
	, m_vPeoplePos			()
	//, m_tObjUpDownFlag		()
	, m_tUseGimmick			()
	, m_UpDownFlag			()
	, m_fStageDistanceMax	(0.0f)
	, m_TutorialFlag		(0)
	, m_SelectNum			(0)
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

	for (int stage = 0; stage < m_pCFileResource->GetStageMax(StageType); stage++) {
		switch (m_pCFileResource->GetStageNum(StageType, StageNum, stage) - 1) {
		case 0:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageDispGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 0.0f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(m_vWorkGhostPos[m_pCWorkGhost.size() - 1]);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		case 1:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageSwitchGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 3.5f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(m_vWorkGhostPos[m_pCWorkGhost.size() - 1]);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		}
	}
	//お化けの座標.
	//m_vWorkGhostPos.resize(m_pCWorkGhost.size());
	//上げ下げフラグ.
	//m_tObjUpDownFlag.resize(m_pCWorkGhost.size());
	m_UpDownFlag.resize(m_pCWorkGhost.size());
	//使用ギミック.
	m_tUseGimmick.resize(m_pCWorkGhost.size());

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

		if (m_TutorialFlag & TUTORIAL_STAGE_FLAG) {
			if (m_TutorialFlag & EXPLAINING_FLAG) {
				//チュートリアルフラグ.
				m_pCWorkGhost[ghost]->SetTutorialFlag(true);

				//選択決定フラグ設定.
				if (m_TutorialFlag & GHOST_DECIDE_FLAG) {
					m_pCWorkGhost[ghost]->SetDecideSelectFlag(true);
				}
				else {
					m_pCWorkGhost[ghost]->SetDecideSelectFlag(false);
				}
			}
			else {
				m_pCWorkGhost[ghost]->SetTutorialFlag(false);
				m_pCWorkGhost[ghost]->SetDecideSelectFlag(true);
			}
			if (m_TutorialFlag & SELECT_WAIT_FLAG) {
				break;
			}
		}
		//お化け更新処理関数.
		m_pCWorkGhost[ghost]->Update();

		//お化けの座標取得.
		m_vWorkGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();
		D3DXVECTOR3 vTargetPos;
		std::unique_ptr<CMainStageWorkGhostBase> pTmp;
		//お化けの要素数変換処理.
		if (ghost < m_pCWorkGhost.size() - 1) {
			//左から右.
			vTargetPos = m_pCWorkGhost[ghost + 1]->GetPos();
			if (m_vWorkGhostPos[ghost].x > vTargetPos.x) {
				//お化けの変更.
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost + 1]);
				m_pCWorkGhost[ghost + 1].swap(pTmp);

				//カーソルがある時は番号を移動させる.
				if (m_SelectNum == ghost) {
					m_SelectNum = ghost + 1;
				}
			}
		}
		if (ghost > 0) {
			//右から左.
			vTargetPos = m_pCWorkGhost[ghost - 1]->GetPos();
			if (m_vWorkGhostPos[ghost].x < vTargetPos.x) {
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost - 1]);
				m_pCWorkGhost[ghost - 1].swap(pTmp);

				if (m_SelectNum == ghost) {
					m_SelectNum = ghost - 1;
				}
			}
		}

		//使用しているギミック設定.
		if (m_pCWorkGhost[ghost]->GetUseGimmickNum() >= 0) {
			m_tUseGimmick[ghost] = std::tuple<int, bool>(m_pCWorkGhost[ghost]->GetUseGimmickNum(), true);
		}

		//ギミックの移動フラグ設定.
		int UseGimmickNum = m_pCWorkGhost[ghost]->GetUseGimmickNum();

		if (UseGimmickNum < 0) {
			//m_tObjUpDownFlag[ghost] = std::tuple<int, unsigned int>(UseGimmickNum, 0);
			m_UpDownFlag[ghost] = 0;
			continue;
		}

		//オブジェクト下げる処理.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->DOWN_FLAG) {
			//m_tObjUpDownFlag[ghost] = std::tuple<int, unsigned int>(UseGimmickNum, OBJ_DOWN_FLAG);
			m_UpDownFlag[ghost] = OBJ_DOWN_FLAG;
			continue;
		}

		//オブジェクト上げる処理.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->UP_FLAG) {
			//m_tObjUpDownFlag[ghost] = std::tuple<int, unsigned int>(UseGimmickNum, OBJ_UP_FLAG);
			m_UpDownFlag[ghost] = OBJ_UP_FLAG;
		}
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
//		解放処理関数.
//================================================.
void CMainStageWorkGhostManager::Release()
{

}