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
	const int			BUBBLE_MAX			= 4;								//�A�ő吔.
	const int			Z_MAX				= 2;								//Z�ő吔.
	const int			ALL_SPRITE_MAX		= BUBBLE_MAX + Z_MAX;				//�S�ẴX�v���C�g�ő吔.
	const D3DXVECTOR3	INIT_LOCAL_POS		= D3DXVECTOR3(-2.3f, 2.0f, 0.0f);	//�����̃��[�J�����W.

	const float			START_ANGLE			= 60.0f;							//�J�n�p�x.
	const float			ANGLE_WIDTH			= 20.0f;							//�p�x��.
	const float			CIRCLE_HALF_ANGLE	= 180.0f;							//���~�̊p�x.
	const float			MOVE_SPEED			= 0.01f;							//�ړ����x.
	const int			LINE_MAX			= 3;								//���̍s�ő吔.
	const float			SLEEP_Z_NUM			= 1;								//����}�[�N�̔ԍ�.
	const float			ANGLE_MOVE_SPEED	= 5.0f;								//�p�x�ړ����x.
	const float			APPEAR_TIME			= 30;								//�\������.



	//===============�֐�=================//.
	void Update();		//�X�V�����֐�.

private:
	//===============�֐�=================//.
	void Init();								//�����������֐�.
	void Release();								//��������֐�.
	void AppeartJudgement(const int& num);		//�\�����f�����֐�.
	void Move(const int& num);					//�ړ������֐�.

};

#endif	//#ifndef CSLEEP_EFFECT_H.