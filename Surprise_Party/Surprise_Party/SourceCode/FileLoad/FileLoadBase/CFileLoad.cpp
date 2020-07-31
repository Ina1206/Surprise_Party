#include <Windows.h>
#include "CFileLoad.h"

/***********************************
*		�t�@�C���ǂݍ��݃N���X.
**/
//�R���X�g���N�^.
CFile::CFile()
	: stData		(nullptr)
	, ifs			()
	, m_line		()
	, strvec		()
	, m_strLinevec	()
	, line_max		(0)
	, column_max	(0)
{
	stData = nullptr;
}

//�f�X�g���N�^.
CFile::~CFile()
{
}

//================================================.
//		�t�@�C���ǂݍ��݂܂Ƃߏ����֐�.
//================================================.
void CFile::FileInput(const char* filename) 
{
	//�t�@�C���̓ǂݍ��ݏ����֐�.
	Load(filename);
	//�f�[�^�ǂݍ��ݏ����֐�.
	DataLoad();
}

//================================================.
//		�t�@�C���ǂݍ��ݏ����֐�.
//================================================.
void CFile::Load(const char* filename)
{
	//�t�@�C���̓ǂݍ���.
	ifs.open(filename);
	if (!ifs) {
		MessageBox(NULL, "�t�@�C���̓ǂݍ��ݎ��s", "Error", MB_OK);
	}
	//strvec�̏�����.
	strvec.erase(strvec.cbegin(), strvec.cend());
}

//================================================.
//		�f�[�^�ǂݍ��ݏ����֐�.
//================================================.
void CFile::DataLoad()
{
	//�f�[�^�̐����R���}��؂�œǂݍ���.
	line_max = 0;
	m_line = "";
	while (std::getline(ifs, m_line))
	{
		m_strLinevec.push_back(m_line);
	}
}

//================================================.
//		�t�@�C������鏈���֐�.
//================================================.
void CFile::Close()
{
	//�t�@�C�������.
	ifs.close();
}
