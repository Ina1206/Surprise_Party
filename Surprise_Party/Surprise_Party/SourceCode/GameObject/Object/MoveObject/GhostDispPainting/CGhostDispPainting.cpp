#include "CGhostDispPainting.h"

/***********************************************
*		お化けが現れる絵画クラス.
***************/
CGhostDispPainting::CGhostDispPainting()
{
	//初期化処理関数.
	Init();
}

CGhostDispPainting::~CGhostDispPainting()
{
	//解放処理関数.
	Release();
}

//=================================.
//		更新処理関数.
//=================================.
void CGhostDispPainting::Update()
{
	//エフェクト更新処理関数.
	EffectUpdate();

	//オブジェクト透過処理関数.
	ObjAlpha();

	//スプライトエフェクト設定.
	const D3DXVECTOR3 vEffectCenterPos = D3DXVECTOR3(m_vPos.x, -1.0f, m_vPos.z);
	for (unsigned int sprite = 0; sprite < m_pCSpriteEffect.size(); sprite++) {
		m_pCSpriteEffect[sprite]->SetPlayFlag(m_bMoveObjectEffect);
		m_pCSpriteEffect[sprite]->SetCenterPos(vEffectCenterPos);
		m_pCSpriteEffect[sprite]->Update();
	}
}

//=================================.
//		初期化処理関数.
//=================================.
void CGhostDispPainting::Init()
{
	//絵画オブジェクトの読み込みアドレス取得.
	m_pCMesh = nullptr;
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Painting);
	m_fScale = SCALE;

	//エフェクトの読み込みアドレス取得.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::DispGhost_Area_Effect);

	//スプライトエフェクトインスタンス化.
	m_pCSpriteEffect.emplace_back(new CSmokeEffect());
}

//=================================.
//		解放処理関数.
//=================================.
void CGhostDispPainting::Release()
{
	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}

//=================================.
//		オブジェクト透過処理関数.
//=================================.
void CGhostDispPainting::ObjAlpha()
{
	if (fabsf(m_vCameraPos.x - m_vPos.x) <= ALPHA_DISTANCE) {
		m_fAlpha = PAINTING_ALPHA_MIN;
	}
	else {
		m_fAlpha = ALPHA_MAX;
	}
}
