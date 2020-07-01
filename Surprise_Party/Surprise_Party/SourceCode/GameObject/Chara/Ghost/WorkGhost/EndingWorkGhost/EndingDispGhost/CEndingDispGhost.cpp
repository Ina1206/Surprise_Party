#include "CEndingDispGhost.h"

/******************************************
*	エンディングの現れるお化けクラス.
**************/
CEndingDispGhost::CEndingDispGhost()
	: m_RotationDirect			(1)
	, m_bChangeRotationDirect	(false)
	, m_bStartHaveTrouble		(false)
{
	//初期化処理関数.
	Init();
}

CEndingDispGhost::~CEndingDispGhost()
{

}

//===========================================.
//		更新処理関数.
//===========================================.
void CEndingDispGhost::Update()
{
	//エフェクト変更処理関数.
	ChangeEffect();

	if (m_pCSpriteEffect != nullptr) {
		//エフェクト更新処理関数.
		m_pCSpriteEffect->SetCenterPos(m_vPos);
		m_pCSpriteEffect->Update();
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		//喜び感情行動処理関数.
		ActRejoiceEmotion();
		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::GoodFeeling)) {
		//上下移動処理関数.
		MoveUpDown();

		//ご機嫌時の行動処理関数.
		ActGoodFeeling();

		//エフェクト再生管理処理関数.
		PlayEffectManager();

		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::HaveTrounble)) {
		//困った感情行動処理関数.
		ActHaveTrouble();

		m_pCSpriteEffect->SetPlayFlag(true);
		return;
	}

	//移動角度処理関数.
	MoveRotation(m_vPos, m_vLookAtPos);
	m_vChangeBeforePos = m_vPos;
}

//===========================================.
//		描画処理関数.
//===========================================.
void CEndingDispGhost::Render()
{
	m_pCSkinMesh->ChangeAnimSet_StartPos(0, WAIT_ANIM_START_POS, m_pAnimCtrl);
	RenderDispGhost(m_vPos);
	
	//スプライトエフェクト描画処理.
	if (m_pCSpriteEffect != nullptr) {
		m_pCSpriteEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CEndingDispGhost::Init()
{
	//アニメーション初期化処理関数.
	InitAnimation();
	m_fScale	= SCALE;
	m_vPrePos.y = PRE_POS_Y;

	//ジャンプ処理準備.
	m_fAccMax	= ACC_MAX;
	m_fAcc		= m_fAccMax;
	m_fAccSpeed = ACC_SPEED;
	m_fGravity	= GRAVITY;
}

//============================================.
//		解放処理関数.
//============================================.
void CEndingDispGhost::Release()
{

}

//============================================.
//		喜び感情行動処理関数.
//============================================.
void CEndingDispGhost::ActRejoiceEmotion()
{
	//ジャンプ処理関数.
	Jump();

	//回転処理関数.
	Rotation();
}

//=============================================.
//		回転処理関数.
//=============================================.
void CEndingDispGhost::Rotation()
{
	m_vRot.z += ROTATION_SPEED * m_RotationDirect;

	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_bChangeRotationDirect = false;
		m_vRot.x = 0.0f;
	}

	//一度変更したら上がるまで処理をしない.
	if (m_bChangeRotationDirect == true) {
		return;
	}

	//落ちるようになると角度変更.
	if (m_fAcc < GRAVITY) {
		m_RotationDirect *= CHANGE_DIRECT;
		m_bChangeRotationDirect = true;
	}

}

//==============================================.
//		困った感情行動処理関数.
//==============================================.
void CEndingDispGhost::ActHaveTrouble()
{
	if (m_bStartHaveTrouble == false) {
		//移動角度処理関数.
		MoveRotation(m_vPos, m_vLookAtPos);
		m_vChangeBeforeRotation = m_vRot;
		m_bStartHaveTrouble		= true;
	}

	m_vRot.x += SWING_SPEED * m_RotationDirect;
	
	//角度最大値.
	if (fabsf(m_vRot.x - m_vChangeBeforeRotation.x) > static_cast<float>(D3DXToRadian(SWING_ROTATION_MAX))) {
		m_RotationDirect *= CHANGE_DIRECT;
	}
}