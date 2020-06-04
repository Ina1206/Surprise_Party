#ifndef _CDX9BASE_H
#define _CDX9BASE_H

#include "..\CCommon.h"

#include "ObjectAlphaBlend\CObjectAlphaBlend.h"
#define ALIGN16 _declspec(align(16))

//ײď��.
struct LIGHT
{
	D3DXVECTOR3	vPos;			//�ʒu.
	D3DXMATRIX	mRot;			//��]�s��.
	float		fIntensity;		//���x(���邳).
	float		m_fLightWidth;	//���̍L��.
	D3DXVECTOR3 vLightColor;	//���C�g�̐F.
	float		fLightPosWidth;	//���C�g�z�u��.
	float		m_fLightMax;	//���C�g�̍ő�l.
};

/***************************************
*	DirectX9Draw���N���X.
***************/
class CDX9Base
	: public CCommon
{
public:
	CDX9Base();
	virtual ~CDX9Base();

	//�ʒu����ݒ�.
	//inline void ��inline�͊֐����̂𒼐ړW�J���邽�ߑ��x���オ��.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}
	//�ʒu�����擾.
	D3DXVECTOR3 GetPosition()
	{
		return m_vPos;
	}
	//��]����ݒ�.
	void SetRotation(const D3DXVECTOR3& vRot) {
		m_vRot = vRot;
	}
	//��]�����擾.
	D3DXVECTOR3 GetRotation() {
		return m_vRot;
	}
	//�g�k����ݒ�.
	void SetScale(float Scale) { m_fScale = Scale; }
	//�g�k�����擾.
	float GetScale() { return m_fScale; }

	//���ߒl��ݒ�.
	void SetAlpha(const float& Alpha) { m_fAlpha = Alpha; }

	//�����ʒu�����炷.
	void SetPrePos(D3DXVECTOR3 vPrePos) { m_vPrePos = vPrePos; }

	void SetUV(const D3DXVECTOR2& vUV) { m_vUV = vUV; }

	void SetAlphaDepth(const bool& flag) { m_pCObjectAlphaBlend->SetAlphaDepth(flag); }

	void SetPreRot(const D3DXVECTOR3& vPreRot) { m_vPreRot = vPreRot; }

protected:
	//======================================.
	//	�\����.
	//======================================.
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct CBUFFER_PER_MESH
	{
		D3DXMATRIX	mW;			//���[���h�s��.
		D3DXMATRIX	mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.
	};
	struct CBUFFER_PER_MATERIAL
	{
		D3DXVECTOR4 vAmbient;	//�A���r�G���g�F(���F).
		D3DXVECTOR4	vDiffuse;	//�f�B�t���[�Y�F(�g�U���ːF).
		D3DXVECTOR4 vSpecular;	//�X�y�L�����F(���ʔ��ːF).
	};
	//�t���[���P�ʂœn�����.
	struct CBUFFER_PER_FRAME
	{
		D3DXVECTOR4			vCamPos;		//�J�����ʒu(���_�ʒu).
		D3DXVECTOR4			vLightPos;		//���C�g����.
		D3DXMATRIX			mLightRot;		//���C�g�p�x.
		D3DXVECTOR4			fIntensity;		//ײċ��x(���邳).
		D3DXVECTOR4			fLightWidth;	//���C�g�̍L��.
		D3DXVECTOR4			vLightColor;	//���C�g�F.
		D3DXVECTOR4			vAlpha;			//�F.
		D3DXVECTOR4			vUV;			//UV.			
		D3DXVECTOR4			vLightPosWidth;	//���C�g�z�u��.
		D3DXVECTOR4			vLightMax;		//���C�g�ő吔.
	};

	HWND								m_hWnd;					//�E�B���h�E�n���h��.
	LPDIRECT3DDEVICE9					m_pDevice9;				//Dx9�f�o�C�X�I�u�W�F�N�g.

	ID3D11Device*						m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*				m_pContext11;			//�f�o�C�X�R���e�L�X�g.
	ID3D11VertexShader*					m_pVertexShader;		//���_�V�F�[�_.
	ID3D11InputLayout*					m_pVertexLayout;		//���_���C�A�E�g.
	ID3D11PixelShader*					m_pPixelShader;			//�s�N�Z���V�F�[�_.
	ID3D11Buffer*						m_pCBufferPerMesh;		//�R���X�^���g�o�b�t�@(���b�V����).
	ID3D11Buffer*						m_pCBufferPerMaterial;	//�R���X�^���g�o�b�t�@(�}�e���A����).
	ID3D11Buffer*						m_pCBufferPerFrame;		//�R���X�^���g�o�b�t�@(�t���[����)

	D3DXVECTOR3							m_vPos;					//�ʒu.
	D3DXVECTOR3							m_vRot;					//�p�x.
	float								m_fScale;				//�傫��.
	D3DXVECTOR3							m_vPrePos;				//�ǂݍ��ݎ��̃I�u�W�F�N�g�̒��S������.
	D3DXVECTOR3							m_vPreRot;				//�p�x.
	float								m_fAlpha;				//���ߒl.

	D3DXVECTOR2							m_vUV;					//UV.

	std::unique_ptr<CObjectAlphaBlend>	m_pCObjectAlphaBlend;	//�I�u�W�F�N�g�A���t�@�u�����h.
	
	bool								m_bSpotLightUseFlag;	//�X�|�b�g���C�g�g�p�t���O.
};

#endif	//#ifndef _CDX9BASE_H.