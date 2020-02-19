#ifndef CMVOE_OBJECT_MANAGER_H
#define CMVOE_OBJECT_MANAGER_H

#include "..\..\FileLoad\FileResource\CFileResource.h"
#include "..\GhostDispPainting\CGhostDispPainting.h"
#include "..\Switch\ObjectMoveSwitch\CObjectMoveSwitch.h"
#include "..\Switch\PlaySoundSwitch\CPlaySoundSwitch.h"
#include "..\..\UI\MapUI\CharaUI\Icon\GimmickIcon\CGimmickIcon.h"
#include "..\..\UI\MapUI\CharaUI\MapCursor\MapGimmickCursor\CMapGimmickCursor.h"
#include "..\..\UI\GameWorldUI\GameWorldCursor\GameGimmickCursor\CGameGimmickCursor.h"

/**********************************
*	移動オブジェクト管理クラス.
*****/
class CMoveObjectManager
{
public:
	CMoveObjectManager();
	CMoveObjectManager(int FileNum);
	~CMoveObjectManager();

	//================列挙体==================//.
	enum class enMoveObjectType {
		GhostDispPainting = 0,		//お化けの現れる絵画.
		ObjectMoveSwitch,			//オブジェクト移動スイッチ.
		PlaySoundSwitch,			//音を鳴らすスイッチ.

		Max,
		Start = GhostDispPainting,
	};

	//=================定数===================//.
	const unsigned int	ATTACHED_MOVE_PREPARA_FLAG	= (1 << 0);							//付属オブジェクト移動準備フラグ.
	const unsigned int	ATTACHED_MOVE_FLAG			= (1 << 1);							//付属オブジェクト移動フラグ.
	const unsigned int	ATTACHED_MOVE_LEFT_FLAG		= (1 << 2);							//付属オブジェクト左移動フラグ.
	const unsigned int	ATTACHED_MOVE_AFTER_FLAG	= (1 << 3);							//付属オブジェクト移動後フラグ.

	const int			MOVEOBJECT_START_NUM		= 3;								//移動オブジェクトの開始番号.
	const float			OBJECT_WIDTH				= 2.5f;								//オブジェクトの幅.
	const float			DISP_CAMERA_WIDHT			= 16.8f;							//表示するカメラ幅.
	const D3DXVECTOR3	STANDERD_PAINTING_POS		= D3DXVECTOR3(0.0f, 5.0f, 1.0f);	//基本の絵画の座標.
	const float			GIMMICK_UP_GHOST_ADJUST		= 0.1f;								//ギミックの上にお化けがいるときの微調整.
	const float			PAINTING_MOVE_GHOST_POS		= 3.4f;								//ギミックが動くお化けの座標.
	const float			PAINTING_MOVE_SPEED			= 0.25f;							//絵画が動く速度.
	const float			PAINTING_DOWN_MAX			= 0.5f;								//絵画落ちる最大数.

	const float			SWITCH_UP_DOWN_SPEED		= 0.3f;								//スイッチ上下速度.
	const float			SWITCH_HIGHT_MIN			= -1.5f;							//スイッチの高さ最小値.
	const float			SWITCH_HIGHT_MAX			= 0.0f;								//スイッチの高さ最大値.

	const float			VASE_UP_DOWN_SPEED			= 0.3f;								//花瓶移動速度.			
	const float			VASE_HIGHT_MAX				= 2.0f;								//花瓶の高さ最大値.
	const float			VASE_HIGHT_MIN				= 0.0f;								//花瓶の高さ最小値.
	const float			VASE_SWING_SPEED			= 0.06f;							//花瓶の揺れる速度.
	const float			VASE_ROT_MAX				= 0.5f;								//花瓶の角度最大値.
	const float			VASE_ROT_MIN				= -0.5f;							//花瓶の角度最小値.
	const float			VASE_ROT_RETURN				= 0.0f;								//花瓶の戻る角度.
	const int			VASE_SWING_MAX				= 1;								//花瓶の揺れる回数最大値.

	const unsigned int	NOT_MOVE_FALG				= (1 << 0);							//移動しないフラグ.
	const unsigned int	DOWN_FLAG					= (1 << 1);							//下がるフラグ.
	const unsigned int	UP_FLAG						= (1 << 2);							//上がるフラグ.


	//=================関数===================//.
	void UpDate();																			//更新処理関数.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight);	//描画処理関数.
	void EffectRender();

