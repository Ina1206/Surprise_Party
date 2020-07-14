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

	m_pCBGM.reserve(BGM_MAX);
	InitSound(m_pCBGM, m_stBGMaliasName);

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
#if 0
	if (FAILED(OneceLoadSE())) {
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
}

//=================================================.
//			単発SEの読み込み処理関数.
//=================================================.
HRESULT CSoundResource::OneceLoadSE()
{
#if 0
	//ファイルパス.
	const char m_filename[][256] =
	{
	};

	//エイリアス名の元.
	char m_Sound[][256] =
	{
	};

	//エイリアス名の結合.
	for (int name = 0; name < ALL_SE_MAX; name++) {
		AddAliasName(m_Sound[name / SE_RESEVE], name);
	}


	//作成処理関数.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {

		//範囲外かチェック.
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