#ifndef CPEOPLE_ICON_H
#define CPEOPLE_ICON_H

#include "..\CIcon.h"
#include "..\..\SpriteUIEffect\ShockingEffect\CShockingEffect.h"

/*********************************
*		�l�̃A�C�R���N���X.
*****/
class CPeopleIcon
	: public CIcon
{
public:
	CPeopleIcon();
	virtual ~CPeopleIcon();

	//===================�萔=====================//.
	const D3DXVECTOR3	START_POS	= D3DXVECTOR3(0.0f, 95.0f, 0.0f);	//�����̍��W.
	const float			ACC_SPEED	= 0.1f;								//�����x���x.
	const float			GRAVITY		= 2.0f;								//�d��.

	//=============���u�������֐�===============//.
	//�����t���O.
	void SetSurpriseFlag(const bool& bFlag) { m_bSurpriseFlag = bFlag; }

	//===================�֐�=====================//.
	void UpDate();			//�X�V�����֐�.
	void RenderEffect();	//�G�t�F�N�g�`�揈���֐�.

protected:
	//===================�֐�=====================//.
	void SurpriseAct();		//�����s�������֐�.

	//===================�ϐ�=====================//.
	bool m_bSurpriseFlag;	//�����t���O.

private:
	//===================�ϐ�=====================//.
	float								m_fAcc;				//�����x.

	std::unique_ptr<CShockingEffect>	m_pCShockingEffect;	//�Ռ��N���X.
};

#endif	//#ifndef CPEOPLE_ICON_H.