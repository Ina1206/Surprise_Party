#include "CGirl.h"
#include <random>

CGirl::CGirl()
	: m_SuspendTime		(0)
	, m_dAnimTime		(0.0)
	, m_SuspendInterval	(0)
{
	//初期化処理関数.
	Init();
}

CGirl::~CGirl()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CGirl::Update()
{
	//表示判定処理関数.
	DispDecision();

	//人の移動処理関数.
 	HumanMove();

	//驚きアニメーション変更処理関数.
	SurpriseAnimChange(static_cast<int>(enGirlAnimType::Rejoice));

	//一時停止処理関数.
	SearchMotion();

	if (m_AnimNo == static_cast<int>(enGirlAnimType::Rejoice)) {
		m_pCSurpriseEffect->SetDispFlag(true);
	}
	//驚きエフェクト更新処理関数.
	m_pCSurpriseEffect->Update();
	m_vEffectCenterPos = m_vPos;
	m_vEffectCenterPos.y += 4.0f;
}

//========================================.
//		初期化処理関数.
//========================================.
void CGirl::Init()
{
	//スキンメッシュのアドレス取得処理.
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::Girl);

	//アニメーションコントローラのクローン作成処理関数.
	AnimCtrlCreat();
	//アニメーション.
	m_fAnimSpeed		= BASE_ANIM_SPEED;
	m_fWalkAnimSpeed	= m_fAnimSpeed;
	m_WalkAnimNo		= static_cast<int>(enGirlAnimType::Walk);
	m_AnimNo			= m_WalkAnimNo;
	m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	m_fScale			= SCALE;

	//ステータス数値取得.
	m_fMoveSpeed		= m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Girl), static_cast<int>(enStatus::MoveSpeed));
	m_SurpriseQuantity	= static_cast<int>(m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Girl), static_cast<int>(enStatus::Scared)));
	
	//一時停止間隔設定処理.
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> IntervalRand(SUSPEND_INTERVAL_TIME_MIN, SUSPEND_INRERVAL_TIME_MAX);
	m_SuspendInterval = IntervalRand(mt);
	
	//驚きエフェクトクラスインスタンス化.
	m_pCSurpriseEffect.reset(new CSurpriseEffect());
}

//========================================.
//		解放処理関数.
//========================================.
void CGirl::Release()
{
	m_pCSkinMesh = nullptr;
}

//=========================================.
//		探索処理関数.
//=========================================.
void CGirl::SearchMotion()
{
	//驚いているときは例外として処理.
	if (m_AnimNo == static_cast<int>(enGirlAnimType::Rejoice)) {
		return;	
	}

	if (m_AnimNo == static_cast<int>(enGirlAnimType::Walk)) {
		//探索アニメーション変更処理.
		SearchAnimChange();
		return;
	}

	//探索していないときは例外として処理.
	if (m_AnimNo != static_cast<int>(enGirlAnimType::Search)) {
		return;
	}

	//歩きモーションへ変更処理.
	if (m_pCSkinMesh->GetAnimPeriod(m_AnimNo) - m_pCSkinMesh->GetAnimSpeed() <= m_dAnimTime) {
		m_AnimNo = static_cast<int>(enGirlAnimType::Walk);
		m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_dAnimTime = 0.0;
	}

	m_dAnimTime += m_pCSkinMesh->GetAnimSpeed();
}

//============================================.
//		探索アニメーション変更処理関数.
//============================================.
void CGirl::SearchAnimChange()
{
	if (m_SuspendTime >= m_SuspendInterval * SECONDS_DELIMITER) {
		m_AnimNo = static_cast<int>(enGirlAnimType::Search);
		m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_SuspendTime = 0;
		m_dAnimTime = 0.0;
	}

	m_SuspendTime++;
}