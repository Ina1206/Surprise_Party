#ifndef CPUSH_ENTER_H
#define CPUSH_ENTER_H

#include "..\..\..\CUI.h"

/********************************************
*		PushEnter�N���X.
***********************/
class CPushEnter
	: public CUI
{
public:
	CPushEnter();
	~CPushEnter();

	//=============================�萔====================================//.
	const D3DXVECTOR3	POS						= D3DXVECTOR3(800.0f, 600.0f, 0.0f);//�ʒu.
	const int			CHANGE_ALPHA_ADD_DIRECT = -1;								//���ߒl�ǉ������̕ύX���l.
	const float			TRANSPARENT_SPEED		= 0.05f;							//���ߑ��x.
	const float			ALPHA_MIN				= 0.0f;								//���ߒl�ŏ��l.
	const float			SCALE_MAX				= 2.0f;								//�傫���ő�l.

	//=============================�֐�====================================//.
	void Update();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.
	
private:
	//=============================�֐�====================================//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.

	//=============================�ϐ�====================================//.
	CSpriteUI*		m_pCSpriteUI;		//�X�v���C�gUI�N���X.
	int				m_AlphaAddDirect;	//���ߒl�ǉ�����.

};

#endif	//#ifndef CPUSH_ENTER_H.