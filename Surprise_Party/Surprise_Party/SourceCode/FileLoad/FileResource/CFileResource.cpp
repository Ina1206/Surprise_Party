#include "CFileResource.h"

CFileResource::CFileResource()
	: m_pCStageFileNumber	()
	, m_pCStatusFileNumber	()
{
	//�����������֐�.
	Init();
}

CFileResource::~CFileResource()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�ǂݍ��ݏ����֐�.
//=====================================.
void CFileResource::Load()
{
	//�X�e�[�W�ǂݍ��ݏ����֐�.
	StageLoad();

	//�X�e�[�^�X�ǂݍ��ݏ����֐�.
	StatusLoad();

	//��b���ǂݍ��ݏ����֐�.
	SpeakLoad();
}

//=====================================.
//		�����������֐�.
//=====================================.
void CFileResource::Init()
{
	//�S�X�e�[�W�̑�����.
	m_pCStageFileNumber.resize(static_cast<int>(enStageType::Max) * ONETYPE_STAGE_MAX);
	for (unsigned int file = 0; file < m_pCStageFileNumber.size(); file++) {
		m_pCStageFileNumber[file] = nullptr;
		m_pCStageFileNumber[file] = new CFileNumber();
	}

	//�S�X�e�[�^�X�̑�����.
	m_pCStatusFileNumber.resize(static_cast<int>(enStatusCharaType::Max));
	for (unsigned int file = 0; file < m_pCStatusFileNumber.size(); file++) {
		m_pCStatusFileNumber[file] = nullptr;
		m_pCStatusFileNumber[file] = new CFileNumber;
	}
}

//====================================.
//		��������֐�.
//====================================.
void CFileResource::Release()
{
	//�X�e�[�^�X�t�@�C���ǂݍ��݂̉������.
	for (int file = m_pCStatusFileNumber.size() - 1; file >= 0; file--) {
		SAFE_DELETE(m_pCStatusFileNumber[file]);
	}
	//�}�b�v�`�b�v�̃t�@�C���ǂݍ��݂̉������.
	for (int file = m_pCStageFileNumber.size() - 1; file >= 0; file--) {
		SAFE_DELETE(m_pCStageFileNumber[file]);
	}
}

//=================================.
//	�X�e�[�W�ǂݍ��ݏ����֐�.
//=================================.
void CFileResource::StageLoad()
{
	//�t�@�C���p�X.
	std::vector<std::string> m_FileName = {
		//�I�u�W�F�N�g�}�b�v.
		"Data\\File\\StageFile\\ObjectMap\\TestNum_Part1.csv",
		"Data\\File\\StageFile\\ObjectMap\\TestNum_Part2.csv",
		"Data\\File\\StageFile\\ObjectMap\\TestNum_Part3.csv",

		//"Data\\File\\StageFile\\ObjectMap\\Second_Day\\TestNum_Part1.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Second_Day\\TestNum_Part2.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Second_Day\\TestNum_Part3.csv",

		//"Data\\File\\StageFile\\ObjectMap\\Third_Day\\TestNum_Part1.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Third_Day\\TestNum_Part2.csv",
		//"Data\\File\\StageFile\\ObjectMap\\Third_Day\\TestNum_Part3.csv",

		//�l.
		"Data\\File\\StageFile\\PeopleOrder\\TestPeopleNum_FirstDay.csv",
		"Data\\File\\StageFile\\PeopleOrder\\TestPeopleNum_SecondDay.csv",
		"Data\\File\\StageFile\\PeopleOrder\\TestPeopleNum_ThirdDay.csv",
		//�������}�b�v.
		"Data\\File\\StageFile\\GhostMap\\TestGhostNum_Part1.csv",
		"Data\\File\\StageFile\\GhostMap\\TestGhostNum_Part2.csv",
		"Data\\File\\StageFile\\GhostMap\\TestGhostNum_Part3.csv",

		//"Data\\File\\StageFile\\GhostMap\\Second_Day\\TestGhostNum_Part1.csv",
		//"Data\\File\\StageFile\\GhostMap\\Second_Day\\TestGhostNum_Part2.csv",
		//"Data\\File\\StageFile\\GhostMap\\Second_Day\\TestGhostNum_Part3.csv",
		//
		//"Data\\File\\StageFile\\GhostMap\\Third_Day\\TestGhostNum_Part1.csv",
		//"Data\\File\\StageFile\\GhostMap\\Third_Day\\TestGhostNum_Part2.csv",
		//"Data\\File\\StageFile\\GhostMap\\Third_Day\\TestGhostNum_Part3.csv",
	};

	//�X�e�[�W�̃t�@�C���̓ǂݍ��ݏ���.
	for (unsigned int file = 0; file < m_FileName.size(); file++) {
		m_pCStageFileNumber[file]->Init(m_FileName[file].c_str());
	}

}

//===================================.
//	�X�e�[�^�X�ǂݍ��ݏ����֐�.
//===================================.
void CFileResource::StatusLoad()
{
	//�t�@�C���p�X.
	std::vector<std::string> m_FileName = {
		"Data\\File\\CharaStatus\\GhostStatus.csv",
		"Data\\File\\CharaStatus\\PeopleStatus.csv",
	};

	//�X�e�[�^�X�̃t�@�C���̓ǂݍ��ݏ���.
	for (int file = 0; file < static_cast<int>(enStatusCharaType::Max); file++) {
		m_pCStatusFileNumber[file]->Init(m_FileName[file].c_str());
	}

}

//===================================.
//	��b���͓ǂݍ��ݏ����֐�.
//===================================.
void CFileResource::SpeakLoad()
{
	//�t�@�C���p�X.
	std::vector<std::string> m_FileName = {
		"Data\\File\\Speak\\Test.csv",
		"Data\\File\\Speak\\SpeakStageNext.csv",
		"Data\\File\\Speak\\TutorialTest.csv",
	};


	//�����������֐�.
	m_pCSpeakFileString.resize(m_FileName.size());
	for (unsigned int file = 0; file < m_FileName.size(); file++) {
		m_pCSpeakFileString[file].reset(new CFileString());
		m_pCSpeakFileString[file]->Init(m_FileName[file].c_str());
	}
}