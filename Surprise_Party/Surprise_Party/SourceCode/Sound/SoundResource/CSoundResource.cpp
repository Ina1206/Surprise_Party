#include "CSoundResource.h"
#include <stdio.h>

/**********************************************
*	サウンド読み込みクラス.
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
//		初期化処理関数.
//==================================.
HRESULT CSoundResource::Init(HWND hWnd)
{
	//ウィンドウハンドル取得.
	m_hWnd = hWnd;

	//BGMの初期設定処理.
	m_pCBGM.reserve(BGM_MAX);
	InitSound(m_pCBGM, m_stBGMaliasName);

	//SEの初期設定処理関数.
	m_pCSE.reserve(ALL_SE_MAX);
	InitSound(m_pCSE, m_stSEaliasName);

#if 0
	//動的確保.
	//サウンドクラス.
	m_ppCOneSound = new clsSound*[ALL_SE_MAX]();
	//SEのエイリアス名.
	m_ppOneSoundSE = new char*[ALL_SE_MAX]();
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppOneSoundSE[sound] = new char[LENGTH_MAX]();
	}

	//初期化.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppCOneSound[sound] = nullptr;
	}

	//サウンドクラス.
	m_ppCLoopSound = new clsSound*[LOOP_SE_MAX]();
	//SEのエイリアス名.
	m_ppLoopSoundSE = new char*[LOOP_SE_MAX]();
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppLoopSoundSE[sound] = new char[LENGTH_MAX]();
		m_ppCLoopSound[sound] = nullptr;
	}
#endif	
	return S_OK;
}

//==================================.
//		読み込み処理関数.
//==================================.
HRESULT CSoundResource::Load()
{
#if 1
	if (FAILED(LoadSE())) {
		_ASSERT_EXPR(false, L"単発SEの読み込み失敗.");
		return E_FAIL;
	}
#endif

	if (FAILED(LoadBGM())) {
		_ASSERT_EXPR(false, L"ループSEの読み込み失敗");
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		解放処理関数.
//==================================.
HRESULT CSoundResource::Release()
{
	//ループSE.
	//for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
	//	//それぞれのエイリアス名配列解放.
	//	SAFE_DELETE_ARRAY(m_ppLoopSoundSE[sound]);
	//	//それぞれのサウンドクラス解放.
	//	SAFE_DELETE(m_ppCLoopSound[sound]);
	//}
	////エイリアス名配列解放.
	//SAFE_DELETE_ARRAY(m_ppLoopSoundSE);
	////サウンドクラス解放.
	//SAFE_DELETE_ARRAY(m_ppCLoopSound);

	//for (int sound = 0; sound < ALL_SE_MAX; sound++) {
	//	//それぞれのエイリアス名配列解放.
	//	SAFE_DELETE_ARRAY(m_ppOneSoundSE[sound]);
	//	//それぞれのサウンドクラス解放.
	//	SAFE_DELETE(m_ppCOneSound[sound]);
	//}
	////エイリアス名配列解放.
	//SAFE_DELETE_ARRAY(m_ppOneSoundSE);
	////サウンドクラス配列解放.
	//SAFE_DELETE_ARRAY(m_ppCOneSound);

	return S_OK;
}

//==================================.
//		作成処理関数.
//==================================.
HRESULT CSoundResource::Create(	const std::string& pfilename,
								std::unique_ptr<clsSound>& pCSound,
								const std::string& paliasname)
{
	//音の読み込み.
	if (FAILED(pCSound->Open(pfilename.c_str(), paliasname, m_hWnd))) {
		return E_FAIL;
	}
	return S_OK;
}

//==================================.
//		調べる処理関数.
//==================================.
HRESULT CSoundResource::Check(int sound, std::unique_ptr<clsSound>& pCSound)
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
//		エイリアス名の結合.
//==================================.
void CSoundResource::AddAliasName(char* alias_name, int name)
{
	//エイリアス名と番号の結合.
	char m_Addname[256];	//追加するもの.
	char m_SoundName[256];	//追加前のエイリアス名.

	//エイリアス名の元をコピー.
	strcpy_s(m_SoundName, LENGTH_MAX, alias_name);

	//エイリアス名の番号と元の名前追加.
	sprintf_s(m_Addname, "%d", name % SE_RESEVE);
	strcat_s(m_SoundName, m_Addname);

	//エイリアス名コピー.
	//strcpy_s(m_ppOneSoundSE[name], sizeof(m_SoundName), m_SoundName);

	const std::string AddName = alias_name + std::to_string(name % SE_RESEVE);
	m_stSEaliasName[name] += AddName;
}

//=================================================.
//			単発SEの読み込み処理関数.
//=================================================.
HRESULT CSoundResource::LoadSE()
{

	const unsigned int SE_MAX = m_pCSE.size();
#if 1
	//ファイルパス.
	const std::string m_filename[] =
	{
		"Data\\Sound\\SE\\Jump.mp3",
	};

	//エイリアス名の元.
	char m_Sound[][256] =
	{
		"Jump"
	};

	//エイリアス名の結合.
	for (unsigned int name = 0; name < SE_MAX; name++) {
		AddAliasName(m_Sound[name / SE_RESEVE], name);
	}


	//作成処理関数.
	for (unsigned int sound = 0; sound < SE_MAX; sound++) {
		if (FAILED(Create(m_filename[sound / SE_RESEVE], m_pCSE[sound], m_stSEaliasName[sound]))) {
			return E_FAIL;
		}
	}
#endif

	return S_OK;
}

//===============================================.
//		ループSEの読み込み処理関数.
//===============================================.
HRESULT CSoundResource::LoadBGM()
{
	//ファイル名.
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

	//エイリアス名.
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

	//読み込み処理.
	for (int sound = 0; sound < BGM_MAX; sound++) {
		//エイリアス名設定.
		m_stBGMaliasName[sound] = alias_name[sound];

		//作成処理関数.
		if (FAILED(Create(filename[sound], m_pCBGM[sound], m_stBGMaliasName[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}

//================================================.
//		音の初期化処理関数.
//================================================.
void CSoundResource::InitSound( std::vector<std::unique_ptr<clsSound>>& CSound,
								std::vector<std::string>& stName)
{
	for (unsigned int sound = 0; sound < CSound.capacity(); sound++) {
		CSound.emplace_back(std::make_unique<clsSound>());
		stName.push_back("");
	}
}