#ifndef CFILE_NUMBER_H
#define CFILE_NUMBER_H

#include "..\FileLoadBase\CFileLoad.h"

/*************************************
*	���l�̃t�@�C���ǂݍ��݃N���X.
*********/
class CFileNumber
	: public CFile
{
public:
	CFileNumber();
	~CFileNumber();

	HRESULT Init(const char* pFileName);								//�����������֐�.

	//==============���擾�����֐�==================//.
	float GetDataNum(int column, int line) { return m_veclineData[column][line]; }
	int GetLineMax(const int& column) { return static_cast<int>(m_veclineData[column].size()); }
	//int GetLineMax(const int& column) { return m_lineMax[column]; }
private:
	HRESULT DataArrage();												//�s�Ɨ�ɕ����Đ��������֐�.
	HRESULT DataSplita(std::string input, char delimiter);				//�f�[�^���������֐�.

	std::vector<std::string>		m_strvec;							//�R���}�ŋ�؂镶����.
	std::vector<std::vector<float>>	m_veclineData;						//�s�Ɨ�̃f�[�^.
	std::vector<int>				m_lineMax;							//�񂲂Ƃ̍ő吔.
	int								m_ColumneMax;						//�s�̍ő吔.
};

#endif	//#ifndef CFILE_NUMBER_H.