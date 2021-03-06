#include "CFileResource.h"

/*****************************************
*		ファイル読み込みクラス.
********/
CFileResource::CFileResource()
	: m_pCSpriteLoad		()
	, m_pCStageFileNumber	()
	, m_pCStatusFileNumber	()
	, m_pCSpeakFileString	()
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
	//スプライト読み込み処理.
	SpriteLoad();

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
//	スプライト読み込み処理関数.
//=================================.
void CFileResource::SpriteLoad()
{
	//ファイルパス.
	std::vector<std::string> m_FileName = {
		"Data\\File\\SpriteInfo\\SpriteInform.csv",
		"Data\\File\\SpriteInfo\\SpriteUIInform.csv",
	};

	//スプライト数値読み込み処理.
	for (unsigned int file = 0; file < m_FileName.size(); file++) {
		m_pCSpriteLoad.push_back(std::make_unique<CFileNumber>());
		m_pCSpriteLoad[file]->SetLoadFlag(true);
		m_pCSpriteLoad[file]->Init(m_FileName[file].c_str());
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
		"Data\\File\\StageFile\\ObjectPos.csv",
		//人.
		"Data\\File\\StageFile\\PeopleComeOrder.csv",	
		//お化けマップ.
		"Data\\File\\StageFile\\GhostPos.csv",
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
		"Data\\File\\CharaStatus\\StageStatus.csv",
		"Data\\File\\CharaStatus\\GhostSpeakStatus.csv",
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
		"Data\\File\\Speak\\EndingSpeak.csv",
	};


	//初期化処理関数.
	m_pCSpeakFileString.resize(m_FileName.size());
	for (unsigned int file = 0; file < m_FileName.size(); file++) {
		m_pCSpeakFileString[file].reset(new CFileString());
		m_pCSpeakFileString[file]->Init(m_FileName[file].c_str());
	}
}