#ifndef CPLAY_SOUND_MANAGER_H
#define CPLAY_SOUND_MANAGER_H

#include "..\SoundResource\CSoundResource.h"

/**************************************
*		サウンド再生管理クラス.
**/
class CPlaySoundManager
{
public:
	CPlaySoundManager();
	~CPlaySoundManager();

	//==================定数==================//.
	const int VOLUME_MAX			= 1000;													//サウンドの最大音量.
	const int VOLUME_STANDERD_MAX	= 1000;

	//=============シングルトン化==============//.
	static CPlaySoundManager* GetSEPlayManagerInstance()
	{
		static CPlaySoundManager s_Instance;
		return &s_Instance;
	}

	//==================関数==================//.
	HRESULT Init(HWND hWnd);							//初期化処理関数.
	void	Update();									//更新処理関数.

	//～情報置換処理関数～.
	//SE再生フラグ.
	void SetPlaySE(const CSoundResource::enSEType enSEType) { m_bPlayingSE[static_cast<int>(enSEType)] = true; }
	//BGM再生フラグ.
	void SetPlayingBGM(const CSoundResource::enBGMType& LoopSE, const bool& flag) { m_bPlayingBGM[static_cast<int>(LoopSE)] = flag;}
	//再生中のBGMの音量.
	void SetPlayingBGMVolume(const int& volume) { m_PlayingBGMVolume = volume; }
	//SEの音量置換処理関数.
	void SetSEVolume(const CSoundResource::enSEType& SoundSE, const int& Volume) { m_PlayingSEVolume[static_cast<int>(SoundSE)] = Volume; }
	//再生BGMの変更処理関数.
	void ChangePlayingBGM(const CSoundResource::enBGMType& BGMTYpe);
private:
	//==================関数==================//.
	void InitBGM();										//BGMの初期化処理関数.
	void InitSE();										//SEの初期化処理関数.
	void PlayBGM(const int& bgm);						//BGMの再生処理関数.
	void PlaySE(const int& se);							//SEの再生処理関数

	//==================変数==================//.
	std::unique_ptr<CSoundResource>	m_pCSoundResource;	//サウンド読み込みクラス.
	
	std::vector<clsSound*>			m_pCBGM;			//BGMのサウンドクラス.
	std::vector<bool>				m_bPlayingBGM;		//BGMの再生フラグ.
	int								m_PlayingBGMNum;	//再生中のBGM番号.
	int								m_PlayingBGMVolume;	//再生中のBGMの音量.

	std::vector<clsSound*>			m_pCSE;				//SEのサウンドクラス.
	std::vector<bool>				m_bPlayingSE;		//SEの再生フラグ.
	std::vector<int>				m_PlaySECnt;		//SE再生カウント.
	std::vector<int>				m_PlayingSEVolume;	//再生中のSEの音量.
};

#endif	//#ifndef CPLAY_SOUND_MANAGER_H.