#ifndef CSURPRIES_EFFECT_H
#define CSURPRIES_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
class CSurpriseEffect
	: public CSpriteEffectBase
{
public:
	CSurpriseEffect();
	~CSurpriseEffect();

	//======================�֐�===========================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�Đ��J�n�����������֐�.

	//================���u�������֐�=====================//.
	void SetDispFlag(const bool& flag) { m_bAllDispFlag = flag; }

private:
	//======================�֐�===========================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.

	//======================�ϐ�===========================//.
	int					m_DispCnt;		//�\���J�E���g.
	bool				m_bAllDispFlag;	//�S�̕\���t���O.
	std::vector<float>	m_fDistance;	//����.

};

#endif	//#ifndef CSURPRIES_EFFECT_H.