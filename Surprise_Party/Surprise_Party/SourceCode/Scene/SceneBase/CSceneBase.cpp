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
//		•`‰æ‰ŠúÝ’èˆ—ŠÖ”.
//===========================================.
void CSceneBase::RenderInitSetting(const D3DXMATRIX& mProj)
{
	m_mProj			= mProj;

	//”wŒiF‚ÌÝ’è.
	m_vBackColor = BACK_COLOR;
}

//===========================================.
//		BGMÄ¶ˆ—ŠÖ”.
//===========================================.
void CSceneBase::PlayBGM(const CSoundResource::enBGMType& enBGMType)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetSEPlayManagerInstance();

	//BGM‚Ì•ÏXˆ—.
	m_pCPlaySoundManager->ChangePlayingBGM(enBGMType);
	//BGM‚Ì‰¹—Ê’²®.
	m_pCPlaySoundManager->SetPlayingBGMVolume(m_BGMVolume);
}