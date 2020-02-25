#include "CMainStage.h"

CMainStage::CMainStage()
	: CMainStage	(0, enBeforeStageEndigneType::Nothing)
{

}

CMainStage::CMainStage(int stageNum, enBeforeStageEndigneType enType)
	: m_pCStaticObjectManager	(nullptr)
	, m_pCMoveObjectManager		(nullptr)
	, m_pCWorkGhost				()
	, m_pCPeopleManager			(nullptr)
	, m_pCStageMap				(nullptr)
	, m_pCMapGhostCursor		(nullptr)
	, m_SelectNum				()
	, m_ObjectSelectFlag		(0)
	, m_pCGameGhostCursor		(nullptr)
	, m_pCClosedTime			(nullptr)
{
	m_StageNum = stageNum;
	m_enBeforeStageEndingType = enType;
	//初期化処理関数.
	Init();
}

CMainStage::~CMainStage()
{
	//解放処理関数.
	Release();
}

//===================================.
//		更新処理関数.
//===================================.
void CMainStage::UpDate(const bool& ControlFlag)
{


	//人の更新処理関数.
	m_pCPeopleManager->UpDate();

	//お化け.
	std::vector<D3DXVECTOR3> m_vGhostPos(m_pCWorkGhost.size());							//お化け座標.
	std::vector<D3DXVECTOR3> m_vGimmickPos = m_pCMoveObjectManager->GetAllGimmickPos();	//ギミック座標.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//ステージ全体の距離取得.
		m_pCWorkGhost[ghost]->SetStageDistanceMax(m_pCStaticObjectManager->GetStageDistanceMax());

		//ギミックと人の座標取得.
		m_pCWorkGhost[ghost]->SetSurprisePosInfo(m_vGimmickPos, m_pCPeopleManager->GetHumanPos());

		//お化け更新処理関数.
		m_pCWorkGhost[ghost]->UpDate();

		//お化けの座標取得.
		m_vGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();
		D3DXVECTOR3 vTargetPos;
		std::unique_ptr<CWorkGhostBase> pTmp;
		//お化けの要素数変換処理.
		if (ghost < m_pCWorkGhost.size() - 1) {
			//左から右.
			vTargetPos = m_pCWorkGhost[ghost + 1]->GetPos();
			if (m_vGhostPos[ghost].x > vTargetPos.x) {
				//お化けの変更.
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost + 1]);
				m_pCWorkGhost[ghost + 1].swap(pTmp);

				//カーソルがある時は番号を移動させる.
				if (m_SelectNum[GHOST_NUM] == ghost) {
					m_SelectNum[GHOST_NUM] = ghost + 1;
				}
			}
		}
		if (ghost > 0) {
			//右から左.
			vTargetPos = m_pCWorkGhost[ghost - 1]->GetPos();
			if (m_vGhostPos[ghost].x < vTargetPos.x) {
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost - 1]);
				m_pCWorkGhost[ghost - 1].swap(pTmp);

				if (m_SelectNum[GHOST_NUM] == ghost) {
					m_SelectNum[GHOST_NUM] = ghost - 1;
				}
			}
		}

		//使用しているギミック設定.
		if (m_pCWorkGhost[ghost]->GetUseGimmickNum() >= 0) {
			m_pCMoveObjectManager->SetUsedGimmickFlag(m_pCWorkGhost[ghost]->GetUseGimmickNum(), true);
		}

		//驚いている人番号取得.
		m_pCPeopleManager->SetNowHumanSurprise(m_pCWorkGhost[ghost]->GetNearHumanNum());

		//追加ポイント量.
		m_pCSurpriseGage->AddSurprisePoint(m_pCPeopleManager->GetAddSurprisePoint());

		//ギミックの移動フラグ設定.
		int UseGimmickNum = m_pCWorkGhost[ghost]->GetUseGimmickNum();

		if (UseGimmickNum < 0) {
			continue;
		}

		//オブジェクト下げる処理.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->DOWN_FLAG) {
			m_pCMoveObjectManager->SetGimmickMoveFlag(UseGimmickNum, m_pCMoveObjectManager->DOWN_FLAG);
			continue;
		}

		//オブジェクト上げる処理.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->UP_FLAG) {
			m_pCMoveObjectManager->SetGimmickMoveFlag(UseGimmickNum, m_pCMoveObjectManager->UP_FLAG);
		}
	}

	//操作処理関数.
	if (ControlFlag == true) {
		Control();
	}

	//動的オブジェクトの更新処理関数.
	m_pCMoveObjectManager->SetCameraPos(m_Camera.vPos);
	m_pCMoveObjectManager->SetSelectionNum(m_SelectNum[GIMMICK_NUM]);
	m_pCMoveObjectManager->SetGhostPos(m_vGhostPos);
	m_pCMoveObjectManager->UpDate();

	//お化け選択フラグ.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetSelectFlag() == false) {
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
		}
	}

	//ギミック選択フラグ.
	if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetChangeGimmickSelect() == true) {
		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;

		//ギミックカーソル表示フラグ設定.
		m_pCMoveObjectManager->SetGimmickCurosrDispFlag(true);
	}

	//マップ上のお化けカーソル更新処理関数.
	m_pCMapGhostCursor->SetCharaPos(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos());
	m_pCMapGhostCursor->UpDate();
	m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetGhostSelectIcon(true);

	//お化け休憩取得処理.
	bool GhostRestFlag = false;	//お化け休憩フラグ.
	if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetMoveFlag() & m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->REST_FLAG) {
		GhostRestFlag = true;
	}
	m_pCGameGhostCursor->SetRestFlag(GhostRestFlag);
	m_pCGameGhostCursor->SetCharacterPos(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos());
	//ゲーム内でのお化けのカーソル更新処理関数.
	m_pCGameGhostCursor->UpDate();

	//カメラ移動.
	CameraMove();


	//驚きゲージ更新処理関数.
	m_pCSurpriseGage->UpDate();

	//閉店までの時間更新処理関数.
	m_pCClosedTime->UpDate();
	m_pCClosedTime->GiveBornusTime(m_pCSurpriseGage->GetBornusGetFlag());

	if (m_pCSurpriseGage->GetSurprisePointMax() == true) {
		m_enBeforeStageEndingType = enBeforeStageEndigneType::Great;
	}

	//終了処理.
	if (m_pCClosedTime->GetClosedFlag() == true) {
		m_bChangeStageFlag = true;
	}
}

