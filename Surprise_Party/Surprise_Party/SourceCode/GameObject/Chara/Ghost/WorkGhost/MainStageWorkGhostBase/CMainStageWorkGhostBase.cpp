#include "CMainStageWorkGhostBase.h"

/**********************************************
*	メインステージの働くお化け基底クラス.
****************/
CMainStageWorkGhostBase::CMainStageWorkGhostBase()
	: m_pCAct_Selection			(nullptr)
	, m_MoveFlag				(SURPRISE_FLAG)
	, m_bSelectFlag				(false)
	, m_ActType					(0)
	, m_fStageMaxDistance		(0.0f)
	, m_pCGhostIcon				(nullptr)
	, m_bGhostSelectIcon		(false)
	, m_vObjectiveGimmickPos	(0.0f, 0.0f, 0.0f)
	, m_bChangeGimmickSelect	(false)
	, m_enSurpriseObjectType	(enSurpriseObjectType::Disp)
	, m_fStrength				(0.0f)
	, m_fStrengthMax			(0.0f)
	, m_fMoveSpeed				(0.0f)
	, m_fMoveSpeedMax			(0.0f)
	, m_fRecoverySpeed			(0.0f)
	, m_SurpriseFlag			(0)
	, m_fScaleMax				(0.0f)
	, m_pCGhostStrengthIcon		(nullptr)
	, m_UpDownObjectFlag		(0)
	, m_vMovePos				(0.0f, 0.0f, 0.0f)
	, m_vSurpriseBeforePos		(0.0f, 0.0f, 0.0f)
	, m_vStrengthIconPos		(0.0f, 0.0f, 0.0f)
	, m_fMoveFinishHight		(0.0f)
	, m_bNowHumanSurprise		(false)
	, m_NearHumanNum			()
	, m_vEffectCenterPos		(0.0f, 0.0f, 0.0f)
	, m_pCFatigue				(nullptr)
	, m_GhostType				(0)
	, m_MoveDirection			(0)
	, m_vGimmickPos				()
	, m_vHumanPos				()
	, m_pCHitSphere				(2)
	, m_RestFlag				(REST_PREPARAT_FLAG)
	, m_OldStrengthType			(0)
	, m_SurpriseRestTime		(0)
	, m_UseGimmickNum			(-1)
	, m_bLimitationRest			(false)
	, m_bTutorialCommentAddFlag	(false)
{
	//読み込んだ球体アドレス取得.
	for (unsigned int sphere = 0; sphere < m_pCHitSphere.size(); sphere++) {
		m_pCHitSphere[sphere] = m_pCResourceManager->GetStaticMesh(enStaticMeshType::HitSphere);
	}
	//お化けの体力アイコンのインスタンス化.
	m_pCGhostStrengthIcon.reset(new CGhostStrengthIcon());

	//疲労エフェクトインスタンス化.
	m_pCFatigue.reset(new CSurpriseEffect());

}

CMainStageWorkGhostBase::~CMainStageWorkGhostBase()
{
	for (int sphere = static_cast<int>(m_pCHitSphere.size()) - 1; sphere >= 0; sphere--) {
		m_pCHitSphere[sphere] = nullptr;
	}

}

//=========================================.
//		行動選択描画処理関数.
//=========================================.
void CMainStageWorkGhostBase::SelectRender()
{
	if (m_MoveFlag & SELECT_FLAG) {
		//描画処理関数.
		m_pCAct_Selection->RenderSetting(m_mView, m_mProj, m_vCameraPos);
		m_pCAct_Selection->Render();
	}
}

//=========================================.
//		体力アイコン描画処理関数.
//=========================================.
void CMainStageWorkGhostBase::StrengthIconRender()
{
	//休憩時以外表示する.
	if (!(m_MoveFlag & REST_FLAG)) {
		m_pCGhostStrengthIcon->RenderSetting(m_mView, m_mProj, m_vCameraPos);
		m_pCGhostStrengthIcon->Render();
	}
}

