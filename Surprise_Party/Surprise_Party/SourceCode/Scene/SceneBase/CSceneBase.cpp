#include "CSceneBase.h"

CSceneBase::CSceneBase()
	: m_mView			()
	, m_mProj			()
	, m_vBackColor		(0.0f, 0.0f, 0.0f, 0.0f)
	, m_bChangeScene	(false)
	, m_bPauseFlag		(false)
	, m_Evaluation		(0)
	, m_bTitle			(false)
	, m_BGMVolume		(1000)
{

}

CSceneBase::~CSceneBase()
{

}

//===========================================.
//		描画初期設定処理関数.
//===========================================.
void CSceneBase::RenderInitSetting(const D3DXMATRIX& mProj)
{
	m_mProj			= mProj;

	//背景色の設定.
	m_vBackColor = BACK_COLOR;
}

//===========================================.
//		BGM再生処理関数.
//===========================================.
void CSceneBase::PlayBGM(const CSoundResource::enBGMType& enBGMType)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetSEPlayManagerInstance();

	//BGMの変更処理.
	m_pCPlaySoundManager->ChangePlayingBGM(enBGMType);
	//BGMの音量調整.
	m_pCPlaySoundManager->SetPlayingBGMVolume(m_BGMVolume);
}