#include "CResourceManager.h"
#include "..\..\FileLoad\FileResource\CFileResource.h"

/*******************************************
*		�ǂݍ��݊Ǘ��N���X.
************/
CResourceManager::CResourceManager()
	: m_pCSprite			(nullptr)
	, m_pCSpriteUI			(nullptr)
	, m_pCStaticMesh		(nullptr)
	, m_pCSkinMesh			(nullptr)
	, m_pCEffect			(nullptr)
	, m_pCFont				(nullptr)
	, m_vSpriteFileName		()
	, m_vSpriteUIFileNmae	()
	, m_vStaticMeshFileName	()
	, m_vSkinMeshFileName	()
	, m_bUseSpotLightFlag	()
	, m_pstSpriteState		(nullptr)
	, m_pstSpriteUIState	(nullptr)
{
	m_pstSpriteState = new SPRITE_STATE[static_cast<int>(enSprite::Max)]();
	m_pstSpriteUIState = new SPRITE_STATE[static_cast<int>(enSpriteUI::Max)]();
}

CResourceManager::~CResourceManager()
{
}

//==========================================.
//		�ǂݍ��ݏ����֐�.
//==========================================.
HRESULT CResourceManager::Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	//�X�v���C�g�t�@�C�����ݒ菈���֐�.
	SpriteFileNameSetting();
	//�X�v���C�gUI�t�@�C�����ݒ菈���֐�.
	SpriteUIFileNameSetting();
	//�X�^�e�B�b�N���b�V���̃t�@�C�����ݒ菈���֐�.
	StaticMeshFileNmaeSetting();
	//�X�L�����b�V���̃t�@�C�����ݒ菈���֐�.
	SkinMeshFileNameSetting();

	//�X�v���C�g���\���̐ݒ菈���֐�.
	SpriteStateSetting();
	//�X�v���C�gUI���\���̐ݒ菈���֐�.
	SpriteUIStateSetting();

	//�X�v���C�g�N���X.
	m_pCSprite.reset(new CSprite_Resource<CSprite, enSprite>());
	//�����l�ݒ菈��.
	m_pCSprite->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCSprite->Init(static_cast<int>(enSprite::Max));
	//�X�v���C�g���\���̐ݒ�.
	m_pCSprite->SetSpriteState(m_pstSpriteState);
	//�ǂݍ��ݏ���.
	m_pCSprite->Load(m_vSpriteFileName);

	//�X�v���C�gUI�N���X.
	m_pCSpriteUI.reset(new CSprite_Resource<CSpriteUI, enSpriteUI>());
	//�����l�ݒ菈��.
	m_pCSpriteUI->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCSpriteUI->Init(static_cast<int>(enSpriteUI::Max));
	//�X�v���C�gUI���\���̐ݒ�.
	m_pCSpriteUI->SetSpriteState(m_pstSpriteUIState);
	//�ǂݍ��ݏ���.
	m_pCSpriteUI->Load(m_vSpriteUIFileNmae);

	//�X�^�e�B�b�N���b�V��.
	m_pCStaticMesh.reset(new CObjectResource<CDX9Mesh, enStaticMeshType>());
	//�����l�ݒ�.
	m_pCStaticMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCStaticMesh->Init(static_cast<int>(enStaticMeshType::Max));
	//�ǂݍ��ݏ���.
	m_pCStaticMesh->Load(m_tStaticMesh);
	//m_pCStaticMesh->Load(m_vStaticMeshFileName);
	//�����蔻��p�X�t�B�A�쐬�����֐�.
	if (FAILED(InitSphere())) {
		_ASSERT_EXPR(false, L"�����蔻��p�X�t�B�A�쐬���s");
		return E_FAIL;
	}

	//�X�L�����b�V��.
	m_pCSkinMesh.reset(new CObjectResource<CDX9SkinMesh, enSkinMeshType>());
	//�����l�ݒ菈��.
	m_pCSkinMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCSkinMesh->Init(static_cast<int>(enSkinMeshType::Max));
	//�ǂݍ��ݏ���.
	m_pCSkinMesh->Load(m_tSkinMesh);

	//�G�t�F�N�g.
	m_pCEffect.reset(new CResourceEffect());
	m_pCEffect->Init(hWnd, pDevice11, pContext11);
	m_pCEffect->LoadEffect();

	//�t�H���g.
	m_pCFont.reset(new CFontResource());
	//�����������֐�.
	m_pCFont->Init(pDevice11, pContext11);

	//�f�o�b�O�e�L�X�g�����������֐�.
	InitDebugText(pContext11);

	return S_OK;
}

