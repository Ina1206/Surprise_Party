#ifndef CSMOKE_EFFECT_H
#define CSMOKE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*************************************
*		���G�t�F�N�g�N���X.
**********/
class CSmokeEffect
	: public CSpriteEffectBase
{
public:
	CSmokeEffect();
	~CSmokeEffect();

	//=====================�萔=======================//.
	const float	INIT_ANGLE		= 90.0f;	//�����p�x.
	const float ALPHA_SPEED		= 0.015f;	//���ߑ��x.
	const float	SCALING_SPEED	= 0.015f;	//�g�k���x.
	const float	ANGLE_SPEED		= 2.0f;		//�p�x���Z���x.
	const float	ANGLE_MAX		= 360.0f;	//�p�x�ő�l.
	const float	HORIZON_SPEED	= 0.04f;	//���ړ����x.
	const float	VERTICAL_SPEED	= 0.05f;	//�c�ړ����x.
	const float	ROT_SPEED		= 0.05f;	//��]���x.

	//=====================�֐�=======================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�G�t�F�N�g�J�n�����������֐�.
	
private:
	//=====================�֐�=======================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.
	void Rotation(const int& num);			//��]�����֐�.

	//=====================�ϐ�=======================//.
	std::vector<int> m_MoveDirection;		//�ړ�����.
};

#endif	//#ifndef CSMOKE_EFFECT_H.