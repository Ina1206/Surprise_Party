#include "CCameraGhostSpeakStage.h"

/**********************************************
*		お化けが話すステージのカメラクラス.
**************/
CCameraGhostSpeakStage::CCameraGhostSpeakStage()
{
	//初期化処理関数.
	Init();
}

CCameraGhostSpeakStage::~CCameraGhostSpeakStage()
{
	//解放処理関数.
	Release();
}

//===============================================.
//			更新処理関数.
//===============================================.
void CCameraGhostSpeakStage::Update()
{

}

//===============================================.
//			初期化処理関数.
//===============================================.
void CCameraGhostSpeakStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);
}

//===============================================.
//			解放処理関数.
//===============================================.
void CCameraGhostSpeakStage::Release()
{

}