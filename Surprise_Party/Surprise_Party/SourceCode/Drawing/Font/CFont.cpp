#include "CFont.h"
#include <crtdbg.h>


//�V�F�[�_�[�t�@�C����(�f�B���N�g�����܂�).
const char SHADER_NAME[] = "Data\\Shader\\SpriteUI.hlsl";

//�R���X�g���N�^.
CFont::CFont()
	: m_pVertexShader(nullptr)
	, m_pVertexLayout(nullptr)
	, m_pPixelShader(nullptr)
	, m_pConstantBuffer(nullptr)
	, m_pVertexBuffer(nullptr)
	, m_pSampleLinear(nullptr)
	, m_pTexture(nullptr)
	, m_AnimCount(0)
	, m_UV(0.0f, 0.0f)
	, m_vPos()
	, m_Alpha(ALPHA_MAX)	//0:����,1:���S�s����.
	, m_fScale(SCALE_MAX)
	, m_vRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//�f�X�g���N�^.
CFont::~CFont()
{
	Release();
}

//������.
HRESULT CFont::Init(ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContex11,
	const char* str, HFONT hFont, HDC hdc)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContex11;

	//�u�����h�X�e�[�g.
	if (FAILED(InitBlend(m_pDevice11, m_pContext11)))
	{
		return E_FAIL;
	}

	//�V�F�[�_�쐬.
	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}

	if (FAILED(FontCreate(str, hFont, hdc))) {
		return E_FAIL;
	}
	//�|���S���쐬.
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}
	//�e�N�X�`���쐬.
	if (FAILED(CreateTexture(&m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//���.
void CFont::Release()
{

	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_RELEASE(m_pNoAlphaBlend);

	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
}

//==================================================================.
//	HLSL�t�@�C����ǂݍ��݃V�F�[�_���쐬����.
//	HLSL : High Level Shading Language �̗�.
//==================================================================.
HRESULT CFont::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT	  uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif	//#ifdef _DEBUG.

	//HLSL����o�[�e�b�N�X�V�F�[�_�̃u���u���쐬.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
			nullptr,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
			nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			"VS_Main",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.				//""�̓v���p�e�B�̐ݒ荀�ڂƈꏏ.
			"vs_5_0",			//�V�F�[�_�̃��f�����w�肷�镶����(�v���t�@�C��).
			uCompileFlag,		//�V�F�[�_�R���p�C���t���O.
			0,					//�G�t�F�N�g�R���p�C���t���O(���g�p).
			nullptr,			//�X���b�h�|���v�C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			&pCompiledShader,	//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,			//�G���[�ƌx���ꗗ���i�[���郁�����ւ̃|�C���^.
			nullptr)))			//�߂�l�ւ̃|�C���^(���g�p).
	{
		_ASSERT_EXPR(false, L"hlsl�ǂݍ��ݎ��s");
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//��L�ō쐬�����u���u����u�o�[�e�b�N�X�V�F�[�_�v���쐬.
	if (FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader)))	//(out)�o�[�e�b�N�X�V�F�[�_.
	{
		_ASSERT_EXPR(false, L"�o�[�e�b�N�X�V�F�[�_�쐬���s");
		return E_FAIL;
	}

	//���_�C���v�b�g���C�A�E�g���`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//�ʒu.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI�̃t�H�[�}�b�g(32bit float�^*3).
			0,
			0,								//�f�[�^�̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",						//�e�N�X�`���ʒu.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGI�̃t�H�[�}�b�g(32bit float�^*2).
			0,
			12,								//�f�[�^�̊J�n�ʒu����̃f�[�^��4�o�C�g��3���邩��12���̊J�n�ʒu�͊ԈႦ�Ă͂����Ȃ�.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}

	};
	//���_�C���v�b�g���C�A�E�g�̔z��v�f�����Z�o.
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//���_�C���v�b�g���C�A�E�g���쐬.
	if (FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout)))	//(out)���_�C���v�b�g���C�A�E�g.
	{
		_ASSERT_EXPR(false, L"���_�C���v�b�g���C�A�E�g�쐬���s");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//HLSL����s�N�Z���V�F�[�_�̃u���u���쐬.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
			nullptr,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
			nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			"PS_Main",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
			"ps_5_0",			//�V�F�[�_�̃��f�����w�肷�镶����(�v���t�@�C��).
			uCompileFlag,		//�V�F�[�_�R���p�C���t���O.
			0,					//�G�t�F�N�g�R���p�C���t���O(���g�p).
			nullptr,			//�X���b�h�|���v�C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			&pCompiledShader,	//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,			//�G���[�ƌx���ꗗ���i�[���郁�����ւ̃|�C���^.
			nullptr)))			//�߂�l�ւ̃|�C���^(���g�p).
	{
		_ASSERT_EXPR(false, L"hlsl�ǂݍ��ݎ��s");
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//��L�ō쐬�����u���u����u�s�N�Z���V�F�[�_�v���쐬.
	if (FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader)))	//(out)�s�N�Z���V�F�[�_.
	{
		_ASSERT_EXPR(false, L"�s�N�Z���V�F�[�_�쐬���s");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//�R���X�^���g(�萔)�o�b�t�@�쐬.
	//�V�F�[�_�ɓ���̐��l�𑗂�o�b�t�@.
	//�����ł͕ϊ��s��n���p.
	//�V�F�[�_�� World, View, Projection �s���n��.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�R���X�^���g�o�b�t�@���w��.
	cb.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);	//�R���X�^���g�o�b�t�@�̃T�C�Y.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;			//�������݂ŃA�N�Z�X.
	cb.MiscFlags = 0;								//���̑��̃t���O(���g�p).
	cb.StructureByteStride = 0;								//�\���̂̃T�C�Y().
	cb.Usage = D3D11_USAGE_DYNAMIC;				//�g�p���@�F���ڏ�������.

	//�R���X�^���g�o�b�t�@�̍쐬.
	if (FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			nullptr,
			&m_pConstantBuffer)))
	{
		_ASSERT_EXPR(false, L"�R���X�^���g�o�b�t�@�쐬���s");
		return E_FAIL;
	}

	return S_OK;
}

