#ifndef CRESOURCE_MANAGER_H
#define CRESOURCE_MANAGER_H

#include "SpriteResource/CSpriteResource.h"
#include "ObjectResource/CObjectResource.h"
#include "EffectResource/CResourceEffect.h"
#include "FontResource/CFontResource.h"

/*******************************************
*		読み込み管理クラス.
************/
class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	//=======================関数========================//.
	HRESULT Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//読み込み処理関数.
	HRESULT Release();																								//解放処理関数.

	//=================情報取得処理関数==================//.	
	CSprite*		GetSprite(enSprite enSpriteType) { return m_pCSprite->GetSprite(enSpriteType); }						//スプライトクラス.
	CSpriteUI*		GetSpriteUI(enSpriteUI enSpriteUIType) { return m_pCSpriteUI->GetSprite(enSpriteUIType); }				//スプライトUIクラス.
	CDX9Mesh*		GetStaticMesh(enStaticMeshType enStaticMesh) { return m_pCStaticMesh->GetMeshObject(enStaticMesh); }	//スタティックメッシュクラス.
	CDX9SkinMesh*	GetSkinMesh(enSkinMeshType enSkinMesh) { return m_pCSkinMesh->GetMeshObject(enSkinMesh); }				//スキンメッシュクラス.
	CEffect*		GetEffect(CResourceEffect::enEffect enEffect) { return m_pCEffect->GetEffect(enEffect); }
	CFontResource*	GetFont() { return m_pCFont.get(); }
	SPRITE_STATE	GetSpriteUIState(const enSpriteUI& enSpriteUIType) { return m_pstSpriteUIState[static_cast<int>(enSpriteUIType)]; }

	//===================シングルトン====================//.
	static CResourceManager* GetResourceManagerInstance()
	{
		static CResourceManager s_Instance;
		return &s_Instance;
	}

private:
	//=====================関数===========================//.
	void	StaticMeshFileNmaeSetting();					//スタティックメッシュのファイル名設定処理関数.
	void	SkinMeshFileNameSetting();						//スキンメッシュのファイル名設定処理関数.
	void	SpriteFileNameSetting();						//スプライトファイル名設定処理関数.
	void	SpriteUIFileNameSetting();						//スプライトUIファイル名設定処理関数.
	void	SpriteStateSetting();							//スプライト情報構造体設定処理関数.
	void	SpriteUIStateSetting();							//スプライトUI情報構造体設定処理関数.
	HRESULT InitSphere();									//当たり判定用スフィア作成処理関数.

	//=====================変数===========================//.
	std::unique_ptr<CSprite_Resource<CSprite, enSprite>>			m_pCSprite;				//スプライトクラス.
	std::unique_ptr<CSprite_Resource<CSpriteUI, enSpriteUI>>		m_pCSpriteUI;			//スプライトUIクラス.
	std::unique_ptr<CObjectResource<CDX9Mesh, enStaticMeshType>>	m_pCStaticMesh;			//スタティックメッシュクラス.
	std::unique_ptr<CObjectResource<CDX9SkinMesh, enSkinMeshType>>	m_pCSkinMesh;			//スキンメッシュクラス.
	std::unique_ptr<CResourceEffect>								m_pCEffect;				//エフェクトクラス.
	std::unique_ptr<CFontResource>									m_pCFont;				//フォントクラス.

	std::vector<std::string>										m_vSpriteFileName;		//スプライトのファイル名.
	std::vector<std::string>										m_vSpriteUIFileNmae;	//スプライトUIのファイル名.
	std::vector<std::string>										m_vStaticMeshFileName;	//スタティックメッシュのファイル名.
	std::vector<std::string>										m_vSkinMeshFileName;	//スキンメッシュのファイル名.

	SPRITE_STATE*													m_pstSpriteState;		//スプライト情報構造体.
	SPRITE_STATE*													m_pstSpriteUIState;		//スプライトUI情報構造体.

};

#endif	//#ifndef CRESOURCE_MANAGER_H.