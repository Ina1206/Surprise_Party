#include "CMainStageSwitchGhost.h"

CMainStageSwitchGhost::CMainStageSwitchGhost()
	: m_PushSwitchActFlag	(0)
	, m_fGravity			(0.0f)
	, m_UpDownDirection		(-1)
	, m_vPointDistance		(0.0f, 0.0f, 0.0f)
	, m_vUnitVector			(0.0f, 0.0f, 0.0f)
	, m_vOldPos				(0.0f, 0.0f, 0.0f)
{
	//初期化処理関数.
	Init();
}

CMainStageSwitchGhost::~CMainStageSwitchGhost()
{
	//解放処理関数.
	Release();
}

//==================================.
//		更新処理関数.
//==================================.
void CMainStageSwitchGhost::Update()
{

	//選択更新処理関数.
	SelectUpdate();

	//お化けアイコン更新処理関数.
	GhostIconUpdate();
	
	//お化け体力アイコン更新関数.
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


	//移動更新処理関数.
	MovePosReference();

	if (!(m_MoveFlag & SURPRISE_FLAG)) {
		if (m_bChangeGimmickSelect == false) {
			if (m_PushSwitchActFlag == 0) {
				ReturnMove();
			}
			else {
				m_vPointDistance = m_vPos - m_vMovePos;
				float fLength = D3DXVec3Length(&m_vPointDistance);
				m_vUnitVector = m_vPointDistance / fLength;
				//初期化.
				m_PushSwitchActFlag = 0;
				m_fGravity = 0.0f;
				m_UpDownDirection = -1;
				//角度.
				m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}


	//疲労エフェクト更新処理関数.
	m_vEffectCenterPos = m_vMovePos + D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	UpdateFutigueEffect();

	m_vOldPos = m_vMovePos;
	m_vSurpriseBeforePos = m_vPos + D3DXVECTOR3(0.0f, -STANDERD_POS_HIGHT, 0.0f);
	m_vStrengthIconPos = m_vMovePos + D3DXVECTOR3(0.0f, -STANDERD_POS_HIGHT, 0.0f);
}

//==================================.
//		描画処理関数.
//==================================.
void CMainStageSwitchGhost::Render()
{
	//スイッチお化け描画処理関数.
	RenderSwitchGhost(m_vMovePos);

	//お化けアイコン描画.
	m_pCGhostIcon->Render();

	//デバッグ用球体描画処理関数.
	DebugHitSphereRender();

	
	//疲労エフェクト描画処理.
	if (m_pCFatigue->GetDispFlag() == true) {
		m_pCFatigue->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//==================================.
//		初期化処理関数.
//==================================.
void CMainStageSwitchGhost::Init()
{
	//静的オブジェクトお化け初期化処理関数.
	InitStaticMeshGhost();

	m_fScale = SWITHC_GHOST_SCALE;
	m_fScaleMax = m_fScale;

	//行動選択インスタンス化.
	m_pCAct_Selection.reset(new CAct_Selection());

	//驚かすオブジェクト種類設定.
	m_enSurpriseObjectType = enSurpriseObjectType::Switch;

	//ステータス設定.
	const int CHARA_TYPE = static_cast<int>(enCharacterType::Ghost);	//キャラクタタイプ.
	const int GHOST_TYPE = static_cast<int>(enGhostType::SwitchGhost);	//お化けタイプ.
	//体力.
	m_fStrength = m_pCFileResource->GetStatusNum(CHARA_TYPE, GHOST_TYPE, static_cast<int>(enStatus::Strength));
	m_fStrengthMax = m_fStrength;
	//移動速度.
	m_fMoveSpeed = m_pCFileResource->GetStatusNum(CHARA_TYPE, GHOST_TYPE, static_cast<int>(enStatus::MoveSpeed));
	m_fMoveSpeedMax = m_fMoveSpeed;
	//回復速度.
	m_fRecoverySpeed = m_pCFileResource->GetStatusNum(CHARA_TYPE, GHOST_TYPE, static_cast<int>(enStatus::RecoverySpeed));

	//マップ上でのお化けアイコンインスタンス化.
	m_pCGhostIcon.reset(new CGhostIcon());
	m_pCGhostIcon->SetColor(GHOST_COLOR / COLOR_MAX);
	m_pCGhostIcon->SetStrengthMax(m_fStrengthMax);

	//移動終了後の高さ.
	m_fMoveFinishHight = STANDERD_POS_HIGHT;
}

//===================================.
//		解放処理関数.
//===================================.
void CMainStageSwitchGhost::Release()
{
	m_pCMesh = nullptr;
}

//===================================.
//		驚かす行動処理関数.
//===================================.
void CMainStageSwitchGhost::SurpriseAct()
{
	if (m_PushSwitchActFlag == 0) {
		m_PushSwitchActFlag = PUSH_BUTTON_FLAG | GO_TO_PUSH_FLAG;
		return;
	}

	//体力を減らす.
	m_fStrength -= BASIC_REDUCE_SPEED;

	if (m_PushSwitchActFlag & GO_TO_PUSH_FLAG) {
		//押す準備処理関数.
		PushPreparation();
		return;
	}

	if (m_PushSwitchActFlag == PUSH_BUTTON_FLAG) {
		//押す処理関数.
		PushButton();
		return;
	}

	//戻る準備.
	if (m_PushSwitchActFlag & PUSH_END_FLAG) {
		//距離.
		m_vPointDistance = m_vPos - m_vMovePos;
		//長さ.
		float m_fLength = D3DXVec3Length(&m_vPointDistance);
		//単位ベクトル.
		m_vUnitVector = m_vPointDistance / m_fLength;
		//フラグ.
		m_PushSwitchActFlag &= ~PUSH_END_FLAG;
		m_PushSwitchActFlag |= PUSH_RETURN_FLAG;
		//元に戻るときの角度.
		m_vRot.y = RETURN_ROTATION;
	}

	if (m_PushSwitchActFlag & PUSH_RETURN_FLAG) {
		//押し終わった処理関数.
		PushEnd();

		m_bNowHumanSurprise = false;
	}
}

//===================================.
//		上下移動変更処理関数.
//===================================.
void CMainStageSwitchGhost::ChangeObjectUpDown()
{
	if (m_vMovePos.y <= CHANGE_UP_DOWN_FLAG_H) {
		m_UpDownObjectFlag = DOWN_FLAG;
		return;
	}

	m_UpDownObjectFlag = UP_FLAG;
}

//===================================.
//		戻る移動処理関数.
//===================================.
void CMainStageSwitchGhost::ReturnMove()
{
	m_vMovePos += m_vUnitVector * MOVE_SPEED;

	if (fabsf(m_vPos.x - m_vMovePos.x) > DISTANCE_ADJUSTMENT) {
		//移動角度処理関数.
		MoveRotation(m_vOldPos, m_vMovePos);
		m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		return;
	}

	m_vMovePos = m_vPos;
	m_MoveFlag |= MOVE_FLAG;
}

//===================================.
//		押す準備処理関数.
//===================================.
void CMainStageSwitchGhost::PushPreparation()
{
	m_vMovePos.x += MOVE_SPEED;
	//移動角度処理関数.
	MoveRotation(m_vOldPos, m_vMovePos);

	if (m_vMovePos.x - m_vPos.x > CHANGE_ACT_DISTANCE) {
		m_vMovePos.x = m_vPos.x + CHANGE_ACT_DISTANCE;
		m_PushSwitchActFlag &= ~GO_TO_PUSH_FLAG;
	}
}

//===================================.
//		押す処理関数.
//===================================.
void CMainStageSwitchGhost::PushButton()
{
	m_fGravity -= GRAVITY * m_UpDownDirection;
	m_vMovePos.y += m_fGravity * m_UpDownDirection;

	m_vMovePos.x -= MOVE_SPEED;
	//移動角度処理関数.
	MoveRotation(m_vOldPos, m_vMovePos);

	if (m_UpDownDirection == DOWN_DIRECTION) {
		//上に上がるように変更.
		if (m_vMovePos.y <= POS_HEIGHT_MIN) {
			m_vMovePos.y = POS_HEIGHT_MIN;
			m_vMovePos.x = m_vPos.x;
			//移動方向変更.
			m_UpDownDirection *= CHANGE_DIRECTION;
			m_bNowHumanSurprise = true;
		}
		return;
	}

	//押し終わる処理に移動.
	if (m_vMovePos.x < m_vPos.x - CHANGE_ACT_DISTANCE) {
		m_vMovePos.y = m_vPos.y;
		m_fGravity = 0.0f;
		m_UpDownDirection = DOWN_DIRECTION;
		m_PushSwitchActFlag |= PUSH_END_FLAG;
	}
}

//===================================.
//		押し終わった処理関数.
//===================================.
void CMainStageSwitchGhost::PushEnd()
{
	if (fabsf(m_vPos.x - m_vMovePos.x) < DISTANCE_ADJUSTMENT) {
		m_vMovePos = m_vPos;

		m_vRot.y += PUSH_END_ROT_SPEED;
		if(m_vRot.y >= 0.0f){
			m_PushSwitchActFlag = 0;
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;
			m_SurpriseFlag |= SURPRISE_REST_FLAG;
		}
		return;
	}
	m_vMovePos += MOVE_SPEED * m_vUnitVector;
	//移動角度処理関数.
	MoveRotation(m_vOldPos, m_vMovePos);

}

