#ifndef CSOUND_RESOURCE_H
#define CSOUND_RESOURCE_H

#include "..\..\Global.h"
#include "..\CSound.h"

/**********************************************
*	サウンド読み込みクラス.
******/
class CSoundResource
{
public:
	CSoundResource();
	~CSoundResource();

	//============列挙体=============//.
	//ループしない音.
	enum class enSoundSE {
		Max,				//最大数.
		Start ,				//最初.
	};
	//ループする音.
	enum class enBGM {
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

	//=============定数==============//.
	const int SE_RESEVE		= 10;											//SEの補欠.

	const int ONE_SE_MAX	= static_cast<int>(enSoundSE::Max);				//単発SEの最大数.
	const int LENGTH_MAX	= 256;											//文字数最大数.
	const int ALL_SE_MAX	= ONE_SE_MAX * SE_RESEVE;						//補欠も合わせたすべての単発SEの最大数.
	
	const int BGM_MAX		= static_cast<int>(enBGM::Max);			//BGMの最大数.

	//=============関数==============//.
	HRESULT Init(HWND hWnd);												//初期化処理関数.
	HRESULT Load();															//読み込み処理関数.
	HRESULT Release();														//解放処理関数.

	//情報取得処理関数.
	//clsSound* GetOneSound(int SoundSE) { return m_ppCOneSound[SoundSE]; }	//単発SEクラス獲得処理関数.
	//clsSound* GetLoopSound(int SoundSE) { return m_ppCLoopSound[SoundSE]; }	//ループSEクラス獲得処理関数.
	clsSound* GetSE(const int& SENum) { return m_pCSE[SENum].get(); }
	clsSound* GetBGM(const int& BGMNum) { return m_pCBGM[BGMNum].get(); }
private:
	//=============関数==============//.
	HRESULT Create(const std::string& pfilename, 
					std::unique_ptr<clsSound>& pCSound,
					const std::string& paliasname);							//作成処理関数.
	HRESULT Check(int sound, clsSound* pCSound);							//調べる処理関数.
	void	AddAliasName(char* alias_name, int name);						//エイリアス名の結合処理関数.												
	HRESULT	OneceLoadSE();													//単発SEの読み込み処理関数.
	HRESULT LoadBGM();														//ループSEの読み込み処理関数.
	void	InitSound(	std::vector<std::unique_ptr<clsSound>>& CSound, 
						std::vector<std::string>& stName);					//音の初期化処理関数.

	//=============変数==============//.
	HWND		m_hWnd;				//ウィンドウハンドル.

	//clsSound**	m_ppCOneSound;		//サウンドクラス.
	//char**		m_ppOneSoundSE;		//SEのエイリアス名.

	//clsSound**	m_ppCLoopSound;		//ループサウンド.
	//char**		m_ppLoopSoundSE;		
	std::vector<std::unique_ptr<clsSound>>	m_pCSE;							//サウンドクラス（SE）.
	std::vector<std::string>				m_stSEaliasName;				//SEの名前エイリアス名.

	std::vector<std::unique_ptr<clsSound>>	m_pCBGM;						//サウンドクラス（BGM）.
	std::vector<std::string>				m_stBGMaliasName;				//BGMのエイリアス名.
};

#endif	//#ifndef CSOUND_RESOURCE_H.