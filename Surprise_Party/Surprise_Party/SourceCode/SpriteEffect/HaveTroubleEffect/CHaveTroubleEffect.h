#ifndef CHAVE_TROUBLE_EFFECT_H
#define CHAVE_TROUBLE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/******************************************
*		����G�t�F�N�g�N���X.
************/
class CHaveTroubleEffect
	: public CSpriteEffectBase
{
public:
	CHaveTroubleEffect();
	~CHaveTroubleEffect();

	//=================�萔===================//.
	const int			SPRITE_MAX		= 6;								//�X�v���C�g�ő吔.
	const D3DXVECTOR3	INT_LOCAL_POS	= D3DXVECTOR3(1.5f, 1.5f, 0.0f);	//�����̃��[�J�����W.
	const int			LINE_MAX		= 3;								//���̍s�ő吔.
	const int			DISP_TIME_MAX	= 20;								//�\�����ԍő吔.
	const float			ALPHA_SPEED		= 0.04f;							//���ߑ��x.
	const float			SCALING_SPEED	= 0.04f;							//�g�k���x.
	const float			START_ANGLE		= 30.0f;							//�J�n�p�x.
	const float			ANGLE_WIDTH		= 30.0f;							//�p�x��.

	const float			ROT_WIDTH		= 0.3f;								//�X�v���C�g�p�x��.

	const float			MOVE_SPEED		= 0.05f;							//�ړ����x.

	const float			ADJUST_ANGLE	= 50.0f;							//�������̊p�x

	//=================�֐�===================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�G�t�F�N�g�J�n�����֐�.

private:
	//=================�֐�===================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.	

	//=================�ϐ�===================//.
	int					m_DispCnt;			//�\���J�E���g.
};

#endif	//#ifndef CHAVE_TROUBLE_EFFECT_H.