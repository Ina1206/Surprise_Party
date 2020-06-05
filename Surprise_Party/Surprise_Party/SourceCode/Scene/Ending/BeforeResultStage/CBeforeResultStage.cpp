#include "CBeforeResultStage.h"

#include "..\..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"

/********************************************
*		���ʔ��\�O�̃X�e�[�W�N���X.
******************/
CBeforeResultStage::CBeforeResultStage()
{
	//�����������֐�.
	Init();
}

CBeforeResultStage::~CBeforeResultStage()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CBeforeResultStage::Update()
{
	//�J�����X�V�����֐�.
	m_pCCameraEnding->Update();

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}
	

}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CBeforeResultStage::Render()
{
	//���̕`�揈���֐�.
	RenderFloor();


	//�������`�揈���֐�.
	RenderGhost();
}

//=======================================.
//		�����������֐�.
//=======================================.
void CBeforeResultStage::Init()
{

}

//=======================================.
//		��������֐�.
//=======================================.
void CBeforeResultStage::Release()
{

}