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

	//�쐬����SE�̑����v(��ނ��Ƃ�SE�� * SE�̕⌇).
	const int ALL_SE_MAX = SE_TYPE_MAX * SE_RESEVE;

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
		"Data\\Sound\\SE\\Shutter.mp3",					//�V���b�^�[.
		"Data\\Sound\\SE\\MoveCursor.mp3",				//�J�[�\���ړ�.
		"Data\\Sound\\SE\\LimitMoveCursor.mp3",			//�J�[�\������ړ�.
		"Data\\Sound\\SE\\SelectDecide.mp3",			//�I�����艹.
		"Data\\Sound\\SE\\Jump.mp3",					//�W�����v.
		"Data\\Sound\\SE\\Turn.mp3",					//��].

		"Data\\Sound\\SE\\Swet.mp3",					//��.
		"Data\\Sound\\SE\\Question.mp3",				//�͂Ă�.
		"Data\\Sound\\SE\\Rejoice.mp3",					//���.
		"Data\\Sound\\SE\\Bubble.mp3",					//�A.
		"Data\\Sound\\SE\\Font.mp3",					//�t�H���g.

		"Data\\Sound\\SE\\MoveCurtain.mp3",				//�J�[�e���ړ�.
		"Data\\Sound\\SE\\OpenBell.mp3",				//�Ŕ�].

		"Data\\Sound\\SE\\ReturnSelect.mp3",			//�I��������.
		"Data\\Sound\\SE\\AppActSelect.mp3",			//�I�������J��.
		"Data\\Sound\\SE\\FlowerSwing.mp3",				//�Ԃ��h���.
		"Data\\Sound\\SE\\PushSwitchPlaySound.mp3",		//�{�^���������Đ����鉹.
		"Data\\Sound\\SE\\PushSwitch.mp3",				//�{�^����������.
		"Data\\Sound\\SE\\FallDownPicture.mp3",			//�G�悪������.
		"Data\\Sound\\SE\\NotSelect.mp3",				//�I������I�ׂȂ�.
		"Data\\Sound\\SE\\GimmickDecide.mp3",			//�M�~�b�N����.
		"Data\\Sound\\SE\\ReturnFromGimmickSelect.mp3",	//�M�~�b�N�I������.

	};

	const std::string m_Sound[] =
	{
		"Shutter",						//�V���b�^�[.
		"MoveCurosor",					//�J�[�\���ړ�.
		"LimitMoveCursor",				//�J�[�\������ړ�.
		"SelectDecide",					//�I�����艹.
		"Jump",							//�W�����v.
		"Turn",							//��].

		"Swet",							//��.
		"Question",						//�͂Ă�.
		"Redjuice",						//���.
		"Bubble",						//�A.
		"Font",							//�t�H���g.
		
		"MoveCurtain",					//�J�[�e���ړ�.
		"OpenBell",						//�Ŕ�].

		"ReturnSelect",					//�I���������.
		"OpenActSelect",				//�s���I�����J��.
		"FlowerSwing",					//�Ԃ̗h��鉹.
		"PushSwitchPlaySound",			//�{�^���������Đ�.
		"PushSwitch",					//�{�^��������.
		"FallDownPicture",				//�G��𗎂Ƃ�.
		"NotSelect",					//�I������I�ׂȂ�.
		"GimmickDecide",				//�M�~�b�N����.
		"ReturnFromGimmickSelect",		//�M�~�b�N�I������.
	};

	for (unsigned int sound = 0; sound < SE_MAX; sound++) {
		
		//�G�C���A�X���̌�.
		AddAliasName(m_Sound[sound / SE_RESEVE], sound);
		
		//�쐬�����֐�.
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
	//�̈�܂ō쐬����.
	for (unsigned int sound = 0; sound < CSound.capacity(); sound++) {
		CSound.emplace_back(std::make_unique<clsSound>());
		stName.push_back("");
	}
}