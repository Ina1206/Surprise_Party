#include "CBoy.h"

CBoy::CBoy()
{
	//初期化処理関数.
	Init();
}

CBoy::~CBoy()
{
	//解放処理関数.
	Release();
}

//===================================.
//		更新処理関数.
//===================================.
void CBoy::Update()
{
	//表示判定処理関数.
	DispDecision();

	//人の移動処理関数.
	HumanMove();

	//驚きアニメーション変更処理関数.
	SurpriseAnimChange(static_cast<int>(enBoyAnim::Surprise));

	//驚きエフェクト更新処理関数.
	m_pCSkinMesh->GetPosFromBone("towa_rig_atama1", &m_vEffectCenterPos);
	m_pCSurpriseEffect->Update();

}

//===================================.
//		初期化処理関数.
//===================================.
void CBoy::Init()
{
	//スキンメッシュのアドレス取得.
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::Boy);
	//アニメーションコントローラのクローン作成処理関数.
	AnimCtrlCreat();
	//アニメーション.
	m_fAnimSpeed		= BASE_ANIM_SPEED;
	m_fWalkAnimSpeed	= m_fAnimSpeed;
	m_WalkAnimNo		= static_cast<int>(enBoyAnim::Walk);
	m_AnimNo			= m_WalkAnimNo;
	m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	m_fScale = SCALE;

	//ステータス数値取得.
	m_fMoveSpeed		= m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Boy), static_cast<int>(enStatus::MoveSpeed));
	m_SurpriseQuantity	= static_cast<int>(m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Boy), static_cast<int>(enStatus::Scared)));

	//アニメーション設定.
	m_AnimNo = static_cast<int>(enBoyAnim::Walk);
	m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	//驚きエフェクトクラスインスタンス化.
	m_pCSurpriseEffect.reset(new CSurpriseEffect());
}

//===================================.
//		解放処理関数.
//===================================.
void CBoy::Release()
{
	m_pCSkinMesh = nullptr;
}