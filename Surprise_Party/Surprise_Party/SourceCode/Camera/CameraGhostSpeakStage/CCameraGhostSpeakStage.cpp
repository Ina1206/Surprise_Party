#include "CCameraGhostSpeakStage.h"

/**********************************************
*		���������b���X�e�[�W�̃J�����N���X.
**************/
CCameraGhostSpeakStage::CCameraGhostSpeakStage()
{
	//�����������֐�.
	Init();
}

CCameraGhostSpeakStage::~CCameraGhostSpeakStage()
{
	//��������֐�.
	Release();
}

//===============================================.
//			�X�V�����֐�.
//===============================================.
void CCameraGhostSpeakStage::Update()
{

}

//===============================================.
//			�����������֐�.
//===============================================.
void CCameraGhostSpeakStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);
}

//===============================================.
//			��������֐�.
//===============================================.
void CCameraGhostSpeakStage::Release()
{

}