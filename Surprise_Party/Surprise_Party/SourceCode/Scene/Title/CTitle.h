#ifndef CTITLE_H
#define CTITLE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Camera\CameraTitle\CCameraTitle.h"
#include "..\..\GameObject\Object\StaticObject\Light\FrontstageLight\CFrontstageLight.h"
#include "..\..\GameObject\Object\StaticObject\StaticObjectManager\CStaticObjectManager.h"
#include "..\..\GameObject\Object\MoveObject\MoveObjectManager\CMoveObjectManager.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\MainStageWorkGhostBase\MainStageWorkGhsotManager\CMainStageWorkGhostManager.h"
#include "..\..\UI\SceneUI\TitleUI\CTitleUI.h"

/**********************************
*		タイトルクラス.
******/
class CTitle
	: public CSceneBase
{
public:
	CTitle();
	~CTitle();

	//====================関数========================//.
	void UpDate();		//更新処理関数.
	void Render();		//描画処理関数.
protected:
	//====================関数========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void SettingView();	//ビュー行列の設定処理関数.

	//====================変数========================//.
	std::unique_ptr<CCameraTitle>				m_pCCameraTitle;			//タイトル用カメラクラス.
	std::unique_ptr<CFrontstageLight>			m_pCFrontstageLight;		//表舞台のライトクラス
	std::unique_ptr<CStaticObjectManager>		m_pCStaticObjectManager;	//静的オブジェクトの管理クラス.
	std::unique_ptr<CMoveObjectManager>			m_pCMoveObjectManager;		//動的オブジェクトの管理クラス.
	std::unique_ptr<CMainStageWorkGhostManager>	m_pCWorkGhostManager;		//働くお化け管理クラス.
	std::unique_ptr<CTitleUI>					m_pCTitleUI;				//タイトルUI.
};


#endif	//#ifndef CTITLE_H.