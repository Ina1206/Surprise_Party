#include "CResourceManager.h"
#include "..\..\FileLoad\FileResource\CFileResource.h"

/*******************************************
*		読み込み管理クラス.
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
//		読み込み処理関数.
//==========================================.
HRESULT CResourceManager::Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	//スプライトファイル名設定処理関数.
	SpriteFileNameSetting();
	//スプライトUIファイル名設定処理関数.
	SpriteUIFileNameSetting();
	//スタティックメッシュのファイル名設定処理関数.
	StaticMeshFileNmaeSetting();
	//スキンメッシュのファイル名設定処理関数.
	SkinMeshFileNameSetting();

	//スプライト情報構造体設定処理関数.
	SpriteStateSetting();
	//スプライトUI情報構造体設定処理関数.
	SpriteUIStateSetting();

	//スプライトクラス.
	m_pCSprite.reset(new CSprite_Resource<CSprite, enSprite>());
	//初期値設定処理.
	m_pCSprite->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCSprite->Init(static_cast<int>(enSprite::Max));
	//スプライト情報構造体設定.
	m_pCSprite->SetSpriteState(m_pstSpriteState);
	//読み込み処理.
	m_pCSprite->Load(m_vSpriteFileName);

	//スプライトUIクラス.
	m_pCSpriteUI.reset(new CSprite_Resource<CSpriteUI, enSpriteUI>());
	//初期値設定処理.
	m_pCSpriteUI->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCSpriteUI->Init(static_cast<int>(enSpriteUI::Max));
	//スプライトUI情報構造体設定.
	m_pCSpriteUI->SetSpriteState(m_pstSpriteUIState);
	//読み込み処理.
	m_pCSpriteUI->Load(m_vSpriteUIFileNmae);

	//スタティックメッシュ.
	m_pCStaticMesh.reset(new CObjectResource<CDX9Mesh, enStaticMeshType>());
	//初期値設定.
	m_pCStaticMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCStaticMesh->Init(static_cast<int>(enStaticMeshType::Max));
	//読み込み処理.
	m_pCStaticMesh->Load(m_tStaticMesh);
	//m_pCStaticMesh->Load(m_vStaticMeshFileName);
	//当たり判定用スフィア作成処理関数.
	if (FAILED(InitSphere())) {
		_ASSERT_EXPR(false, L"当たり判定用スフィア作成失敗");
		return E_FAIL;
	}

	//スキンメッシュ.
	m_pCSkinMesh.reset(new CObjectResource<CDX9SkinMesh, enSkinMeshType>());
	//初期値設定処理.
	m_pCSkinMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCSkinMesh->Init(static_cast<int>(enSkinMeshType::Max));
	//読み込み処理.
	m_pCSkinMesh->Load(m_tSkinMesh);

	//エフェクト.
	m_pCEffect.reset(new CResourceEffect());
	m_pCEffect->Init(hWnd, pDevice11, pContext11);
	m_pCEffect->LoadEffect();

	//フォント.
	m_pCFont.reset(new CFontResource());
	//初期化処理関数.
	m_pCFont->Init(pDevice11, pContext11);

	//デバッグテキスト初期化処理関数.
	InitDebugText(pContext11);

	return S_OK;
}

//=======================================.
//		解放処理関数.
//=======================================.
HRESULT CResourceManager::Release()
{
	//解放呼び出し処理関数.
	m_pCSkinMesh->ReleaseCalling();		//スキンメッシュ.
	m_pCStaticMesh->ReleaseCalling();	//スタティックメッシュ.
	m_pCSpriteUI->ReleaseCalling();		//スプライトUI.
	m_pCSprite->ReleaseCalling();		//スプライト.

	SAFE_DELETE_ARRAY(m_pstSpriteUIState);
	SAFE_DELETE_ARRAY(m_pstSpriteState);

	return S_OK;
}

//==================================================.
//	スタティックメッシュのファイル名設定処理関数.
//==================================================.
void CResourceManager::StaticMeshFileNmaeSetting()
{
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Wall\\Wall.x",				true));	//壁.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Floor\\Flor.X",				true));	//床.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Painting\\e.X",				true));	//絵画.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\BookShelf\\BookShelf.x",		true));	//本棚.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\UpDownFloor\\UpDownFloor.X", true));	//オブジェクト移動スイッチ.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Switch\\Switch.X",			true));	//音が鳴るスイッチ.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Ghost\\gost_a.X",			true));	//スイッチを押すお化け.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Phone\\phone.X",				false));//携帯.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\HitSphere\\Sphere.x",		true));	//当たり判定用スフィア.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Table\\Round table.X",		true));	//机.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\VaseFlowar\\vase_flower.X",	true));	//花瓶.
}

//=================================================.
//	スキンメッシュのファイル名設定処理関数.
//=================================================.
void CResourceManager::SkinMeshFileNameSetting()
{
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\People\\Sayaka\\Sayaka_s.X",		true));	//女の子.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\People\\Towa\\Towa_s.X",			true));	//男の子.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\Ghost\\GhostB\\GhostB_s.X",		true));	//現れるお化け.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\Ghost\\BigGhost\\BigGhost_s.X",	true));	//大きいお化け.
}

//=================================================.
//	スプライトのファイル名設定処理関数.
//=================================================.
void CResourceManager::SpriteFileNameSetting()
{
	//ファイル読み込みクラス.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//ファイル番号.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::Sprite);

	//ファイル名.
	for (int sprite = 0; sprite < m_pCFileResource->GetSpriteMax(FILE_NUM); sprite++) {
		m_vSpriteFileName.push_back(m_pCFileResource->GetFileName(FILE_NUM, sprite));
	}
}

//=================================================.
//	スプライトUIのファイル名設定処理関数.
//=================================================.
void CResourceManager::SpriteUIFileNameSetting()
{
	//ファイル読み込みクラス.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//ファイル番号.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::SpriteUI);

	//ファイル名.
	for (int UI = 0; UI < m_pCFileResource->GetSpriteMax(FILE_NUM); UI++) {
		m_vSpriteUIFileNmae.push_back(m_pCFileResource->GetFileName(FILE_NUM, UI));
	}

}

//=================================================.
//	スプライト情報構造体設定処理関数.
//=================================================.
void CResourceManager::SpriteStateSetting()
{

	//ファイル読み込みクラス.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//ファイル番号.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::Sprite);
	
	//それぞれの数値を設定.
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
//	スプライトUI情報構造体設定処理関数.
//================================================.
void CResourceManager::SpriteUIStateSetting()
{
	//ファイル読み込みクラス.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//ファイル番号.
	const int FILE_NUM = static_cast<int>(CFileResource::enSpriteInfo::SpriteUI);
	
	//それぞれの数値を設定.
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
//		当たり判定用スフィア作成処理関数.
//============================================.
HRESULT CResourceManager::InitSphere()
{
	//メッシュ番号.
	const int	MeshNo = static_cast<int>(enStaticMeshType::HitSphere);
	//スフィアメッシュ.
	CDX9Mesh*	m_pCHitSphere = m_pCStaticMesh->GetMeshObject(enStaticMeshType::HitSphere);

	LPDIRECT3DVERTEXBUFFER9 pVB			= nullptr;		//頂点バッファ.
	void*					pVertices	= nullptr;		//頂点.
	D3DXVECTOR3				vCenter;					//中心.
	float					fRadius;					//半径.

	//頂点バッファを取得.
	if (FAILED(m_pCHitSphere->GetMesh()->GetVertexBuffer(&pVB))){
		return E_FAIL;
	}

	//メッシュの頂点バッファをロックする.
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0))) {
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//メッシュの外接円と中心の半径を計算する.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),						
		m_pCHitSphere->GetMesh()->GetNumVertices(),					//頂点の数.
		D3DXGetFVFVertexSize(m_pCHitSphere->GetMesh()->GetFVF()),	//頂点情報.
		&vCenter,													//(out)中心座標.			
		&fRadius);													//(out)半径.

	//アンロック.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//中心と半径を構造体に設定.
	m_pCHitSphere->m_Sphere.vCenter = vCenter;
	m_pCHitSphere->m_Sphere.fRadius = fRadius;

	return S_OK;
}

//===========================================.
//		デバッグテキスト初期化処理関数.
//===========================================.
void CResourceManager::InitDebugText(ID3D11DeviceContext* pContext11)
{
	m_pCDebugText = std::make_unique<CDebugText>();

	//色.
	const D3DXVECTOR4 vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//初期化処理関数.
	if (FAILED(m_pCDebugText->Init(pContext11, WND_W, WND_H, 2.0f, vColor))) {
		return;
	}
}