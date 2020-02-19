#ifndef CDX9MESH_H
#define CDX9MESH_H

#include "..\ObjectAlphaBlend\CObjectAlphaBlend.h"

#define ALIGN16 _declspec(align(16))

const int SHADOW_MAX = 10;

//�X�t�B�A�\����.
struct SPHERE
{
	D3DXVECTOR3 vCenter;	//���S.
	float		fRadius;	//���a.
};
//�o�E���f�B���O�{�b�N�X�\����.
struct BBOX
{
	D3DXVECTOR3 vPosMax;	//�ő咸�_.
	D3DXVECTOR3 vPosMin;	//�ŏ����_.
	D3DXVECTOR3 vAxisX;		//x��.
	D3DXVECTOR3 vAxisY;		//y��.
	D3DXVECTOR3 vAxisZ;		//z��.
	FLOAT		LenghtX;	//X����.
	FLOAT		LenghtY;	//Y����.
	FLOAT		LenghtZ;	//Z����.

	//������.
	BBOX()
		: vPosMax(), vPosMin()
		, vAxisX(1.0f, 0.0f, 0.0f)
		, vAxisY(0.0f, 1.0f, 0.0f)
		, vAxisZ(0.0f, 0.0f, 1.0f)
		, LenghtX(0.0f), LenghtY(0.0f), LenghtZ(0.0f)
	{}
};

//�J�������.
//�����Y����]�̂ݑΉ�.
struct CAMERA
{
	D3DXVECTOR3	vPos;	//�ʒu.
	D3DXVECTOR3 vLook;	//�����ʒu.
	float		fYaw;	//Y����].
	D3DXMATRIX	mRot;	//��]�s��.
};

//ײď��.
struct LIGHT
{
	D3DXVECTOR3	vPos;			//�ʒu.
	D3DXVECTOR3	vDir;			//����.
	D3DXMATRIX	mRot;			//��]�s��.
	float		fIntensity;		//���x(���邳).
	float		m_fLightWidth;	//���̍L��.

};

//���b�V���f�[�^���t�@�C��������o���ׂ�����DirectX9���g�p����.
//�������_�����O(�`��)�́ADirectX11�ōs��.
class CDX9Mesh
	: public CObjectAlphaBlend
{
public:
	CDX9Mesh();		//�R���X�g���N�^.
	~CDX9Mesh();	//�f�X�g���N�^.

	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, const char* fileName);
	//���b�V���ǂݍ���.
	HRESULT LoadXMesh(const char* fileName);
	//����֐�.
	void Release();

	//�V�F�[�_�쐬.
	HRESULT InitShader();

	//�����_�����O�p.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj,
				const D3DXVECTOR3& vCamPos, const LIGHT& stLight);

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
	void SetScale(float Scale)	{ m_fScale = Scale; }
	//�g�k�����擾.
	float GetScale()			{ return m_fScale; }

	//���ߒl��ݒ�.
	void SetAlpha(const float& Alpha) { m_fAlpha = Alpha; }

	//�����ʒu�����炷.
	void SetPrePos(D3DXVECTOR3 vPrePos) { m_vPrePos = vPrePos; }

	//��]�s��쐬.
	void SetRot(const D3DXMATRIX& mRot){
		m_bvRotNotUse = true;
		m_mRot = mRot;
	}

	//��]�p�x���f.
	void SetRotAngleApplication() {
		m_bvRotNotUse = false;
	}

	//���b�V�����擾.
	LPD3DXMESH GetMesh() {
		return m_pMesh;
	}

	SPHERE m_Sphere;			//�X�t�B�A�\����.
	BBOX   m_BBox;				//B�{�b�N�X�\����.


	void SetUV(const D3DXVECTOR2& vUV) { m_vUV = vUV; }

	LPD3DXMESH	m_pMeshForRay;	//���C�ƃ��b�V���p.

