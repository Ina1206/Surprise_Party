#include "CDescriptionUIManager.h"

/*****************************************
*		����UI�Ǘ��N���X.
**************/
CDescriptionUIManager::CDescriptionUIManager()
	: m_pCArrow(nullptr)
	, m_pCTutorialBlackScreen(nullptr)
{
	//�����������֐�.
	Init();
}

CDescriptionUIManager::~CDescriptionUIManager()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CDescriptionUIManager::Update()
{
	//���̌����ݒ�.
	m_pCArrow->SetUsingArrowFlag(m_pCArrow->USING_LEFT_FLAG);
	const D3DXVECTOR3 vCenterPos = D3DXVECTOR3(m_vCenterPos.x + 500.0f, m_vCenterPos.y - 30.0f, m_vCenterPos.z);
	m_pCArrow->SetCenterPos(vCenterPos);
	
	
	m_pCArrow->SetUsingArrowFlag(m_pCArrow->USING_RIGHT_FLAG);
	const D3DXVECTOR3 vCenterPos = D3DXVECTOR3(m_vCenterPos.x - 100.0f, m_vCenterPos.y, m_vCenterPos.z);
	m_pCArrow->SetCenterPos(vCenterPos);

	
	m_pCArrow->Update();

	m_pCTutorialBlackScreen->SetCenterPos(m_vCenterPos);
	m_pCTutorialBlackScreen->Update();

}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CDescriptionUIManager::Render()
{
	m_pCTutorialBlackScreen->Render();

	m_pCArrow->Render();

}

//===========================================.
//		�����������֐�.
//===========================================.
void CDescriptionUIManager::Init()
{
	m_pCArrow.reset(new CArrow());
	m_pCTutorialBlackScreen.reset(new CTutorialBlackScreen());

}

//===========================================.
//		��������֐�.
//===========================================.
void CDescriptionUIManager::Release()
{

}