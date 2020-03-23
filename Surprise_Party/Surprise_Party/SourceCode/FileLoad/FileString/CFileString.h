#ifndef CFILE_STRING_H
#define CFILE_STRING_H

#include "..\FileLoadBase\CFileLoad.h"

/************************************
*		���͓ǂݎ�菈���֐�.
*********/
class CFileString
	: public CFile
{
public:
	CFileString();
	~CFileString();

	//====================�֐�========================//.
	HRESULT Init(const char*	pFileName);										//�����������֐�.

	//================���l�������֐�================//.
	std::string GetData(const int& column, const int& line) const { return m_veclineData[column][line]; }

private:
	//====================�֐�========================//.
	HRESULT DataSplita(const std::string& input, const char& delimiter);	//�f�[�^���������֐�.
	HRESULT DataArrage();													//�s�Ɨ�ɕ����鏈���֐�.

	//====================�ϐ�========================//.
	std::vector<std::string>				m_strvec;						//�R���}�ŋ�؂镶����.
	std::vector<std::vector<std::string>>	m_veclineData;					//�s�Ɨ�̃f�[�^.
	int										m_lineMax;						//��̍ő吔.
	int										m_ColumneMax;					//�s�̍ő吔.

};

#endif	//#ifndef CFILE_STRING_H.