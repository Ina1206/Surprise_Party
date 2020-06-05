#ifndef CDX9MESH_H
#define CDX9MESH_H

#include "..\CDX9Base.h"

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

//���b�V���f�[�^���t�@�C��������o���ׂ�����DirectX9���g�p����.
//�������_�����O(�`��)�́ADirectX11�ōs��.
class CDX9Mesh
	: public CDX9Base
{
public:
	CDX9Mesh();		//�R���X�g���N�^.
	~CDX9Mesh();	//�f�X�g���N�^.

	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, const char* fileName, const bool& bSpotLightHLSL);

	//�����_�����O�p.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj,
				const D3DXVECTOR3& vCamPos, const LIGHT& stLight);
	//����֐�.
	void Release();

	//���b�V�����擾.
	LPD3DXMESH GetMesh() {
		return m_pMesh;
	}

	SPHERE m_Sphere;			//�X�t�B�A�\����.
	BBOX   m_BBox;				//B�{�b�N�X�\����.



	LPD3DXMESH	m_pMeshForRay;	//���C�ƃ��b�V���p.

private:

	//���b�V���ǂݍ���.
	HRESULT LoadXMesh(const char* fileName);

	//�V�F�[�_�쐬.
	HRESULT InitShader();

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


	//Dx9.
	LPDIRECT3D9				m_pD3d9;				//Dx9�I�u�W�F�N�g.

	ID3D11Buffer*			m_pVertexBuffer;		//���_�o�b�t�@.
	ID3D11Buffer**			m_ppIndexBuffer;		//�C���f�b�N�X�o�b�t�@.
	ID3D11SamplerState*		m_pSampleLinear;		//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.

	LPD3DXMESH				m_pMesh;				//���b�V���I�u�W�F�N�g.
	DWORD					m_NumMaterials;			//�}�e���A����.

	MY_MATERIAL*			m_pMaterials;			//�}�e���A���\����.
	DWORD					m_NumAttr;				//������.
	DWORD					m_AttrID[300];			//����ID�@��300�����܂�.

	bool					m_EnableTexture;		//�e�N�X�`������.

	//�����_�����O�֐�(�N���X���ł̂ݎg�p).
	void RenderMesh(const D3DXMATRIX& mWorld, const D3DXMATRIX& mView, const D3DXMATRIX& mProj);

};


#endif	//#ifndef CDX9MESH_H