//=======================================.
//		��������֐�.
//=======================================.
HRESULT CResourceManager::Release()
{
	//����Ăяo�������֐�.
	m_pCSkinMesh->ReleaseCalling();		//�X�L�����b�V��.
	m_pCStaticMesh->ReleaseCalling();	//�X�^�e�B�b�N���b�V��.
	m_pCSpriteUI->ReleaseCalling();		//�X�v���C�gUI.
	m_pCSprite->ReleaseCalling();		//�X�v���C�g.

	SAFE_DELETE_ARRAY(m_pstSpriteUIState);
	SAFE_DELETE_ARRAY(m_pstSpriteState);

	return S_OK;
}

//==================================================.
//	�X�^�e�B�b�N���b�V���̃t�@�C�����ݒ菈���֐�.
//==================================================.
void CResourceManager::StaticMeshFileNmaeSetting()
{
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Wall\\Wall.x",				true));	//��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Floor\\Flor.X",				true));	//��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Painting\\e.X",				true));	//�G��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\BookShelf\\BookShelf.x",		true));	//�{�I.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\UpDownFloor\\UpDownFloor.X", true));	//�I�u�W�F�N�g�ړ��X�C�b�`.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Switch\\Switch.X",			true));	//������X�C�b�`.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Ghost\\gost_a.X",			true));	//�X�C�b�`������������.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Phone\\phone.X",				false));//�g��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\HitSphere\\Sphere.x",		true));	//�����蔻��p�X�t�B�A.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Table\\Round table.X",		true));	//��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\VaseFlowar\\vase_flower.X",	true));	//�ԕr.
}

//=================================================.
//	�X�L�����b�V���̃t�@�C�����ݒ菈���֐�.
//=================================================.
void CResourceManager::SkinMeshFileNameSetting()
{
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\People\\Sayaka\\Sayaka_s.X",		true));	//���̎q.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\People\\Towa\\Towa_s.X",			true));	//�j�̎q.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\Ghost\\GhostB\\GhostB_s.X",		true));	//����邨����.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\Ghost\\BigGhost\\BigGhost_s.X",	true));	//�傫��������.
}

//=================================================.
//	�X�v���C�g�̃t�@�C�����ݒ菈���֐�.
//=================================================.
void CResourceManager::SpriteFileNameSetting()
{
	//�t�@�C���ǂݍ��݃N���X.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//�t�@�C���ԍ�.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::Sprite);

	//�t�@�C����.
	for (int sprite = 0; sprite < m_pCFileResource->GetSpriteMax(FILE_NUM); sprite++) {
		m_vSpriteFileName.push_back(m_pCFileResource->GetFileName(FILE_NUM, sprite));
	}
}

//=================================================.
//	�X�v���C�gUI�̃t�@�C�����ݒ菈���֐�.
//=================================================.
void CResourceManager::SpriteUIFileNameSetting()
{
	//�t�@�C���ǂݍ��݃N���X.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//�t�@�C���ԍ�.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::SpriteUI);

	//�t�@�C����.
	for (int UI = 0; UI < m_pCFileResource->GetSpriteMax(FILE_NUM); UI++) {
		m_vSpriteUIFileNmae.push_back(m_pCFileResource->GetFileName(FILE_NUM, UI));
	}

}