//�t�H���g�̍쐬.
HRESULT CFont::FontCreate(const char* str, HFONT hFont, HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	
	UINT code = 0;
#if _UNICODE
	// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
	code = (UINT)*c;
#else
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
	if (IsDBCSLeadByte(*str))
		code = (BYTE)str[0] << 8 | (BYTE)str[1];
	else
		code = str[0];
#endif

	GetTextMetrics(hdc, &TM);
	const MAT2 Mat = { {0,1},{0,0},{0,0},{0,1} };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, nullptr, &Mat);
	ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
	SelectObject(hdc, oldFont);
	DeleteObject(oldFont);
	
	return S_OK;
}


//���f���쐬.
HRESULT CFont::InitModel()
{
	float w = 1.0f;						//�\���X�v���C�g��.
	float h = 1.0f;						//�\���X�v���C�g����.
	float u = 1.0f;	//1�R�}������̕�.
	float v = 1.0f;	//1�R�}������̍���.

	//�|��(�l�p�`)�̒��_���쐬.
	VERTEX vertices[] =
	{
		//���_���W(x,y,z).				UV���W(u,v).
		D3DXVECTOR3(0.0f,    h, 0.0f),	D3DXVECTOR2(0.0f,    v),//���_�P(����).
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f),//���_�Q(����).
		D3DXVECTOR3(w,    h, 0.0f),	D3DXVECTOR2(u,    v),//���_�R(�E��).
		D3DXVECTOR3(w, 0.0f, 0.0f),	D3DXVECTOR2(u, 0.0f)	//���_�S(�E��).
	};
	//�ő�v�f�����Z�o����.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//�o�b�t�@�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;				//�g�p���@(�f�t�H���g).
	bd.ByteWidth = sizeof(VERTEX) * uVerMax;	//���_�̃T�C�Y.
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���_�o�b�t�@�Ƃ��Ĉ���.
	bd.CPUAccessFlags = 0;						//CPU����̓A�N�Z�X���Ȃ�.
	bd.MiscFlags = 0;							//���̑��̃t���O(���g�p).
	bd.StructureByteStride = 0;					//�\���̂̃T�C�Y(���g�p).

	//�T�u���\�[�X�f�[�^�\����.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;				//�|���̒��_���Z�b�g.

	//���_�o�b�t�@�̍쐬.
	if (FAILED(m_pDevice11->CreateBuffer(
		&bd, &InitData, &m_pVertexBuffer)))
	{
		_ASSERT_EXPR(false, L"���_�o�b�t�@�쐬���s");
		return E_FAIL;
	}

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(VERTEX);	//�f�[�^�Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1,
		&m_pVertexBuffer, &stride, &offset);

	//�e�N�X�`���p�̃T���v���\����.
	D3D11_SAMPLER_DESC	samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	//���j�A�t�B���^(���`���).
							//POINT:���������e��.
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//���b�s���O���[�h(WRAP:�J��Ԃ�).
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//MIRROR: ���]�J��Ԃ�.
	//CLAMP : �[�̖͗l�������L�΂�.
	//BORDER: �ʓr���E�F�����߂�.
	//�T���v���쐬.
	if (FAILED(m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear)))					//(out)�T���v��.
	{
		_ASSERT_EXPR(false, L"�T���v���쐬���s");
		return E_FAIL;
	}


	return S_OK;
}

