#ifndef CFILE_STRING_H
#define CFILE_STRING_H

#include "..\FileLoadBase\CFileLoad.h"

/************************************
*		文章読み取り処理関数.
*********/
class CFileString
	: public CFile
{
public:
	CFileString();
	~CFileString();

	//====================関数========================//.
	HRESULT Init(const char*	pFileName);										//初期化処理関数.

	//================情報獲得処理関数================//.
	std::string GetData(const int& column, const int& line) const { return m_veclineData[column][line]; }

private:
	//====================関数========================//.
	HRESULT DataSplita(const std::string& input, const char& delimiter);	//データ分解処理関数.
	HRESULT DataArrage();													//行と列に分ける処理関数.

	//====================変数========================//.
	std::vector<std::string>				m_strvec;						//コンマで区切る文字列.
	std::vector<std::vector<std::string>>	m_veclineData;					//行と列のデータ.
	int										m_lineMax;						//列の最大数.
	int										m_ColumneMax;					//行の最大数.

};

#endif	//#ifndef CFILE_STRING_H.