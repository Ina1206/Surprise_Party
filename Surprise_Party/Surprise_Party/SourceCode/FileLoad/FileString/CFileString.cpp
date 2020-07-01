#include "CFileString.h"

/************************************
*		���͓ǂݎ��N���X.
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
//		�����������֐�.
//=========================================.
HRESULT CFileString::Init(const char* pFileName)
{
	//�t�@�C���̓ǂݍ��݂܂Ƃߏ����֐�.
	FileInput(pFileName);

	for (unsigned int splite = 0; splite < m_strLinevec.size(); splite++) {
		//�f�[�^���������֐�.
		if (FAILED(DataSplita(m_strLinevec[splite], ','))) {
			return E_FAIL;
		}
		if (m_lineMax <= 0) {
			m_lineMax = m_strvec.size();
		}
	}

	//�s�Ɨ�ɕ����鏈���֐�.
	if (FAILED(DataArrage())) {
		return E_FAIL;
	}

	//�t�@�C������鏈���֐�.
	Close();
	
	return S_OK;
}

//=========================================.
//		�f�[�^���������֐�.
//=========================================.
HRESULT CFileString::DataSplita(const std::string& input, const char& delimiter)
{
	std::stringstream str(input);
	std::string filed;

	//�R���}�ŋ�؂�.
	while (std::getline(str, filed, delimiter)) {
		m_strvec.push_back(filed);
	}

	return S_OK;
}

//=========================================.
//		�s�Ɨ�ɕ����鏈���֐�.
//=========================================.
HRESULT CFileString::DataArrage()
{
	//��̍ő吔.
	m_ColumneMax = static_cast<int>(m_strvec.size()) / m_lineMax;

	m_veclineData.resize(m_ColumneMax);
	for (int column = 0; column < m_ColumneMax; column++) {
		m_veclineData[column].resize(m_lineMax);
	}

	for (unsigned int DataNum = 0; DataNum < m_strvec.size(); DataNum++) {
		const int Column = DataNum / m_lineMax;	//��̃f�[�^�̗v�f��.
		const int Line = DataNum % m_lineMax;	//�s�̃f�[�^�̗v�f��.

		m_veclineData[Column][Line] = m_strvec.at(DataNum);
	}

	return S_OK;
}