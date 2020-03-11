#include "CMoveObjectManager.h"

CMoveObjectManager::CMoveObjectManager() 
	: CMoveObjectManager	(0, 0)
{

}

CMoveObjectManager::CMoveObjectManager(const int& FileNum, const int& StageNum)
	: m_mView				()
	, m_mProj				()
	, m_pCMoveObjectBase	()
	, m_vMoveObjectPos		()
	, m_vAttachObjPos		()
	, m_vAttachRot			()
	, m_pCFileResource		(nullptr)
	, m_pCGimmickIcon		()
	, m_pCMapGimmicKCursor	(nullptr)
	, m_SelectionNum		(0)
	, m_pCGameGimmickCursor	(nullptr)
	, m_vGhostPos			()
	, m_GhostMax			(0)
	, m_ObjeMoveFlag		(NOT_MOVE_FALG)
	, m_bGimmickCursorDisp	(false)
	, m_DispPaintingMax		(0)
	, m_AttachedObjMoveFlag	(0)
	, m_FlowerSwingCnt		(0)
{
	//初期化処理関数.
	Init(FileNum, StageNum);
}

CMoveObjectManager::~CMoveObjectManager()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CMoveObjectManager::UpDate()
{
	//オブジェクト.
	for (int obj = 0; obj < static_cast<int>(enMoveObjectType::Max); obj++) {
		for (unsigned int allObj = 0; allObj < m_vMoveObjectPos.size(); allObj++) {
			if (obj == m_enMoveObjectType[allObj]) {
				if (m_vCameraPos.x + DISP_CAMERA_WIDHT > m_vMoveObjectPos[allObj].x &&
					m_vCameraPos.x - DISP_CAMERA_WIDHT < m_vMoveObjectPos[allObj].x) {
					//オブジェクト位置設定処理.
					m_pCMoveObjectBase[obj]->SetPos(m_vMoveObjectPos[allObj]);
					//カメラ表示フラグ.
					m_pCMoveObjectBase[obj]->SetCameraDispFlag();
					if (obj == static_cast<int>(enMoveObjectType::ObjectMoveSwitch)) {
						for (int attach = 1; attach < 2; attach++) {
							//座標.
							m_pCMoveObjectBase[obj]->SetAttachedObjPos(attach, m_vAttachObjPos[allObj]);
							//角度.
							m_pCMoveObjectBase[obj]->SetAttachedObjRot(attach, m_vAttachRot[allObj]);
						}

					}
				}
			}

			//移動処理.
			const unsigned int UP_DOWN_FLAG = DOWN_FLAG | UP_FLAG;
			if (m_ObjeMoveFlag[allObj] & UP_DOWN_FLAG) {
				//絵画.
				if (m_enSurpriseObjectType[allObj] == CGameObject::enSurpriseObjectType::Disp) {
					//絵画を落としたり上げる処理関数.
					PaintingUpDown(allObj);
					continue;
				}

				//スイッチ.
				SwitchPush(allObj, m_enSurpriseObjectType[allObj]);
			}

		}
		

		//更新処理関数.
		m_pCMoveObjectBase[obj]->UpDate();
	}

	//机と花瓶の移動処理関数.
	for (unsigned int attachedObj = 0; attachedObj < m_AttachedObjMoveFlag.size(); attachedObj++) {
		if (m_AttachedObjMoveFlag[attachedObj] != 0) {
			Table_VaseFlowerMove(attachedObj);
		}
	}

	//カーソル更新処理.
	//マップUI.
	m_pCGimmickIcon[m_SelectionNum]->SetSelectingFlag();
	m_pCMapGimmicKCursor->SetCharaPos(m_vMoveObjectPos[m_SelectionNum]);
	m_pCMapGimmicKCursor->UpDate();
	//ゲーム内UI.
	m_pCGameGimmickCursor->SetCharacterPos(m_vMoveObjectPos[m_SelectionNum]);
	m_pCGameGimmickCursor->SetUnSelectableFlag(m_bUsedGimmickFlag[m_SelectionNum]);
	m_pCGameGimmickCursor->UpDate();
	
	for (unsigned int icon = 0; icon < m_pCGimmickIcon.size(); icon++) {
		//ギミックアイコンの更新処理関数.
		m_pCGimmickIcon[icon]->UpDate();

		m_bUsedGimmickFlag[icon] = false;
	}
}

