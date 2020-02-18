#ifndef CFILE_RESOURCE_H
#define CFILE_RESOURCE_H
 
#include "..\..\FileLoad\FileNumber\CFileNumber.h"

/*****************************************
*		ファイル読み込みクラス.
********/
class CFileResource
{
public:
	CFileResource();
	~CFileResource();

	//===================関数=======================//.
	const int ONETYPE_STAGE_MAX = 3;	//1タイプのステージの最大数.

	//==================列挙体======================//.
	//ステージ種類.
	enum class enStageType {
		OneDay,				//1日目.
		TwoDay,				//2日目.
		ThreeDay,			//3日目.
		PeopleOder,			//人が入る順番.
		GhostPos_OneDay,	//お化けの位置1日目.
		GhostPos_TwoDay,	//お化けの位置2日目.
		GhostPos_ThreeDay,	//お化けの位置3日目.

		Max,		//最大値.
		Start = OneDay,
	};
	//ステータス必要キャラ.
	enum class enStatusCharaType {
		Ghost = 0,		//お化け.
		People,			//人.

		Max,			//最大値.
		Start = Ghost,
	};

	//===================関数=======================//.
	void Load();		//読み込み処理関数.

	//シングルトン.
	static CFileResource* GetResourceInstance() {
		static CFileResource s_Instance;
		return &s_Instance;
	}
	//=============情報取得処理関数=================//.
	//ステージのマップチップの取得.
	int GetStageNum(int fileNum, int column, int line) { return static_cast<int>(m_pCStageFileNumber[fileNum]->GetDataNum(column, line)); }
	//ステータスのマップチップの取得.
	float GetStatusNum(int fileNum, int column, int line) { return m_pCStatusFileNumber[fileNum]->GetDataNum(column, line); }
	//ステージの最大.
	int GetStageMax(int fileNum) { return m_pCStageFileNumber[fileNum]->GetLineMax(); }
private:
	//===================関数=======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void StageLoad();	//ステージ読み込み処理関数.
	void StatusLoad();	//ステータス読み込み処理関数.

	//===================変数=======================//.
	std::vector<CFileNumber*>	m_pCStageFileNumber;	//マップチップのファイル読み込み.
	std::vector<CFileNumber*>	m_pCStatusFileNumber;	//ステータスのファイル読み込み.
};

#endif	//#ifndef CFILE_RESOURCE_H.