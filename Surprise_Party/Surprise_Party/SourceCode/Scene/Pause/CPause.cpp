#include "CPause.h"

/****************************************
*		�ꎞ��~�N���X.
************/
CPause::CPause()
	: m_pCPauseUI	(nullptr)
{
	//�����������֐�.
	Init();
}

CPause::~CPause()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CPause::UpDate()
{
	//�X�V�����֐�.
	m_pCPauseUI->Update();

	m_bTitle = false;
	if (m_pCPauseUI->GetSelectFinishFlag() == true) {
		if (m_pCPauseUI->GetSelectNum() == 1) {
			m_bTitle = true;
		}
		m_bPauseFlag = false;
	}
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CPause::Render()
{
	//�`�揈���֐�.
	m_pCPauseUI->Render();
}

//========================================.
//		�����������֐�.
//========================================.
void CPause::Init()
{
	m_pCPauseUI.reset(new CPauseUI());
}

//========================================.
//		��������֐�.
//========================================.
void CPause::Release()
{

}