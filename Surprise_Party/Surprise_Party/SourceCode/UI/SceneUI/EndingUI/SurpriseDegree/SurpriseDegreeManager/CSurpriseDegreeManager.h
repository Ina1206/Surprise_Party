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

private:
	//==========================�֐�============================//.
	void Init();		//�����������֐�.

	//==========================�ϐ�============================//.
	

};

#endif	//#ifndef CSURPRISE_DEGREE_MANAGER_H.