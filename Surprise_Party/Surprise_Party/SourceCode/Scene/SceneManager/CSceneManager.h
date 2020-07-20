#ifndef CSCENE_MANAGER_H
#define CSCENE_MANAGER_H

#include "..\Title\CTitle.h"
#include "..\GameMain\CGameMain.h"
#include "..\Ending\CEnding.h"
#include "..\Pause\CPause.h"
	
#include "..\..\Drawing/Resource/CResourceManager.h"
#include "..\GameMain\CGameMain.h"

#include "..\..\UI\Fade\SceneFade\CSceneFade.h"

#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

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

	//===================定数======================//.
	const unsigned int	INIT_SETTED_FLAG	= (1 << 0);						//初期設定後フラグ.
	const unsigned int	START_GAME_FLAG		= (1 << 1);						//ゲーム開始フラグ.
	const int			NORMAL_SCENE_NUM	= 0;							//通常シーン番号(タイトル、ゲームメイン、クリア画面).
	const int			PAUSE_SCENE_NUM		= 1;							//一時停止シーン番号.
	const D3DXVECTOR2	SCENE_NAME_POS		= D3DXVECTOR2(50.0f, 200.0f);	//シーン名座標.
	const float			HIGHT_WIDTH			= 30.0f;						//高さ幅.
	const D3DXVECTOR2	CURSOR_POS			= D3DXVECTOR2(20.0f, 200.0f);	//カーソル座標.

	//===================関数======================//.
	void Init(HWND hWnd,LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext*	pContext11);//初期化処理関数.
	void Load();																								//読み込み処理関数.
	void UpDate();																								//更新処理関数.
	void Render(const D3DXMATRIX& mProj);												//描画処理関数.
	void Release();																								//解放処理関数.

	//=============情報獲得処理関数=================//.
	D3DXVECTOR4	GetBackColor() { return m_Color; }		//後ろの色の情報獲得処理関数.

private:
	//===================関数=======================//.
	void ChangeScene();									//シーン変更処理関数.
	void NextScene();									//次のシーンに進む処理関数.
	void Pause();										//ポーズ処理化数.
	void FlyToScene();									//シーンに飛ぶ処理関数.
	void RenderDebugFont();								//デバッグ用フォント描画処理関数.

	//===================変数=======================//.
	HWND										m_hWnd;						//ウィンドウハンドル.
	LPDIRECT3DDEVICE9							m_pDevice9;
	ID3D11Device*								m_pDevice11;				//デバイスオブジェクト.
	ID3D11DeviceContext*						m_pContext11;				//デバイスコンテキスト.
	CDepth_Stencil*								m_pCDepthStencil;			//デプスステンシル.

	std::vector<std::unique_ptr<CSceneBase>>	m_pCSceneBase;				//シーンクラス.
	D3DXVECTOR4									m_Color;
	int											m_ChangeSceneCnt;			//シーン変更カウント.
	int											m_SceneType;				//シーン種類.

	std::unique_ptr<CSceneFade>					m_pCSceneFade;				//シーンフェードクラス.
	bool										m_PausingFlag;				//一時停止フラグ.
	unsigned int								m_StartFlag;				//開始フラグ.

	CDebugText*									m_pCDebugText;				//デバッグテキスト.
	int											m_FlyToSceneNum;			//変更するシーン番号.
	int											m_FlyToSceneMax;			//変更するデバッグ用のシーン最大数.
	bool										m_bFlyToSceneFlag;			//シーンに飛ぶフラグ.

	int											m_FlyToSceneEvaluation;		//シーンに飛ぶ場合の評価.

	CPlaySoundManager*							m_pCPlaySoundManager;		//音再生管理クラス.
};

#endif	//#ifndef CSCENE_MANAGER_H.