//=========================================.
//		選択更新処理関数.
//=========================================.
void CMainStageWorkGhostBase::SelectUpdate()
{
	m_bTutorialCommentAddFlag = false;

	//体力無いときに自動休憩処理.
	if (m_fStrength <= 0.0f) {
		if (m_MoveFlag & SURPRISE_FLAG) {
			m_MoveFlag |= REST_FLAG;
			//驚かす行動停止.	
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;

			m_bLimitationRest = true;

			//選択肢を閉じ終わったら.
			if (m_pCAct_Selection->GetSelectFlag() == false) {
				//驚かすフラグから休憩フラグへ.
				m_MoveFlag &= ~SURPRISE_FLAG;
				
				//お化けの近くにいる人番号を削除処理関数.		
				ClearNearHumanOfGhost();
				return;
			}
		}
	}

	if (m_MoveFlag & REST_FLAG && m_bLimitationRest == true) {
		RestAct();
	}

	//選択中の行動フラグ.
	if (m_bSelectFlag == true) {
		m_MoveFlag = SELECT_FLAG | SURPRISE_FLAG;
	}

	//お化けの行動選択処理.
	if (m_MoveFlag & SELECT_FLAG) {
		//お化けの座標取得.
		m_pCAct_Selection->SetCharacterPos(m_vSurpriseBeforePos);
		//行動選択更新処理関数.
		m_pCAct_Selection->UpDate();
		//アイコンの表情変更.
		m_pCGhostIcon->SetSelectedFlag(true);

		//選択肢を閉じる.
		if (m_bLimitationRest == true) {
			m_pCAct_Selection->SetCloseMoveFlag();
		}

		//選択から戻る処理.
		if (m_pCAct_Selection->GetSelectFlag() == false) {
			//選択終了.
			m_bSelectFlag = false;

			//アイコンの表情戻す.
			m_pCGhostIcon->SetSelectedFlag(false);

			//全てのフラグ.
			unsigned int ACT_ALL_FLAG = m_pCAct_Selection->MOVE_FLAG | m_pCAct_Selection->REST_FLAG;
			if (m_pCAct_Selection->GetGhostActFlag() & ACT_ALL_FLAG) {
				//選択終了(選択フラグを降ろす).
				m_MoveFlag &= ~SELECT_FLAG;
				//選択後の行動.
				m_MoveFlag |= SELECT_ACT_FLAG;


				//チュートリアル時コメント一つ増やすフラグ.
				m_bTutorialCommentAddFlag = true;

				m_ActType = m_pCAct_Selection->GetGhostActFlag();
				if (m_ActType & m_pCAct_Selection->MOVE_FLAG) {
					m_bChangeGimmickSelect = true;
				}
				else {
					//驚かすフラグから休憩フラグへ.
					m_MoveFlag &= ~SURPRISE_FLAG;
					m_MoveFlag |= REST_FLAG;
					//驚かす行動停止.	
					m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;
				}

				return;
			}

			//驚かす.
			m_MoveFlag = SURPRISE_FLAG;
		}
	}

	//選択後の行動処理関数.
	if (m_MoveFlag & SELECT_ACT_FLAG) {
		SelectAfterActivity();
	}
}

