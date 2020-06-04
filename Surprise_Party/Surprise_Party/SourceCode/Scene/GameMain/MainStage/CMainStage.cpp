#include "CMainStage.h"
#include <random>
#include "..\..\Camera\CameraGameMainStage\CCameraGameMainStage.h"

CMainStage::CMainStage()
	: CMainStage	(0, enStageType::Start ,enBeforeStageEndigneType::Nothing)
{

}

CMainStage::CMainStage(int stageNum, enStageType enStage, enBeforeStageEndigneType enType)
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
	, m_pCSurpriseGage			()
	, m_pCFrontstageLight		(nullptr)
	, m_enStageType				(enStage)
	, m_ExplainFlag				(0)
	, m_bDispTextFlag			(true)
	, m_pCSpeakWorkGhost		(nullptr)
	, m_vSelectGhostPos			(0.0f, 0.0f, 0.0f)
	, m_pCDescriptionUIManager	(nullptr)
	//, m_bTutorialCameraMove		(false)
	//, m_stOldCamera				()
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
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		m_pCCamera->SetTargetPos(m_pCMoveObjectManager->GetGimmickPos());
	}
	else {
		m_pCCamera->SetTargetPos(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos());
	}
	m_pCCamera->Update();
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//表舞台ライトクラスの更新処理関数.
	m_pCFrontstageLight->SetCameraPos(m_vCameraPos);
	//m_pCFrontstageLight->SetCameraPos(m_Camera.vPos);
	m_pCFrontstageLight->Update();

	//静的オブジェクト更新処理関数.
	m_pCStaticObjectManager->SetCameraPos(m_vCameraPos);
	//m_pCStaticObjectManager->SetCameraPos(m_Camera.vPos);
	m_pCStaticObjectManager->Updata();

	//お化け.
	std::vector<D3DXVECTOR3> m_vGhostPos(m_pCWorkGhost.size());							//お化け座標.
	std::vector<D3DXVECTOR3> m_vGimmickPos = m_pCMoveObjectManager->GetAllGimmickPos();	//ギミック座標.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {

		//ステージ全体の距離取得.
		m_pCWorkGhost[ghost]->SetStageDistanceMax(m_pCStaticObjectManager->GetStageDistanceMax());

		//ギミックと人の座標取得.
		m_pCWorkGhost[ghost]->SetSurprisePosInfo(m_vGimmickPos, m_pCPeopleManager->GetHumanPos());

		if (m_enStageType == enStageType::Tutorial) {
			if (m_ExplainFlag != 0) {
				//チュートリアルフラグ.
				m_pCWorkGhost[ghost]->SetTutorialFlag(true);

				//選択決定フラグ設定.
				if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == false) {
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
		}


		//お化け更新処理関数.
		m_pCWorkGhost[ghost]->Update();

		//チュートリアル時コメント一つ進める処理.
		if (m_pCDescriptionUIManager != nullptr) {
			if (m_pCWorkGhost[ghost]->GetTutorialAddCommentFlag() == true) {
				m_pCDescriptionUIManager->SetAdvanceComment();
			}
		}

		//お化けの座標取得.
		m_vGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();
		D3DXVECTOR3 vTargetPos;
		std::unique_ptr<CMainStageWorkGhostBase> pTmp;
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

	//動的オブジェクトの更新処理関数.
	m_pCMoveObjectManager->SetCameraPos(m_vCameraPos);
	//m_pCMoveObjectManager->SetCameraPos(m_Camera.vPos);
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
	m_pCSurpriseGage->Update();

	//チュートリアルまでの処理(ここでお化けとギミックの時は例外の処理を行わなければならない).
	if (m_enStageType == enStageType::Tutorial && (m_ExplainFlag & EXPLAINING_FLAG)) {

		//フェード中は例外処理.
		if (ControlFlag == false) {
			return;

		}

		//説明UI管理クラス.
		m_pCDescriptionUIManager->SetCenterPos(m_pCSurpriseGage->GetUIPos(), m_pCClosedTime->GetUIPos());
		m_pCDescriptionUIManager->Update();

		if (GetAsyncKeyState('Q') & 0x8000) {
			//説明終了ゲームを動かすフラグ.
			m_ExplainFlag = 0;
		}
		
		if (m_pCDescriptionUIManager->GetDescriptionEndFlag() == true) {
			m_ExplainFlag = 0;
			//テキスト描画終了.
			m_bDispTextFlag = false;
			//m_bTutorialCameraMove = 0;
		}
	}

	if (m_pCDescriptionUIManager != nullptr) {
		//コメント進めるときは下まで処理しない.
		if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == true) {
			const unsigned int DESCRIPTION_LAST_FLAG = SeePeople | DescriptionEnd;
			if (!(m_pCDescriptionUIManager->GetStartLatestFlag() & DESCRIPTION_LAST_FLAG)) {
				return;
			}
		}
	}

	//操作処理関数.
	if (ControlFlag == true) {
		Control();
		//説明中例外処理.
		if (m_ExplainFlag & EXPLAINING_FLAG ){
			m_pCPeopleManager->SetTutorialFlag(true);

			if(!(m_pCDescriptionUIManager->GetStartLatestFlag() & SeePeople)) {
				//if (m_bTutorialCameraMove & CAMERA_MOVE_START_FLAG) {
				//	m_bTutorialCameraMove = CAMERA_MOVE_RETURN_FLAG;
				//}
				if (m_pCCamera->GetMoveFlag() & m_pCCamera->PEOPLE_LOOK_FLAG) {
					m_pCCamera->SetMoveFlag(m_pCCamera->GHOST_LOOK_FLAG);
				}
				return;
			}
			if (m_pCDescriptionUIManager->GetStartLatestFlag() & SeePeople) {
				//カメラ移動フラグ.
				//m_bTutorialCameraMove = CAMERA_MOVE_START_FLAG;
				m_pCCamera->SetMoveFlag(m_pCCamera->PEOPLE_LOOK_FLAG);
				m_pCCamera->AcquisitionDifference();
				//m_stOldCamera.vPos = m_Camera.vPos;
				//m_stOldCamera.vLook = m_Camera.vLook;

			}
		}

	}

	

	//人の更新処理関数.
	m_pCPeopleManager->Update();


	//閉店までの時間更新処理関数.
	m_pCClosedTime->Update();
	m_pCClosedTime->GiveBornusTime(m_pCSurpriseGage->GetBornusGetFlag());

	//if (m_pCSurpriseGage->GetSurprisePointMax() == true) {
	//	m_enBeforeStageEndingType = enBeforeStageEndigneType::Great;
	//}
	m_enBeforeStageEndingType = Evalute();

	//終了処理.
	if (m_pCClosedTime->GetClosedFlag() == true) {
		if (m_enStageType == enStageType::Tutorial) {
			m_TutorialFlag = TUTORIAL_FINISH;
		}
		m_bChangeStageFlag = true;
	}
}

