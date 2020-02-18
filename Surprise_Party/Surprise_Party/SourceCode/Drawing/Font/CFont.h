#ifndef CFONT_H
#define CFONT_H

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )

#include "..\CCommon.h"
#include <tchar.h>
#define ALINGN16 _declspec(align(16))

class CFont
	: public CCommon
{
public:
	//==================�萔=======================//.
	const float		ALPHA_MAX = 1.0f;		//���ߒl�ő吔.
	const float		SCALE_MAX = 1.0f;		//�傫���ő�l.
	//const int		FONT_SIZE = 500;			//�t�H���g�̑傫��.

	CFont();
	~CFont();
	//������.
	HRESULT Init(ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContex11,
		const char* str, HFONT hFont, HDC hdc);


	//�����_�����O�p.
	void Render();

	//�ʒu����ݒ�.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}

	//�ʒu����ݒ�.
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}

	//�傫����ݒ�.
	void SetScale(float fScale) {
		m_fScale = fScale;
	}
	float GetScale() {
		return m_fScale;
	}

	//�p�x.
	void SetRotation(D3DXVECTOR3 Rot) {
		m_vRot = Rot;
	}

	//���ߒl��ݒ�.
	void SetAlpha(float Alpha) {
		m_Alpha = Alpha;
	}


private:
	//���.
	void Release();

	//�V�F�[�_�쐬.
	HRESULT InitShader();

	//�t�H���g�̍쐬.
	HRESULT FontCreate(const char* str, HFONT hFont, HDC hdc);

	//���f���쐬.
	HRESULT InitModel();
	//�e�N�X�`���쐬.
	HRESULT CreateTexture(ID3D11ShaderResourceView** pTexture);
	//======================================.
	//	�\����.
	//======================================.
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	//D3DXMATRIX...float�^��4�o�C�g�~�S.
	struct SHADER_CONSTANT_BUFFER
	{
		ALINGN16 D3DMATRIX	 mW;				//���[���h�s��.
		ALINGN16 float		 fViewPortWidth;	//�r���[�|�[�g��.
		ALINGN16 float		 fViewPortHeight;	//�r���[�|�[�g����.
		ALINGN16 D3DXVECTOR4 vColor;			//�A���t�@�l(���߂Ŏg�p����).
		ALINGN16 D3DXVECTOR2 vUV;				//UV���W.
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//���_���W.
		D3DXVECTOR2 Tex;		//�e�N�X�`�����W.
	};

	//�����f���̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;		//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;		//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;			//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;		//�R���X�^���g�o�b�t�@.

	//�����f�����Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;		//���_�o�b�t�@.

	ID3D11SamplerState*		m_pSampleLinear;		//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.
	ID3D11ShaderResourceView*	m_pTexture;			//�e�N�X�`��.

	int						m_AnimCount;			//�J�E���^.
	D3DXVECTOR2				m_UV;					//�e�N�X�`��UV���W.


	D3DXVECTOR3				m_vPos;					//�ʒu.
	float					m_Alpha;				//�A���t�@�l.
	float					m_fScale;				//�傫��.
	D3DXVECTOR3				m_vRot;					//�p�x.
	TEXTMETRIC	TM;
	GLYPHMETRICS GM;
	BYTE* ptr;
};

#endif	//#ifndef CFONT_H.