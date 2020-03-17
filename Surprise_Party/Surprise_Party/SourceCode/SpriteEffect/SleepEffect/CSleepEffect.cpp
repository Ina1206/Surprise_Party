#include "CSleepEffect.h"

/********************************************
*		寝ているエフェクトクラス.
****************/
CSleepEffect::CSleepEffect()
{
	//初期化処理関数.
	Init();
}

CSleepEffect::~CSleepEffect()
{
	//解放処理関数.
	Release();
}

//===================================.
//		更新処理関数.
//===================================.
void CSleepEffect::Update()
{
	m_vPos[0] = m_vCenterPos;
}

//===================================.
//		初期化処理関数.
//===================================.
void CSleepEffect::Init()
{
	m_pCSprite.resize(1);
	m_vPos.resize(m_pCSprite.size());
	m_vScale.resize(m_pCSprite.size());
	m_vRot.resize(m_pCSprite.size());
	m_pCSprite[0] = CResourceManager::GetResourceManagerInstance()->GetSprite(enSprite::Bubble);
}

//====================================.
//		解放処理関数.
//====================================.
void CSleepEffect::Release()
{

}