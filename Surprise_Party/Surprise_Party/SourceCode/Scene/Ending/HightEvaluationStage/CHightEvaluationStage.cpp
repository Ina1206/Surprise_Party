#include "CHightEvaluationStage.h"

/**********************************************
*			���]���X�e�[�W�N���X.
*******************/
CHightEvaluationStage::CHightEvaluationStage()
{
	//�����������֐�.
	Init();
}

CHightEvaluationStage::~CHightEvaluationStage()
{
	//��������֐�.
	Release();
}

//=============================================.
//			�X�V�����֐�.
//=============================================.
void CHightEvaluationStage::Update()
{

}

//=============================================.
//			�`�揈���֐�.
//=============================================.
void CHightEvaluationStage::Render()
{
	//���̕`�揈���֐�.
	RenderFloor();

	//�������`�揈���֐�.
	RenderGhost();
}

//=============================================.
//			�����������֐�.
//=============================================.
void CHightEvaluationStage::Init()
{

}

//=============================================.
//			��������֐�.
//=============================================.
void CHightEvaluationStage::Release()
{

}