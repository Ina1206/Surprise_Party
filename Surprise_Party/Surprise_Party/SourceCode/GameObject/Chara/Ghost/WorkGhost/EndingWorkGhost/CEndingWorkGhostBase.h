#ifndef CENDING_WORK_GHOST_BASE_H
#define CENDING_WORK_GHOST_BASE_H

#include "..\CWorkGhostBase.h"

/**************************************************
*		�G���f�B���O�������������N���X.
********************/
class CEndingWorkGhostBase
	: public CWorkGhostBase
{
public:
	CEndingWorkGhostBase();
	virtual ~CEndingWorkGhostBase();

	//========================�萔=============================//.
	const int	CHANGE_DIRECT = -1;		//�����ύX.
	
protected:
	//========================�֐�=============================//.
	void Jump();		//�W�����v�����֐�.
	void ChangeEffect();//�G�t�F�N�g�ύX�����֐�.

	//========================�ϐ�=============================//.
	std::unique_ptr<CSpriteEffectBase>	m_pCSpriteEffect;	//�X�v���C�g�G�t�F�N�g.
	float								m_fAcc;				//�����x.
	float								m_fAccSpeed;		//�����x���Z���x.
	float								m_fAccMax;			//�����x�ő�l.
	float								m_fGravity;			//�d��.
private:
	//========================�ϐ�=============================//.
	int									m_OldEmotionNum;

};

#endif	//#ifndef CENDING_WORK_GHOST_BASE_H.