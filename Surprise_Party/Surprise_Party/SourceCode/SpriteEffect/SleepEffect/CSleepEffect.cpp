#include "CSleepEffect.h"

/********************************************
*		�Q�Ă���G�t�F�N�g�N���X.
****************/
CSleepEffect::CSleepEffect()
{
	//�����������֐�.
	Init();
}

CSleepEffect::~CSleepEffect()
{
	//��������֐�.
	Release();
}

//===================================.
//		�X�V�����֐�.
//===================================.
void CSleepEffect::Update()
{
	m_vPos[0] = m_vCenterPos;
}

//===================================.
//		�����������֐�.
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
//		��������֐�.
//====================================.
void CSleepEffect::Release()
{

}