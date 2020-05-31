#ifndef CQUESTION_EFFECT_H
#define CQUESTION_EFFECT_H

#include "..\CSpriteEffectBase.h"

/************************************
*		�^��G�t�F�N�g�N���X.
***************/
class CQuestionEffect
	: public CSpriteEffectBase
{
public:
	CQuestionEffect();
	~CQuestionEffect();

	//====================�萔========================//.
	const unsigned int	FINISH_MOVE_HORIZONTAL	= (1 << 0);	//���ړ��I���t���O.
	const unsigned int	FINISH_MOVE_VERTICAL	= (1 << 1);	//�c�ړ��I���t���O.

	const float			ACC_SPEAD				= 0.004f;	//�����x�̌������x.
	const float			GRAVITY					= 0.08f;	//�d��.
	const float			MOVE_SPEED				= 0.025f;	//�ړ����x.
	const float			DISTANCE_MAX			= 1.5f;		//�����ő�l.

	const float			SCALING_SPEED			= 0.1f;		//�g�k���x.
	const float			SCALING_MIN				= 0.2f;		//�g�k�ŏ��l.

	//====================�֐�========================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�G�t�F�N�g�J�n�����������֐�.

private:
	//====================�֐�========================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.
	void Scaling(const int& num);			//�g�k�����֐�.

	//====================�ϐ�========================//.
	float			m_fAcc;					//�����x.
	D3DXVECTOR3		m_vStartPos;			//�ړ��J�n���̍��W.
	unsigned int	m_MoveFinishFlag;		//�ړ��t���O.

};

#endif	//#ifndef CQUESTION_EFFECT_H.