//===================================.
//		描画処理関数.
//===================================.
void CMainStage::Render()
{
	static bool	m_ControlFlag = true;
	if (m_ControlFlag == true) {
		if (GetAsyncKeyState('1') & 0x8000) {
			m_stLight.fIntensity -= 0.1f;
		}

		if (GetAsyncKeyState('2') & 0x8000) {
			m_stLight.fIntensity += 0.1f;
		}
	}
	else {
		if (GetAsyncKeyState('1') & 0x8000) {
			m_stLight.m_fLightWidth -= 0.1f;
		}

		if (GetAsyncKeyState('2') & 0x8000) {
			m_stLight.m_fLightWidth += 0.1f;
		}

	}

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		if (m_ControlFlag == true) {
			m_ControlFlag = false;
		}
		else {
			m_ControlFlag = true;
		}
	}

	//ステージマップの描画.
	m_pCStageMap->Render();

	//マップ上のお化けカーソル描画処理関数.
	m_pCMapGhostCursor->Render();


	//お化けの描画.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//お化け本体の描画処理関数.
		m_pCWorkGhost[ghost]->SetCameraPos(m_Camera.vPos);
		m_pCWorkGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_stLight);
		m_pCWorkGhost[ghost]->Render();
	}


	//動くオブジェクトの描画.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_stLight);

	//静的オブジェクトの描画.
	m_pCStaticObjectManager->SetCameraPos(m_Camera.vPos);
	m_pCStaticObjectManager->UpData();
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_Camera.vPos, m_stLight);

	//お化け体力アイコン描画処理関数.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		m_pCWorkGhost[ghost]->StrengthIconRender();
	}

	//人の描画処理関数.
	m_pCPeopleManager->Render(m_mView, m_mProj, m_Camera.vPos, m_stLight);

	//動くオブジェクトのエフェクト描画.
	m_pCMoveObjectManager->EffectRender();
	
	//ゲーム内でのお化けのカーソル描画処理関数.
	m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_Camera.vPos);
	m_pCGameGhostCursor->Render();

	//お化けの選択描画処理関数.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SelectRender();
	}

	//閉店までの時間描画処理関数.
	m_pCClosedTime->Render();

	//驚きゲージ描画処理関数.
	m_pCSurpriseGage->Render();
}

