#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"
#include "..\..\FileLoad\FileResource\CFileResource.h"

/**********************************************
*		�r�b�O�S�[�X�g������ׂ�N���X.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================�萔=======================//.
	const float		STRING_WIDTH_MAX = 950.0f;		//���͂̕��ő吔.

	//======================�֐�=======================//.
	void Update();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//======================�֐�========================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.
	void LoadSpeakString();	//��b���͓ǂݍ��ݏ����֐�.

	//======================�ϐ�========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vPos;			//���W.
	std::vector<D3DXVECTOR3>	m_vRot;			//�p�x.
	std::vector<float>			m_fAlpha;		//���ߒl.
	std::vector<float>			m_fScale;		//�傫��.

	bool						m_bSelectFlag;	//�I���t���O.

	std::vector<std::string>	m_stSpeakString;//��b����.
	int							m_SpeakNum;		//��b�ԍ�.
};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.