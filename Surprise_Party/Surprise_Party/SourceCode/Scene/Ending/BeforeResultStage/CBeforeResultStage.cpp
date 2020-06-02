#include "CBeforeResultStage.h"

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

	//�r�b�O�S�[�X�g�`�揈���֐�.
	//RenderBigGhost();

	//�������`�揈���֐�.
	RenderGhost();

}

//=======================================.
//		�����������֐�.
//=======================================.
void CBeforeResultStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);

}

//=======================================.
//		��������֐�.
//=======================================.
void CBeforeResultStage::Release()
{

}