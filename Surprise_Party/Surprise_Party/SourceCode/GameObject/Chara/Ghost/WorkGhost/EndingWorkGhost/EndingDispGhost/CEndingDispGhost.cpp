#include "CEndingDispGhost.h"

/******************************************
*	エンディングの現れるお化けクラス.
**************/
CEndingDispGhost::CEndingDispGhost()
	: m_RotationDirect			(1)
	, m_bChangeRotationDirect	(false)
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

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		//喜び感情行動処理関数.
		ActRejoiceEmotion();
		//喜び更新処理関数.
		m_pCSpriteEffect->SetCenterPos(m_vPos);
		m_pCSpriteEffect->Update();
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
	m_fScale = SCALE;
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