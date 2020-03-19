#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"

/**********************************************
*		�r�b�O�S�[�X�g������ׂ�N���X.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================�֐�=======================//.
	void Update();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.

private:
	//======================�֐�========================//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.

	//======================�ϐ�========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vPos;			//���W.
	std::vector<D3DXVECTOR3>	m_vRot;			//�p�x.
	std::vector<float>			m_fAlpha;		//���ߒl.
	std::vector<float>			m_fScale;		//�傫��.

	float						m_fFontScale;	//�傫��

	bool						m_bSelectFlag;	//�I���t���O.
};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.