//===================================.
//		初期化処理関数.
//===================================.
void CMainStage::Init()
{
	//全体的にファイル番号.
	int FileNum = 0;

	//オブジェクトファイル番号.
	int ObjFileNum = m_StageNum + FileNum;

	//読み込みクラスアドレス取得.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();

	//静的オブジェクトインスタンス化.
	m_pCStaticObjectManager.reset(new CStaticObjectManager());

	//お化け設定.
	int GhostFilenum = (static_cast<int>(CFileResource::enStageType::GhostPos_OneDay) * 3) + FileNum;
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(GhostFilenum); stage++) {
		switch (m_pCFileResource->GetStageNum(GhostFilenum, 0, stage) - 1) {
		case 0:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CDispGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 0.0f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		case 1:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CSwitchGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 3.5f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		}
	}

	//動的オブジェクトインスタンス化.
	m_pCMoveObjectManager.reset(new CMoveObjectManager(ObjFileNum));
	m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkGhost.size());
	
	//人管理クラス設定.
	m_pCPeopleManager.reset(new CPeopleManager());
	m_pCPeopleManager->Init(static_cast<int>(CFileResource::enStageType::PeopleOder) + FileNum, 12, m_pCFileResource->GetStageMax(GhostFilenum) * m_pCMoveObjectManager->OBJECT_WIDTH);
	m_pCPeopleManager->SetStageDistanceMax(m_pCStaticObjectManager->GetStageDistanceMax());

	//====UI系のインスタンス化====.
	//ステージ.
	m_pCStageMap.reset(new CStageMap());
	//マップ上のお化けのカーソル.
	m_pCMapGhostCursor.reset(new CMapGhostCursor());
	m_pCMapGhostCursor->SetStageMax(m_pCStaticObjectManager->GetStageDistanceMax());
	//ゲーム内お化けのカーソル.
	m_pCGameGhostCursor.reset(new CGameGhostCursor());
	//閉店までの時間.
	//ステージごとに制限時間を伸ばす.
	int TimeUpMax = START_TIME_UP_MAX + (ADD_TIME_UP * m_StageNum);
	//Good,Greatだとボーナスで制限時間を追加.
	if (m_enBeforeStageEndingType == enBeforeStageEndigneType::Great) {
		TimeUpMax += BENEFITS_PREVIOS_RESULT;
	}
	m_pCClosedTime.reset(new CClosedTime(TimeUpMax * TIME_DELIMITER));
	//驚きゲージ.
	//ステージごとに驚きゲージの最大数を増やす.
	int SurpriseGageMax = START_SUPRISE_GAGE_MAX + (SURPRISE_GAGE_ADD * m_StageNum);
	m_pCSurpriseGage.reset(new CSurpriseGage(SurpriseGageMax));

	//初めはお化けの選択から.
	m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
	
	//選択番号初期化.
	m_SelectNum.resize(SLECTION_MAX);
	for (unsigned int select = 0; select < m_SelectNum.size(); select++) {
		m_SelectNum[select] = 0;
	}

	//カメラ初期設置.
	m_Camera.vPos = CAMERA_START_POS;
	m_Camera.vLook = CAMERA_START_LOOK;

	//ライト情報初期設定.
	m_stLight.vPos = D3DXVECTOR3(17.1f, -3.7f, -0.3f);
	m_stLight.fIntensity = 15.0f;
	m_stLight.m_fLightWidth = 10.0f;
	m_stLight.m_fLightWidth = 0.9f;
	D3DXMatrixIdentity(&m_stLight.mRot);
	
	D3DXMATRIX mYaw, mPich, mRoll;
	D3DXMatrixRotationY(&mYaw, 0.0f);
	D3DXMatrixRotationX(&mPich, 2.8f);
	D3DXMatrixRotationZ(&mRoll, 0.0f);
	m_stLight.mRot = mYaw * mPich * mRoll;

}

