#include "CFileNumber.h"

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
	FileInput(pFileName);
	//if (FAILED(DataArrage())) {
	//	return E_FAIL;
	//}

	for (unsigned int splite = 0; splite < m_strLinevec.size(); splite++) {
		if (FAILED(DataSplita(m_strLinevec[splite], ','))) {
			return E_FAIL;
		}
		if (m_lineMax <= 0) {
			m_lineMax = m_strvec.size();
		}
	}

	if (FAILED(DataArrage())) {
		return E_FAIL;
	}

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

		//コンマで区切る.
		while (std::getline(str, filed, delimiter)) {
			//アルファベットと空白以外の文字列を通す.
			if (!(std::any_of(filed.cbegin(), filed.cend(), isalpha) || filed == "")) {
				m_strvec.push_back(filed);
			}
		}

	return S_OK;
}

//========================================.
//		行と列に分けて整理処理関数.
//========================================.
HRESULT	CFileNumber::DataArrage()
{
	//列の最大数.
	m_ColumneMax = static_cast<int>(m_strvec.size()) / m_lineMax;

	m_veclineData.resize(m_ColumneMax);
	for (int column = 0; column < m_ColumneMax; column++) {
		m_veclineData[column].resize(m_lineMax);
	}

	for (int dataNum = 0; dataNum < static_cast<int>(m_strvec.size()); dataNum++) {
		int column	= dataNum / m_lineMax;	//列のデータの要素数.
		int line	= dataNum % m_lineMax;	//行のデータの要素数.

		m_veclineData[column][line] = stof(m_strvec.at(dataNum));
	}

	return S_OK;
}