//�e�N�X�`���쐬.
HRESULT CFont::CreateTexture(ID3D11ShaderResourceView** pTexture)
{
	//�e�N�X�`���쐬.
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = GM.gmCellIncX;
	desc.Height = TM.tmHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D* tex2D;
	if (FAILED(m_pDevice11->CreateTexture2D(&desc, 0, &tex2D)))
	{
		_ASSERT_EXPR(nullptr, L"�e�N�X�`���쐬���s");
		return E_FAIL;
	}

	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	if (FAILED(m_pContext11->Map( tex2D, 0,	D3D11_MAP_WRITE_DISCARD,
		0, &hMappedResource))) {
		_ASSERT_EXPR(nullptr, L"�e�N�X�`���}�b�v���s");
		return E_FAIL;
	}

	BYTE* pBits = (BYTE*)hMappedResource.pData;

	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	memset(pBits, 0, hMappedResource.RowPitch * TM.tmHeight);
	for (y = iOfs_y; y < iOfs_y + iBmp_h; y++) {
		for (x = iOfs_x; x < iOfs_x + iBmp_w; x++) {
			Alpha = (255 * ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);
			
			memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &Color, sizeof(DWORD));
		}
	}
	m_pContext11->Unmap(tex2D, 0);

	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	m_pDevice11->CreateShaderResourceView(tex2D, &srvDesc, pTexture);

	//�������.
	SAFE_RELEASE(tex2D);
	SAFE_DELETE_ARRAY(ptr);

	return S_OK;
}


//�����_�����O�p.
void CFont::Render()
{
	//���[���h�s��.
	D3DXMATRIX mWorld, mScale, mRot;
	D3DXMATRIX mYaw, mPitch, mRoll;

	//Y����]�s��쐬.
	D3DXMatrixRotationY(&mYaw, m_vRot.y);
	//X����]�s��쐬.
	D3DXMatrixRotationX(&mPitch, m_vRot.x);
	//Z����]�s��쐬.
	D3DXMatrixRotationZ(&mRoll, m_vRot.z);

	//���s�ړ�.
	D3DXMatrixTranslation(&mWorld, m_vPos.x, m_vPos.y, m_vPos.z);

	//�g��k���s��쐬.
	D3DXMatrixScaling(
		&mScale,						//(out)�v�Z����.
		m_fScale, m_fScale, m_fScale);	//x,y,z���ꂼ��̊g�k�l.

	//��]�s����쐬.
	mRot = mYaw * mPitch * mRoll;

	mWorld = mScale * mRot * mWorld;

	//�g�p����V�F�[�_�̓o�^.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);

	//�V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
	D3D11_MAPPED_SUBRESOURCE	pData;
	SHADER_CONSTANT_BUFFER		cb;		//�R���X�^���g�o�b�t�@.
	//�o�b�t�@���̃f�[�^�̏��������J�n����map.
	if (SUCCEEDED(
		m_pContext11->Map(m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�s���n��.
		D3DXMATRIX m = mWorld;
		D3DXMatrixTranspose(&m, &m);			//�s���]�u����.
		cb.mW = m;

		//�r���[�|�[�g��,������n��.
		cb.fViewPortWidth = WND_W;
		cb.fViewPortHeight = WND_H;

		//�A���t�@�l��n��.
		//�t�F�[�h�C���t�F�[�h�A�E�g�Ŏg�����Ƃ��ł���.
		//�u���C�N�|�C���g�̎��ϐ��̐��l��ύX���邱�Ƃ��ł���.
		D3DXVECTOR4 vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_Alpha);
		cb.vColor = vColor;


		//UV���W.
		//1�R�}������̊����Ƀp�^�[���ԍ��������Ĉʒu��ݒ肷��.
		//�A���J�[�Ƃ�����l��ݒ肷��Ɖ�]�Ƃ����^�񒆂𒆐S�ɓ�����.
		cb.vUV.x = 0.0f;
		cb.vUV.y = 0.0f;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�����H.
	//registar��b2��2�ƘA�����Ă���.
	m_pContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(VERTEX);	//�f�[�^�̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//���_�C���v�b�g���C�A�E�g���Z�b�g.
	m_pContext11->IASetInputLayout(m_pVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g.
	m_pContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�e�N�X�`���[���V�F�[�_�ɓn��.
	m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pContext11->PSSetShaderResources(0, 1, &m_pTexture);

	//�A���t�@�u�����h�L���ɂ���.
	SetBlend(true);

	//�v���~�e�B�u�������_�����O.
	m_pContext11->Draw(4, 0);	//�|��(���_�S��).

	//�A���t�@�u�����h�����ɂ���.
	SetBlend(false);
}

