#include "CGhostDispPainting.h"

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
void CGhostDispPainting::UpDate()
{
	//エフェクト更新処理関数.
	EffectUpDate();

	//オブジェクト透過処理関数.
	ObjAlpha();

}

//=================================.
//		初期化処理関数.
//=================================.
void CGhostDispPainting::Init()
{
	//絵画オブジェクトの読み込みアドレス取得.
	m_pCMesh = nullptr;
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Painting);
	m_fScale = 0.4f;

	//エフェクトの読み込みアドレス取得.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::DispGhost_Area_Effect);
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
