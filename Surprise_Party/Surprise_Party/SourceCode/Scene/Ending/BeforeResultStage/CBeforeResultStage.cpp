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

}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CBeforeResultStage::Render()
{
	//���̕`�揈���֐�.
	RenderFloor();

	//�r�b�O�S�[�X�g�`�揈���֐�.
	RenderBigGhost();

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