//==========================================.
//		驚かす行動を決める処理関数.
//==========================================.
void CMainStageWorkGhostBase::SurpriseActDecide()
{
	//驚かし休憩処理.
	if (m_SurpriseFlag & SURPRISE_REST_FLAG) {
		const int FileNum			= static_cast<int>(CFileResource::enStatusCharaType::Ghost);							//ファイル番号.
		const int StrengthType		= m_pCGhostIcon->GetFaceType() + 4;														//表情番号.
		const int SurpriseRestMax	= static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, m_GhostType, StrengthType));	//驚く休憩時間最大値.

		if (m_SurpriseRestTime <= SurpriseRestMax) {
			m_SurpriseRestTime++;

			//お化けの近くにいる人番号を削除処理関数.		
			ClearNearHumanOfGhost();

			return;
		}
		m_SurpriseRestTime = 0;
		m_SurpriseFlag &= ~SURPRISE_REST_FLAG;
	}

	//お化けがギミックの上にいるかどうかの処理.
	if (m_UseGimmickNum >= 0) {
		m_SurpriseFlag |= GIMMICK_TOP_FLAG;
	}

	if (!(m_SurpriseFlag & SURPRISE_ACT_FLAG)) {

		//お化けがギミックの上にいなければ終了.
		if (!(m_SurpriseFlag & GIMMICK_TOP_FLAG)) {
			//お化けの近くにいる人番号を削除処理関数.		
			ClearNearHumanOfGhost();
			return;
		}

		//人がお化けの近くにいるかどうか.
		for (unsigned int human = 0; human < m_vHumanPos.size(); human++) {
			if (fabsf((m_vPos.x - 5.0f) - m_vHumanPos[human].x) < NEAR_SENTER_ADJUST) {
				m_SurpriseFlag |= HUMAN_NEAR_FLAG;
			}
		}

		//人が近くにいなければ終了.
		if (!(m_SurpriseFlag & HUMAN_NEAR_FLAG)) {
			//お化けの近くにいる人番号を削除処理関数.		
			ClearNearHumanOfGhost();
			return;
		}

		//驚かす.
		m_SurpriseFlag = SURPRISE_ACT_FLAG;

		//人が驚く場所.
		m_vSurprisePos = m_vHumanPos[0];
		m_vSurprisePos.x = m_vPos.x - SURPRISE_POS_ADJUST;

	}

	//お化けの近くにいる人番号.
	if (m_SurpriseFlag & SURPRISE_ACT_FLAG) {
		int NearHumanCnt = 0;	//お化けの近くにいる人カウント.
		if (m_bNowHumanSurprise == true) {
			for (unsigned int human = 0; human < m_vHumanPos.size(); human++) {
				if (fabsf((m_vPos.x - NEAR_SENTER_ADJUST) - m_vHumanPos[human].x) < NEAR_SENTER_ADJUST) {

					//人番号設定.
					if (static_cast<int>(m_NearHumanNum.size()) > NearHumanCnt) {
						if (m_NearHumanNum[NearHumanCnt] != human) {
							m_NearHumanNum[NearHumanCnt] = human;
						}
						NearHumanCnt++;
						continue;
					}

					m_NearHumanNum.push_back(human);
					NearHumanCnt++;
				}
			}
		}

		//不要な要素数変更.
		if (static_cast<int>(m_NearHumanNum.size()) > NearHumanCnt) {
			m_NearHumanNum.erase(m_NearHumanNum.begin() + NearHumanCnt, m_NearHumanNum.end());
		}

	}

	return;
}

//==========================================.
//		驚かす当たり判定処理関数.
//==========================================.
HRESULT CMainStageWorkGhostBase::SurpriseHit()
{
	const int PEOPLE_NUM = 0;	//人の番号.
	const int GHOST_NUM = 1;	//お化けの番号.

	//2点の長さ.
	std::vector<float>	fLength(m_NearHumanNum.size());
	for (unsigned int human = 0; human < m_NearHumanNum.size(); human++) {

		//2点の中心間の距離を求める.
		D3DXVECTOR3 vLength = m_vSurprisePos - m_vHumanPos[m_NearHumanNum[human]];
		//長さに変換.
		fLength[human] = D3DXVec3Length(&vLength);

		//衝突判定.
		if (fLength[human] <= m_pCHitSphere[PEOPLE_NUM]->m_Sphere.fRadius * HUMAN_HIT_SCALE + m_pCHitSphere[GHOST_NUM]->m_Sphere.fRadius * SURPRISE_HIT_SCALE) {
			//驚いた人の処理.
			m_bHumanSurpriseFlag = true;
			m_SurpriseHumanNum = m_NearHumanNum[human];

			break;
		}

		m_bHumanSurpriseFlag = false;
		m_SurpriseHumanNum = NOT_SURPRISE_NUM;

	}

	return S_OK;
}

//==========================================.
//		選択後の行動処理関数.
//==========================================.
void CMainStageWorkGhostBase::SelectAfterActivity()
{

	if (m_ActType & m_pCAct_Selection->MOVE_FLAG) {
		if (m_bChangeGimmickSelect == false) {

			//驚かす判定終了.
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;
			m_MoveFlag &= ~SURPRISE_FLAG;

			//選択止める処理.
			if (m_MoveFlag & SELECT_STOP_FLAG) {
				m_MoveFlag = SURPRISE_FLAG;
				m_ActType = 0;
				return;
			}

			if (m_MoveFlag & MOVE_FLAG) {
				//お化けの近くにいる人番号を削除処理関数.		
				ClearNearHumanOfGhost();

				//ギミック移動処理関数.
				MoveGimmick();
			}
		}
		return;
	}

	if (m_MoveFlag & MOVE_FLAG) {
		//お化けの近くにいる人番号を削除処理関数.		
		ClearNearHumanOfGhost();

		//休憩処理関数.
		RestAct();
	}

}

