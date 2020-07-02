#ifndef CFILE_RESOURCE_H
#define CFILE_RESOURCE_H
 
#include "..\FileNumber\CFileNumber.h"
#include "..\FileString\CFileString.h"

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
		ObjectPos,			//オブジェクト座標.
		PeopleComeOder,		//人が入る順番.
		GhostPos,			//お化けの位置1日目.

		Max,				//最大値.
		Start = ObjectPos,
	};
	//ステータス必要キャラ.
	enum class enStatusCharaType {
		Ghost = 0,		//お化け.
		People,			//人.

		Max,			//最大値.
		Start = Ghost,
	};
	//会話ファイル種類.
	enum class enSpeakFileType {
		GhostSpeakFirstStage,
		GhostSpeakStage,
		SpeakTutorialBigGhost,
		EndingSpeak,
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
	int GetStageMax(const int& fileNum, const int& column) { return m_pCStageFileNumber[fileNum]->GetLineMax(column); }
	//会話文章.
	std::string GetSpeakString(const int& fileNum, const int& column, const CFileString::enStringType& line) { return m_pCSpeakFileString[fileNum]->GetData(column, line); }
	int	GetSringMax(const int& fileNum) const { return m_pCSpeakFileString[fileNum]->GetColumnMax(); }

private:
	//===================関数=======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void StageLoad();	//ステージ読み込み処理関数.
	void StatusLoad();	//ステータス読み込み処理関数.
	void SpeakLoad();	//会話文章読み込み処理関数.

	//===================変数=======================//.
	std::vector<CFileNumber*>					m_pCStageFileNumber;	//マップチップのファイル読み込み.
	std::vector<CFileNumber*>					m_pCStatusFileNumber;	//ステータスのファイル読み込み.
	std::vector<std::unique_ptr<CFileString>>	m_pCSpeakFileString;	//会話文章読み込み.
};

#endif	//#ifndef CFILE_RESOURCE_H.