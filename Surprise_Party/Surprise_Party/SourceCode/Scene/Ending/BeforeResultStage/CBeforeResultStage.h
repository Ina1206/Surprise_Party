#ifndef CBEFORE_RESULT_STAGE_H
#define CBEFORE_RESULT_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"
#include "..\..\UI\SpeakUI\ReputationSNS\CReputationSNS.h"

/********************************************
*		���ʔ��\�O�̃X�e�[�W�N���X.
******************/
class CBeforeResultStage
	: public CEndingStageBase
{
public:
	CBeforeResultStage();
	~CBeforeResultStage();

	//========================�֐�=========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//========================�֐�=========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void DecideString();//���͌��菈���֐�.

	//========================�ϐ�=========================//.
	std::unique_ptr<CReputationSNS>	m_pCReputationSNS;	//SNS�]�������֐�.

};

#endif	//#ifndef CBEFORE_RESULT_STAGE_H.