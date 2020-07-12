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
	bool GetAllDispFlag() const { return m_bAllDispFlag; }

private:
	//==========================�֐�============================//.
	void Init();		//�����������֐�.

	//==========================�ϐ�============================//.
	std::vector<std::unique_ptr<CSurpriseDegreeBase>>	m_pCSurpriseDegreeBase;	//�������xUI�N���X.
	bool												m_bAllDispFlag;			//�S�Ă�\�������t���O.
	int													m_UpdateUINum;			//�X�V���Ă���UI�ԍ�.
};

#endif	//#ifndef CSURPRISE_DEGREE_MANAGER_H.