//===================================.
//		描画処理関数.
//===================================.
void CMainStage::Render()
{
	{
	//	static bool	m_ControlFlag = true;
	//	if (m_ControlFlag == true) {
	//		if (GetAsyncKeyState('1') & 0x8000) {
	//			m_stLight.fIntensity -= 0.1f;
	//		}

	//		if (GetAsyncKeyState('2') & 0x8000) {
	//			m_stLight.fIntensity += 0.1f;
	//		}
	//	}
	//	else {
	//		if (GetAsyncKeyState('1') & 0x8000) {
	//			m_stLight.m_fLightWidth -= 0.1f;
	//		}

	//		if (GetAsyncKeyState('2') & 0x8000) {
	//			m_stLight.m_fLightWidth += 0.1f;
	//		}

	//	}

	//	if (GetAsyncKeyState(VK_F1) & 0x8000) {
	//		if (m_ControlFlag == true) {
	//			m_ControlFlag = false;
	//		}
	//		else {
	//			m_ControlFlag = true;
	//		}
	//	}
	}

	//ライト情報.
	const LIGHT m_Light = m_pCFrontstageLight->GetLight();
	//カメラ座標.
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//ステージマップの描画.
	m_pCStageMap->Render();

	//マップ上のお化けカーソル描画処理関数.
	m_pCMapGhostCursor->Render();


	//お化けの描画.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//お化け本体の描画処理関数.
		m_pCWorkGhost[ghost]->SetCameraPos(m_vCameraPos);
		//m_pCWorkGhost[ghost]->SetCameraPos(m_Camera.vPos);
		m_pCWorkGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
		m_pCWorkGhost[ghost]->Render();
	}



	//動くオブジェクトスイッチの描画.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_Light);
	//静的オブジェクトの描画.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//m_pCStaticObjectManager->Render(m_mView, m_mProj, m_Camera.vPos, m_Light);
	//動くオブジェクト描画処理.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_Light);

	//お化け体力アイコン描画処理関数.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		m_pCWorkGhost[ghost]->StrengthIconRender();
	}

	//人の描画処理関数.
	m_pCPeopleManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//m_pCPeopleManager->Render(m_mView, m_mProj, m_Camera.vPos, m_Light);

	//動くオブジェクトのエフェクト描画.
	m_pCMoveObjectManager->EffectRender();
	
	//ゲーム内でのお化けのカーソル描画処理関数.
	m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_vCameraPos);
	//m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_Camera.vPos);
	m_pCGameGhostCursor->Render();

	//お化けの選択描画処理関数.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SelectRender();
	}

	//閉店までの時間描画処理関数.
	m_pCClosedTime->Render();

	//驚きゲージ描画処理関数.
	m_pCSurpriseGage->Render();

	//テキスト表示.
	if (m_bDispTextFlag == false) {
		return;
	}


	//働くお化け会話クラス.
	if (m_pCSpeakWorkGhost != nullptr) {
		//お化けの選択に関係する全てのフラグ.
		const unsigned int RELATED_TO_GHOST_ALL_FLAG = SELECT_GHOST_FLAG | GHOST_ACT_SELECT_FLAG;
		if (m_vCameraPos.x == m_vSelectGhostPos.x ||
		//if (m_Camera.vPos.x == m_vSelectGhostPos.x ||
			m_ObjectSelectFlag & RELATED_TO_GHOST_ALL_FLAG) {
			m_pCSpeakWorkGhost->Render();
		}
	}

	//説明UI管理クラス.
	if (m_pCDescriptionUIManager != nullptr) {
		m_pCDescriptionUIManager->Render();
	}
}

