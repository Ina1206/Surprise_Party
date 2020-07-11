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
}

//=============================================.
//			�`�揈���֐�.
//=============================================.
void CSurpriseDegreeManager::Render()
{
	for (int UI = 0; UI <= m_UpdateUINum; UI++) {
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