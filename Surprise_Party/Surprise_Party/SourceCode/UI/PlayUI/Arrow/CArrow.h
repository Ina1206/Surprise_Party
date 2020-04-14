#ifndef CARROW_H
#define CARROW_H

#include "..\CPlayUI.h"

/**********************************************
*			���N���X.
*****************/
class CArrow
	: public CPlayUI
{
public:
	CArrow();
	~CArrow();

	//===================�萔====================//.
	const D3DXVECTOR3	BASE_POS			= D3DXVECTOR3(600.0f, 500.0f, 0.0f);	//��{�ʒu.
	const int			ARROW_MAX			= 2;									//���ő�l.
	const int			LEFT_ARROW_NUM		= 0;									//�����ԍ�.
	const float			ARROW_WIDTH			= 100.0f;								//���.
	const float			LEFT_ARROW_ROT_Y	= 2.9f;									//�����y�p�x.

	const unsigned int	USING_LEFT_FLAG		= (1 << 0);								//���̖��g�p�t���O.
	const unsigned int	USING_RIGHT_FLAG	= (1 << 1);								//�E�̖��g�p�t���O.

	//===================�֐�====================//.
	void Update();		//�X�V�����֐�.

	//=============���u�������֐�==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

private:
	//===================�֐�====================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.

	//===================�ϐ�====================//.
	D3DXVECTOR3		m_vCenterPos;		//���S���W.
	unsigned int	m_UsingArrowFlag;	//�g�p���̖��t���O.
};

#endif	//#ifndef CARROW_H.