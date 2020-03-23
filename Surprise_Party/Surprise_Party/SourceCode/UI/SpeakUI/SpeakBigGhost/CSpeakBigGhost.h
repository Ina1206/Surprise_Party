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
	const float		STRING_WIDTH_MAX	= 950.0f;		//���͂̕��ő吔.
	const float		ALPHA_MIN			= 0.0f;			//���ߒl�ŏ��l.
	const float		ALPHA_MAX			= 1.0f;			//���ߒl�ő�l.
	const float		ALPHA_SPEED			= 0.1f;			//���ߒl���x.
	const float		FONT_SCALE			= 50.0f;		//�����̑傫��.

	const int		SELECT_MAX			= 2;			//�I���ő吔.

	const unsigned int TRANSPARENTING_FLAG	= (1 << 0);	//���ߏ������t���O.
	const unsigned int SELECT_FLAG			= (1 << 1);	//�I���t���O.
	const unsigned int SELECTED_STRING_FLAG = (1 << 2);	//�I���������̓t���O.

	//======================�֐�=======================//.
	void Update();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//======================�֐�========================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.
	void LoadSpeakString();			//��b���͓ǂݍ��ݏ����֐�.
	void TransparentFont();			//�������ߏ����֐�.
	void DecisionSelectString();	//�I�𕶏͏����֐�.
	void SelectingMove();			//�I�𒆈ړ������֐�.

	//======================�ϐ�========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;		//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vPos;				//���W.
	std::vector<D3DXVECTOR3>	m_vRot;				//�p�x.
	std::vector<float>			m_fAlpha;			//���ߒl.
	std::vector<float>			m_fScale;			//�傫��.

	std::vector<std::string>	m_stSpeakString;	//��b����.
	std::vector<std::string>	m_stSelectString;	//�I�𕶏�.
	int							m_SpeakNum;			//��b�ԍ�.
	float						m_fFontAlpha;		//�������ߒl.
	int							m_ChangingFontNum;	//�ύX���̃t�H���g�ԍ�.
	unsigned int				m_StringFlag;		//���̓t���O.
	int							m_SelectNum;		//�I��ԍ�.
	int							m_SelectCnt;		//�I���J�E���g.

};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.