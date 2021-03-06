#ifndef CFILE_NUMBER_H
#define CFILE_NUMBER_H

#include "..\FileLoadBase\CFileLoad.h"

/*************************************
*	数値のファイル読み込みクラス.
*********/
class CFileNumber
	: public CFile
{
public:
	CFileNumber();
	~CFileNumber();

	HRESULT Init(const char* pFileName);								//初期化処理関数.

	//==============情報取得処理関数==================//.
	float GetDataNum(int column, int line) { return m_veclineData[column][line]; }
	int GetLineMax(const int& column) { return static_cast<int>(m_veclineData[column].size()); }
	std::string GetFileName(const int& column) { return m_FileName[column]; }
	int GetFileNumColumnMax() { return static_cast<int>(m_lineMax.size()); }

	//==============情報置換処理関数==================//.
	//読み込みフラグ.
	void SetLoadFlag(const bool& bFlag) { m_bLoadFlag = bFlag; }
private:
	HRESULT DataArrage();												//行と列に分けて整理処理関数.
	HRESULT DataSplita(std::string input, char delimiter);				//データ分解処理関数.

	std::vector<std::string>		m_strvec;							//コンマで区切る文字列.
	std::vector<std::vector<float>>	m_veclineData;						//行と列のデータ.
	std::vector<int>				m_lineMax;							//列ごとの最大数.
	int								m_ColumneMax;						//行の最大数.
	bool							m_bLoadFlag;						//読み込みフラグ.
	std::vector<std::string>		m_FileName;							//ファイル名

};

#endif	//#ifndef CFILE_NUMBER_H.