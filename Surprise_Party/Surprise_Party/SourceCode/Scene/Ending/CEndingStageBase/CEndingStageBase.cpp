#include "CEndingStageBase.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_pCBigGhost			(nullptr)
	, m_pCFloor				(nullptr)
	, m_pCBackstageLight	(nullptr)
{
	//���ʂ̒l�̏����������֐�.
	InitCommonValue();
}

CEndingStageBase::~CEndingStageBase()
{

}

//=========================================.
//		���ʒl�̏����������֐�.
//=========================================.
void CEndingStageBase::InitCommonValue()
{
	//�C���X�^���X��.
	m_pCBigGhost.reset(new CBigGhost());
	m_pCFloor.reset(new CFloor());
	m_pCBackstageLight.reset(new CBackstageLight());
}