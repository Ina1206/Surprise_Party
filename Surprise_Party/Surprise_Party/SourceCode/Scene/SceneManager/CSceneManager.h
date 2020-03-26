#ifndef CSCENE_MANAGER_H
#define CSCENE_MANAGER_H

#include "..\Title\CTitle.h"
#include "..\GameMain\CGameMain.h"
#include "..\Ending\CEnding.h"

#include "..\..\Drawing/Resource/CResourceManager.h"
#include "..\GameMain\CGameMain.h"

#include "..\..\UI\Fade\SceneFade\CSceneFade.h"

/*****************************************
*		シーン管理クラス.
*********/
class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	//==================列挙体=====================//.
	//ゲームのシーン種類.
	enum class enSceneType {
		Title = 0,		//タイトル.
		GameMain,		//ゲームメイン.
		Ending,			//クリア.

		Max,			//最大値.
		Start = Title,	//最初のシーン.
	};

	//===================関数======================//.
	void Init(HWND hWnd,LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext*	pContext11);					//初期化処理関数.
	void Load();																													//読み込み処理関数.
	void UpDate();																													//更新処理関数.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);		//描画処理関数.
	void Release();																													//解放処理関数.

	//=============情報獲得処理関数=================//.
	D3DXVECTOR4	GetBackColor() { return m_Color; }		//後ろの色の情報獲得処理関数.

private:
	//===================関数=======================//.
	void ChangeScene();									//シーン変更処理関数.

	//===================変数=======================//.
	HWND						m_hWnd;					//ウィンドウハンドル.
	LPDIRECT3DDEVICE9			m_pDevice9;
	ID3D11Device*				m_pDevice11;			//デバイスオブジェクト.
	ID3D11DeviceContext*		m_pContext11;			//デバイスコンテキスト.

	std::unique_ptr<CSceneBase>	m_pCSceneBase;			//シーンクラス.
	D3DXVECTOR4					m_Color;
	int							m_ChangeSceneCnt;		//シーン変更カウント.
	int							m_SceneType;			//シーン種類.

	std::unique_ptr<CSceneFade> m_pCSceneFade;			//シーンフェードクラス.
};

#endif	//#ifndef CSCENE_MANAGER_H.