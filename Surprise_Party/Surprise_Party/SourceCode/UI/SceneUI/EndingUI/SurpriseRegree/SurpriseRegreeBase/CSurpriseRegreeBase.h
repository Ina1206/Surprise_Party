#ifndef CSURPRSEI_REGREE_BASE_H
#define CSURPRSEI_REGREE_BASE_H

#include "..\..\..\..\CUI.h"

/****************************************
*		�������x�̊��N���X.
**********************/
class CSurpriseRegreeBase
	: public CUI
{
public:
	CSurpriseRegreeBase();
	virtual ~CSurpriseRegreeBase();

	//===================�萔====================//.
	const D3DXVECTOR3 EATCH_SCALE_MAX = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//���ꂼ��̑傫���ő�l.

	//===================�֐�====================//.
	virtual void Update() = 0;		//�X�V�����֐�.
	void Render();					//�`�揈���֐�.
	
protected:

	//===================�ϐ�====================//.
	CSpriteUI*	m_pCSpriteUI;		//�X�v���C�gUI.
	D3DXVECTOR3 m_vEatchSizeScale;	//���ꂼ��̑傫��.

private:
};

#endif	//#ifndef CSURPRSEI_REGREE_BASE_H.