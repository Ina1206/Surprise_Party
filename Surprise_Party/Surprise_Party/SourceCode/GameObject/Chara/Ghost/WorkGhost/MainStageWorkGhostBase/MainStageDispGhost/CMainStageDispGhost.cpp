#include "CMainStageDispGhost.h"

/***********************************************
*		メインステージの現れるお化けクラス.
******************/
CMainStageDispGhost::CMainStageDispGhost()
	: m_fAnimSpeed		(0.0f)
	, m_SurpriseActFlag	(0)
	, m_dAnimTime		(0.0)
{
	//初期化処理関数.
	Init();
}

CMainStageDispGhost::~CMainStageDispGhost()
{
	//解放処理関数.
	Release();
}

//=================================.
//		更新処理関数.
//=================================.
void CMainStageDispGhost::Update()
{
	//選択更新処理関数.
	SelectUpdate();

	//お化けアイコン更新処理関数.
	GhostIconUpdate();

	//お化け体力アイコン更新処理関数.
	StrengthIconUpdate();

	//移動速度変更処理関数.
	MoveSpeedChange();

	if (m_MoveFlag & SURPRISE_FLAG) {
		//驚かす行動を決める処理関数.
		SurpriseActDecide();

		if (m_SurpriseFlag & SURPRISE_ACT_FLAG) {
			//驚かす当たり判定処理関数.
			SurpriseHit();
			//驚かす行動処理関数.
			SurpriseAct();
			//上下移動変更処理関数.
			ChangeObjectUpDown();
		}
	}
	else {
		//初期に戻す.
		m_SurpriseActFlag = APPEAR_FLAG;
		m_dAnimTime = 0.0;
		//絵画は上げとく.
		m_UpDownObjectFlag = UP_FLAG;
	}

	//移動更新処理関数.
	MovePosReference();

	if (!(m_MoveFlag & SURPRISE_FLAG)) {
		//絵画は上げとく.
		m_UpDownObjectFlag = UP_FLAG;
		if (m_bChangeGimmickSelect == false) {
			ReturnMove();
		}
	}

	//疲労エフェクト更新処理関数.
	m_vEffectCenterPos = m_vPos;
	m_vEffectCenterPos.y += EFFECT_DISP_HIGHT;
	UpdateFutigueEffect();

	//選択スプライト表示座標設定.
	m_vSurpriseBeforePos = m_vPos;
	//体力アイコン座標設定.
	m_vStrengthIconPos = m_vMovePos;

}

//=================================.
//		描画処理関数.
//=================================.
void CMainStageDispGhost::Render()
{
	if (fabsf(m_vCameraPos.x - m_vPos.x) < CAMERA_DISP_RANGE) {
		if (!(m_RestFlag & IN_REST_FLAG)) {
			//アニメーション速度.
			if (m_SurpriseFlag & SURPRISE_ACT_FLAG) {
				m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
			}
			else {
				m_pCSkinMesh->ChangeAnimSet_StartPos(0, WAIT_ANIM_START_POS, m_pAnimCtrl);
			}

			//現れるお化け描画処理関数.
			RenderDispGhost(m_vMovePos);
		}
	}


	//お化けアイコン描画処理関数.
	m_pCGhostIcon->Render();

	//疲労エフェクト描画.
	if (m_pCFatigue->GetDispFlag() == true) {
		m_pCFatigue->Render(m_mView, m_mProj, m_vCameraPos);
	}

}

