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
	const int		FONT_SIZE		= 500;													//�t�H���g�̑傫��.
	const float		BASIC_WIDTH		= 1.0f;													//��{�̕�.

	//=================�֐�====================//.
	void Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);					//�����������֐�.
	void Load(std::string str, bool InputPictureFlag = false);								//�ǂݍ��ݏ����֐�.
	void String_Render();																	//������`�揈���֐�.
	void Destroy();																			//�폜�����֐�.

	//==========���u�������֐�===============//.
	void SetStartPos(const D3DXVECTOR3& vPos) { m_vStartPos = vPos; }						//�J�n���W.
	void SetFontScale(const float& fScale) { m_fFontScale = fScale; }						//�t�H���g�傫��.
	void SetAlpha(const float& fAlpha, const int& FontNum) { m_fAlpha[FontNum] = fAlpha; }	//���ߒl.
	void SetWidthMax(const float& fWidthMax) { m_fWidthMax = fWidthMax; }					//�\�������ő�l.

	//==========���l�������֐�===============//.
	CFont*			GetFont() const { return m_pCFont[0].get(); }
	int				GetStrLength() const { return m_StrLength; }							//�����񒷂��擾.
	D3DXVECTOR3		GetFontPos(const int& num) const { return m_vPos[num]; }				//�t�H���g���W�擾.
	unsigned int	GetInputPictureSize() const { return m_InputPictureNum.size(); }		//���͂̒��ɓ����G�̃T�C�Y.
	int				GetInputPictureNum(const int& num) { return m_InputPictureNum[num]; }	//���͂̒��ɓ����G�̔ԍ�.
	std::string		GetPictureTypeNum(const int& num) { return m_PictureTypeNum[num]; }		//�G�̎�ޔԍ�.

private:
	//=================�֐�====================//.
	void Release();																			//��������֐�.

	//=================�ϐ�====================//.
	ID3D11Device*							m_pDevice11;									//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*					m_pContext11;									//�R���e�L�X�g.
	std::vector<std::unique_ptr<CFont>>		m_pCFont;										//�t�H���g�N���X.
	int										m_StrLength;									//������̒���.
	D3DXVECTOR3								m_vStartPos;									//�ꕶ���ڂ̈ʒu.
	std::vector<D3DXVECTOR3>				m_vPos;											//���W.
	HFONT									m_hFont;										//�t�H���g.
	HDC										m_hdc;											//�f�o�C�X�R���e�L�X�g.
	float									m_fFontScale;									//�����̑傫��.
	std::vector<float>						m_fAlpha;										//�����̓��ߒl.
	float									m_fWidthMax;									//���͕��̍ő吔.
	std::vector<int>						m_InputPictureNum;								//�A�C�R�������ԍ�.
	std::vector<std::string>				m_PictureTypeNum;								//�G��ޔԍ�.
};

#endif	//#ifndef CFONT_RESOURCE_H.