//======================================.
//		描画処理関数.
//======================================.
void CMoveObjectManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight)
{
	for (int stage = 0; stage < static_cast<int>(enMoveObjectType::UseAttachObjectMax); stage++) {
		//描画初期設定処理関数.
		m_pCMoveObjectBase[stage]->SetCameraPos(m_vCameraPos);
		m_pCMoveObjectBase[stage]->RenderInitSetting(mView, mProj, stLight);
		//付属オブジェクトの描画処理関数.
		m_pCMoveObjectBase[stage]->AttachedObjRender();
	}

	//ギミックカーソル描画処理関数.
	//マップUI.
	m_pCMapGimmicKCursor->Render();

	//ギミックアイコン描画処理関数.
	for (unsigned int icon = 0; icon < m_pCGimmickIcon.size(); icon++) {
		m_pCGimmickIcon[icon]->Render();
	}
}

//======================================.
//		スイッチの描画処理関数.
//======================================.
void CMoveObjectManager::RenderSwitch(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight)
{
	for (int obj = 0; obj < static_cast<int>(enMoveObjectType::Max); obj++) {
		//描画処理.
		m_pCMoveObjectBase[obj]->RenderInitSetting(mView, mProj, stLight);
		m_pCMoveObjectBase[obj]->Render();
	}
}

//======================================.
//		エフェクト描画処理関数.
//======================================.
void CMoveObjectManager::EffectRender() 
{
	for (int stage = 0; stage < static_cast<int>(enMoveObjectType::Max); stage++) {
		//エフェクト描画処理関数.
		m_pCMoveObjectBase[stage]->EffectRender();
	}
	//ゲーム内UI.
	if (m_bGimmickCursorDisp == true) {
		m_pCGameGimmickCursor->RenderSetting(m_mView, m_mProj, m_vCameraPos);
		m_pCGameGimmickCursor->Render();
	}
}

