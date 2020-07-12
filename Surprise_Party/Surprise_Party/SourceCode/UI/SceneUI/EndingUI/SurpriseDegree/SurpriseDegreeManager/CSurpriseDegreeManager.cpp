#include "CSurpriseDegreeManager.h"
#include "..\SurpriseDegreeString\CSurpriesDegreeString.h"

/*********************************************
*		�������x�̊Ǘ��N���X.
********************/
CSurpriseDegreeManager::CSurpriseDegreeManager()
	: m_pCSurpriseDegreeBase()
	, m_bAllDispFlag		(false)
	, m_UpdateUINum			(0)
{
	//�����������֐�.
	Init();
}

CSurpriseDegreeManager::~CSurpriseDegreeManager()
{

}

//=============================================.
//			�X�V�����֐�.
//=============================================.
void CSurpriseDegreeManager::Update()
{
	if (m_bAllDispFlag == true) {
		return;
	}
	m_pCSurpriseDegreeBase[m_UpdateUINum]->Update();

	if (m_pCSurpriseDegreeBase[m_UpdateUINum]->GetDispFlag() == true) {
		m_UpdateUINum++;
	}

	if (m_UpdateUINum >= static_cast<int>(m_pCSurpriseDegreeBase.size())) {
		m_bAllDispFlag = true;
	}
}

//=============================================.
//			�`�揈���֐�.
//=============================================.
void CSurpriseDegreeManager::Render()
{
	for (unsigned int UI = 0; UI < m_pCSurpriseDegreeBase.size(); UI++) {
		m_pCSurpriseDegreeBase[UI]->Render();
	}
}

//=============================================.
//			�����������֐�.
//=============================================.
void CSurpriseDegreeManager::Init()
{
	//�������x�̕���UI�\�z.
	m_pCSurpriseDegreeBase.emplace_back(std::make_unique<CSurpriseDegreeString>());
}