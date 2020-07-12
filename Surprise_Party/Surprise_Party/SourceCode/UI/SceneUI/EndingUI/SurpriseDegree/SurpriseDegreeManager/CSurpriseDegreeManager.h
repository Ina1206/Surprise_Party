#ifndef CSURPRISE_DEGREE_MANAGER_H
#define CSURPRISE_DEGREE_MANAGER_H

#include "..\SurpriseDegreeBase\CSurpriseDegreeBase.h"

/*********************************************
*		�������x�̊Ǘ��N���X.
********************/
class CSurpriseDegreeManager
{
public:
	CSurpriseDegreeManager();
	~CSurpriseDegreeManager();

	//==========================�֐�============================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//====================���擾�����֐�======================//.
	//�S�ĕ\���t���O.
	bool GetAllDispFlag() const { return m_bAllDispFlag; }

	//====================���u�������֐�======================//.
	//��C�ɕ\���t���O.
	void SetDisplayAllAtOnce(const bool& bFlag) { m_bDisplayAllAtOnce = bFlag; }

private:
	//==========================�֐�============================//.
	void Init();		//�����������֐�.

	//==========================�ϐ�============================//.
	std::vector<std::unique_ptr<CSurpriseDegreeBase>>	m_pCSurpriseDegreeBase;	//�������xUI�N���X.
	bool												m_bAllDispFlag;			//�S�Ă�\�������t���O.
	int													m_UpdateUINum;			//�X�V���Ă���UI�ԍ�.
	bool												m_bDisplayAllAtOnce;	//��C�ɕ\���t���O.
};

#endif	//#ifndef CSURPRISE_DEGREE_MANAGER_H.