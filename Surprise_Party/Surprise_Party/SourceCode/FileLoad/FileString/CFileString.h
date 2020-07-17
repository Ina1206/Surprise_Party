#ifndef CFILE_STRING_H
#define CFILE_STRING_H

#include "..\FileLoadBase\CFileLoad.h"

/************************************
*		文章読み取りクラス.
*********/
class CFileString
	: public CFile
{
public:
	CFileString();
	~CFileString();

	//===================列挙体=======================//.
	enum class enStringType {
		MainString = 0,	//メイン文章.
		SelectString,	//選択文章.
		EmotionNum,		//感情番号.
	};

	//====================関数========================//.
	HRESULT Init(const char*	pFileName);									//初期化処理関数.

	//================情報獲得処理関数================//.
	//ファイルのデータ.
	std::string GetData(const int& column, const enStringType& line) const { return m_veclineData[column][static_cast<int>(line)]; }

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