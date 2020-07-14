#include "CSoundResource.h"
#include <stdio.h>

/**********************************************
*	�T�E���h�ǂݍ��݃N���X.
******/
CSoundResource::CSoundResource()
	: m_hWnd			(nullptr)
	//, m_ppCOneSound	(nullptr)
	//, m_ppOneSoundSE(nullptr)
	//, m_ppCLoopSound	(nullptr)
	//, m_ppLoopSoundSE(nullptr)
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

	m_pCBGM.reserve(BGM_MAX);
	InitSound(m_pCBGM, m_stBGMaliasName);

#if 0
	//���I�m��.
	//�T�E���h�N���X.
	m_ppCOneSound = new clsSound*[ALL_SE_MAX]();
	//SE�̃G�C���A�X��.
	m_ppOneSoundSE = new char*[ALL_SE_MAX]();
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppOneSoundSE[sound] = new char[LENGTH_MAX]();
	}

	//������.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppCOneSound[sound] = nullptr;
	}

	//�T�E���h�N���X.
	m_ppCLoopSound = new clsSound*[LOOP_SE_MAX]();
	//SE�̃G�C���A�X��.
	m_ppLoopSoundSE = new char*[LOOP_SE_MAX]();
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppLoopSoundSE[sound] = new char[LENGTH_MAX]();
		m_ppCLoopSound[sound] = nullptr;
	}
#endif	
	return S_OK;
}

//==================================.
//		�ǂݍ��ݏ����֐�.
//==================================.
HRESULT CSoundResource::Load()
{
#if 0
	if (FAILED(OneceLoadSE())) {
		_ASSERT_EXPR(false, L"�P��SE�̓ǂݍ��ݎ��s.");
		return E_FAIL;
	}
#endif

	if (FAILED(LoadBGM())) {
		_ASSERT_EXPR(false, L"���[�vSE�̓ǂݍ��ݎ��s");
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		��������֐�.
//==================================.
HRESULT CSoundResource::Release()
{
	//���[�vSE.
	//for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
	//	//���ꂼ��̃G�C���A�X���z����.
	//	SAFE_DELETE_ARRAY(m_ppLoopSoundSE[sound]);
	//	//���ꂼ��̃T�E���h�N���X���.
	//	SAFE_DELETE(m_ppCLoopSound[sound]);
	//}
	////�G�C���A�X���z����.
	//SAFE_DELETE_ARRAY(m_ppLoopSoundSE);
	////�T�E���h�N���X���.
	//SAFE_DELETE_ARRAY(m_ppCLoopSound);

	//for (int sound = 0; sound < ALL_SE_MAX; sound++) {
	//	//���ꂼ��̃G�C���A�X���z����.
	//	SAFE_DELETE_ARRAY(m_ppOneSoundSE[sound]);
	//	//���ꂼ��̃T�E���h�N���X���.
	//	SAFE_DELETE(m_ppCOneSound[sound]);
	//}
	////�G�C���A�X���z����.
	//SAFE_DELETE_ARRAY(m_ppOneSoundSE);
	////�T�E���h�N���X�z����.
	//SAFE_DELETE_ARRAY(m_ppCOneSound);

	return S_OK;
}

//==================================.
//		�쐬�����֐�.
//==================================.
HRESULT CSoundResource::Create(	const std::string& pfilename,
								std::unique_ptr<clsSound>& pCSound,
								const std::string& paliasname)
{
	//���̓ǂݍ���.
	if (FAILED(pCSound->Open(pfilename.c_str(), paliasname, m_hWnd))) {
		return E_FAIL;
	}
	return S_OK;
}

//==================================.
//		���ׂ鏈���֐�.
//==================================.
HRESULT CSoundResource::Check(int sound, clsSound* pCSound)
{
	if (sound < static_cast<int>(enSoundSE::Start) || ONE_SE_MAX < sound) {
		return E_FAIL;
	}

	if (pCSound != nullptr) {
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		�G�C���A�X���̌���.
//==================================.
void CSoundResource::AddAliasName(char* alias_name, int name)
{
	//�G�C���A�X���Ɣԍ��̌���.
	char m_Addname[256];	//�ǉ��������.
	char m_SoundName[256];	//�ǉ��O�̃G�C���A�X��.

	//�G�C���A�X���̌����R�s�[.
	strcpy_s(m_SoundName, LENGTH_MAX, alias_name);

	//�G�C���A�X���̔ԍ��ƌ��̖��O�ǉ�.
	sprintf_s(m_Addname, "%d", name % SE_RESEVE);
	strcat_s(m_SoundName, m_Addname);

	//�G�C���A�X���R�s�[.
	//strcpy_s(m_ppOneSoundSE[name], sizeof(m_SoundName), m_SoundName);
}

//=================================================.
//			�P��SE�̓ǂݍ��ݏ����֐�.
//=================================================.
HRESULT CSoundResource::OneceLoadSE()
{
#if 0
	//�t�@�C���p�X.
	const char m_filename[][256] =
	{
	};

	//�G�C���A�X���̌�.
	char m_Sound[][256] =
	{
	};

	//�G�C���A�X���̌���.
	for (int name = 0; name < ALL_SE_MAX; name++) {
		AddAliasName(m_Sound[name / SE_RESEVE], name);
	}


	//�쐬�����֐�.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {

		//�͈͊O���`�F�b�N.
		if (Check(sound / SE_RESEVE, m_ppCOneSound[sound])) {
			return E_FAIL;
		}

		m_ppCOneSound[sound] = new clsSound();

		if (FAILED(Create(sound, m_filename[sound / SE_RESEVE],
				   m_ppCOneSound[sound], m_ppOneSoundSE[sound]))) {
			return E_FAIL;
		}
	}
#endif

	return S_OK;
}

//===============================================.
//		���[�vSE�̓ǂݍ��ݏ����֐�.
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