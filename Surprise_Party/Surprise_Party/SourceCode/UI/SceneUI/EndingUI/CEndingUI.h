#ifndef CENDING_UI_H
#define CENDING_UI_H

#include "PushEnter\CPushEnter.h"
#include "EvaluationUI\EvaluationUIManager\CEvaluationUIManager.h"
#include "SurpriseDegree\SurpriseDegreeManager\CSurpriseDegreeManager.h"
#include "..\CSceneUIBase.h"

/*******************************************
*		�G���f�B���OUI�N���X.
********************/
class CEndingUI
	: public CSceneUIBase
{
public:
	CEndingUI();
	CEndingUI(const int& EvaluationNum);
	~CEndingUI();

	//======================�萔==========================//.
	const unsigned int SURPRISE_DEGREE_FLAG = (1 << 0);	//�������x�t���O.
	const unsigned int EVALUATION_FLAG		= (1 << 1);	//�]���t���O.
	const unsigned int PUSH_ENTER_FLAG		= (1 << 2);	//PushEnter�t���O.

	//======================�֐�==========================//.
	void Update();					//�X�V�����֐�.
	void Render();					//�`�揈���֐�.

	//===============-���擾�����֐�====================//.
	//�]���I���t���O.
	bool GetFinishEvaluationFlag() const { return m_bFinishEvaluationFlag; }
	//�V�[���ύX�t���O.
	bool GetChangeSceneFlag() const { return m_bChangeSceneFlag; }

private:
	//======================�֐�==========================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.
	void UpdateSurpriseDegree();	//�������x�X�V�����֐�.
	void UpdateEvaluation();		//�]���X�V�����֐�.
	void UpdatePushEnter();			//PushEnter�X�V�����֐�.

	//======================�ϐ�==========================//.
	std::unique_ptr<CSurpriseDegreeManager>	m_pCSurpriseDegreeManager;	//�������xUI�Ǘ��N���X.
	std::unique_ptr<CEvaluationUIManager>	m_pCEvaluationManager;		//�]��UI�Ǘ��N���X.
	std::unique_ptr<CPushEnter>				m_pCPushEnter;				//PushEnter�N���X.

	unsigned int							m_UpdateUIFlag;				//�X�V����UI�t���O.
	bool									m_bFinishEvaluationFlag;	//�]���I���t���O.
	int										m_EvaluationNum;			//�]���ԍ�.
	bool									m_bDisplayAllAtOnce;		//��C�ɕ`�悷��t���O.
	bool									m_bChangeSceneFlag;			//�V�[���ύX�t���O.

};


#endif	//#ifndef CENDING_UI_H.