//===========================================.
//		お化けアイコン更新処理関数.
//===========================================.
void CMainStageWorkGhostBase::GhostIconUpdate()
{
	//休憩時の顔の変更用.
	if (m_MoveFlag & REST_FLAG) {
		m_pCGhostIcon->SetRestFlag(true);
	}
	else {
		m_pCGhostIcon->SetRestFlag(false);
	}
	//表示するキャラ座標設定.
	m_pCGhostIcon->SetCharaPos(m_vPos);
	//ステージ全体マップ設定.
	m_pCGhostIcon->SetStageMax(m_fStageMaxDistance);
	//体力設定.
	m_pCGhostIcon->SetStrength(m_fStrength);
	//更新処理関数.
	m_pCGhostIcon->UpDate();

	//選ばれているとき.
	if (m_bGhostSelectIcon == true) {
		m_pCGhostIcon->SetSelectingFlag();
	}
	m_bGhostSelectIcon = false;
}

//===========================================.
//		体力アイコン更新処理関数.
//===========================================.
void CMainStageWorkGhostBase::StrengthIconUpdate()
{
	//座標.
	m_pCGhostStrengthIcon->SetCharacterPos(m_vStrengthIconPos);
	//体力アイコン.
	m_pCGhostStrengthIcon->SetStrengthIcon(m_pCGhostIcon->GetFaceType());
	m_pCGhostStrengthIcon->UpDate();
}

//===========================================.
//		休憩処理関数.
//===========================================.
void CMainStageWorkGhostBase::RestAct()
{
	//回復準備処理.
	if (m_RestFlag & REST_PREPARAT_FLAG) {
		//回復処理関数.
		RestMove(&m_vMovePos.y, REST_MOVE_SPEED, REST_MOVE_MAX);
		RestMove(&m_vRot.x, REST_ROTATION_SPEED.x, REST_ROTATION_MAX.x);
		RestMove(&m_vRot.y, REST_ROTATION_SPEED.y, REST_ROTATION_MAX.y);

		//休憩中.
		m_fScale -= REST_SCALE_SPEED;
		if (m_fScale <= REST_SCALE_MIN) {
			m_fScale = REST_SCALE_MIN;
			m_RestFlag = IN_REST_FLAG;
		}
	}

	//回復中処理.
	if (m_RestFlag & IN_REST_FLAG) {
		//疲労回復速度の調整.
		float RecoverySpeed = 1.0f;
		if (m_bLimitationRest == true) {
			RecoverySpeed = 4.0f;
		}
		m_fStrength += m_fRecoverySpeed / RecoverySpeed;

		//復活.
		if (m_fStrength >= m_fStrengthMax) {
			m_fStrength = m_fStrengthMax;;
			m_RestFlag = RESURRECTION_FLAG;
		}
	}

	//復活処理.
	if (m_RestFlag & RESURRECTION_FLAG) {
		//休憩移動処理関数.
		Resurrection(&m_vMovePos.y, REST_MOVE_SPEED, 0.0f);
		Resurrection(&m_vRot.x, REST_ROTATION_SPEED.x, 0.0f);
		Resurrection(&m_vRot.y, REST_ROTATION_SPEED.y, 0.0f);
		m_fScale += REST_SCALE_SPEED;

		//元に戻す.
		if (m_fScale > m_fScaleMax) {
			m_fScale = m_fScaleMax;
			m_MoveFlag = SURPRISE_FLAG;
			m_RestFlag = REST_PREPARAT_FLAG;
			m_ActType = 0;

			m_bLimitationRest = false;
		}

	}
}

//===========================================.
//		ギミック移動処理関数.
//===========================================.
void CMainStageWorkGhostBase::MoveGimmick()
{
	if (fabsf(m_vPos.x - m_vObjectiveGimmickPos.x) <= ADJUSTMENT_WIDTH) {
		m_vPos.x = m_vObjectiveGimmickPos.x;

		//高さ微調整.
		m_vPos.y -= UP_DOWN_SPEED;
		if (m_vPos.y <= m_fMoveFinishHight) {
			m_vPos.y = m_fMoveFinishHight;
		}

		//角度戻す.
		float Rotation_Direction = m_vRot.y / fabsf(m_vRot.y);
		m_vRot.y -= ROT_SPEED * Rotation_Direction;
		if (fabsf(m_vRot.y) <= ROT_MIN_ADJUST) {
			m_vRot.y = ROT_MIN;
			//驚かす行動に移動.
			m_MoveFlag = SURPRISE_FLAG;
			m_ActType = 0;
		}
		return;
	}

	//移動方向.
	int MoveDirection = static_cast<int>((m_vObjectiveGimmickPos.x - m_vPos.x ) / fabsf(m_vObjectiveGimmickPos.x - m_vPos.x));

	//角度移動.
	m_vRot.y -= ROT_SPEED * MoveDirection;
	if (fabsf(m_vRot.y) >= ROT_MAX) {
		m_vRot.y = -ROT_MAX * MoveDirection;
	}

	//横移動.
	m_vPos.x += m_fMoveSpeed * MoveDirection;

	//浮遊処理関数.
	MoveUpDown();

	//体力減少処理.
	m_fStrength -= MOVE_REDUCE_SPEED;
}

