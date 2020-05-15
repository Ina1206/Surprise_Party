#include "CPlaySoundSwitch.h"

CPlaySoundSwitch::CPlaySoundSwitch()
	: m_pCMoveNoteEffect	(nullptr)
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
void CPlaySoundSwitch::Update()
{
	//スイッチの奥行座標設定.
	m_vPos.z = SWITCH_DEPTH_POS;

	//エフェクト更新処理関数.
	EffectUpdate();

	for (unsigned int Effect = 0; Effect < m_pCSpriteEffect.size(); Effect++) {
		const D3DXVECTOR3 vEffectCenterPos = m_vPos + D3DXVECTOR3(0.0f, 0.0f, 8.0f);
		m_pCSpriteEffect[Effect]->SetCenterPos(vEffectCenterPos);
		m_pCSpriteEffect[Effect]->SetPlayFlag(m_bMoveObjectEffect);
		m_pCSpriteEffect[Effect]->Update();
	}
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
	
	//音符移動エフェクトクラスインスタンス化.
	m_pCSpriteEffect.emplace_back(new CMoveNoteEffect());
}

//=======================================.
//		解放処理関数.
//=======================================.
void CPlaySoundSwitch::Release()
{
	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}