//===================================.
//		初期化処理関数.
//===================================.
void CMainStage::Init()
{
	//全体的にファイル番号.
	int FileNum = 0;

	//オブジェクトファイル番号.
	int ObjFileNum = static_cast<int>(CFileResource::enStageType::OneDay) + m_StageNum;

	//読み込みクラスアドレス取得.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();

	//静的オブジェクトインスタンス化.
	std::random_device rnda;
	std::mt19937 mta(rnda());
	std::uniform_int_distribution<> IntervalRand4(0, 2);
	int m_columna = IntervalRand4(mta);
	
	m_pCStaticObjectManager.reset(new CStaticObjectManager(ObjFileNum, m_columna));

	//ステージの長さ最大数.
	float m_fStageDistanceMax = m_pCStaticObjectManager->GetStageDistanceMax();

	//お化け設定.
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> IntervalRand(0, 2);
	int m_column = IntervalRand(mt);

	int GhostFilenum = static_cast<int>(CFileResource::enStageType::GhostPos_OneDay) * 3;
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(GhostFilenum); stage++) {
		switch (m_pCFileResource->GetStageNum(GhostFilenum, m_column, stage) - 1) {
		case 0:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageDispGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 0.0f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		case 1:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageSwitchGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 3.5f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		}
	}

	//動的オブジェクトインスタンス化.
	m_pCMoveObjectManager.reset(new CMoveObjectManager(ObjFileNum, m_column));
	m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkGhost.size());
	
	//人管理クラス設定.
	m_pCPeopleManager.reset(new CPeopleManager());
	m_pCPeopleManager->Init(static_cast<int>(CFileResource::enStageType::PeopleOder) /*+ FileNum*/ * 3, 12, m_pCFileResource->GetStageMax(GhostFilenum) * m_pCMoveObjectManager->OBJECT_WIDTH);
	m_pCPeopleManager->SetStageDistanceMax(m_fStageDistanceMax);

	//====UI系のインスタンス化====.
	//ステージ.
	m_pCStageMap.reset(new CStageMap());
	//マップ上のお化けのカーソル.
	m_pCMapGhostCursor.reset(new CMapGhostCursor());
	m_pCMapGhostCursor->SetStageMax(m_fStageDistanceMax);
	//ゲーム内お化けのカーソル.
	m_pCGameGhostCursor.reset(new CGameGhostCursor());
	//閉店までの時間.
	//ステージごとに制限時間を伸ばす.
	int TimeUpMax = START_TIME_UP_MAX + (ADD_TIME_UP * m_StageNum);
	//Good,Greatだとボーナスで制限時間を追加.
	if (m_enBeforeStageEndingType == enBeforeStageEndigneType::Great) {
		TimeUpMax += BENEFITS_PREVIOS_RESULT;
	}
	//チュートリアルは別.
	if (m_enStageType == enStageType::Tutorial) {
		TimeUpMax = 1;
	}

	//前回のステージ初期化.
	m_enBeforeStageEndingType = enBeforeStageEndigneType::Nothing;

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
	//m_Camera.vPos = CAMERA_START_POS;
	//m_Camera.vLook = CAMERA_START_LOOK;
	m_pCCamera.reset(new CCameraGameMainStage());

	//表舞台のライトクラスのインスタンス化.
	m_pCFrontstageLight.reset(new CFrontstageLight());
	m_pCFrontstageLight->SettingAllLightPos(m_fStageDistanceMax);
	
	//チュートリアルでの初期化処理.
	if (m_enStageType != enStageType::Tutorial) {
		return;
	}
	m_TutorialFlag = TUTORIAL_START;
	m_ExplainFlag = EXPLAINING_FLAG;
	m_pCSpeakWorkGhost.reset(new CSpeakWorkGhost());
	m_pCDescriptionUIManager.reset(new CDescriptionUIManager());

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
		if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
			if (!(m_pCDescriptionUIManager->GetTutorialFlag() & (SELECT_GHOST_FLAG | DECIDE_GHOST_FLAG))) {
				return;
			}
		}
		GhostSelect();
	}


	//============================================.
	//ギミック選択処理関数.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		
		//チュートリアル時お化けの説明していなければ終了.
		if (m_ExplainFlag != 0) {
			if (m_enStageType == enStageType::Tutorial &&
				!(m_ExplainFlag & EXPLAINED_GHOST_FLAG)) {
				return;
			}
		}

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

				if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
					if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GHOST_FLAG)) {
						return;
					}
					//コメント進める.
					m_pCDescriptionUIManager->SetAdvanceComment();
				}

				//お化け選択後行動.
				m_ObjectSelectFlag = GHOST_ACT_SELECT_FLAG;
				//選択フラグ.
				m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetSelectFlag(true);

				if (m_ExplainFlag & EXPLAINING_FLAG) {
					//お化けの説明終了.
					m_ExplainFlag |= EXPLAINED_GHOST_FLAG;
				}
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

					//チュートリアル時にコメントを進める処理.
					if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
						//例外処理.
						if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GIMMICK_FLAG)) {
							return;
						}
						m_pCDescriptionUIManager->SetAdvanceComment();
					}

					//移動目的のオブジェクト座標取得.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
					//お化けの選択に戻る.
					m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
					//ギミック選択フラグ.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetChangeGimmickSelect(false);
					//ギミックカーソル非表示フラグ設定.
					m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);

					if (m_ExplainFlag & EXPLAINING_FLAG) {
						//ギミック説明終了.
						m_ExplainFlag |= EXPLAINED_GIMMICK_FLAG;
					}
				}
			}
		}
	}


