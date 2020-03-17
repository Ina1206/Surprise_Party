#ifndef CSPRITE_H
#define CSPRITE_H
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )
#include "..\..\CCommon.h"
#include "..\..\Resource\SpriteResource\SpriteResourceInfo.h"
#define ALINGN16 _declspec(align(16))


/********************************************
*	�X�v���C�g�N���X.
**/
class CSprite
	: public CCommon
{
public:
	CSprite();	//�R���X�g���N�^.
	~CSprite();	//�f�X�g���N�^.

	//===================�萔=========================//.
	const D3DXVECTOR3	STANDERD_SCALE	= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//�����̑傫��.
	const float			ALPHA_MAX		= 1.0f;

	//	//�������\����(float�^).
	//struct WHSIZE_FLOAT
	//{
	//	float w;
	//	float h;
	//	float z;

	//	WHSIZE_FLOAT()
	//		: w(0.0f)
	//		, h(0.0f)
	//		, z(0.0f)
	//	{}
	//};

	////���ײč\����.
	//struct SPRITE_STATE
	//{
	//	WHSIZE_FLOAT	Disp;	//�\��������.
	//	WHSIZE_FLOAT	Base;	//���摜������.
	//	WHSIZE_FLOAT	Stride;	//�P�R�}������̕�����.
	//};


	//������.
	HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContex11, const char* fileName, SPRITE_STATE* pSs);

	//���.
	void Release();

	//�V�F�[�_�쐬.
	HRESULT InitShader();

	//���f���쐬.
	HRESULT InitModel(const char* fileName);

	//�����_�����O�p.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCamPos);

	//�ʒu����ݒ�.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}

	//�傫����ݒ�.
	void SetScale(D3DXVECTOR3 Scale) {
		m_vScale = Scale;
	}

	//�p�x.
	void SetRotation(D3DXVECTOR3 Rot) {
		m_vRot = Rot;
	}
	//�F�ݒ�.
	void SetColor(const D3DXVECTOR3& vColor) {
		m_vColor = vColor;
	}
	//���ߒl��ݒ�.
	void SetAlpha(float Alpha) {
		m_fAlpha = Alpha;
	}
	//CancelRotation�̃t���O�̐ݒ�.
	void SetCancelRotationFlag(bool flag) {
		m_bCancelRotation = flag;
	}

	void SetPatternNo(const D3DXVECTOR2& point) { m_vPatternNo = point; }

private:
	//======================================.
	//	�\����.
	//======================================.
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX				mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.
		D3DXVECTOR4				vColor;		//�J���[(RGBA�̌^�ɍ��킹��).
		D3DXVECTOR4				vUV;		//UV���W(x,y�̂ݎg�p).
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
	D3DXVECTOR3				m_vScale;				//�傫��.
	D3DXVECTOR3				m_vRot;					//�p�x.
	D3DXVECTOR3				m_vColor;				//�F.
	float					m_fAlpha;				//���ߒl.
	bool					m_bCancelRotation;		//CancelRotation�����邩�ǂ����̃t���O.

	SPRITE_STATE	m_SState;	//���ײď��.
	D3DXVECTOR2		m_vPatternNo;
};

#endif//#ifndef CSPRITE_H