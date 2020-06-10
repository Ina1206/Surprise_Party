#ifndef CBEFORE_RESULT_STAGE_H
#define CBEFORE_RESULT_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"
#include "..\..\UI\SpeakUI\ReputationSNS\CReputationSNS.h"
#include "..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"

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
	void Update();				//�X�V�����֐�.
	void Render();				//�`�揈���֐�.

private:
	//========================�֐�=========================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void DecideString();		//���͌��菈���֐�.
	void RenderSmartPhone();	//�X�}�[�g�t�H���`�揈���֐�.

	//========================�ϐ�=========================//.
	std::unique_ptr<CReputationSNS>	m_pCReputationSNS;	//SNS�]�������֐�.
	std::unique_ptr<CSmartPhone>	m_pCSmartPhone;		//�X�}�[�g�t�H���N���X
};

#endif	//#ifndef CBEFORE_RESULT_STAGE_H.