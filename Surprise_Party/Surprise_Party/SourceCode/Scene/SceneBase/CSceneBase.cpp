#include "CSceneBase.h"

/************************************
*		シーン基底クラス.
*****/
CSceneBase::CSceneBase()
	: m_mView			()
	, m_mProj			()
	, m_vBackColor		(0.0f, 0.0f, 0.0f, 0.0f)
	, m_bChangeScene	(false)
	, m_bPauseFlag		(false)
	, m_Evaluation		(0)
	, m_bTitle			(false)
	, m_BGMVolume		(0)
	, m_enPlayBGMType	()
	, m_bChangeVolume	(true)
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
void CSceneBase::PlayBGM(const enBGMType& enBGMType)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();

	//BGMの変更処理.
	m_enPlayBGMType = enBGMType;
	m_pCPlaySoundManager->ChangePlayingBGM(m_enPlayBGMType);
}

//===========================================.
//		再生BGMの音量置換処理関数.
//===========================================.
void CSceneBase::SetBGMVolume(const int& Volume)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();
	//BGMの音量.
	m_pCPlaySoundManager->SetPlayingBGMVolume(Volume);
}
