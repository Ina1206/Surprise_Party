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
void CSceneBase::PlayBGM(const CSoundResource::enBGMType& enBGMType)
{
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetSEPlayManagerInstance();

	//BGM�̕ύX����.
	m_pCPlaySoundManager->ChangePlayingBGM(enBGMType);
	//BGM�̉��ʒ���.
	m_pCPlaySoundManager->SetPlayingBGMVolume(m_BGMVolume);
}