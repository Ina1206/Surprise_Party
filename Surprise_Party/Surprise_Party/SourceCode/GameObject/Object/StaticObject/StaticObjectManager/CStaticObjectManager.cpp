#include "CStaticObjectManager.h"
#include <random>

CStaticObjectManager::CStaticObjectManager()
	: CStaticObjectManager(0, 0)
{

}

CStaticObjectManager::CStaticObjectManager(const int& filenum, const int& stagenum)
	: m_mView				()
	, m_mProj				()
	, m_stLight				()
	, m_Filenum				(0)
	, m_Stagenum			(0)
	, m_pCFileResource		(nullptr)
	, m_pCObjectBase		()
	, m_vObjectPos			()
	, m_pCOtherObjectBase	()
	, m_vOtherObjectPos		()
	, m_vCameraPos			(0.0f, 0.0f, 0.0f)
	, m_fStageDistanceMax	(0.0f)
{
	//ファイル番号.
	m_Filenum = filenum;
	//ステージ番号.
	m_Stagenum = stagenum;

	//初期化処理関数.
	Init();
}

CStaticObjectManager::~CStaticObjectManager()
{
	//解放処理関数.
	Release();
}

//====================================.
//		更新処理関数.
//====================================.
void CStaticObjectManager::Updata()
{
	//オブジェクト設定用番号.
	int num = 0;

	int checkStageNum = 0;
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum) * COLUMN_MAX; stage++) {
		//壁に合わせて表示場所を決める.
		if (stage % COLUMN_MAX == 0) {
			checkStageNum = stage;
		}

		if (m_vCameraPos.x + DISP_CAMERA_WIDHT > m_vObjectPos[checkStageNum].x &&
			m_vCameraPos.x - DISP_CAMERA_WIDHT < m_vObjectPos[checkStageNum].x) {
			//オブジェクト座標設定.
			m_pCObjectBase[num]->SetPos(m_vObjectPos[stage]);
			//オブジェクト更新処理関数.
			m_pCObjectBase[num]->Update();
			num++;
		}

		if (num >= ALL_OBJECT_MAX) {
			break;
		}
	}

	//その他のオブジェクト.
	std::vector<int> m_ObjDispCnt(static_cast<int>(enStaticObjectType::ObjMax));
	for (unsigned int obj = 0; obj < static_cast<int>(enStaticObjectType::ObjMax); obj++) {
		//種類ごとのオブジェクトの最大数.
		int objMax = 0;
		if (obj >= m_BeforeObjMax.size() - 1) {
			objMax = m_vOtherObjectPos.size() - m_BeforeObjMax[obj];
		}
		else {
			objMax = m_BeforeObjMax[obj + 1] - m_BeforeObjMax[obj];
		}
		for (int stage = 0; stage < objMax; stage++) {
			if (m_vCameraPos.x + DISP_CAMERA_WIDHT > m_vOtherObjectPos[stage + m_BeforeObjMax[obj]].x &&
				m_vCameraPos.x - DISP_CAMERA_WIDHT < m_vOtherObjectPos[stage + m_BeforeObjMax[obj]].x) {
				m_pCOtherObjectBase[m_ObjDispCnt[obj] + (obj * OTHER_CREATION_MAX)]->SetPos(m_vOtherObjectPos[stage + m_BeforeObjMax[obj]]);
				m_pCOtherObjectBase[m_ObjDispCnt[obj] + (obj * OTHER_CREATION_MAX)]->Update();
				m_ObjDispCnt[obj]++;
			}

			if (m_ObjDispCnt[obj] >= OTHER_CREATION_MAX) {
				break;
			}
		}
	}
}

//====================================.
//		描画処理関数.
//====================================.
void CStaticObjectManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos, const LIGHT& stLight)
{
	m_mView = mView;
	m_mProj = mProj;
	m_vCameraPos = vCameraPos;
	m_stLight = stLight;

	//壁と床の描画.
	ObjectRender(m_pCObjectBase, m_pCObjectBase.size());
	//その他のオブジェクトの描画.
	ObjectRender(m_pCOtherObjectBase, m_pCOtherObjectBase.size());
}

//====================================.
//		初期化処理関数.
//====================================.
void CStaticObjectManager::Init()
{
	m_pCFileResource = CFileResource::GetResourceInstance();

	//壁と床の設定処理関数.
	WallAndFloorSetting();

	//他のオブジェクト設定処理関数.
	OtherObjectSetting();
}

