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
	, m_pCPlaySoundManager		(CPlaySoundManager::GetPlaySoundManager())
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


	//動的オブジェクトの更新処理関数.
	m_pCMoveObjectManager->SetSurpriseObjToGhost(m_pCWorkghostManager->GetSurpriseObjectType());
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

	//チュートリアル処理関数.
	if (Tutorial(ControlFlag) == false) {
		return;
	}

	if (ControlFlag == true) {
		//操作処理関数.
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

	if (m_pCCamera->GetNotRenderMap() == false) {
		//ステージマップの描画.
		m_pCStageMap->Render();

		//マップ上のお化けカーソル描画処理関数.
		m_pCMapGhostCursor->Render();

		//お化けの描画.
		m_pCWorkghostManager->SetPauseFlag(m_bPauseFlag);
		m_pCWorkghostManager->Render(m_mView, m_mProj, m_Light, m_vCameraPos);
	}

	//動くオブジェクトスイッチの描画.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_Light);
	//静的オブジェクトの描画.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//動くオブジェクト描画処理.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_Light);

	//お化け体力アイコン描画処理関数.
	m_pCWorkghostManager->RenderIcon();

	//人の描画処理関数.
	m_pCPeopleManager->SetNotRenderIcon(m_pCCamera->GetNotRenderMap());
	m_pCPeopleManager->SetPauseFlag(m_bPauseFlag);
	m_pCPeopleManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);

	//動くオブジェクトのエフェクト描画.
	bool m_bUIRender = true;
	if (m_pCCamera->GetNotRenderMap() == true) {
		m_bUIRender = false;
	}
	m_pCMoveObjectManager->SetRenderUI(m_bUIRender);
	m_pCMoveObjectManager->SetPauseFlag(m_bPauseFlag);
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
		const unsigned int RELATED_TO_GHOST_ALL_FLAG = SELECT_GHOST_FLAG | GIMMICK_SELECTION_FLAG;
		if (m_vCameraPos.x == m_vSelectGhostPos.x &&
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
	const int FileNum = 0;

	//オブジェクトファイル番号.
	const int ObjFileNum = static_cast<int>(CFileResource::enStageType::ObjectPos);

	//読み込みクラスアドレス取得.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	
	m_pCStaticObjectManager.reset(new CStaticObjectManager(ObjFileNum, m_StageNum));

	//ステージの長さ最大数.
	float m_fStageDistanceMax = m_pCStaticObjectManager->GetStageDistanceMax();

	const int GhostFilenum = static_cast<int>(CFileResource::enStageType::GhostPos);
	//お化け管理クラスをインスタンス化.
	m_pCWorkghostManager.reset(new CMainStageWorkGhostManager());
	m_pCWorkghostManager->Init(GhostFilenum, m_StageNum, m_pCStaticObjectManager->OBJECT_WIDTH);

	//動的オブジェクトインスタンス化.
	m_pCMoveObjectManager.reset(new CMoveObjectManager(ObjFileNum, m_StageNum));
	m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkghostManager->GetAllGhostNum());
	

	//人管理クラス設定.
	const int PeopleFileNum = static_cast<int>(CFileResource::enStageType::PeopleComeOder);
	m_pCPeopleManager.reset(new CPeopleManager());
	m_pCPeopleManager->Init( PeopleFileNum, m_StageNum, m_fStageDistanceMax);
	
	//ギミックの上にお化けがいるかの判定処理.
	const std::vector<D3DXVECTOR3> m_vGimmickPos = m_pCMoveObjectManager->GetAllGimmickPos();
	const std::vector<D3DXVECTOR3> m_vWorkGhostPos = m_pCWorkghostManager->GetAllGhostPos();
	const float			GIMMICK_UP_DECISION = 0.1f;								//ギミックの上に乗っているかの判定差分.
	for (unsigned int gimmick = 0; gimmick < m_vGimmickPos.size(); gimmick++) {
		for (unsigned int ghost = 0; ghost < m_vWorkGhostPos.size(); ghost++) {
			if (fabsf(m_vWorkGhostPos[ghost].x - m_vGimmickPos[gimmick].x) < GIMMICK_UP_DECISION) {
				m_pCWorkghostManager->SetUseGimmickNum(ghost, gimmick);	
				m_pCMoveObjectManager->SetUsedGimmickFlag(gimmick, true);
			}
		}
	}

	//====UI系のインスタンス化====.
	//ステージ.
	m_pCStageMap.reset(new CStageMap());
	//マップ上のお化けのカーソル.
	m_pCMapGhostCursor.reset(new CMapGhostCursor());
	m_pCMapGhostCursor->SetStageMax(m_fStageDistanceMax);
	//ゲーム内お化けのカーソル.
	m_pCGameGhostCursor.reset(new CGameGhostCursor());
	//前回のステージ初期化.
	m_enBeforeStageEndingType = enBeforeStageEndigneType::Nothing;

	//閉店までの時間.
	m_pCClosedTime.reset(new CClosedTime(m_StageNum));

	//驚きゲージ.
	m_pCSurpriseGage.reset(new CSurpriseGage(m_StageNum));

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

				//ギミック番号取得.
				m_SelectNum[GIMMICK_NUM] = m_pCWorkghostManager->GetUseGimmickNumToSelectGhost();

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
		if ((GetAsyncKeyState(VK_BACK) & 0x0001) || 
			m_pCWorkghostManager->GetRestSelectGhostFlag() == true) {
			//説明中は処理してほしくない.
			if (m_ExplainFlag != 0) {
				return;
			}
			m_pCWorkghostManager->SetSelectStop();
			//お化けの選択に戻る.
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
			//ギミック選択フラグ.
			m_pCWorkghostManager->SetChangeGimmickSelect(false);
			//ギミックカーソル非表示フラグ設定.
			m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);
			//ギミック選択解除SEの再生.
			m_pCPlaySoundManager->SetPlaySE(enSEType::ReturnFromGimmickSelect);
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (m_pCMoveObjectManager->GetUsedGimmickFlag(m_SelectNum[GIMMICK_NUM]) == true) {
				//ギミックが使用されていたら処理しない.
				m_pCPlaySoundManager->SetPlaySE(enSEType::NotSelect);
				return;
			}


			//チュートリアル時にコメントを進める処理.
			if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
				//例外処理.
				if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GIMMICK_FLAG)) {
					return;
				}
				m_pCDescriptionUIManager->SetAdvanceComment();
			}

			//使用するギミック番号の変更.
			if (m_pCWorkghostManager->GetUseGimmickNumToSelectGhost() >= 0) {
				m_pCMoveObjectManager->SetUsedGimmickFlag(m_pCWorkghostManager->GetUseGimmickNumToSelectGhost(), false);
			}
			m_pCMoveObjectManager->SetUsedGimmickFlag(m_SelectNum[GIMMICK_NUM], true);
			m_pCWorkghostManager->SetUseGimmickNumToSelectGhost(m_SelectNum[GIMMICK_NUM]);

			//移動目的のオブジェクト座標取得.
			m_pCWorkghostManager->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
			//お化けの選択に戻る.
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
			//ギミック選択フラグ.
			m_pCWorkghostManager->SetChangeGimmickSelect(false);
			//ギミックカーソル非表示フラグ設定.
			m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);

			//選択SE再生処理.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GimmickDecide);

			if (m_ExplainFlag & EXPLAINING_FLAG) {
				//ギミック説明終了.
				m_ExplainFlag |= EXPLAINED_GIMMICK_FLAG;
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
	//選択移動フラグ.
	bool MoveSelectFlag = false;					
	//ギミックタイプ番号.
	const int GimmickType = static_cast<int>(m_pCWorkghostManager->GetSurpriseObjectType());
	//ギミック変更番号.
	int	ChangeSelectNum = m_pCMoveObjectManager->FindSelectGimmickNumByType(GimmickType, m_SelectNum[GIMMICK_NUM]);


	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		//最大値の手前の数値.
		const int BeforeGimmickMax = m_pCMoveObjectManager->GetGimmickMaxByType(GimmickType) - 1;
		//同じギミックに選択を移動する処理.
		if (ChangeSelectNum < BeforeGimmickMax) {
			ChangeSelectNum++;
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickNumByType(GimmickType, ChangeSelectNum);
			MoveSelectFlag = true;
			//カーソル移動SEの再生.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickMove);
		}
		else {
			//カーソル移動上限SEの再生.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickSelectLimit);
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		//同じギミックに選択を移動する処理.
		if (ChangeSelectNum > 0) {
			ChangeSelectNum--;
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickNumByType(GimmickType, ChangeSelectNum);
			MoveSelectFlag = true;
			//カーソル移動SEの再生.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickMove);
		}
		else {
			//カーソル移動上限SEの再生.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickSelectLimit);
		}
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
//		チュートリアル処理関数.
//===========================================.
bool CMainStage::Tutorial(const bool& ControlFlag)
{
	//チュートリアルまでの処理(ここでお化けとギミックの時は例外の処理を行わなければならない).
	if (m_enStageType == enStageType::Tutorial && (m_ExplainFlag & EXPLAINING_FLAG)) {

		//フェード中は例外処理.
		if (ControlFlag == false) {
			return false;

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
		}
	}

	if (m_pCDescriptionUIManager != nullptr) {
		//コメント進めるときは下まで処理しない.
		if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == true) {
			const unsigned int DESCRIPTION_LAST_FLAG = SeePeople | DescriptionEnd;
			if (!(m_pCDescriptionUIManager->GetStartLatestFlag() & DESCRIPTION_LAST_FLAG)) {
				return false;
			}
		}
	}

	return true;

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
		//追加ポイント量.
		m_pCSurpriseGage->AddSurprisePoint(m_pCPeopleManager->GetAddSurprisePoint());

		//コメント進めるフラグ.
		if (m_pCDescriptionUIManager != nullptr) {
			if (m_pCWorkghostManager->GetTutorialAddCommentFlag(ghost) == true) {
				m_pCDescriptionUIManager->SetAdvanceComment();
			}
		}

		//オブジェクト上げ下げフラグ.
		const unsigned int UpDownFlag = m_pCWorkghostManager->GetUpDownFlag(ghost);
		const int	GimmickNum = m_pCWorkghostManager->GetUseGimmickNum(ghost);
		if (UpDownFlag != 0 && GimmickNum >= 0) {
			if (UpDownFlag & m_pCWorkghostManager->OBJ_DOWN_FLAG) {
				m_pCMoveObjectManager->SetGimmickMoveFlag(GimmickNum, m_pCMoveObjectManager->DOWN_FLAG);
				continue;
			}
			m_pCMoveObjectManager->SetGimmickMoveFlag(GimmickNum, m_pCMoveObjectManager->UP_FLAG);
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