//#ifdef _DEBUG
//	if (GetAsyncKeyState(VK_UP) & 0x0001) {
//		m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
//	}
//
//	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
//		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;
//	}
//#endif	//#ifdef _DEBUG.
}

//========================================.
//		お化け選択処理関数.
//========================================.
void CMainStage::GhostSelect()
{
	bool MoveSelectFlag = false;	//お化け選択移動フラグ.

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GHOST_NUM]++;

		if (m_SelectNum[GHOST_NUM] >= static_cast<int>(m_pCWorkGhost.size())) {
			m_SelectNum[GHOST_NUM] = m_pCWorkGhost.size() - 1;
		}
		MoveSelectFlag = true;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GHOST_NUM]--;

		if (m_SelectNum[GHOST_NUM] < 0) {
			m_SelectNum[GHOST_NUM] = 0;
		}
		MoveSelectFlag = true;
	}

	if (MoveSelectFlag == true) {
		const int GHOST_TYPE_NUM = static_cast<int>(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetSurpriseObjectType());
		
		if (m_pCSpeakWorkGhost != nullptr) {
			//お化け選択に関係するすべてのフラグ.
			const unsigned int RELATED_TO_GHOST_ALL_FLAG = GHOST_SELECTION_FLAG | GHOST_ACT_SELECT_FLAG;
			//お化け選択している時のみ設定可能.
			if (m_ObjectSelectFlag & RELATED_TO_GHOST_ALL_FLAG) {
				m_pCSpeakWorkGhost->SetGhostTypeNum(GHOST_TYPE_NUM);
				m_vSelectGhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
			}
		}

		if (m_pCDescriptionUIManager != nullptr) {
			//選択移動カウント追加処理関数.
			m_pCDescriptionUIManager->SetAddSelectMoveCount();
		}
	}
}

