#ifndef CPLAY_UI_H
#define CPLAY_UI_H

#include "..\CUI.h"

/*************************************
*	�v���C����UI�N���X.
*****/
class CPlayUI
	: public CUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

	//=====================�萔========================//.
	const float	ALPHA_MAX				= 1.0f;								//���ߒl�ő吔.
	const float	ALPHA_MIN				= 0.0f;								//���ߒl�ŏ��l.

	const D3DXVECTOR3	SCALE_MAX		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//�傫���ő吔.
	const D3DXVECTOR3	SCALE_MIN		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫���ŏ��l.
	const D3DXVECTOR2	INIT_PATTARN_NO = D3DXVECTOR2(0.0f, 0.0f);			//��{�p�^�[���ԍ�.

	//=====================�֐�========================//.
	virtual void UpDate() = 0;	//�X�V�����֐�.
	
	void Render();				//�`�揈���֐�.

protected:
	//=====================�ϐ�=========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vUIPos;		//UI���W.
	std::vector<D3DXVECTOR3>	m_vUIScale;		//UI�傫��.
	std::vector<D3DXVECTOR2>	m_vPatternNo;	//�p�^�[���ԍ�.
	std::vector<float>			m_fUIAlpha;		//���ߒl.

private:

};

#endif	//#ifndef CPLAY_UI_H.	