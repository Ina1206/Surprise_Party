#ifndef CICON_H
#define CICON_H

#include "..\CCharaUI.h"

/**********************************
*		�A�C�R���N���X.
*******/
class CIcon
	: public CCharaUI
{
public:
	CIcon();
	virtual ~CIcon();

	//================�萔====================//.
	const float	SELECTING_SCALE		= 1.1f;		//�I�𒆂̑傫��.
	const float SELECTION_ALPHA		= 1.0f;		//�I�𒆂̓��ߒl.
	const float BASIC_SCALE			= 1.0f;		//��{�I�ȑ傫��.
	const float BASIC_ALPHA			= 0.75f;	//��{�I�ȓ��ߒl.

	//===========���u�������֐�=============//.
	//UI�̐F�u�������֐�.
	void SetColor(const D3DXVECTOR3& vColor) { m_vColor = vColor; }
	//�I���t���O.
	void SetSelectingFlag() { m_bSelectingFlag = true; }
	//����t���O.
	void SetSelectedFlag(const bool& flag) { m_bSelectedFlag = flag; }
protected:
	//================�֐�====================//.
	void SelectingDisplay();		//�I�𒆂̕\�������֐�.

	//================�ϐ�====================//.
	bool	m_bSelectingFlag;		//�I�𒆃t���O.
	bool	m_bSelectedFlag;		//�I�΂ꂽ�t���O.

};

#endif	//#ifndef CICON_H.