#include "CSoundResource.h"
#include <stdio.h>

/**********************************************
*	サウンド読み込みクラス.
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
//		初期化処理関数.
//==================================.
HRESULT CSoundResource::Init(HWND hWnd)
{
	//ウィンドウハンドル取得.
	m_hWnd = hWnd;

	//BGMの初期設定処理.
	m_pCBGM.reserve(BGM_MAX);
	InitSound(m_pCBGM, m_stBGMaliasName);

	//作成するSEの総合計(種類ごとのSE数 * SEの補欠).
	const int ALL_SE_MAX = SE_TYPE_MAX * SE_RESEVE;

	//SEの初期設定処理関数.
	m_pCSE.reserve(ALL_SE_MAX);
	InitSound(m_pCSE, m_stSEaliasName);

	return S_OK;
}

//==================================.
//		読み込み処理関数.
//==================================.
HRESULT CSoundResource::Load()
{
	//SEの読み込み処理関数.
	if (FAILED(LoadSE())) {
		_ASSERT_EXPR(false, L"SEの読み込み失敗.");
		return E_FAIL;
	}

	//BGMの読み込み処理関数.
	if (FAILED(LoadBGM())) {
		_ASSERT_EXPR(false, L"BGMの読み込み失敗");
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		解放処理関数.
//==================================.
HRESULT CSoundResource::Release()
{

	return S_OK;
}

//==================================.
//		作成処理関数.
//==================================.
HRESULT CSoundResource::Create(	const std::string& pfilename, std::unique_ptr<clsSound>& pCSound, const std::string& paliasname)
{
	//音の読み込み.
	if (FAILED(pCSound->Open(pfilename.c_str(), paliasname, m_hWnd))) {
		return E_FAIL;
	}
	return S_OK;
}

//==================================.
//		エイリアス名の結合.
//==================================.
void CSoundResource::AddAliasName(const std::string& alias_name, const int& name)
{
	//エイリアス名と番号の結合.
	const std::string AddName = alias_name + std::to_string(name % SE_RESEVE);
	m_stSEaliasName[name] = AddName;
}

//=================================================.
//			SEの読み込み処理関数.
//=================================================.
HRESULT CSoundResource::LoadSE()
{

	const unsigned int SE_MAX = m_pCSE.size();

	//ファイルパス.
	const std::string m_filename[] =
	{
		"Data\\Sound\\SE\\Shutter.mp3",					//シャッター.
		"Data\\Sound\\SE\\MoveCursor.mp3",				//カーソル移動.
		"Data\\Sound\\SE\\LimitMoveCursor.mp3",			//カーソル上限移動.
		"Data\\Sound\\SE\\SelectDecide.mp3",			//選択決定音.
		"Data\\Sound\\SE\\Jump.mp3",					//ジャンプ.
		"Data\\Sound\\SE\\Turn.mp3",					//回転.

		"Data\\Sound\\SE\\Font.mp3",					//フォント.
		"Data\\Sound\\SE\\FontSkip.mp3",				//フォントスキップ.
		"Data\\Sound\\SE\\NextString.mp3",				//次の文章.

		"Data\\Sound\\SE\\Swet.mp3",					//汗.
		"Data\\Sound\\SE\\Question.mp3",				//はてな.
		"Data\\Sound\\SE\\Rejoice.mp3",					//喜び.
		"Data\\Sound\\SE\\Bubble.mp3",					//泡.
		"Data\\Sound\\SE\\GoodHumor.mp3",				//上機嫌.

		"Data\\Sound\\SE\\CurtainMove.mp3",				//カーテン移動.
		"Data\\Sound\\SE\\OpenBell.wav",				//看板回転.

		"Data\\Sound\\SE\\ReturnSelect.mp3",			//選択肢閉じる.
		"Data\\Sound\\SE\\AppActSelect.mp3",			//選択肢を開く.
		"Data\\Sound\\SE\\FlowerSwing.mp3",				//花が揺れる.
		"Data\\Sound\\SE\\PushSwitchSound.mp3",			//ボタンを押し再生する音.
		"Data\\Sound\\SE\\PushSwitch.mp3",				//ボタンを押す音.
		"Data\\Sound\\SE\\FallDownPicture.mp3",			//絵画が落ちる.
		"Data\\Sound\\SE\\NotSelect.mp3",				//選択肢を選べない.
		"Data\\Sound\\SE\\GimmickDecide.mp3",			//ギミック決定.
		"Data\\Sound\\SE\\ReturnFromGimmickSelect.mp3",	//ギミック選択解除.
		"Data\\Sound\\SE\\GhostGimmickMove.mp3",		//お化けとギミック移動.
		"Data\\Sound\\SE\\GhostGimmickSelectLimit.mp3",	//お化けとギミック選択上限.

		"Data\\Sound\\SE\\ManShout.mp3",				//男性の叫び声.
		"Data\\Sound\\SE\\WomanShout.mp3",				//女性の叫び声.

		"Data\\Sound\\SE\\Extension.mp3",				//延長歓声.
		"Data\\Sound\\SE\\Stump.mp3",					//スタンプ.

		"Data\\Sound\\SE\\EmdingSurpriseString.mp3",	//エンディング文字.
		"Data\\Sound\\SE\\LowString.mp3",				//低評価文字.
		"Data\\Sound\\SE\\IntermediateString.mp3",		//中間評価文字.
		"Data\\Sound\\SE\\HightString.mp3",				//高評価文字.

		"Data\\Sound\\SE\\Floating.mp3",				//浮遊.
		"Data\\Sound\\SE\\JumpSNS.mp3",					//SNSへ飛ぶ.

		"Data\\Sound\\SE\\PauseButton.mp3",				//ポーズボタン.

		"Data\\Sound\\SE\\Skip.mp3",					//スキップ.
	};

	const std::string m_Sound[] =
	{
		"Shutter",						//シャッター.
		"MoveCurosor",					//カーソル移動.
		"LimitMoveCursor",				//カーソル上限移動.
		"SelectDecide",					//選択決定音.
		"Jump",							//ジャンプ.
		"Turn",							//回転.

		"Font",							//フォント.
		"FontSkip",						//フォントスキップ.
		"NextStrign",					//次の文章.

		"Swet",							//汗.
		"Question",						//はてな.
		"Redjuice",						//喜び.
		"Bubble",						//泡.
		"GoodHumor",					//上機嫌.
		
		"MoveCurtain",					//カーテン移動.
		"OpenBell",						//看板回転.

		"ReturnSelect",					//選択肢を閉じる.
		"OpenActSelect",				//行動選択を開く.
		"FlowerSwing",					//花の揺れる音.
		"PushSwitchPlaySound",			//ボタンを押し再生.
		"PushSwitch",					//ボタンを押す.
		"FallDownPicture",				//絵画を落とす.
		"NotSelect",					//選択肢を選べない.
		"GimmickDecide",				//ギミック決定.
		"ReturnFromGimmickSelect",		//ギミック選択解除.
		"GhostGimmickMove",				//お化けとギミック移動.
		"GhostGimmickSelectLimit",		//お化けとギミック選択上限.

		"ManShout",						//男性の叫び声.
		"WomanShout",					//女性の叫び声.

		"Extension",					//歓声.
		"Stump",						//スタンプ.

		"EndingSurprise",				//エンディング文字.
		"LowString",					//低評価文字.
		"Intermediate",					//中間評価文字.
		"HightString",					//高評価文字.

		"Floating",						//浮遊.
		"JumpSNS",						//SNSへ飛ぶ.

		"PauseButton",					//ポーズボタン.

		"Skip",							//スキップ.
	};

	for (unsigned int sound = 0; sound < SE_MAX; sound++) {
		
		//エイリアス名の元.
		AddAliasName(m_Sound[sound / SE_RESEVE], sound);
		
		//作成処理関数.
		if (FAILED(Create(m_filename[sound / SE_RESEVE], m_pCSE[sound], m_stSEaliasName[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}

//===============================================.
//		BGMの読み込み処理関数.
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
	//領域まで作成する.
	for (unsigned int sound = 0; sound < CSound.capacity(); sound++) {
		CSound.emplace_back(std::make_unique<clsSound>());
		stName.push_back("");
	}
}