//====================================.
//		解放処理関数.
//====================================.
void CMainStage::Release()
{

}

//====================================.
//		操作処理関数.
//====================================.
void CMainStage::Control()
{
	//============================================.
	//お化け選択処理関数.
	if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
		GhostSelect();
	}

	//============================================.
	//ギミック選択処理関数.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		GimmickSelect();
	}

	//============================================.
	//決定処理.

	//行動を起こすお化け決定.
	if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//お化けが驚かしているときのみ.
			if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetMoveFlag() & 
				m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SURPRISE_FLAG) {
				//お化け選択後行動.
				m_ObjectSelectFlag = GHOST_ACT_SELECT_FLAG;
				//選択フラグ.
				m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetSelectFlag(true);
			}
		}
	}

	//移動するギミック決定.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		if (GetAsyncKeyState(VK_BACK) & 0x0001) {
			m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetSelectStop();
			//お化けの選択に戻る.
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
			//ギミック選択フラグ.
			m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetChangeGimmickSelect(false);
			//ギミックカーソル非表示フラグ設定.
			m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			if (m_pCMoveObjectManager->GetUsedGimmickFlag(m_SelectNum[GIMMICK_NUM]) == false) {
				//お化けの種類とギミックの種類があっているときのみ.
				if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetSurpriseObjectType() ==
					m_pCMoveObjectManager->GetSurpriseObjectType()) {
					if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetUseGimmickNum() >= 0) {
						m_pCMoveObjectManager->SetUsedGimmickFlag(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetUseGimmickNum(), false);
					}

					//移動目的のオブジェクト座標取得.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
					//お化けの選択に戻る.
					m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
					//ギミック選択フラグ.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetChangeGimmickSelect(false);
					//ギミックカーソル非表示フラグ設定.
					m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);
				}
			}
		}
	}


#ifdef _DEBUG
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;
	}
#endif	//#ifdef _DEBUG.
}

//========================================.
//		お化け選択処理関数.
//========================================.
void CMainStage::GhostSelect()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GHOST_NUM]++;

		if (m_SelectNum[GHOST_NUM] >= static_cast<int>(m_pCWorkGhost.size())) {
			m_SelectNum[GHOST_NUM] = m_pCWorkGhost.size() - 1;
		}
		return;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GHOST_NUM]--;

		if (m_SelectNum[GHOST_NUM] < 0) {
			m_SelectNum[GHOST_NUM] = 0;
		}
		return;
	}
}

//========================================.
//		ギミック選択処理関数.
//========================================.
void CMainStage::GimmickSelect()
{

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]++;
		if (m_SelectNum[GIMMICK_NUM] >= m_pCMoveObjectManager->GetGimmickIconMax()) {
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickIconMax() - 1;
		}
		return;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]--;
		if (m_SelectNum[GIMMICK_NUM] < 0) {
			m_SelectNum[GIMMICK_NUM] = 0;
		}
		return;
	}

	
}

//=======================================.
//		お化け要素数変換処理関数.
//=======================================.
template<typename T>
void CMainStage::GhostElementSort(T pClass, int array)
{
	std::unique_ptr<T> pTmp;
	pTmp.swap(pClass[array]);
	pClass[array].swap(pClass[array + 1]);
	pClass[array + 1].swap(pTmp);
}

//=======================================.
//		カメラ移動処理関数.
//=======================================.
void CMainStage::CameraMove()
{
	D3DXVECTOR3 m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	//お化け選択時.
	if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
		m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	}
	//ギミック選択時.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		m_GhostPos = m_pCMoveObjectManager->GetGimmickPos();
	}
	//カメラ座標と注視点の座標設定.
	m_Camera.vLook.x = m_Camera.vPos.x = m_GhostPos.x;
	
}

//template void CMainStage::GhostElementSort<std::unique_ptr<CWorkGhostBase>>(CWorkGhostBase, int);