#ifndef FILELOAD
#define FILELOAD
#include "..\..\Global.h"
#include <fstream>	
#include <sstream> 
#include <cctype>
#include <algorithm>


/***********************************
*		ファイル読み込みクラス.
**/
class CFile {
public:
	CFile();
	virtual ~CFile();

	//========関数==========//.
	void FileInput(const char* filename);					//ファイル読み込みまとめ.
	void Close();											//ファイルを閉じる処理関数.

	//=====情報取得関数=====//.
	int GetLineDataMax() { return line_max; }				//１行あたりのデータの最大数.
	int GetColumnDataMax() {
		return static_cast<int>(strvec.size()) / line_max;	//1列当たりのデータの最大数. 
	}
	int GetData(int data_column, int data_line) {
		return stData[data_column].st[data_line];			//それぞれのデータ.
	}
	//一列分のデータ.
	std::string GetLineData(int lineNum) { return m_strLinevec.at(lineNum); }
	int GetColumnMax() { return m_strLinevec.size(); }

protected:
	std::vector<std::string> m_strLinevec;					//ライン区切りでのデータ.

private:
	//==========関数==========//.
	void Load(const char* filename);						//ファイル読み込み処理関数.
	void DataLoad();										//データ読み込み処理関数.

	//=========構造体========//.
	//列と行に分けるための構造体.
	struct STDATA {
		int *st;			//行の中のデータ.
	};
	STDATA *stData;

	//==========変数==========//.
	std::ifstream ifs;										//ファイル.
	std::string m_line;										//読み取った全てのデータ.
	std::vector<std::string> strvec;						//コンマで区切った後のそれぞれのデータ.

	int line_max;											//データの行の最大数.
	int column_max ;										//データの列の最大数.
};
#endif //ifndef FILELOAD.