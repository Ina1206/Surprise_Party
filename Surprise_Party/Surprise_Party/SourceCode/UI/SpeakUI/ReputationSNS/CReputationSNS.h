#ifndef CREPUTATION_SNS_H
#define CREPUTATION_SNS_H

#include "..\CSpeakUI.h"

/***************************************
*		SNS�ł̕]�������֐�.
*******************/
class CReputationSNS
	: public CSpeakUI
{
public:
	CReputationSNS();
	~CReputationSNS();

	//===========================�֐�=================================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//===========================�֐�=================================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//===========================�ϐ�=================================//.
	std::vector<std::string>	m_stArticleDetail;	//�L���ڍ�.
	int							m_EndingTypeNum;	//�G���f�B���O�^�C�v�ԍ�.

};

#endif	//#ifndef CREPUTATION_SNS_H.