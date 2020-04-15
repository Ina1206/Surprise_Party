#include "CMainStage.h"
#include <random>

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
	, m_vLightPos				()
	, m_enStageType				(enStage)
	, m_ExplainFlag				(0)
	, m_bDispTextFlag			(true)
	, m_pCSpeakTutorial			(nullptr)
	, m_pCSpeakWorkGhost		(nullptr)
	, m_pCArrow					(nullptr)
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
	//スポットライト更新処理関数.
	SpotLightUpdate();

	//静的オブジェクト更新処理関数.
	m_pCStaticObjectManager->SetCameraPos(m_Camera.vPos);
	m_pCStaticObjectManager->Updata();

	//お化け.
	std::vector<D3DXVECTOR3> m_vGhostPos(m_pCWorkGhost.size());							//お化け座標.
	std::vector<D3DXVECTOR3> m_vGimmickPos = m_pCMoveObjectManager->GetAllGimmickPos();	//ギミック座標.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {

		//ステージ全体の距離取得.
		m_pCWorkGhost[ghost]->SetStageDistanceMax(m_pCStaticObjectManager->GetStageDistanceMax());

		//ギミックと人の座標取得.
		m_pCWorkGhost[ghost]->SetSurprisePosInfo(m_vGimmickPos, m_pCPeopleManager->GetHumanPos());

		//チュートリアルフラグ.
		if (m_enStageType == enStageType::Tutorial) {
			m_pCWorkGhost[ghost]->SetTutorialFlag(true);
		}

		//選択決定フラグ設定.
		if (m_pCSpeakTutorial->GetAdvanceCommentFlag() == false) {
			m_pCWorkGhost[ghost]->SetDecideSelectFlag(true);
		}
		else {
			m_pCWorkGhost[ghost]->SetDecideSelectFlag(false);
		}

		//お化け更新処理関数.
		m_pCWorkGhost[ghost]->Update();

		//チュートリアル時コメント一つ進める処理.
		if (m_pCSpeakTutorial != nullptr) {
			if (m_pCWorkGhost[ghost]->GetTutorialAddCommentFlag() == true) {
				m_pCSpeakTutorial->AdvanceOnceComment();
			}
		}

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
	m_pCSurpriseGage->Update();

	//チュートリアルまでの処理(ここでお化けとギミックの時は例外の処理を行わなければならない).
	if (m_enStageType == enStageType::Tutorial && (m_ExplainFlag & EXPLAINING_FLAG)) {

		if (ControlFlag == false) {
			return;

		}

		//チュートリアル会話更新処理関数.
		if (m_pCSpeakTutorial != nullptr) {
			m_pCSpeakTutorial->Update();
		}
		if (GetAsyncKeyState('Q') & 0x8000) {
			//説明終了ゲームを動かすフラグ.
			m_ExplainFlag = 0;
		}

		if (!(m_pCSpeakTutorial->GetTutorialFlag() & m_pCSpeakTutorial->SELECT_GHOST_FLAG)) {
			return;
		}
	}

	if (m_pCSpeakTutorial != nullptr) {
		//コメント進めるときは下まで処理しない.
		if (m_pCSpeakTutorial->GetAdvanceCommentFlag() == true) {
			return;
		}
	}

	//操作処理関数.
	if (ControlFlag == true) {
		Control();

		//矢印
		const unsigned int SELECT_ALL_FLAG = GHOST_SELECTION_FLAG | GIMMICK_SELECTION_FLAG;
		if (m_ObjectSelectFlag & SELECT_ALL_FLAG) {
			if (m_pCArrow != nullptr) {
				//動かす矢印フラグ.
				const unsigned int MOVE_ARROW_FLAG = m_pCArrow->USING_RIGHT_FLAG | m_pCArrow->USING_LEFT_FLAG;
				m_pCArrow->SetUsingArrowFlag(MOVE_ARROW_FLAG);
				//矢印更新処理関数.
				m_pCArrow->Update();
			}
		}

		//説明中例外処理.
		if (m_ExplainFlag & EXPLAINING_FLAG) {
			return;
		}
	}

	//人の更新処理関数.
	m_pCPeopleManager->Update();


	//閉店までの時間更新処理関数.
	m_pCClosedTime->Update();
	m_pCClosedTime->GiveBornusTime(m_pCSurpriseGage->GetBornusGetFlag());

	if (m_pCSurpriseGage->GetSurprisePointMax() == true) {
		m_enBeforeStageEndingType = enBeforeStageEndigneType::Great;
	}

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

	//	if (GetAsyncKeyState('S') & 0x8000) {
	//		m_stLight.vPos.y += 0.1f;
	//	}
	//	if (GetAsyncKeyState('X') & 0x8000) {
	//		m_stLight.vPos.y -= 0.1f;
	//	}
	//	if (GetAsyncKeyState('Z') & 0x8000) {
	//		m_stLight.vPos.z += 0.1f;
	//	}
	//	if (GetAsyncKeyState('C') & 0x8000) {
	//		m_stLight.vPos.z -= 0.1f;
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



	//動くオブジェクトスイッチの描画.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_stLight);
	//静的オブジェクトの描画.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_Camera.vPos, m_stLight);
	//動くオブジェクト描画処理.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_stLight);

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

	//テキスト表示.
	if (m_bDispTextFlag == false) {
		return;
	}

	//チュートリアル会話描画処理.
	if (m_pCSpeakTutorial != nullptr) {
		m_pCSpeakTutorial->Render();
	}

	//働くお化け会話クラス.
	if (m_pCSpeakWorkGhost != nullptr) {
		m_pCSpeakWorkGhost->Render();
	}

	//矢印クラス.
	if (m_pCArrow != nullptr) {
		//会話文を進めるときは例外処理.
		if (m_pCSpeakTutorial->GetAdvanceCommentFlag() == true) {
			return;
		}

		//選択時のみ描画.
		if (m_ObjectSelectFlag == GHOST_SELECTION_FLAG ||
			m_ObjectSelectFlag == GIMMICK_SELECTION_FLAG) {
			
			const unsigned int SELECT_ALL_TUTORIAL_FLAG = m_pCSpeakTutorial->SELECT_GHOST_FLAG | m_pCSpeakTutorial->SELECT_GIMMICK_FLAG;
			if (m_pCSpeakTutorial->GetTutorialFlag() & SELECT_ALL_TUTORIAL_FLAG) {
				m_pCArrow->Render();
			}
		}
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
	m_stLight.vPos = D3DXVECTOR3(0.0f , 21.7f, -0.5f);
	m_stLight.fIntensity = 119.0f;
	m_stLight.m_fLightWidth = 10.9f;
	m_stLight.fLightPosWidth = 20.0f;
	m_stLight.vLightColor = D3DXVECTOR3(0.5f, 0.5f, 1.0f);
	m_stLight.m_fLightMax = 3.0f;
	D3DXMatrixIdentity(&m_stLight.mRot);

	//ライトの配置横幅.
	float m_LightWidth = m_stLight.fLightPosWidth;
	for (int Light = 0; m_LightWidth * Light <= m_fStageDistanceMax; Light++) {
		D3DXVECTOR3 vLightPos = m_stLight.vPos;
		vLightPos.x = m_LightWidth * Light;
		m_vLightPos.push_back(vLightPos);
	}
	
	D3DXMATRIX mYaw, mPich, mRoll;
	D3DXMatrixRotationY(&mYaw, 0.0f);
	D3DXMatrixRotationX(&mPich, 0.0f);
	D3DXMatrixRotationZ(&mRoll, 0.0f);
	m_stLight.mRot = mYaw * mPich * mRoll;

	//チュートリアルでの初期化処理.
	if (m_enStageType != enStageType::Tutorial) {
		return;
	}
	m_TutorialFlag = TUTORIAL_START;
	m_ExplainFlag = EXPLAINING_FLAG;
	m_pCSpeakTutorial.reset(new CSpeakTutorial());
	m_pCSpeakWorkGhost.reset(new CSpeakWorkGhost());
	m_pCArrow.reset(new CArrow());
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
		if (m_pCSpeakTutorial != nullptr) {
			if (!(m_pCSpeakTutorial->GetTutorialFlag() & m_pCSpeakTutorial->SELECT_GHOST_FLAG)) {
				return;
			}
		}
		GhostSelect();
	}


	//============================================.
	//ギミック選択処理関数.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		
		//チュートリアル時お化けの説明していなければ終了.
		if (m_enStageType == enStageType::Tutorial &&
			!(m_ExplainFlag & EXPLAINED_GHOST_FLAG)) {
			return;
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

				if (m_pCSpeakTutorial != nullptr) {
					if (!(m_pCSpeakTutorial->GetTutorialFlag() & m_pCSpeakTutorial->DECIDE_GHOST_FLAG)) {
						return;
					}
					//コメント進める.
					m_pCSpeakTutorial->AdvanceOnceComment();
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

					//移動目的のオブジェクト座標取得.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
					//お化けの選択に戻る.
					m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
					//ギミック選択フラグ.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetChangeGimmickSelect(false);
					//ギミックカーソル非表示フラグ設定.
					m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);

					//チュートリアル時にコメントを進める処理.
					if (m_pCSpeakTutorial != nullptr) {
						m_pCSpeakTutorial->AdvanceOnceComment();
					}

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
			m_pCSpeakWorkGhost->SetGhostTypeNum(GHOST_TYPE_NUM);
		}

		if (m_pCSpeakTutorial != nullptr) {
			//選択移動カウント追加処理関数.
			m_pCSpeakTutorial->AddSelectMoveCount();
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
		if (m_pCSpeakTutorial != nullptr) {
			m_pCSpeakTutorial->AddSelectMoveCount();
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

//=========================================.
//		スポットライト更新処理関数.
//=========================================.
void CMainStage::SpotLightUpdate()
{
	for (unsigned int light = 0; light < m_vLightPos.size(); light++) {
		if (m_Camera.vPos.x + 16.0f > m_vLightPos[light].x &&
			m_Camera.vPos.x - 16.0f < m_vLightPos[light].x) {
			m_stLight.vPos = m_vLightPos[light];
			break;
		}
	}
}