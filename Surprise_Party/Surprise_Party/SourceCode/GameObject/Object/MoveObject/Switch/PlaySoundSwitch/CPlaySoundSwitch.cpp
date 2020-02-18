#include "CPlaySoundSwitch.h"

CPlaySoundSwitch::CPlaySoundSwitch()
{
	//初期化処理関数.
	Init();
}

CPlaySoundSwitch::~CPlaySoundSwitch()
{
	//解放処理関数.
	Release();
}


//=======================================.
//		更新処理関数.
//=======================================.
void CPlaySoundSwitch::UpDate()
{
	//スイッチの奥行座標設定.
	m_vPos.z = SWITCH_DEPTH_POS;

	//エフェクト更新処理関数.
	EffectUpDate();
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CPlaySoundSwitch::Init()
{
	//メッシュアドレス取得処理.
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::PlaySoundSwitch);
	m_fScale = 0.2f;

	//エフェクトアドレス取得処理関数.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::PlaySound_Area_Effect);
}

//=======================================.
//		解放処理関数.
//=======================================.
void CPlaySoundSwitch::Release()
{
	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}