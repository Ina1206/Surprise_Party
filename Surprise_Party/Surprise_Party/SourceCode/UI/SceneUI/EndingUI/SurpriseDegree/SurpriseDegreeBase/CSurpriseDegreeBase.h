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
	const D3DXVECTOR3	EATCH_SCALE_MAX = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//���ꂼ��̑傫���ő�l.
	const D3DXVECTOR3	EATCH_SCALE_MIN = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���ꂼ��̑傫���ŏ��l.
	const float			ALPHA_MIN		= 0.0f;								//���ߒl�ŏ��l.

	//===================�֐�====================//.
	virtual void Update() = 0;		//�X�V�����֐�.
	void Render();					//�`�揈���֐�.
	
	//=============���擾�����֐�==============//.
	//�\���t���O.
	bool GetDispFlag() const { return m_bDispFlag; }

	//=============���u�������֐�==============//.
	//��C�ɕ\���t���O.
	void SetDisplayAllAtOnce(const bool& bFlag) { m_bDisplayAllAtOnce = bFlag; }
	//�\���ԍ�.
	void SetDipslayNum(const int& Num) { m_DipslayNum = Num; }

protected:

	//===================�ϐ�====================//.
	CSpriteUI*	m_pCSpriteUI;		//�X�v���C�gUI.
	D3DXVECTOR3 m_vEatchSizeScale;	//���ꂼ��̑傫��.
	bool		m_bDispFlag;		//�\���t���O.
	bool		m_bDisplayAllAtOnce;//��C�ɕ\���t���O.
	int			m_DipslayNum;		//�\���ԍ�.

private:
};

#endif	//#ifndef CSURPRSEI_REGREE_BASE_H.