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

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		ActRejoiceEmotion();
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

	m_fAcc = ACC_MAX;
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
	m_fAcc -= ACC_SPEED;
	m_vPos.y += m_fAcc - GRAVITY;

	m_vRot.z += ROTATION_SPEED * m_RotationDirect;

	if (m_vPos.y < m_vChangeBeforePos.y) {
		m_vPos = m_vChangeBeforePos;
		m_bChangeRotationDirect = false;
		m_fAcc = ACC_MAX;
		m_vRot.x = 0.0f;
	}

	if (m_bChangeRotationDirect == true) {
		return;
	}

	//落ちるようになると角度変更.
	if (m_fAcc < GRAVITY) {
		m_RotationDirect *= CHANGE_DIRECT;
		m_bChangeRotationDirect = true;
	}

}