	//===========情報置換処理関数=============//.
	//カメラの位置.
	void SetCameraPos(const D3DXVECTOR3& vPos) { m_vCameraPos = vPos; }
	//選択している番号.
	void SetSelectionNum(const int& SelectionNum) { m_SelectionNum = SelectionNum; }
	//お化けの座標.
	void SetGhostPos(const std::vector<D3DXVECTOR3>& vPos) { m_vGhostPos = vPos; }
	//お化けの座標要素数設定.
	void SetGhostElementCount(const int& Max) { m_vGhostPos.resize(Max); }
	//ギミック移動フラグ.
	void SetGimmickMoveFlag(const int& objNum, const unsigned int& flag) { m_ObjeMoveFlag[objNum] = flag; }
	//ギミック表示フラグ設定.
	void SetGimmickCurosrDispFlag(const bool& flag) { m_bGimmickCursorDisp = flag; }
	//ギミック使われているかフラグ.
	void SetUsedGimmickFlag(const int& num, const bool& flag) { m_bUsedGimmickFlag[num] = flag; }

	//===========情報獲得処理関数=============//.
	//ギミックアイコン最大数.
	int GetGimmickIconMax() { return static_cast<int>(m_pCGimmickIcon.size()); }
	//選択されているギミックの場所.
	D3DXVECTOR3 GetGimmickPos() { return m_vMoveObjectPos[m_SelectionNum]; }
	//ギミックの種類.
	CGameObject::enSurpriseObjectType GetSurpriseObjectType() { return m_enSurpriseObjectType[m_SelectionNum]; }
	//ギミックの座標.
	std::vector<D3DXVECTOR3> GetAllGimmickPos() { return m_vMoveObjectPos; }
	//ギミック使われているかフラグ.
	bool GetUsedGimmickFlag(const int& num) { return m_bUsedGimmickFlag[num]; }

private:
	//=================関数===================//.
	void Init(int FileNum);																	//初期化処理関数.
	void Release();																	//解放処理関数.
	void GimmickSort();																//ギミック要素数並べ替え処理関数.
	void PaintingUpDown(int objNum);												//絵画を落としたり上げる処理関数..
	void SwitchPush(int objNum, CGameObject::enSurpriseObjectType enSurpriseObj);	//スイッチを押した処理関数.
	void Table_VaseFlowerMove(int objNum);											//机と花瓶の移動処理関数.

	//=================変数===================//.
	D3DXMATRIX										m_mView;				//ビュー行列.
	D3DXMATRIX										m_mProj;				//プロジェクション行列.
	std::vector<CMoveObjectBase*>					m_pCMoveObjectBase;		//移動オブジェクト.
	std::vector<D3DXVECTOR3>						m_vMoveObjectPos;		//移動オブジェクト座標.
	std::vector<D3DXVECTOR3>						m_vAttachObjPos;		//付属オブジェクト座標.
	std::vector<D3DXVECTOR3>						m_vAttachRot;			//付属オブジェクトの角度.
	std::vector<int>								m_enMoveObjectType;		//移動オブジェクトタイプ.
	CFileResource*									m_pCFileResource;		//読み込みクラス.
	D3DXVECTOR3										m_vCameraPos;			//カメラ座標.
	std::vector <std::unique_ptr<CGimmickIcon>>		m_pCGimmickIcon;		//ギミックアイコンクラス.
	std::unique_ptr<CMapGimmickCursor>				m_pCMapGimmicKCursor;	//マップ上のギミックカーソル.
	int												m_SelectionNum;			//選択している番号.
	std::unique_ptr<CGameGimmickCursor>				m_pCGameGimmickCursor;	//ギミックカーソルクラス.
	std::vector<CGameObject::enSurpriseObjectType>	m_enSurpriseObjectType;	//驚かすオブジェクト種類.
	std::vector<D3DXVECTOR3>						m_vGhostPos;			//お化け座標.
	int												m_GhostMax;				//お化け最大数.
	std::vector<unsigned int>						m_ObjeMoveFlag;			//上下フラグ.
	bool											m_bGimmickCursorDisp;	//ギミックカーソル表示フラグ.
	unsigned int									m_DispPaintingMax;		//絵画最大数.		
	std::vector<unsigned int>						m_AttachedObjMoveFlag;	//付属オブジェクト移動フラグ.
	std::vector<int>								m_FlowerSwingCnt;		//花瓶の揺れるカウント.
	std::vector<bool>								m_bUsedGimmickFlag;		//ギミックが使われているフラグ.
};

#endif	//#ifndef CMVOE_OBJECT_MANAGER_H.