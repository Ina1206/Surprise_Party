#ifndef COBJECT_MOVE_SWITCH_H
#define COBJECT_MOVE_SWITCH_H

#include "..\CSwitchBase.h"

/*****************************************
*		�X�C�b�`�̈ړ��I�u�W�F�N�g�N���X.
*****************/
class CObjectMoveSwitch
	: public CSwitchBase
{
public:
	CObjectMoveSwitch();
	~CObjectMoveSwitch();

	//============�萔===============//.
	const int	MOVE_OBJECT_MAX = 2;	//�ړ��I�u�W�F�N�g�ő吔.
	const int	TABLE_NUM		= 0;	//���ԍ�.
	const int	FLOWER_NUM		= 1;	//�Ԕԍ�.

	//============�֐�===============//.
	void Update();		//�X�V�����֐�.
private:
	//============�֐�===============//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//============�ϐ�===============//.
	D3DXVECTOR3	m_vAttachedOldPos;	//�t���I�u�W�F�N�g�O��̍��W.

};

#endif //#ifndef COBJECT_MOVE_SWITCH_H.