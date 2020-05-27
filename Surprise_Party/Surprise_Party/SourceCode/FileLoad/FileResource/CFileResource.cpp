#include "CFileResource.h"

CFileResource::CFileResource()
	: m_pCStageFileNumber	()
	, m_pCStatusFileNumber	()
{
	//初期化処理関数.
	Init();
}

CFileResource::~CFileResource()
{
	//解放処理関数.
	Release();
}

//=====================================.
//		読み込み処理関数.
//=====================================.
void CFileResource::Load()
{
	//ステージ読み込み処理関数.
	StageLoad();

	//ステータス読み込み処理関数.
	StatusLoad();

	//会話文読み込み処理関数.
	SpeakLoad();
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CFileResource::Init()
{
	//全ステージの総合数.
	m_pCStageFileNumber.resize(static_cast<int>(enStageType::Max) * ONETYPE_STAGE_MAX);
	for (unsigned int file = 0; file < m_pCStageFileNumber.size(); file++) {
		m_pCStageFileNumber[file] = nullptr;
		m_pCStageFileNumber[file] = new CFileNumber();
	}

	//全ステータスの総合数.
	m_pCStatusFileNumber.resize(static_cast<int>(enStatusCharaType::Max));
	for (unsigned int file = 0; file < m_pCStatusFileNumber.size(); file++) {
		m_pCStatusFileNumber[file] = nullptr;
		m_pCStatusFileNumber[file] = new CFileNumber;
	}
}

//====================================.
//		解放処理関数.
//====================================.
void CFileResource::Release()
{
	//ステータスファイル読み込みの解放処理.
	for (int file = m_pCStatusFileNumber.size() - 1; file >= 0; file--) {
		SAFE_DELETE(m_pCStatusFileNumber[file]);
	}
	//マップチップのファイル読み込みの解放処理.
	for (int file = m_pCStageFileNumber.size() - 1; file >= 0; file--) {
		SAFE_DELETE(m_pCStageFileNumber[file]);
	}
}

//=================================.
//	ステージ読み込み処理関数.
//=================================.
void CFileResource::StageLoad()
{
	//ファイルパス.
	std::vector<std::string> m_FileName = {
		//オブジェクトマップ.
		"Data\\File\\StageFile\\ObjectMap\\TestNum_Part1.csv",
		"Data\\File\\StageFile\\ObjectMap\\TestNum_Part2.csv",
		"Data\\File\\StageFile\\ObjectMap\\TestNum_Part3.csv",

		//"Data\\File\\StageFile\\ObjectMap\\Second_Day\\TestNum_Part1.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Second_Day\\TestNum_Part2.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Second_Day\\TestNum_Part3.csv",

		//"Data\\File\\StageFile\\ObjectMap\\Third_Day\\TestNum_Part1.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Third_Day\\TestNum_Part2.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Third_Day\\TestNum_Part3.csv",

		//人.
		"Data\\File\\StageFile\\PeopleOrder\\TestPeopleNum_FirstDay.csv",
		"Data\\File\\StageFile\\PeopleOrder\\TestPeopleNum_SecondDay.csv",
		"Data\\File\\StageFile\\PeopleOrder\\TestPeopleNum_ThirdDay.csv",
		//お化けマップ.
		"Data\\File\\StageFile\\GhostMap\\TestGhostNum_Part1.csv",
		"Data\\File\\StageFile\\GhostMap\\TestGhostNum_Part2.csv",
		"Data\\File\\StageFile\\GhostMap\\TestGhostNum_Part3.csv",

		//"Data\\File\\StageFile\\GhostMap\\Second_Day\\TestGhostNum_Part1.csv",
		//"Data\\File\\StageFile\\GhostMap\\Second_Day\\TestGhostNum_Part2.csv",
		//"Data\\File\\StageFile\\GhostMap\\Second_Day\\TestGhostNum_Part3.csv",
		//
		//"Data\\File\\StageFile\\GhostMap\\Third_Day\\TestGhostNum_Part1.csv",
		//"Data\\File\\StageFile\\GhostMap\\Third_Day\\TestGhostNum_Part2.csv",
		//"Data\\File\\StageFile\\GhostMap\\Third_Day\\TestGhostNum_Part3.csv",
	};

	//ステージのファイルの読み込み処理.
	for (unsigned int file = 0; file < m_FileName.size(); file++) {
		m_pCStageFileNumber[file]->Init(m_FileName[file].c_str());
	}

}

//===================================.
//	ステータス読み込み処理関数.
//===================================.
void CFileResource::StatusLoad()
{
	//ファイルパス.
	std::vector<std::string> m_FileName = {
		"Data\\File\\CharaStatus\\GhostStatus.csv",
		"Data\\File\\CharaStatus\\PeopleStatus.csv",
	};

	//ステータスのファイルの読み込み処理.
	for (int file = 0; file < static_cast<int>(enStatusCharaType::Max); file++) {
		m_pCStatusFileNumber[file]->Init(m_FileName[file].c_str());
	}

}

//===================================.
//	会話文章読み込み処理関数.
//===================================.
void CFileResource::SpeakLoad()
{
	//ファイルパス.
	std::vector<std::string> m_FileName = {
		"Data\\File\\Speak\\Test.csv",
		"Data\\File\\Speak\\SpeakStageNext.csv",
		"Data\\File\\Speak\\TutorialTest.csv",
	};


	//初期化処理関数.
	m_pCSpeakFileString.resize(m_FileName.size());
	for (unsigned int file = 0; file < m_FileName.size(); file++) {
		m_pCSpeakFileString[file].reset(new CFileString());
		m_pCSpeakFileString[file]->Init(m_FileName[file].c_str());
	}
}