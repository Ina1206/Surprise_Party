#ifndef CFONT_RESOURCE_H
#define CFONT_RESOURCE_H

#include "..\..\..\Global.h"
#include "..\..\Font\CFont.h"
#include "..\..\Sprite\CDepth_Stencil.h"

/*********************************************
*	�t�H���g�ǂݍ��݃N���X.
**********/
class CFontResource
{
public:
	CFontResource();
	~CFontResource();

	//=================�萔====================//.
	const int		FONT_SIZE		= 500;			//�t�H���g�̑傫��.
	const float		BASIC_WIDTH		= 1.0f;		//��{�̕�.
	//const float		BASIC_WIDTH		= 250.0f;		//��{�̕�.

	//=================�֐�====================//.
	void Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);//�����������֐�.
	void Load(std::string str);											//�ǂݍ��ݏ����֐�.
	void String_Render();												//������`�揈���֐�.
	void Destroy();														//�폜�����֐�.

	//==========���u�������֐�===============//.
	void SetStartPos(const D3DXVECTOR3& vPos) { m_vStartPos = vPos; }
	void SetFontScale(const float& fScale) { m_fFontScale = fScale; }

	//==========���l�������֐�===============//.
	CFont* GetFont() { return m_pCFont[0]; }
private:
	//=================�֐�====================//.
	void Release();														//��������֐�.

	//=================�ϐ�====================//.
	ID3D11Device*			m_pDevice11;	//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;	//�R���e�L�X�g.
	std::vector<CFont*>		m_pCFont;		//�t�H���g�N���X.
	int						m_StrLength;	//������̒���.
	D3DXVECTOR3				m_vStartPos;	//�ꕶ���ڂ̈ʒu.
	HFONT					m_hFont;		//�t�H���g.
	HDC						m_hdc;			//�f�o�C�X�R���e�L�X�g.
	float					m_fFontScale;	//�����̑傫��.

};

#endif	//#ifndef CFONT_RESOURCE_H.