#include "CSceneBase.h"

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
void CSceneBase::PlayBGM(const enBGMType& enBGMType)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();

	//BGM‚Ì•ÏXˆ—.
	m_enPlayBGMType = enBGMType;
	m_pCPlaySoundManager->ChangePlayingBGM(m_enPlayBGMType);
}

//===========================================.
//		Ä¶BGM‚Ì‰¹—Ê’uŠ·ˆ—ŠÖ”.
//===========================================.
void CSceneBase::SetBGMVolume(const int& Volume)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();
	//BGM‚Ì‰¹—Ê.
	m_pCPlaySoundManager->SetPlayingBGMVolume(Volume);
}
