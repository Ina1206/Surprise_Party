#ifndef CSOUND_RESOURCE_H
#define CSOUND_RESOURCE_H

#include "..\..\Global.h"
#include "..\CSound.h"

//============列挙体=============//.
//ループしない音.
enum class enSEType {
	Shutter,						//シャッター.
	MoveCursor,						//カーソル移動.
	LimitMoveCursor,				//カーソル上限移動.
	SelectDecide,					//選択肢決定.
	Jump,							//ジャンプ.
	Turn,							//回転.

	Font,							//フォント.
	Swet,							//汗.
	Question,						//はてな.
	Redjuice,						//喜び.
	Bubble,							//泡.

	MoveCurtain,					//カーテン移動.
	OpenBell,						//看板回転.

	ReturnSelect,					//選択肢閉じる.
	OpenActSelect,					//選択し開く.
	FlowerSwing,					//花の揺れる音.
	PushSwitchPlaySound,			//ボタンを押し再生される音.
	PushSwitch,						//ボタンを押す.
	FallDownPicture,				//絵画落ちる.
	NotSelect,						//選択肢を選べない.
	GimmickDecide,					//ギミック決定.
	ReturnFromGimmickSelect,		//ギミック選択解除.
	GhostGimmickMove,				//お化けとギミックに移動する音.
	GhostGimmickSelectLimit,		//お化けとギミック選択上限.

	ManShout,						//男性の叫び声.
	WomanShout,						//女性の叫び声.

	ExtensionCheers,				//延長歓声.
	Stump,							//スタンプ.

	Max,							//最大数.
	Start ,							//最初.
};
//ループする音.
enum class enBGMType {
	Title,							//タイトル.
	GhostSpeakStage,				//お化け会話ステージ.
	GameMain,						//ゲームメイン.
	ResultBefore,					//リザルト前ステージ.
	LowEvaluationStage,				//低評価ステージ.
	IntermediateEvaluationStage,	//中間評価ステージ.
	HightEvaluationStage,			//高評価ステージ.

	Max,							//最大数.
	Start = Title,					//最初.
};

/**********************************************
*	サウンド読み込みクラス.
******/
class CSoundResource
{
public:
	CSoundResource();
	~CSoundResource();

	//=============定数==============//.
	const int SE_TYPE_MAX	= static_cast<int>(enSEType::Max);				//種類ごとのSEの最大数.
	const int SE_RESEVE		= 10;											//SEの補欠.
	
	const int BGM_MAX		= static_cast<int>(enBGMType::Max);				//BGMの最大数.

	//=============関数==============//.
	HRESULT Init(HWND hWnd);												//初期化処理関数.
	HRESULT Load();															//読み込み処理関数.

	//情報取得処理関数.
	clsSound* GetSE(const int& SENum) { return m_pCSE[SENum].get(); }		//SEのサウンドクラス.
	clsSound* GetBGM(const int& BGMNum) { return m_pCBGM[BGMNum].get(); }	//BGMのサウンドクラス.
	int GetSEMax() const { return static_cast<int>(m_pCSE.size()); }		//SEの最大数.
	int GetBGMMax() const { return static_cast<int>(m_pCBGM.size()); }		//BGMの最大数.
private:
	
	//=============関数==============//.
	HRESULT Release();														//解放処理関数.
	
	HRESULT Create( const std::string& pfilename, 
					std::unique_ptr<clsSound>& pCSound,
					const std::string& paliasname);							//作成処理関数.
	
	void	AddAliasName(const std::string& alias_name, 
						 const int& name);									//エイリアス名の結合処理関数.												
	HRESULT	LoadSE();														//SEの読み込み処理関数.
	HRESULT LoadBGM();														//ループSEの読み込み処理関数.
	
	void	InitSound( std::vector<std::unique_ptr<clsSound>>& CSound, 
					   std::vector<std::string>& stName);					//音の初期化処理関数.

	//=============変数==============//.
	HWND									m_hWnd;							//ウィンドウハンドル.

	std::vector<std::unique_ptr<clsSound>>	m_pCSE;							//サウンドクラス（SE）.
	std::vector<std::string>				m_stSEaliasName;				//SEの名前エイリアス名.

	std::vector<std::unique_ptr<clsSound>>	m_pCBGM;						//サウンドクラス（BGM）.
	std::vector<std::string>				m_stBGMaliasName;				//BGMのエイリアス名.
};

#endif	//#ifndef CSOUND_RESOURCE_H.