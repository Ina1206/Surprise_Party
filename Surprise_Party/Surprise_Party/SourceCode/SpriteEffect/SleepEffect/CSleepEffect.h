#ifndef CSLEEP_EFFECT_H
#define CSLEEP_EFFECT_H

#include "..\CSpriteEffectBase.h"

/********************************************
*		�Q�Ă���G�t�F�N�g�N���X.
****************/
class CSleepEffect
	: public CSpriteEffectBase
{
public:
	CSleepEffect();
	~CSleepEffect();

	//===============�萔=================//.
	const float	ALPHA_SPEED			= 0.005f;		//���ߑ��x.
	const float	SCALE_SPEED			= 0.005f;		//�g�k���x.
	const float START_ANGLE			= 60.0f;		//�J�n�p�x.
	const float	ANGLE_WIDTH			= 20.0f;		//�p�x��.
	const float CIRCLE_HALF_ANGLE	= 180.0f;		//���~�̊p�x.
	const float	MOVE_SPEED			= 0.01f;		//�ړ����x.
	const int	LINE_MAX			= 3;			//���̍s�ő吔.
	const float SLEEP_Z_NUM			= 1;			//����}�[�N�̔ԍ�.
	const float	ANGLE_MOVE_SPEED	= 5.0f;			//�p�x�ړ����x.
	const float	APPEAR_TIME			= 30;			//�\������.

	//===============�֐�=================//.
	void Update();		//�X�V�����֐�.

private:
	//===============�֐�=================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����f�����֐�.
	void Move(const int& num);				//�ړ������֐�.

};

#endif	//#ifndef CSLEEP_EFFECT_H.