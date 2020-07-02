#include "CFileNumber.h"

/*************************************
*	数値のファイル読み込みクラス.
*********/
CFileNumber::CFileNumber()
	: m_strvec		()
	, m_veclineData	()
	, m_lineMax		(0)
	, m_ColumneMax	(0)
{

}

CFileNumber::~CFileNumber()
{

}

//========================================.
//		初期化処理関数.
//========================================.
HRESULT CFileNumber::Init(const char* pFileName)
{
	//ファイル読み込みまとめ処理関数.
	FileInput(pFileName);

	for (unsigned int splite = 0; splite < m_strLinevec.size(); splite++) {
		//データ分解処理関数.
		if (FAILED(DataSplita(m_strLinevec[splite], ','))) {
			return E_FAIL;
		}
	}

	//行と列に分けて整理処理関数.
	if (FAILED(DataArrage())) {
		return E_FAIL;
	}

	//閉じる処理関数.
	Close();

	return S_OK;
}

//========================================.
//		データ分解処理関数.
//========================================.
HRESULT CFileNumber::DataSplita(std::string input, char delimiter)
{
	std::stringstream str(input);
	std::string filed;
	int LineMax = 0;

	//コンマで区切る.
	while (std::getline(str, filed, delimiter)) {
		//アルファベットと空白以外の文字列を通す.
		if (!(std::any_of(filed.cbegin(), filed.cend(), isalpha) || filed == "")) {
			m_strvec.push_back(filed);
			LineMax++;
		}
	}
	m_lineMax.push_back(LineMax);

	return S_OK;
}

//========================================.
//		行と列に分けて整理処理関数.
//========================================.
HRESULT	CFileNumber::DataArrage()
{
	//列の最大数.
	m_ColumneMax = static_cast<int>(m_strLinevec.size());

	m_veclineData.resize(m_ColumneMax);
	for (int column = 0; column < m_ColumneMax; column++) {
		m_veclineData[column].resize(m_lineMax[column]);
	}

	int column	= 0;	//列のデータの要素数.
	int line	= 0;	//行のデータの要素数.
	
	for (int dataNum = 0; dataNum < static_cast<int>(m_strvec.size()); dataNum++) {
		if (m_lineMax[column] <= line) {
			line = 0;
			column++;
		}

		m_veclineData[column][line] = stof(m_strvec.at(dataNum));
		line++;
	}

	return S_OK;
}
