#include "CEndingSwitchGhost.h"

/*******************************************
*		エンディングスイッチお化けクラス.
******************/
CEndingSwitchGhost::CEndingSwitchGhost()
	: m_MoveDirect	(1)
	, m_bSetDirect	(false)
{
	//初期化処理関数.
	Init();
}

CEndingSwitchGhost::~CEndingSwitchGhost()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		更新処理関数.
//===========================================.
void CEndingSwitchGhost::Update()
{
	//エフェクト変更処理関数.
	ChangeEffect();

	if (m_pCSpriteEffect != nullptr) {
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
		ActHaveTrouble();
	}

	//移動角度処理関数.
	MoveRotation(m_vPos, m_vLookAtPos);

}

//===========================================.
//		描画処理関数.
//===========================================.
void CEndingSwitchGhost::Render()
{
	//スイッチお化け描画処理関数.
	RenderSwitchGhost(m_vPos);

	//エフェクト描画処理関数.
	if (m_pCSpriteEffect != nullptr) {
		m_pCSpriteEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CEndingSwitchGhost::Init()
{
	//静的オブジェクトお化け初期化処理関数.
	InitStaticMeshGhost();

	m_fScale = SCALE;
	m_vPrePos.y = PRE_POS_Y;

	//ジャンプ処理準備.
	m_fAccMax	= ACC_MAX;
	m_fAcc		= m_fAccMax;
	m_fAccSpeed = ACC_SPEED;
	m_fGravity	= GRAVITY;

}

//===========================================.
//		解放処理関数.
//===========================================.
void CEndingSwitchGhost::Release()
{

}

//===========================================.
//		喜び感情行動処理化数.
//===========================================.
void CEndingSwitchGhost::ActRejoiceEmotion()
{
	//初期設定処理関数.
	SettingInitDirect();

	//ジャンプ処理関数.
	Jump();

	m_vPos.x += MOVE_SPEED * m_MoveDirect;

	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_MoveDirect *= CHANGE_DIRECT;
	}
}

//===========================================.
//		初期方向設定処理関数.
//===========================================.
void CEndingSwitchGhost::SettingInitDirect()
{
	if (m_bSetDirect == true) {
		return;
	}

	if (m_vPos.x < m_vLookAtPos.x) {
		m_MoveDirect *= CHANGE_DIRECT;
	}
	m_bSetDirect = true;
}

//===========================================.
//		困った感情処理関数.
//===========================================.
void CEndingSwitchGhost::ActHaveTrouble()
{
	//落ちる処理.
	m_vPos.y -= DOWN_SPEED;
	if (m_vPos.y < 0.0f) {
		m_vPos.y = 0.0f;

		return;
	}

	//落ちる間横移動処理.
	const float m_Distance = m_vPos.x - m_vLookAtPos.x;
	const float	m_Direct = m_Distance / fabsf(m_Distance);
	m_vPos.x += MOVE_SPEED * m_Direct;
}