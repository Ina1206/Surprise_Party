#ifndef CSHOUT_H
#define CSHOUT_H

#include "..\SurpriseDegreeBase\CSurpriseDegreeBase.h"

/*****************************************
*		���уN���X.
********************/
class CShout
	: public CSurpriseDegreeBase
{
public:
	CShout();
	~CShout();

	//====================�萔=======================//.
	const D3DXVECTOR3	FINISH_BASE_POS	= D3DXVECTOR3(300.0f, 560.0f, 0.0f);	//�ŏI�ʒu��{���W.
	const D3DXVECTOR3	INIT_POS		= D3DXVECTOR3(270.0f, 450.0f, 0.0f);	//�������W.
	const float			MOVE_SPEED		= 0.65f;								//�ړ����x.
	const unsigned int	BOUND_DOWN_FLAG = (1 << 0);								//�o�E���h������t���O.
	const unsigned int	BOUND_UP_FALG	= (1 << 1);								//�o�E���h�オ��t���O.
	const float			DISP_SPEED		= 0.1f;									//�\�����x.
	const float			ACC_ADD_SPEED	= 1.0f;									//�����x���Z���x.
	const float			GRAVITY			= 10.0f;								//�d��.
	const float			BOUND_SPEED		= 0.2f;									//�o�E���h���x.
	const int			JUMP_MAX		= 2;									//�W�����v�ő吔.
	const int			BOUND_MAX		= 1;									//�o�E���h�ő吔.

	//====================�֐�=======================//.
	void Update();		//�X�V�����֐�.

private:
	//====================�֐�=======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void Move();		//�ړ������֐�.
	void BoundSprite();	//�X�v���C�g�̃o�E���h�����֐�.
	void Disp();		//�\�������֐�.
	void Jump();		//�W�����v�����֐�.

	//====================�ϐ�=======================//.
	float			m_fAcc;				//�����x.
	int				m_JumpCnt;			//�W�����v�J�E���g.
	unsigned int	m_BoundFlag;		//�o�E���h�t���O.
};

#endif	//#ifndef CSHOUT_H.