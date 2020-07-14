#include "CSoundResource.h"
#include <stdio.h>

/**********************************************
*	�T�E���h�ǂݍ��݃N���X.
******/
CSoundResource::CSoundResource()
	: m_hWnd			(nullptr)
	, m_pCSE			()
	, m_stSEaliasName	()
	, m_pCBGM			()
	, m_stBGMaliasName	()
{
}

CSoundResource::~CSoundResource()
{
}

//==================================.
//		�����������֐�.
//==================================.
HRESULT CSoundResource::Init(HWND hWnd)
{
	//�E�B���h�E�n���h���擾.
	m_hWnd = hWnd;

	//BGM�̏����ݒ菈��.
	m_pCBGM.reserve(BGM_MAX);
	InitSound(m_pCBGM, m_stBGMaliasName);

	//SE�̏����ݒ菈���֐�.
	m_pCSE.reserve(ALL_SE_MAX);
	InitSound(m_pCSE, m_stSEaliasName);

	return S_OK;
}

//==================================.
//		�ǂݍ��ݏ����֐�.
//==================================.
HRESULT CSoundResource::Load()
{
	//SE�̓ǂݍ��ݏ����֐�.
	if (FAILED(LoadSE())) {
		_ASSERT_EXPR(false, L"SE�̓ǂݍ��ݎ��s.");
		return E_FAIL;
	}

	//BGM�̓ǂݍ��ݏ����֐�.
	if (FAILED(LoadBGM())) {
		_ASSERT_EXPR(false, L"BGM�̓ǂݍ��ݎ��s");
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		��������֐�.
//==================================.
HRESULT CSoundResource::Release()
{

	return S_OK;
}

//==================================.
//		�쐬�����֐�.
//==================================.
HRESULT CSoundResource::Create(	const std::string& pfilename, std::unique_ptr<clsSound>& pCSound, const std::string& paliasname)
{
	//���̓ǂݍ���.
	if (FAILED(pCSound->Open(pfilename.c_str(), paliasname, m_hWnd))) {
		return E_FAIL;
	}
	return S_OK;
}

//==================================.
//		�G�C���A�X���̌���.
//==================================.
void CSoundResource::AddAliasName(const std::string& alias_name, const int& name)
{
	//�G�C���A�X���Ɣԍ��̌���.
	const std::string AddName = alias_name + std::to_string(name % SE_RESEVE);
	m_stSEaliasName[name] = AddName;
}

//=================================================.
//			SE�̓ǂݍ��ݏ����֐�.
//=================================================.
HRESULT CSoundResource::LoadSE()
{

	const unsigned int SE_MAX = m_pCSE.size();

	//�t�@�C���p�X.
	const std::string m_filename[] =
	{
		"Data\\Sound\\SE\\Jump.mp3",
	};

	//�G�C���A�X���̌�.
	const std::string m_Sound[] =
	{
		"Jump"
	};

	//�G�C���A�X���̌���.
	for (unsigned int name = 0; name < SE_MAX; name++) {
		AddAliasName(m_Sound[name / SE_RESEVE], name);
	}


	//�쐬�����֐�.
	for (unsigned int sound = 0; sound < SE_MAX; sound++) {
		if (FAILED(Create(m_filename[sound / SE_RESEVE], m_pCSE[sound], m_stSEaliasName[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}

//===============================================.
//		BGM�̓ǂݍ��ݏ����֐�.
//===============================================.
HRESULT CSoundResource::LoadBGM()
{
	//�t�@�C����.
	const std::string filename[] =
	{
		"Data\\Sound\\BGM\\Title.mp3",
		"Data\\Sound\\BGM\\GhostSpeakStage.mp3",
		"Data\\Sound\\BGM\\GameMain.mp3",
		"Data\\Sound\\BGM\\Result.mp3",
		"Data\\Sound\\BGM\\LowEvaluationStage.mp3",
		"Data\\Sound\\BGM\\IntermediateEvaluationStage.mp3",
		"Data\\Sound\\BGM\\HightEvaluationStage.mp3",
	};

	//�G�C���A�X��.
	const std::string alias_name[]=
	{
		"Title",
		"GhostSpeakStage",
		"GameMain",
		"Result",
		"LowEvaluationStage",
		"IntermediateEvaluationStage",
		"HightEvaluationStage",
	};

	//�ǂݍ��ݏ���.
	for (int sound = 0; sound < BGM_MAX; sound++) {
		//�G�C���A�X���ݒ�.
		m_stBGMaliasName[sound] = alias_name[sound];

		//�쐬�����֐�.
		if (FAILED(Create(filename[sound], m_pCBGM[sound], m_stBGMaliasName[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}

//================================================.
//		���̏����������֐�.
//================================================.
void CSoundResource::InitSound( std::vector<std::unique_ptr<clsSound>>& CSound,
								std::vector<std::string>& stName)
{
	for (unsigned int sound = 0; sound < CSound.capacity(); sound++) {
		CSound.emplace_back(std::make_unique<clsSound>());
		stName.push_back("");
	}
}