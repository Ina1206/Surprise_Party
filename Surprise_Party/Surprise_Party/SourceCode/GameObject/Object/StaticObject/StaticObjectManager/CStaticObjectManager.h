#ifndef COBJECT_MANAGER_H
#define COBJECT_MANAGER_H

#include "..\..\..\FileLoad\FileResource\CFileResource.h"
#include "..\Floor\CFloor.h"
#include "..\Wall\CWall.h"
#include "..\Painting\CPainting.h"
#include "..\BookShelf\CBookShelf.h"

/********************************************
*		静的オブジェクト管理クラス.
*********/
class CStaticObjectManager
{
public:
	CStaticObjectManager();
	~CStaticObjectManager();

	//================列挙体===================//.
	//オブジェクトの種類.
	enum class enStaticObjectType {
		Painting = 0,			//絵画.
		BookShelf,				//本棚.
		Wall,					//壁.
		Floor,					//地面.

		Max,					//最大値.
		Start = Wall,			//スタート値.
		ObjMax = Wall,			//オブジェクトの最大値.
	};

	//=================定数===================//.
	const float			OBJECT_WIDTH			= 2.5f;									//オブジェクトの幅.
	const float			DISP_CAMERA_WIDHT		= 16.8f;								//表示するカメラ幅.
	const int			CREATION_MAX			= 14;									//作成する最大数.
	const int			COLUMN_MAX				= 4;									//列の最大数.
	const int			ALL_OBJECT_MAX			= CREATION_MAX * COLUMN_MAX;			//床と壁のオブジェクトの総数.
	const float			WALL_POS_Z				= 1.0f;									//壁のz座標の位置.
	const D3DXVECTOR3	FLOOR_START_POS			= D3DXVECTOR3(-1.25f, -1.1f, -1.4f);	//床の開始位置.
	const int			OTHER_CREATION_MAX		= 6;									//他の作成するオブジェクトの最大数.
	const D3DXVECTOR3	STANDERD_PAINTING_POS	= D3DXVECTOR3(0.0f, 5.0f, 1.0f);		//基本の絵画の座標.

	//=================関数====================//.
	void UpData();																						//更新処理関数.
	void Render(const D3DXMATRIX& mView,const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);		//描画処理関数.

	//===========情報置換処理関数==============//.
	//カメラ座標.
	void SetCameraPos(const D3DXVECTOR3& vPos) { m_vCameraPos = vPos; }

	//===========情報獲得処理関数==============//.
	//ステージ距離最大数.
	float GetStageDistanceMax() { return m_fStageDistanceMax; }

private:
	//=================関数====================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
	void WallAndFloorSetting();		//壁と床の設定処理関数.
	void OtherObjectSetting();		//他のオブジェクト設定処理関数.
	void ObjectRender(std::vector<CObjectBase*> obj, int max);


	//=================変数====================//.
	D3DXMATRIX					m_mView;
	D3DXMATRIX					m_mProj;
	D3DXVECTOR3					m_vLightPos;

	CFileResource*				m_pCFileResource;	//ファイル読み込み.
	std::vector<CObjectBase*>	m_pCObjectBase;		//壁と床のオブジェクトクラス.
	std::vector<D3DXVECTOR3>	m_vObjectPos;		//壁と床のオブジェクト座標.

	std::vector<CObjectBase*>	m_pCOtherObjectBase;//他のオブジェクトクラス.
	std::vector<D3DXVECTOR3>	m_vOtherObjectPos;	//他のオブジェクト座標.
	std::vector<unsigned int>	m_BeforeObjMax;		//前のオブジェクトまでの総合値.
	D3DXVECTOR3					m_vCameraPos;		//カメラ座標.
	float						m_fStageDistanceMax;//ステージ距離最大数.
};

#endif	//#ifndef COBJECT_MANAGER_H.