//======================================.
//		初期化処理関数.
//======================================.
void CMoveObjectManager::Init(const int& FileNum, const int& StageNum)
{
	//ファイル.
	m_pCFileResource = CFileResource::GetResourceInstance();

	unsigned int objNum = 0;	//オブジェクト番号.
	unsigned int objMax = m_pCFileResource->GetStageMax(FileNum) * static_cast<int>(enMoveObjectType::Max);
	unsigned int stageMax = m_pCFileResource->GetStageMax(FileNum);
	unsigned int obj = 0;

	//座標設定処理.
	for (unsigned int stage = 0; stage < objMax; stage++) {
		//各オブジェクト区切りのステージマップ数.
		int stagenum = stage - (stageMax - m_pCFileResource->GetStageMax(FileNum));
		//オブジェクト番号.
		objNum = m_pCFileResource->GetStageNum(FileNum, StageNum, stagenum) - MOVEOBJECT_START_NUM;
		if (obj == objNum) {
			//オブジェクトごとの座標設定.
			switch (static_cast<enMoveObjectType>(objNum)) {
			case enMoveObjectType::GhostDispPainting:
				m_vMoveObjectPos.push_back(STANDERD_PAINTING_POS);
				m_vMoveObjectPos[m_vMoveObjectPos.size() - 1].x = stagenum * OBJECT_WIDTH;
				m_enSurpriseObjectType.push_back(CGameObject::enSurpriseObjectType::Disp);
				m_vAttachObjPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				break;
			case enMoveObjectType::ObjectMoveSwitch:
				m_vMoveObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, -0.5f));
				m_enSurpriseObjectType.push_back(CGameObject::enSurpriseObjectType::Switch);
				m_vAttachObjPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, -0.5f));
				break;
			case enMoveObjectType::PlaySoundSwitch:
				m_vMoveObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, -0.5f));
				m_enSurpriseObjectType.push_back(CGameObject::enSurpriseObjectType::Switch);
				m_vAttachObjPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				break;
			}
			//移動オブジェクト番号設定.
			m_enMoveObjectType.push_back(objNum);
			//ギミッククラスインスタンス化.
			m_pCGimmickIcon.push_back(nullptr);
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1].reset(new CGimmickIcon(objNum));
			//ステージの距離最大値取得.
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1]->SetStageMax(m_pCFileResource->GetStageMax(FileNum) * OBJECT_WIDTH);
			//ギミックアイコン座標取得.
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1]->SetCharaPos(m_vMoveObjectPos[m_pCGimmickIcon.size() - 1]);
			//ギミックアイコン1回だけ更新させる.
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1]->UpDate();

		}
		//次の動くオブジェクトへ.
		if (stage >= stageMax - 1) {
			if (obj == static_cast<int>(enMoveObjectType::GhostDispPainting)) {
				m_DispPaintingMax = m_vMoveObjectPos.size();
			}
			obj++;
			stageMax += m_pCFileResource->GetStageMax(FileNum);
		}
	}
	//上下フラグ要素数設定.
	m_ObjeMoveFlag.resize(m_pCGimmickIcon.size());
	//使われているかフラグ.
	m_bUsedGimmickFlag.resize(m_pCGimmickIcon.size());
	//付属オブジェクト.
	//移動フラグ.
	m_AttachedObjMoveFlag.resize(m_pCGimmickIcon.size());
	//角度.
	m_vAttachRot.resize(m_pCGimmickIcon.size(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//花瓶が揺れるカウント.
	m_FlowerSwingCnt.resize(m_pCGimmickIcon.size());

	//オブジェクトインスタンス化.
	m_pCMoveObjectBase.resize(static_cast<int>(enMoveObjectType::Max));
	m_pCMoveObjectBase[static_cast<int>(enMoveObjectType::GhostDispPainting)]	= new CGhostDispPainting();	//お化けが現れる絵画.
	m_pCMoveObjectBase[static_cast<int>(enMoveObjectType::ObjectMoveSwitch)]	= new CObjectMoveSwitch();	//物が動くスイッチ.
	m_pCMoveObjectBase[static_cast<int>(enMoveObjectType::PlaySoundSwitch)]		= new CPlaySoundSwitch();	//音が鳴るスイッチ.

	//ギミックカーソルインスタンス化.
	m_pCMapGimmicKCursor.reset(new CMapGimmickCursor());
	m_pCMapGimmicKCursor->SetStageMax(m_pCFileResource->GetStageMax(FileNum) * OBJECT_WIDTH);

	//ゲーム内でのギミックカーソルインスタンス化.
	m_pCGameGimmickCursor.reset(new CGameGimmickCursor());
	

	//ギミック要素数並べ替え処理関数.
	GimmickSort();
}

//======================================.
//		解放処理関数.
//======================================.
void CMoveObjectManager::Release()
{
	for (int stage = static_cast<int>(enMoveObjectType::Max) - 1; stage >= 0; stage--) {
		SAFE_DELETE(m_pCMoveObjectBase[stage]);
	}
}

//======================================.
//	ギミック要素数並べ替え処理関数.
//======================================.
void CMoveObjectManager::GimmickSort()
{
	for (unsigned int i = 0; i < m_pCGimmickIcon.size(); i++) {
		for (unsigned int j = m_pCGimmickIcon.size() - 1; j > i; j--) {
			if (m_vMoveObjectPos[j - 1].x > m_vMoveObjectPos[j].x) {

				//オブジェクトタイプ.
				int tmpObj;
				tmpObj = m_enMoveObjectType[j];
				m_enMoveObjectType[j] = m_enMoveObjectType[j - 1];
				m_enMoveObjectType[j - 1] = tmpObj;

				//オブジェクト座標.
				D3DXVECTOR3	tmpPos;
				tmpPos = m_vMoveObjectPos[j];
				m_vMoveObjectPos[j] = m_vMoveObjectPos[j - 1];
				m_vMoveObjectPos[j - 1] = tmpPos;

				//アイコン.
				std::unique_ptr<CGimmickIcon>	tmpIcon;
				tmpIcon.swap(m_pCGimmickIcon[j]);
				m_pCGimmickIcon[j].swap(m_pCGimmickIcon[j - 1]);
				m_pCGimmickIcon[j - 1].swap(tmpIcon);

				//オブジェクトタイプ.
				CGameObject::enSurpriseObjectType enTmp;
				enTmp = m_enSurpriseObjectType[j];
				m_enSurpriseObjectType[j] = m_enSurpriseObjectType[j - 1];
				m_enSurpriseObjectType[j - 1] = enTmp;

				//付属オブジェクト座標.
				D3DXVECTOR3 tmpAttachPos;
				tmpAttachPos = m_vAttachObjPos[j];
				m_vAttachObjPos[j] = m_vAttachObjPos[j - 1];
				m_vAttachObjPos[j - 1] = tmpAttachPos;
			}
		}
	}
}

//============================================.
//		絵画を落としたり上げる処理関数.
//============================================.
void CMoveObjectManager::PaintingUpDown(int objNum)
{
	//下げる処理.
	if (m_ObjeMoveFlag[objNum] & DOWN_FLAG) {
		m_vMoveObjectPos[objNum].y -= PAINTING_MOVE_SPEED;
		if (m_vMoveObjectPos[objNum].y <= PAINTING_DOWN_MAX) {
			m_vMoveObjectPos[objNum].y = PAINTING_DOWN_MAX;
		}
		return;
	}

	//上げる処理.
	if (m_ObjeMoveFlag[objNum] & UP_FLAG) {
		m_vMoveObjectPos[objNum].y += PAINTING_MOVE_SPEED;
		//元の位置に戻す.
		if (m_vMoveObjectPos[objNum].y >= STANDERD_PAINTING_POS.y) {
			m_vMoveObjectPos[objNum].y = STANDERD_PAINTING_POS.y;
		}
	}

	//フラグを降ろす.
	m_ObjeMoveFlag[objNum] &= ~m_ObjeMoveFlag[objNum];
}

//==============================================.
//		スイッチを押した処理関数.
//==============================================.
void CMoveObjectManager::SwitchPush(int objNum, CGameObject::enSurpriseObjectType enSurpriseObj)
{
	//下げる処理.
	if (m_ObjeMoveFlag[objNum] & DOWN_FLAG) {
		m_vMoveObjectPos[objNum].y -= SWITCH_UP_DOWN_SPEED;
		if (m_vMoveObjectPos[objNum].y <= SWITCH_HIGHT_MIN) {
			m_vMoveObjectPos[objNum].y = SWITCH_HIGHT_MIN;
			//物体の移動.
			if (m_vAttachObjPos[objNum].x > 0.0f && m_AttachedObjMoveFlag[objNum] == 0) {
				//付属オブジェクト移動準備.
				m_AttachedObjMoveFlag[objNum] = ATTACHED_MOVE_PREPARA_FLAG;
				//カウント初期設定.
				m_FlowerSwingCnt[objNum] = 0;
			}
			else{
				//SE鳴らす.

			}
		}
		return;
	}

	//上げる処理.
	if (m_ObjeMoveFlag[objNum] & UP_FLAG) {
		m_vMoveObjectPos[objNum].y += SWITCH_UP_DOWN_SPEED;
		if (m_vMoveObjectPos[objNum].y >= SWITCH_HIGHT_MAX) {
			m_vMoveObjectPos[objNum].y = SWITCH_HIGHT_MAX;
		}
	}

	m_ObjeMoveFlag[objNum] &= ~m_ObjeMoveFlag[objNum];
}

//====================================================.
//		机と花瓶の移動処理関数.
//====================================================.
void CMoveObjectManager::Table_VaseFlowerMove(int objNum)
{
	//移動準備.
	if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_PREPARA_FLAG) {
		//花瓶を上げる処理.
		m_vAttachObjPos[objNum].y += VASE_UP_DOWN_SPEED;
		if (m_vAttachObjPos[objNum].y >= VASE_HIGHT_MAX) {
			m_vAttachObjPos[objNum].y = VASE_HIGHT_MAX;
			m_AttachedObjMoveFlag[objNum] = ATTACHED_MOVE_FLAG | ATTACHED_MOVE_LEFT_FLAG;
		}


		return;
	}

	//移動.
	if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_FLAG) {
		//花瓶の揺れる処理.

		//戻る.
		if (m_FlowerSwingCnt[objNum] > VASE_SWING_MAX) {
			m_vAttachRot[objNum].z += VASE_SWING_SPEED;

			if (m_vAttachRot[objNum].z >= VASE_ROT_RETURN) {
				m_vAttachRot[objNum].z = VASE_ROT_RETURN;
				m_AttachedObjMoveFlag[objNum] = ATTACHED_MOVE_AFTER_FLAG;
			}
			return;
		}

		//左揺れ.
		if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_LEFT_FLAG) {
			m_vAttachRot[objNum].z += VASE_SWING_SPEED;
			if (m_vAttachRot[objNum].z >= VASE_ROT_MAX) {
				m_vAttachRot[objNum].z = VASE_ROT_MAX;
				m_AttachedObjMoveFlag[objNum] &= ~ATTACHED_MOVE_LEFT_FLAG;
			}
			return;
		}

		//右揺れ.
		m_vAttachRot[objNum].z -= VASE_SWING_SPEED;
		if (m_vAttachRot[objNum].z <= VASE_ROT_MIN) {
			m_vAttachRot[objNum].z = VASE_ROT_MIN;
			m_FlowerSwingCnt[objNum]++;

			m_AttachedObjMoveFlag[objNum] |= ATTACHED_MOVE_LEFT_FLAG;
		}
		return;

	}

	//移動終了.
	if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_AFTER_FLAG) {
		m_vAttachObjPos[objNum].y -= VASE_UP_DOWN_SPEED;
		if (m_vAttachObjPos[objNum].y < VASE_HIGHT_MIN) {
			m_vAttachObjPos[objNum].y = VASE_HIGHT_MIN;
			//全フラグを降ろす.
			m_AttachedObjMoveFlag[objNum] = 0;
		}
	}
}