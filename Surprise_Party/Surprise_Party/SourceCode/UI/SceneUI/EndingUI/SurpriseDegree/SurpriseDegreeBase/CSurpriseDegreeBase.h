#ifndef CSURPRSEI_REGREE_BASE_H
#define CSURPRSEI_REGREE_BASE_H

#include "..\..\..\..\CUI.h"

/****************************************
*		�������x�̊��N���X.
**********************/
class CSurpriseDegreeBase
	: public CUI
{
public:
	CSurpriseDegreeBase();
	virtual ~CSurpriseDegreeBase();

	//===================�萔====================//.
	const D3DXVECTOR3 EATCH_SCALE_MAX = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//���ꂼ��̑傫���ő�l.

	//===================�֐�====================//.
	virtual void Update() = 0;		//�X�V�����֐�.
	void Render();					//�`�揈���֐�.
	
	//=============���擾�����֐�==============//.
	//�\���t���O.
	bool GetDispFlag() const { return m_bDispFlag; }

protected:

	//===================�ϐ�====================//.
	CSpriteUI*	m_pCSpriteUI;		//�X�v���C�gUI.
	D3DXVECTOR3 m_vEatchSizeScale;	//���ꂼ��̑傫��.
	bool		m_bDispFlag;		//�\���t���O.

private:
};

#endif	//#ifndef CSURPRSEI_REGREE_BASE_H.