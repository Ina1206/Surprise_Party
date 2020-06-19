#ifndef CMAIN_STAGE_H
#define CMAIN_STAGE_H

#include "..\StageBase\CStageBase.h"
#include "..\..\..\GameObject/Object/StaticObject/StaticObjectManager/CStaticObjectManager.h"
#include "..\..\..\GameObject/Object/MoveObject/MoveObjectManager/CMoveObjectManager.h"
#include "..\..\..\FileLoad/FileResource/CFileResource.h"

#include "..\..\..\GameObject\Chara\Ghost\WorkGhost\MainStageWorkGhostBase\MainStageWorkGhsotManager\CMainStageWorkGhostManager.h"

#include "..\..\..\GameObject/Chara/People/PeopleManager/CPeopleManager.h"

#include "..\..\..\GameObject\Object\StaticObject\Light\FrontstageLight\CFrontstageLight.h"

#include "..\..\..\UI\MapUI\StageMap\CStageMap.h"
#include "..\..\..\UI\MapUI\CharaUI\MapCursor\MapGhostCursor\CMapGhostCursor.h"
#include "..\..\..\UI\MapUI\CharaUI\MapCursor\MapGimmickCursor\CMapGimmickCursor.h"
#include "..\..\..\UI\GameWorldUI\GameWorldCursor\GameGhostCursor\CGameGhostCursor.h"
#include "..\..\..\UI\PlayUI\ClosedTime\CClosedTime.h"
#include "..\..\..\UI\PlayUI\SurpriseGage\CSurpriseGage.h"

#include "..\..\..\UI\SpeakUI\SpeakWorkGhost\CSpeakWorkGhost.h"

#include "..\..\..\UI\PlayUI\DescriptionUIManager\CDescriptionUIManager.h"

/************************************
*		メインステージクラス.
********/
class CMainStage
	: public CStageBase
{
public:

	CMainStage();
	CMainStage(int stageNum, enStageType enStage, enBeforeStageEndigneType enType);
	~CMainStage();

	//====================定数=========================//.
	const unsigned int	GHOST_SELECTION_FLAG	= (1 << 0);		//お化け選択フラグ.
	const unsigned int	GHOST_ACT_SELECT_FLAG	= (1 << 1);		//お化けの行動選択フラグ.
	const unsigned int	GIMMICK_SELECTION_FLAG	= (1 << 2);		//ギミック選択フラグ.

	const unsigned int	EXPLAINING_FLAG			= (1 << 0);		//説明中フラグ.
	const unsigned int	EXPLAINED_GHOST_FLAG	= (1 << 1);		//お化けを説明したフラグ.
	const unsigned int	EXPLAINED_GIMMICK_FLAG	= (1 << 2);		//ギミックを説明したフラグ.
	const unsigned int	EXPLAINED_MAP_FLAG		= (1 << 3);		//マップを説明したフラグ.
	const unsigned int	EXPLAINED_GAGE_FLAG		= (1 << 4);		//ゲージを説明したフラグ.
	const unsigned int	EXPLAINED_CLOSE_FLAG	= (1 << 5);		//閉店の説明したフラグ.
	const int			SLECTION_MAX			= 2;			//選択最大個数.
	const int			GHOST_NUM				= 0;			//お化け番号.
	const int			GIMMICK_NUM				= 1;			//ギミック番号.
	const int			TIME_DELIMITER			= 60;			//時間区切り.

	const int			START_TIME_UP_MAX		= 6;			//開始時の制限時間最大数.
	const int			ADD_TIME_UP				= 1;			//制限時間追加量.
	const int			BENEFITS_PREVIOS_RESULT	= 1;			//前回の結果の特典.

	const int			START_SUPRISE_GAGE_MAX	= 50;			//開始時の驚きゲージの最大数.
	const int			SURPRISE_GAGE_ADD		= 20;			//驚きゲージ追加量.

	//====================関数=========================//.
	void UpDate(const bool& ControlFlag);			//更新処理関数.
	void Render();									//描画処理関数.
	void Control();									//操作処理関数.

private:
	//====================関数==========================//.
	void Init();									//初期化処理関数.
	void Release();									//解放処理関数.
	void GhostSelect();								//お化け選択処理関数.
	void GimmickSelect();							//ギミック選択処理関数.
	template <typename T>
	void GhostElementSort(T pClass, int array);		//お化け要素数変換処理関数.
	enBeforeStageEndigneType Evalute();				//評価処理関数.
	bool Tutorial(const bool& ControlFlag);			//チュートリアル処理関数.
	void UpdateWorkGhost();							//働くお化け更新処理関数.
	void UnloadSetTrueTutrialFlag();				//チュートリアルフラグ上げ下げ処理.

	//===================変数=======================//.
	std::unique_ptr<CStaticObjectManager>					m_pCStaticObjectManager;	//静的オブジェクト管理クラス.
	std::unique_ptr<CMoveObjectManager>						m_pCMoveObjectManager;		//動的オブジェクト管理クラス.

	std::unique_ptr<CMainStageWorkGhostManager>				m_pCWorkghostManager;		//働くお化け管理クラス.

	std::unique_ptr<CPeopleManager>							m_pCPeopleManager;			//人管理クラス.

	std::unique_ptr<CStageMap>								m_pCStageMap;				//ステージマップ.
	std::unique_ptr<CMapCursor>								m_pCMapGhostCursor;			//マップ上のお化けのカーソルクラス.

	std::vector<int>										m_SelectNum;				//選択番号.
	unsigned int											m_ObjectSelectFlag;			//オブジェクト選択フラグ.

	std::unique_ptr<CGameGhostCursor>						m_pCGameGhostCursor;		//ゲーム内のお化けのカーソルクラス.

	std::unique_ptr<CClosedTime>							m_pCClosedTime;				//閉店までの時間クラス.
	std::unique_ptr<CSurpriseGage>							m_pCSurpriseGage;			//驚きゲージクラス.
	
	std::unique_ptr<CFrontstageLight>						m_pCFrontstageLight;		//表舞台のライトクラス.

	enStageType												m_enStageType;				//ステージタイプ.
	unsigned int											m_ExplainFlag;				//説明フラグ.
	bool													m_bDispTextFlag;			//テキスト表示フラグ.

	std::unique_ptr<CSpeakWorkGhost>						m_pCSpeakWorkGhost;			//働くお化け会話クラス.
	D3DXVECTOR3												m_vSelectGhostPos;			//選択しているお化けの座標.

	std::unique_ptr<CDescriptionUIManager>					m_pCDescriptionUIManager;	//説明UI管理クラス.
};

#endif	//#ifndef CMAIN_STAGE_H.