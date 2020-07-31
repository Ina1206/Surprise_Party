#include <Windows.h>
#include "CFileLoad.h"

/***********************************
*		ファイル読み込みクラス.
**/
//コンストラクタ.
CFile::CFile()
	: stData		(nullptr)
	, ifs			()
	, m_line		()
	, strvec		()
	, m_strLinevec	()
	, line_max		(0)
	, column_max	(0)
{
	stData = nullptr;
}

//デストラクタ.
CFile::~CFile()
{
}

//================================================.
//		ファイル読み込みまとめ処理関数.
//================================================.
void CFile::FileInput(const char* filename) 
{
	//ファイルの読み込み処理関数.
	Load(filename);
	//データ読み込み処理関数.
	DataLoad();
}

//================================================.
//		ファイル読み込み処理関数.
//================================================.
void CFile::Load(const char* filename)
{
	//ファイルの読み込み.
	ifs.open(filename);
	if (!ifs) {
		MessageBox(NULL, "ファイルの読み込み失敗", "Error", MB_OK);
	}
	//strvecの初期化.
	strvec.erase(strvec.cbegin(), strvec.cend());
}

//================================================.
//		データ読み込み処理関数.
//================================================.
void CFile::DataLoad()
{
	//データの数をコンマ区切りで読み込む.
	line_max = 0;
	m_line = "";
	while (std::getline(ifs, m_line))
	{
		m_strLinevec.push_back(m_line);
	}
}

//================================================.
//		ファイルを閉じる処理関数.
//================================================.
void CFile::Close()
{
	//ファイルを閉じる.
	ifs.close();
}