//=================================================.
//	�X�v���C�g���\���̐ݒ菈���֐�.
//=================================================.
void CResourceManager::SpriteStateSetting()
{

	//�t�@�C���ǂݍ��݃N���X.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//�t�@�C���ԍ�.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::Sprite);
	
	//���ꂼ��̐��l��ݒ�.
	for (int sprite = 0; sprite < m_pCFileResource->GetSpriteMax(FILE_NUM); sprite++) {
		m_pstSpriteState[sprite].Base.w		= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::OriginalSize_W));
		m_pstSpriteState[sprite].Base.h		= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::OriginalSize_H));
		m_pstSpriteState[sprite].Stride.w	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::BreakSize_W));
		m_pstSpriteState[sprite].Stride.h	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::BreakSize_H));
		m_pstSpriteState[sprite].Frame.w	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::BreakCnt_W));
		m_pstSpriteState[sprite].Frame.h	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::BreakCnt_H));
		m_pstSpriteState[sprite].Disp.w		= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::Disp_W));
		m_pstSpriteState[sprite].Disp.h		= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, sprite, static_cast<int>(CFileResource::enSpriteInformType::Disp_H));
	}
}

//================================================.
//	�X�v���C�gUI���\���̐ݒ菈���֐�.
//================================================.
void CResourceManager::SpriteUIStateSetting()
{
	//�t�@�C���ǂݍ��݃N���X.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//�t�@�C���ԍ�.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::SpriteUI);
	
	//���ꂼ��̐��l��ݒ�.
	for (int UI = 0; UI < m_pCFileResource->GetSpriteMax(FILE_NUM); UI++) {
		m_pstSpriteUIState[UI].Base.w	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::OriginalSize_W));
		m_pstSpriteUIState[UI].Base.h	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::OriginalSize_H));
		m_pstSpriteUIState[UI].Stride.w	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::BreakSize_W));
		m_pstSpriteUIState[UI].Stride.h	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::BreakSize_H));
		m_pstSpriteUIState[UI].Frame.w	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::BreakCnt_W));
		m_pstSpriteUIState[UI].Frame.h	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::BreakCnt_H));
		m_pstSpriteUIState[UI].Disp.w	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::Disp_W));
		m_pstSpriteUIState[UI].Disp.h	= m_pCFileResource->GetSpriteLoadNum(FILE_NUM, UI, static_cast<int>(CFileResource::enSpriteInformType::Disp_H));
	}
}

//============================================.
//		�����蔻��p�X�t�B�A�쐬�����֐�.
//============================================.
HRESULT CResourceManager::InitSphere()
{
	//���b�V���ԍ�.
	const int	MeshNo = static_cast<int>(enStaticMeshType::HitSphere);
	//�X�t�B�A���b�V��.
	CDX9Mesh*	m_pCHitSphere = m_pCStaticMesh->GetMeshObject(enStaticMeshType::HitSphere);

	LPDIRECT3DVERTEXBUFFER9 pVB			= nullptr;		//���_�o�b�t�@.
	void*					pVertices	= nullptr;		//���_.
	D3DXVECTOR3				vCenter;					//���S.
	float					fRadius;					//���a.

	//���_�o�b�t�@���擾.
	if (FAILED(m_pCHitSphere->GetMesh()->GetVertexBuffer(&pVB))){
		return E_FAIL;
	}

	//���b�V���̒��_�o�b�t�@�����b�N����.
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0))) {
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//���b�V���̊O�ډ~�ƒ��S�̔��a���v�Z����.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),						
		m_pCHitSphere->GetMesh()->GetNumVertices(),					//���_�̐�.
		D3DXGetFVFVertexSize(m_pCHitSphere->GetMesh()->GetFVF()),	//���_���.
		&vCenter,													//(out)���S���W.			
		&fRadius);													//(out)���a.

	//�A�����b�N.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//���S�Ɣ��a���\���̂ɐݒ�.
	m_pCHitSphere->m_Sphere.vCenter = vCenter;
	m_pCHitSphere->m_Sphere.fRadius = fRadius;

	return S_OK;
}

//===========================================.
//		�f�o�b�O�e�L�X�g�����������֐�.
//===========================================.
void CResourceManager::InitDebugText(ID3D11DeviceContext* pContext11)
{
	m_pCDebugText = std::make_unique<CDebugText>();

	//�F.
	const D3DXVECTOR4 vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//�����������֐�.
	if (FAILED(m_pCDebugText->Init(pContext11, WND_W, WND_H, 2.0f, vColor))) {
		return;
	}
}