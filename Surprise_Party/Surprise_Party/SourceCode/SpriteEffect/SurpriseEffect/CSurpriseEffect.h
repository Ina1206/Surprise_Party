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

	//======================�萔===========================//.
	const int	SPRITE_MAX	= 3;		//�X�v���C�g�ő吔.
	const float SCALE_SPEED = 0.05f;	//�傫�����x.
	const float ALPHA_SPEED = 0.05f;	//���ߑ��x.
	const float ROT_Y		= 3.1f;		//y���̊p�x.
	const float BASE_ANGLE	= 120.0f;	//��{�̊p�x.
	const float ANGLE_WIDTH = 30.0f;	//�p�x��.
	const float MOVE_SPEED	= 0.003f;	//�ړ����x.

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

};

#endif	//#ifndef CSURPRIES_EFFECT_H.