//========================================.
//		ギミック選択処理関数.
//========================================.
void CMainStage::GimmickSelect()
{
	bool MoveSelectFlag = false;		//選択移動フラグ.

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]++;
		if (m_SelectNum[GIMMICK_NUM] >= m_pCMoveObjectManager->GetGimmickIconMax()) {
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickIconMax() - 1;
		}
		MoveSelectFlag = true;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]--;
		if (m_SelectNum[GIMMICK_NUM] < 0) {
			m_SelectNum[GIMMICK_NUM] = 0;
		}
		MoveSelectFlag = true;
	}

	if (MoveSelectFlag == true) {
		//選択移動カウント追加処理関数.
		if (m_pCDescriptionUIManager != nullptr) {
			m_pCDescriptionUIManager->SetAddSelectMoveCount();
		}
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
	//チュートリアル時のカメラ移動.
	//if(m_bTutorialCameraMove & CAMERA_MOVE_START_FLAG){
	//	if (m_Camera.vPos.x > 11.0f) {
	//		m_Camera.vPos.x -= 0.6f;
	//		m_Camera.vLook.x = m_Camera.vPos.x;
	//		return;
	//	}

	//	const D3DXVECTOR3 vSeePeopleOldPos = D3DXVECTOR3(m_Camera.vPos.x, m_stOldCamera.vPos.y, m_stOldCamera.vPos.z);
	//	const D3DXVECTOR3 vOldPos_Camera = vSeePeopleOldPos - CAMERA_PEOPLE_SEE_POS;
	//	const float	vLength = D3DXVec3Length(&(vOldPos_Camera));
	//	const D3DXVECTOR3 vRato = vOldPos_Camera / vLength;

	//	m_Camera.vPos -= 0.2f * vRato;

	//	if(m_Camera.vPos.y < CAMERA_PEOPLE_SEE_POS.y){
	//		m_Camera.vPos = CAMERA_PEOPLE_SEE_POS;
	//	}

	//	const D3DXVECTOR3 vSeePeopleOldLook = D3DXVECTOR3(m_Camera.vLook.x, m_stOldCamera.vLook.y, m_stOldCamera.vLook.z);
	//	const D3DXVECTOR3 vOldLook_SeeLook = m_stOldCamera.vLook - CAMERA_PEOPLE_SEE_LOOK;
	//	const float	vLookLength = D3DXVec3Length(&vOldLook_SeeLook);
	//	const D3DXVECTOR3 vLookRaito = vOldLook_SeeLook / vLookLength;

	//	m_Camera.vLook -= 0.2f * vLookRaito;

	//	if (m_Camera.vPos.y < CAMERA_PEOPLE_SEE_LOOK.y) {
	//		m_Camera.vLook = CAMERA_PEOPLE_SEE_LOOK;
	//	}

	//	return;
	//}

	//if (m_bTutorialCameraMove & CAMERA_MOVE_RETURN_FLAG) {
	//	//現在選択しているお化けのところへカメラを戻す.
	//	const D3DXVECTOR3 vSelectGhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	//	m_Camera.vPos = CAMERA_START_POS;
	//	m_Camera.vPos.x = vSelectGhostPos.x;
	//	m_Camera.vLook = CAMERA_START_LOOK;
	//	m_Camera.vLook.x = vSelectGhostPos.x;
	//	return;
	//}

	//D3DXVECTOR3 m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	////お化け選択時.
	//if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
	//	m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	//}
	////ギミック選択時.
	//if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
	//	m_GhostPos = m_pCMoveObjectManager->GetGimmickPos();
	//}
	////カメラ座標と注視点の座標設定.
	//m_Camera.vLook.x = m_Camera.vPos.x = m_GhostPos.x;
	
}

//=========================================.
//		スポットライト更新処理関数.
//=========================================.
void CMainStage::SpotLightUpdate()
{
}

//==========================================.
//		評価処理関数.
//==========================================.
CMainStage::enBeforeStageEndigneType CMainStage::Evalute()
{
	const unsigned int EVALUTION_FLAG = m_pCSurpriseGage->GetEvalutionFlag();

	if (EVALUTION_FLAG & m_pCSurpriseGage->BAD_FLAG) {
		return enBeforeStageEndigneType::Bad;
	}

	if (EVALUTION_FLAG & m_pCSurpriseGage->GOOD_FLAG) {
		return enBeforeStageEndigneType::Good;
	}

	return enBeforeStageEndigneType::Great;
}