//====================================.
//		解放処理関数.
//====================================.
void CStaticObjectManager::Release()
{
	//オブジェクトのインスタンス化したクラスの解放.
	for (int obj = static_cast<int>(m_pCOtherObjectBase.size()) - 1; obj >= 0; obj--) {
		SAFE_DELETE(m_pCOtherObjectBase[obj]);
	}
	//壁と床のインスタンス化したクラスの解放.
	for (int stage = static_cast<int>(m_pCObjectBase.size()) - 1; stage >= 0; stage--) {
		SAFE_DELETE(m_pCObjectBase[stage]);
	}

	m_pCFileResource = nullptr;
}

//====================================.
//		壁と床の設定処理関数.
//====================================.
void CStaticObjectManager::WallAndFloorSetting()
{
	for (int stage = 0; stage < ALL_OBJECT_MAX; stage++) {
		m_pCObjectBase.push_back(nullptr);

		if (stage % COLUMN_MAX == 0) {
			//壁のクラスのインスタンス化.
			m_pCObjectBase[stage] = new CWall();
			continue;
		}

		//床のクラスのインスタンス化.
		m_pCObjectBase[stage] = new CFloor();
	}

	D3DXVECTOR3 vInitPos;
	int stagenum = 0;
	//床と壁の座標設定.
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum) * COLUMN_MAX; stage++) {
		if (stage % COLUMN_MAX == 0) {
			//列番号.
			stagenum = stage / COLUMN_MAX;
			//壁の座標.
			m_vObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, 1.0f));
			continue;
		}
		//床の座標.
		vInitPos.x = FLOOR_START_POS.x + (stagenum * OBJECT_WIDTH);
		vInitPos.y = FLOOR_START_POS.y;
		vInitPos.z = FLOOR_START_POS.z - (((stage % COLUMN_MAX) - 1)* OBJECT_WIDTH);
		m_vObjectPos.push_back(vInitPos);
	}

	//ステージの距離最大数計算.
	m_fStageDistanceMax = m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum) * OBJECT_WIDTH;
}

//====================================.
//	他のオブジェクト設定処理関数.
//====================================.
void CStaticObjectManager::OtherObjectSetting()
{
	//他のオブジェクトのインスタンス化と座標設定.
	//各オブジェクトのステージ最大数.
	int stageMax = m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum);
	//オブジェクト数分ステージ数.
	int objMax = stageMax * static_cast<int>(enStaticObjectType::ObjMax);
	int obj = 0;
	m_BeforeObjMax.push_back(m_vOtherObjectPos.size());

	for (int stage = 0; stage < objMax; stage++) {
		int stagenum = stage - (stageMax - m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum));
		int objNum = m_pCFileResource->GetStageNum(m_Filenum, m_Stagenum, stagenum) - 1;
		if (objNum == obj) {
			//オブジェクト番号ごとに設定.
			switch (objNum) {
			case static_cast<int>(enStaticObjectType::Painting):
				m_vOtherObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 5.0f, 1.0f));
				break;
			case static_cast<int>(enStaticObjectType::BookShelf):
				m_vOtherObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, 0.5f));
				break;

			}

		}
		//オブジェクトのステージ最大数になると次のオブジェクトへ.
		if (stage >= stageMax - 1) {
			obj++;
			stageMax += m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum);
			m_BeforeObjMax.push_back(m_vOtherObjectPos.size());
		}
	}

	//全ての他のオブジェクトの作成.
	for (int stage = 0; stage < static_cast<int>(enStaticObjectType::ObjMax) * OTHER_CREATION_MAX; stage++) {
		int stagenum = static_cast<int>(stage / OTHER_CREATION_MAX);
		switch (static_cast<enStaticObjectType>(stagenum)) {
		//絵画.
		case enStaticObjectType::Painting:
			m_pCOtherObjectBase.push_back(nullptr);
			m_pCOtherObjectBase[m_pCOtherObjectBase.size() - 1] = new CPainting();
			break;
		case enStaticObjectType::BookShelf:
			m_pCOtherObjectBase.push_back(nullptr);
			m_pCOtherObjectBase[m_pCOtherObjectBase.size() - 1] = new CBookShelf();
			break;
		}
	}

}

//================================.
//	オブジェクトの描画処理関数.
//================================.
void CStaticObjectManager::ObjectRender(std::vector<CObjectBase*> obj, int max)
{
	for (int stage = 0; stage < max; stage++) {
		obj[stage]->SetCameraPos(m_vCameraPos);
		obj[stage]->RenderInitSetting(m_mView, m_mProj, m_stLight);
		obj[stage]->Render();
	}
}

