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
	//カメラの更新処理関数.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		m_pCCamera->SetTargetPos(m_pCMoveObjectManager->GetGimmickPos());
	}
	else {
		m_pCCamera->SetTargetPos(m_pCWorkghostManager->GetSelectGhostPos());
	}
	m_pCCamera->Update();
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//表舞台ライトクラスの更新処理関数.
	m_pCFrontstageLight->SetCameraPos(m_vCameraPos);
	m_pCFrontstageLight->Update();

	//静的オブジェクト更新処理関数.
	m_pCStaticObjectManager->SetCameraPos(m_vCameraPos);
	m_pCStaticObjectManager->Updata();

	//働くお化け更新処理関数.
	UpdateWorkGhost();

	//追加ポイント量.
	m_pCSurpriseGage->AddSurprisePoint(m_pCPeopleManager->GetAddSurprisePoint());

	//動的オブジェクトの更新処理関数.
	m_pCMoveObjectManager->SetCameraPos(m_vCameraPos);
	m_pCMoveObjectManager->SetSelectionNum(m_SelectNum[GIMMICK_NUM]);
	m_pCMoveObjectManager->SetGhostPos(m_pCWorkghostManager->GetAllGhostPos());
	m_pCMoveObjectManager->UpDate();


	//ギミック選択フラグ.
	if (m_pCWorkghostManager->GetChangeGimmickSelectFlag() == true) {
		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;

		//ギミックカーソル表示フラグ設定.
		m_pCMoveObjectManager->SetGimmickCurosrDispFlag(true);
	}

	//マップ上のお化けカーソル更新処理関数.
	m_pCMapGhostCursor->SetCharaPos(m_pCWorkghostManager->GetSelectGhostPos());
	m_pCMapGhostCursor->UpDate();

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

			m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->EXPLAINING_FLAG);
			m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->SELECT_WAIT_FLAG);
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
				//お化けに視点を戻す.
				if (m_pCCamera->GetMoveFlag() & m_pCCamera->PEOPLE_LOOK_FLAG) {
					m_pCCamera->SetMoveFlag(m_pCCamera->GHOST_LOOK_FLAG);
				}
				return;
			}
			if (m_pCDescriptionUIManager->GetStartLatestFlag() & SeePeople) {
				//人に視点を移動.
				m_pCCamera->SetMoveFlag(m_pCCamera->PEOPLE_LOOK_FLAG);
				//差分取得処理関数.
				m_pCCamera->AcquisitionDifference();

			}
		}

	}

	//人の更新処理関数.
	m_pCPeopleManager->Update();

	//閉店までの時間更新処理関数.
	m_pCClosedTime->Update();
	m_pCClosedTime->GiveBornusTime(m_pCSurpriseGage->GetBornusGetFlag());

	//評価処理関数.
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
	//ライト情報.
	const LIGHT m_Light = m_pCFrontstageLight->GetLight();
	//カメラ座標.
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//ステージマップの描画.
	m_pCStageMap->Render();

	//マップ上のお化けカーソル描画処理関数.
	m_pCMapGhostCursor->Render();

	//お化けの描画.
	m_pCWorkghostManager->Render(m_mView, m_mProj, m_Light, m_vCameraPos);


	//動くオブジェクトスイッチの描画.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_Light);
	//静的オブジェクトの描画.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//動くオブジェクト描画処理.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_Light);

	//お化け体力アイコン描画処理関数.
	m_pCWorkghostManager->RenderIcon();

	//人の描画処理関数.
	m_pCPeopleManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);

	//動くオブジェクトのエフェクト描画.
	m_pCMoveObjectManager->EffectRender();
	
	//ゲーム内でのお化けのカーソル描画処理関数.
	m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_vCameraPos);
	m_pCGameGhostCursor->Render();

	//お化けの選択描画処理関数.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		m_pCWorkghostManager->RenderSelectUI();
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
	//お化け管理クラスをインスタンス化.
	m_pCWorkghostManager.reset(new CMainStageWorkGhostManager());
	m_pCWorkghostManager->Init(GhostFilenum, m_column, m_pCStaticObjectManager->OBJECT_WIDTH);

	//動的オブジェクトインスタンス化.
	m_pCMoveObjectManager.reset(new CMoveObjectManager(ObjFileNum, m_column));
	//m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkGhost.size());
	m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkghostManager->GetAllGhostNum());
	
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
	TimeUpMax = 1;

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

	//カメラクラスのインスタンス化.
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
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			//お化けが驚かしているときのみ.
			if (m_pCWorkghostManager->DecisionSelectSurprise() == true) {

				if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
					if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GHOST_FLAG)) {
						return;
					}

					if (m_pCDescriptionUIManager->GetAppearancedAllFont() == false) {
						return;
					}

					//コメント進める.
					m_pCDescriptionUIManager->SetAdvanceComment();
				}
				//選択フラグ.
				m_pCWorkghostManager->SetSelectFlag(true);

				//お化け選択後行動.
				m_ObjectSelectFlag = GHOST_ACT_SELECT_FLAG;

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
			m_pCWorkghostManager->SetSelectStop();
			//お化けの選択に戻る.
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
			//ギミック選択フラグ.
			m_pCWorkghostManager->SetChangeGimmickSelect(false);
			//ギミックカーソル非表示フラグ設定.
			m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (m_pCMoveObjectManager->GetUsedGimmickFlag(m_SelectNum[GIMMICK_NUM]) == false) {
				//お化けの種類とギミックの種類があっているときのみ.
				if (m_pCWorkghostManager->GetSurpriseObjectType() ==
					m_pCMoveObjectManager->GetSurpriseObjectType()) {
					if (m_pCWorkghostManager->GetUseGimmickNum() >= 0) {
						m_pCMoveObjectManager->SetUsedGimmickFlag(m_pCWorkghostManager->GetUseGimmickNum(), false);
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
					m_pCWorkghostManager->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
					//お化けの選択に戻る.
					m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
					//ギミック選択フラグ.
					m_pCWorkghostManager->SetChangeGimmickSelect(false);
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
	//お化け選択移動フラグ.
	bool MoveSelectFlag = m_pCWorkghostManager->SelectGhost();	

	if (MoveSelectFlag == true) {
		const int GHOST_TYPE_NUM = static_cast<int>(m_pCWorkghostManager->GetSurpriseObjectType());
		
		if (m_pCSpeakWorkGhost != nullptr) {
			//お化け選択に関係するすべてのフラグ.
			const unsigned int RELATED_TO_GHOST_ALL_FLAG = GHOST_SELECTION_FLAG | GHOST_ACT_SELECT_FLAG;
			//お化け選択している時のみ設定可能.
			if (m_ObjectSelectFlag & RELATED_TO_GHOST_ALL_FLAG) {
				m_pCSpeakWorkGhost->SetGhostTypeNum(GHOST_TYPE_NUM);
				m_vSelectGhostPos = m_pCWorkghostManager->GetSelectGhostPos();
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

//===========================================.
//		働くお化け更新処理関数.
//===========================================.
void CMainStage::UpdateWorkGhost()
{
	//チュートリアルかどうか.
	if (m_enStageType == enStageType::Tutorial) {
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->TUTORIAL_STAGE_FLAG);
	}

	//説明終了.
	if (m_ExplainFlag != 0) {
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->EXPLAINING_FLAG);
	}

	if (m_pCDescriptionUIManager != nullptr) {
		//チュートリアルフラグ上げ下げ処理関数.
		UnloadSetTrueTutrialFlag();
	}

	//働くお化け管理クラスの更新処理関数.
	m_pCWorkghostManager->SetStageDisntaceMax(m_pCStaticObjectManager->GetStageDistanceMax());
	m_pCWorkghostManager->SetGimmickPos(m_pCMoveObjectManager->GetAllGimmickPos());
	m_pCWorkghostManager->SetPeoplePos(m_pCPeopleManager->GetHumanPos());
	m_pCWorkghostManager->Update();

	//他クラスに値参照.
	for (unsigned int ghost = 0; ghost < m_pCWorkghostManager->GetAllGhostNum(); ghost++) {
		//驚いている人番号取得.
		m_pCPeopleManager->SetNowHumanSurprise(m_pCWorkghostManager->GetNearPeopleNum(ghost));

		//オブジェクト使用フラグ.
		const std::tuple<int, bool> tUseObjFlag = std::tuple<int, bool>(m_pCWorkghostManager->GetUseGimmick(ghost));
		if (std::get<0>(tUseObjFlag) >= 0) {
			m_pCMoveObjectManager->SetUsedGimmickFlag(std::get<0>(tUseObjFlag), std::get<1>(tUseObjFlag));
		}

		//コメント進めるフラグ.
		if (m_pCDescriptionUIManager != nullptr) {
			if (m_pCWorkghostManager->GetTutorialAddCommentFlag(ghost) == true) {
				m_pCDescriptionUIManager->SetAdvanceComment();
			}
		}

		//オブジェクト上げ下げフラグ.
		const std::tuple<int, unsigned int> tUpDownFlag = std::tuple<int, unsigned int>(m_pCWorkghostManager->GetObjUpDownFlag(ghost));
		if (std::get<1>(tUpDownFlag) != 0) {
			if (std::get<1>(tUpDownFlag) & m_pCWorkghostManager->OBJ_DOWN_FLAG) {
				m_pCMoveObjectManager->SetGimmickMoveFlag(std::get<0>(tUseObjFlag), m_pCMoveObjectManager->DOWN_FLAG);
				continue;
			}
			m_pCMoveObjectManager->SetGimmickMoveFlag(std::get<0>(tUseObjFlag), m_pCMoveObjectManager->UP_FLAG);
		}

	}

	//お化け選択フラグ.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		if (m_pCWorkghostManager->GetSelectGhostFlag() == false) {
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
		}
	}

	//お化け休憩フラグ.	
	bool GhostRestFlag = m_pCWorkghostManager->DecisionSelectRest();
	m_pCGameGhostCursor->SetRestFlag(GhostRestFlag);
	m_pCGameGhostCursor->SetCharacterPos(m_pCWorkghostManager->GetSelectGhostPos());

	//ゲーム内でのお化けのカーソル更新処理関数.
	m_pCGameGhostCursor->UpDate();

}

//========================================.
//	チュートリアルフラグ上げ下げ処理.
//========================================.
void CMainStage::UnloadSetTrueTutrialFlag()
{
	if (m_ExplainFlag == 0) {
		return;
	}

	//お化けを決めるフラグ.
	if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == false) {
		//フラグを立てる.
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->GHOST_DECIDE_FLAG);
	}
	else {
		//フラグを降ろす.
		m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->GHOST_DECIDE_FLAG);
	}

	//選択待機フラグ.
	if (m_pCDescriptionUIManager->GetAppearancedAllFont() == false &&
		m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		//フラグを立てる.
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->SELECT_WAIT_FLAG);
	}
	else {
		//フラグを降ろす.
		m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->SELECT_WAIT_FLAG);
	}

}
