#ifndef CEVALUATION_UI_MANAGER_H
#define CEVALUATION_UI_MANAGER_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/*********************************************
*		�]��UI�̊Ǘ��N���X.
********************/
class CEvaluationUIManager
{
public:

	CEvaluationUIManager();
	CEvaluationUIManager(const int& EvaluationNum);
	~CEvaluationUIManager();

	//=====================�֐�========================//.
	void Update();												//�X�V�����֐�.
	void Render();												//�`�揈���֐�.

	//===============���擾�����֐�==================//.
	//�S�ĕ\���I�������t���O.
	bool GetFinishedAllDispFlag() const { return m_bFinishedAllDispFlag; }

	//===============���u�������֐�==================//.
	//��C�ɕ\������t���O.
	void SetDispAllAtOnce(const bool& bFlag) { m_bDisplayAllAtOnce = bFlag; }

private:
	//=====================�֐�========================//.
	void Init();												//�����������֐�.
	std::unique_ptr<CEvaluationUIBase> DecideEvaluationUIType();//�]��UI�̎�ތ��菈���֐�.

	//=====================�ϐ�========================//.
	std::unique_ptr<CEvaluationUIBase>	m_pCEvaluationUIBase;	//�]��UI.
	int									m_EvaluationNum;		//�]���ԍ�.
	bool								m_bFinishedAllDispFlag;	//�S�ĕ\���I�������t���O.
	bool								m_bDisplayAllAtOnce;	//��C�ɕ\������t���O.
};

#endif	//#ifndef CEVALUATION_UI_MANAGER_H.