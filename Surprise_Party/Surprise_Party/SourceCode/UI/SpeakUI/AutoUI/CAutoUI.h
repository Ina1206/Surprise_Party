#ifndef CAUTO_UI_H
#define CAUTO_UI_H

#include "..\..\CUI.h"

/**********************************
*		�����Đ�����UI�N���X.
************/
class CAutoUI
	: public CUI
{
public:
	CAutoUI();
	~CAutoUI();

	//=======================�萔==========================//.
	const D3DXVECTOR3	POS				= D3DXVECTOR3(900.0f, 665.0f, 0.0f);	//�\�����W.
	const unsigned int	APPEAR_FLAG		= (1 << 0);								//�����t���O.
	const unsigned int	DISAPPEAR_FLAG	= (1 << 1);								//������t���O.
	const float			ALPHA_SPEED		= 0.02f;								//���ߑ��x.
	const int			CHANGE_DIRECT	= -1;									//�����ύX.
	const float			ALPHA_MIN		= 0;									//���ߒl�ŏ��l.

	//=======================�֐�==========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=======================�ϐ�==========================//.
	CSpriteUI*		m_pCSpriteUI;			//�X�v���C�gUI.
	unsigned int	m_FlashingFlag;			//�_�Ńt���O.
	int				m_TransparentDirect;	//���ߕ���.

};

#endif	//#ifndef CAUTO_UI_H.