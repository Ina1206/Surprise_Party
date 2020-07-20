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
	//�I���I���t���O.
	if (m_pCPauseUI->GetSelectFinishFlag() == true) {
		//�I��ԍ�.
		if (m_pCPauseUI->GetSelectNum() == SELECT_TITLE_NUM) {
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