//=============================================.
//		デバッグ用球体描画処理関数.
//=============================================.
void CMainStageWorkGhostBase::DebugHitSphereRender()
{
#ifdef _DEBUG
	if (m_NearHumanNum.size() > 0) {
		std::vector<D3DXVECTOR3> SpherePos;
		SpherePos.push_back(m_vHumanPos[m_NearHumanNum[0]]);
		SpherePos.push_back(D3DXVECTOR3(m_vPos.x - SURPRISE_POS_ADJUST, m_vHumanPos[m_NearHumanNum[0]].y, m_vHumanPos[m_NearHumanNum[0]].z));
		std::vector<float> SphereScale;
		SphereScale.push_back(HUMAN_HIT_SCALE);
		SphereScale.push_back(SURPRISE_HIT_SCALE);
		for (unsigned int sphere = 0; sphere < m_pCHitSphere.size(); sphere++) {
			m_pCHitSphere[sphere]->SetScale(SphereScale[sphere]);
			m_pCHitSphere[sphere]->SetPosition(SpherePos[sphere]);
			m_pCHitSphere[sphere]->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
		}
	}
#endif	//#ifdef _DEBUG.
}

//===========================================.
//		休憩移動処理関数.
//===========================================.
void CMainStageWorkGhostBase::RestMove(float* pfVar, float fSpeed, float fMax)
{
	*pfVar += fSpeed;
	if (*pfVar >= fMax) {
		*pfVar = fMax;
	}
}

//===========================================.
//		回復処理関数.
//===========================================.
void CMainStageWorkGhostBase::Resurrection(float* pfVar, float fSpeed, float fMin)
{
	*pfVar -= fSpeed;
	if (*pfVar <= fMin) {
		*pfVar = fMin;
	}
}

//============================================.
//		移動速度変更処理関数.
//============================================.
void CMainStageWorkGhostBase::MoveSpeedChange()
{
	int StrengthType = m_pCGhostIcon->GetFaceType();

	//体力タイプが減った時.
	if (StrengthType < m_OldStrengthType) {
		m_fMoveSpeed -= m_fMoveSpeedMax / m_pCGhostIcon->STRENGTH_FACE_MAX;
	}

	//体力回復.
	if (StrengthType > m_OldStrengthType) {
		m_fMoveSpeed = m_fMoveSpeedMax;
	}

	m_OldStrengthType = StrengthType;
}

//============================================.
//		移動更新処理関数.
//============================================.
void CMainStageWorkGhostBase::MovePosReference()
{
	//驚かしているとき以外場所更新.
	if (!(m_SurpriseFlag & SURPRISE_ACT_FLAG) &&
		m_MoveFlag & MOVE_FLAG) {
		m_vMovePos = m_vPos;
	}
}

//============================================.
//		疲労エフェクト更新処理関数.
//============================================.
void CMainStageWorkGhostBase::UpdateFutigueEffect()
{
	//疲労の表情種類番号.
	const int FutigueEffectFaceType = static_cast<int>(CGhostIcon::enFaceType::Bad_Face);

	//疲労エフェクト更新処理.
	if ((m_pCGhostIcon->GetFaceType() == FutigueEffectFaceType) && !(m_ActType & REST_FLAG)) {
		m_pCFatigue->SetCenterPos(m_vEffectCenterPos); {
			if (m_pCFatigue->GetDispFlag() == false && !(m_SurpriseFlag & SURPRISE_ACT_FLAG))
				m_pCFatigue->SetDispFlag(true);
		}
		m_pCFatigue->Update();
		return;
	}

	if (m_pCFatigue->GetDispFlag() == true) {
		m_pCFatigue->SetDispFlag(false);
	}
}

//=============================================.
//	お化けの近くにいる人番号を削除処理関数.
//=============================================.
void CMainStageWorkGhostBase::ClearNearHumanOfGhost()
{
	if (m_NearHumanNum.size() > 0) {
		m_NearHumanNum.clear();
	}
}