private:
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
	struct CBUFFER_PRE_MATERIAL
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
		D3DXVECTOR4			vLightDir;		//ײĕ���.
		D3DXMATRIX			vLightRot;		//���C�g�p�x.
		ALIGN16 float		fIntensity;		//ײċ��x(���邳).
		ALIGN16 float		fLightWidth;	//���C�g�̍L��.
		ALIGN16 float		vAlpha;			//�F.
		ALIGN16 D3DXVECTOR2 vUV;			//UV.			
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//���_���W.
		D3DXVECTOR3 Normal;		//�@��(�A�e�v�Z�ɕK�{).
		D3DXVECTOR2 Tex;		//�e�N�X�`�����W.
	};
	//�}�e���A���\����.
	struct MY_MATERIAL
	{
		D3DXVECTOR4					Ambient;			//�A���r�G���g.
		D3DXVECTOR4					Diffuse;			//�f�B�t���[�Y.
		D3DXVECTOR4					Specular;			//�X�y�L�����[.
		char						szTextureName[128];	//�e�N�X�`���t�@�C����.
		ID3D11ShaderResourceView*	pTexture;			//�e�N�X�`��.
		DWORD						dwNumFace;			//���̃}�e���A���̃|���S����.
		//�R���X�g���N�^.
		MY_MATERIAL()
			:Ambient(),Diffuse(),Specular(), szTextureName()
			,pTexture(nullptr), dwNumFace(0)
		{
		}
		//�f�X�g���N�^.
		~MY_MATERIAL(){
			SAFE_RELEASE(pTexture);
		}
	};


	HWND					m_hWnd;					//�E�B���h�E�n���h��.

	//Dx9.
	LPDIRECT3D9				m_pD3d9;				//Dx9�I�u�W�F�N�g.
	LPDIRECT3DDEVICE9		m_pDevice9;				//Dx9�f�o�C�X�I�u�W�F�N�g.

	//Dx11.
	ID3D11Device*			m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;			//�f�o�C�X�R���e�L�X�g.

	ID3D11VertexShader*		m_pVertexShader;		//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;		//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;			//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pCBufferPerMesh;		//�R���X�^���g�o�b�t�@(���b�V����).
	ID3D11Buffer*			m_pCBufferPerMaterial;	//�R���X�^���g�o�b�t�@(�}�e���A����).
	ID3D11Buffer*			m_pCBufferPerFrame;		//�R���X�^���g�o�b�t�@(�t���[����)

	ID3D11Buffer*			m_pVertexBuffer;		//���_�o�b�t�@.
	ID3D11Buffer**			m_ppIndexBuffer;		//�C���f�b�N�X�o�b�t�@.
	ID3D11SamplerState*		m_pSampleLinear;		//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.

	LPD3DXMESH				m_pMesh;				//���b�V���I�u�W�F�N�g.
	DWORD					m_NumMaterials;			//�}�e���A����.

	MY_MATERIAL*			m_pMaterials;			//�}�e���A���\����.
	DWORD					m_NumAttr;				//������.
	DWORD					m_AttrID[300];			//����ID�@��300�����܂�.

	bool					m_EnableTexture;		//�e�N�X�`������.

	float					m_fScale;				//�g��k���l(x,y,z���{).
	D3DXVECTOR3				m_vRot;					//��]�l(x,y,z).
													//��x = Pitch, y = Yaw, z = Roll.
	D3DXVECTOR3				m_vPos;					//�ʒu(x,y,z).
	D3DXVECTOR3				m_vPrePos;

	int						m_ShadowMax;			//�e�̍ő吔.
	float					m_fAlpha;				//���ߒl.

	D3DXVECTOR2				m_vUV;					//UV.
	bool					m_bvRotNotUse;			//�p�x�g��Ȃ��t���O.
	D3DXMATRIX				m_mRot;					//��]�s��.
	

	//�����_�����O�֐�(�N���X���ł̂ݎg�p).
	void RenderMesh(const D3DXMATRIX& mWorld, const D3DXMATRIX& mView, const D3DXMATRIX& mProj);

};


#endif	//#ifndef CDX9MESH_H