//=================================.
//		初期化処理関数.
//=================================.
void CMainStageDispGhost::Init()
{
	m_fScale = 0.15f;

	//アニメーション初期化処理関数.
	InitAnimation();

	m_fScaleMax = m_fScale;

	m_fAnimSpeed = SURPRISE_ANIM_SPEED;

	//ステータス設定.
	const int FileNum	= static_cast<int>(CFileResource::enStatusCharaType::Ghost);	//ファイル番号.
	m_GhostType			= static_cast<int>(enGhostType::DispGhost);						//お化けの種類.

	//体力.
	m_fStrength = m_pCFileResource->GetStatusNum(FileNum, m_GhostType, static_cast<int>(enStatus::Strength));
	m_fStrengthMax = m_fStrength;
	//速度.
	m_fMoveSpeed = m_pCFileResource->GetStatusNum(FileNum, m_GhostType, static_cast<int>(enStatus::MoveSpeed));
	m_fMoveSpeedMax = m_fMoveSpeed;
	//回復速度.
	m_fRecoverySpeed = m_fStrengthMax / m_pCFileResource->GetStatusNum(FileNum, m_GhostType, static_cast<int>(enStatus::RecoveryTime));
	m_fLimitRecoverySpeed = m_fStrengthMax / m_pCFileResource->GetStatusNum(FileNum, m_GhostType, static_cast<int>(enStatus::LimitRecoveryTime));

	//行動選択クラスインスタンス化.
	m_pCAct_Selection.reset(new CAct_Selection());

	//お化けアイコンインスタンス化.
	m_pCGhostIcon.reset(new CGhostIcon());
	const D3DXVECTOR3 ICON_COLOR = D3DXVECTOR3(GHOST_ICON_COLOR.x / COLOR_BASE.x, GHOST_ICON_COLOR.y / COLOR_BASE.y, GHOST_ICON_COLOR.z / COLOR_BASE.z);
	m_pCGhostIcon->SetColor(ICON_COLOR);
	m_pCGhostIcon->SetStrengthMax(m_fStrengthMax);

	//驚かすオブジェクト種類設定.
	m_enSurpriseObjectType = enSurpriseObjectType::Disp;

	//驚かす行動フラグ.
	m_SurpriseActFlag = APPEAR_FLAG;

	//移動終了後の高さ.
	m_fMoveFinishHight = HIGHT_MIN;
}

//==================================.
//		解放処理関数.
//==================================.
void CMainStageDispGhost::Release()
{
	m_pCSkinMesh = nullptr;
}

//==================================.
//		驚かす行動処理関数.
//==================================.
void CMainStageDispGhost::SurpriseAct()
{
	//驚かしに現れる処理.
	if (m_SurpriseActFlag & APPEAR_FLAG) {
		m_vMovePos.z -= APPEAR_SPEED;
		if (m_vMovePos.z <= APPEAR_POS_MAX) {
			m_vMovePos.z = APPEAR_POS_MAX;

			//範囲内の人が驚くフラグ.
			m_bNowHumanSurprise = true;
		}

		//戻る処理に変更処理.
		if (m_dAnimTime >= RETURN_ANIM_TIME) {
			m_SurpriseActFlag = RETURN_FLAG;
			m_bNowHumanSurprise = false;
		}
	}

	//戻る処理.
	if (m_SurpriseActFlag & RETURN_FLAG) {
		m_vMovePos.z += RETURN_SPEED;
		if (m_vMovePos.z >= RETURN_POS_MAX) {
			m_vMovePos.z = RETURN_POS_MAX	;
		}

		//驚かす行動終了処理.
		if (m_dAnimTime >= WAIT_ANIM_TIME) {
			//初期に戻す.
			m_SurpriseActFlag = APPEAR_FLAG;
			m_dAnimTime = 0.0;
			//驚く行動フラグを降ろす.
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;

			m_SurpriseFlag |= SURPRISE_REST_FLAG;
		}
	}

	//アニメーション速度加算.
	m_dAnimTime += m_pCSkinMesh->GetAnimSpeed();
	//体力減少処理.
	m_fStrength -= BASIC_REDUCE_SPEED;
}

//==================================.
//		上下移動変更処理関数.
//==================================.
void CMainStageDispGhost::ChangeObjectUpDown()
{
	//下げる.
	if (m_vMovePos.z <= OBJECT_DOWN_POS) {
		m_UpDownObjectFlag = DOWN_FLAG;
		return;
	}

	//上げる.
	m_UpDownObjectFlag = UP_FLAG;
}

//==================================.
//		戻る移動処理関数.
//==================================.
void CMainStageDispGhost::ReturnMove()
{
	if (m_vMovePos.z < GHOST_POS_Z) {
		m_vMovePos.z += RETURN_SPEED;
		return;
	}

	//移動フラグ.
	m_MoveFlag |= MOVE_FLAG;
}