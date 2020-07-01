#include "CFileString.h"

/************************************
*		文章読み取りクラス.
*********/
CFileString::CFileString()
	: m_strvec		()
	, m_veclineData	()
	, m_lineMax		(0)
	, m_ColumneMax	(0)
{

}

CFileString::~CFileString()
{

}

//=========================================.
//		初期化処理関数.
//=========================================.
HRESULT CFileString::Init(const char* pFileName)
{
	//ファイルの読み込みまとめ処理関数.
	FileInput(pFileName);

	for (unsigned int splite = 0; splite < m_strLinevec.size(); splite++) {
		//データ分解処理関数.
		if (FAILED(DataSplita(m_strLinevec[splite], ','))) {
			return E_FAIL;
		}
		if (m_lineMax <= 0) {
			m_lineMax = m_strvec.size();
		}
	}

	//行と列に分ける処理関数.
	if (FAILED(DataArrage())) {
		return E_FAIL;
	}

	//ファイルを閉じる処理関数.
	Close();
	
	return S_OK;
}

//=========================================.
//		データ分解処理関数.
//=========================================.
HRESULT CFileString::DataSplita(const std::string& input, const char& delimiter)
{
	std::stringstream str(input);
	std::string filed;

	//コンマで区切る.
	while (std::getline(str, filed, delimiter)) {
		m_strvec.push_back(filed);
	}

	return S_OK;
}

//=========================================.
//		行と列に分ける処理関数.
//=========================================.
HRESULT CFileString::DataArrage()
{
	//列の最大数.
	m_ColumneMax = static_cast<int>(m_strvec.size()) / m_lineMax;

	m_veclineData.resize(m_ColumneMax);
	for (int column = 0; column < m_ColumneMax; column++) {
		m_veclineData[column].resize(m_lineMax);
	}

	for (unsigned int DataNum = 0; DataNum < m_strvec.size(); DataNum++) {
		const int Column = DataNum / m_lineMax;	//列のデータの要素数.
		const int Line = DataNum % m_lineMax;	//行のデータの要素数.

		m_veclineData[Column][Line] = m_strvec.at(DataNum);
	}

	return S_OK;
}