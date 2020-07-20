#include "CSceneBase.h"

/************************************
*		�V�[�����N���X.
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
//		�`�揉���ݒ菈���֐�.
//===========================================.
void CSceneBase::RenderInitSetting(const D3DXMATRIX& mProj)
{
	m_mProj			= mProj;

	//�w�i�F�̐ݒ�.
	m_vBackColor = BACK_COLOR;
}

//===========================================.
//		BGM�Đ������֐�.
//===========================================.
void CSceneBase::PlayBGM(const enBGMType& enBGMType)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();

	//BGM�̕ύX����.
	m_enPlayBGMType = enBGMType;
	m_pCPlaySoundManager->ChangePlayingBGM(m_enPlayBGMType);
}

//===========================================.
//		�Đ�BGM�̉��ʒu�������֐�.
//===========================================.
void CSceneBase::SetBGMVolume(const int& Volume)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();
	//BGM�̉���.
	m_pCPlaySoundManager->SetPlayingBGMVolume(Volume);
}
