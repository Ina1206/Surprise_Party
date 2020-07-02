#include "CFileNumber.h"

/*************************************
*	���l�̃t�@�C���ǂݍ��݃N���X.
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
//		�����������֐�.
//========================================.
HRESULT CFileNumber::Init(const char* pFileName)
{
	//�t�@�C���ǂݍ��݂܂Ƃߏ����֐�.
	FileInput(pFileName);

	for (unsigned int splite = 0; splite < m_strLinevec.size(); splite++) {
		//�f�[�^���������֐�.
		if (FAILED(DataSplita(m_strLinevec[splite], ','))) {
			return E_FAIL;
		}
	}

	//�s�Ɨ�ɕ����Đ��������֐�.
	if (FAILED(DataArrage())) {
		return E_FAIL;
	}

	//���鏈���֐�.
	Close();

	return S_OK;
}

//========================================.
//		�f�[�^���������֐�.
//========================================.
HRESULT CFileNumber::DataSplita(std::string input, char delimiter)
{
	std::stringstream str(input);
	std::string filed;
	int LineMax = 0;

	//�R���}�ŋ�؂�.
	while (std::getline(str, filed, delimiter)) {
		//�A���t�@�x�b�g�Ƌ󔒈ȊO�̕������ʂ�.
		if (!(std::any_of(filed.cbegin(), filed.cend(), isalpha) || filed == "")) {
			m_strvec.push_back(filed);
			LineMax++;
		}
	}
	m_lineMax.push_back(LineMax);

	return S_OK;
}

//========================================.
//		�s�Ɨ�ɕ����Đ��������֐�.
//========================================.
HRESULT	CFileNumber::DataArrage()
{
	//��̍ő吔.
	m_ColumneMax = static_cast<int>(m_strLinevec.size());

	m_veclineData.resize(m_ColumneMax);
	for (int column = 0; column < m_ColumneMax; column++) {
		m_veclineData[column].resize(m_lineMax[column]);
	}

	int column	= 0;	//��̃f�[�^�̗v�f��.
	int line	= 0;	//�s�̃f�[�^�̗v�f��.
	
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
