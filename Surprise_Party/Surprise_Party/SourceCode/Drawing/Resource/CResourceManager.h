#ifndef CRESOURCE_MANAGER_H
#define CRESOURCE_MANAGER_H

#include "SpriteResource/CSpriteResource.h"
#include "ObjectResource/CObjectResource.h"
#include "EffectResource/CResourceEffect.h"
#include "FontResource/CFontResource.h"

/*******************************************
*		�ǂݍ��݊Ǘ��N���X.
************/
class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	//=======================�֐�========================//.
	HRESULT Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//�ǂݍ��ݏ����֐�.
	HRESULT Release();																								//��������֐�.

	//=================���擾�����֐�==================//.	
	CSprite*		GetSprite(enSprite enSpriteType) { return m_pCSprite->GetSprite(enSpriteType); }						//�X�v���C�g�N���X.
	CSpriteUI*		GetSpriteUI(enSpriteUI enSpriteUIType) { return m_pCSpriteUI->GetSprite(enSpriteUIType); }				//�X�v���C�gUI�N���X.
	CDX9Mesh*		GetStaticMesh(enStaticMeshType enStaticMesh) { return m_pCStaticMesh->GetMeshObject(enStaticMesh); }	//�X�^�e�B�b�N���b�V���N���X.
	CDX9SkinMesh*	GetSkinMesh(enSkinMeshType enSkinMesh) { return m_pCSkinMesh->GetMeshObject(enSkinMesh); }				//�X�L�����b�V���N���X.
	CEffect*		GetEffect(CResourceEffect::enEffect enEffect) { return m_pCEffect->GetEffect(enEffect); }
	CFontResource*	GetFont() { return m_pCFont.get(); }
	SPRITE_STATE	GetSpriteUIState(const enSpriteUI& enSpriteUIType) { return m_pstSpriteUIState[static_cast<int>(enSpriteUIType)]; }

	//===================�V���O���g��====================//.
	static CResourceManager* GetResourceManagerInstance()
	{
		static CResourceManager s_Instance;
		return &s_Instance;
	}

private:
	//=====================�֐�===========================//.
	void	StaticMeshFileNmaeSetting();					//�X�^�e�B�b�N���b�V���̃t�@�C�����ݒ菈���֐�.
	void	SkinMeshFileNameSetting();						//�X�L�����b�V���̃t�@�C�����ݒ菈���֐�.
	void	SpriteFileNameSetting();						//�X�v���C�g�t�@�C�����ݒ菈���֐�.
	void	SpriteUIFileNameSetting();						//�X�v���C�gUI�t�@�C�����ݒ菈���֐�.
	void	SpriteStateSetting();							//�X�v���C�g���\���̐ݒ菈���֐�.
	void	SpriteUIStateSetting();							//�X�v���C�gUI���\���̐ݒ菈���֐�.
	HRESULT InitSphere();									//�����蔻��p�X�t�B�A�쐬�����֐�.

	//=====================�ϐ�===========================//.
	std::unique_ptr<CSprite_Resource<CSprite, enSprite>>			m_pCSprite;				//�X�v���C�g�N���X.
	std::unique_ptr<CSprite_Resource<CSpriteUI, enSpriteUI>>		m_pCSpriteUI;			//�X�v���C�gUI�N���X.
	std::unique_ptr<CObjectResource<CDX9Mesh, enStaticMeshType>>	m_pCStaticMesh;			//�X�^�e�B�b�N���b�V���N���X.
	std::unique_ptr<CObjectResource<CDX9SkinMesh, enSkinMeshType>>	m_pCSkinMesh;			//�X�L�����b�V���N���X.
	std::unique_ptr<CResourceEffect>								m_pCEffect;				//�G�t�F�N�g�N���X.
	std::unique_ptr<CFontResource>									m_pCFont;				//�t�H���g�N���X.

	std::vector<std::string>										m_vSpriteFileName;		//�X�v���C�g�̃t�@�C����.
	std::vector<std::string>										m_vSpriteUIFileNmae;	//�X�v���C�gUI�̃t�@�C����.
	std::vector<std::string>										m_vStaticMeshFileName;	//�X�^�e�B�b�N���b�V���̃t�@�C����.
	std::vector<std::string>										m_vSkinMeshFileName;	//�X�L�����b�V���̃t�@�C����.

	SPRITE_STATE*													m_pstSpriteState;		//�X�v���C�g���\����.
	SPRITE_STATE*													m_pstSpriteUIState;		//�X�v���C�gUI���\����.

};

#endif	//#ifndef CRESOURCE_MANAGER_H.