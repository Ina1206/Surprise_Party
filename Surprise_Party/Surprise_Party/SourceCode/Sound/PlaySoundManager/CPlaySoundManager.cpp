#include "CPlaySoundManager.h"

/**************************************
*		サウンド再生管理クラス.
**/
CPlaySoundManager::CPlaySoundManager()
	: m_pCSoundResource	(nullptr)
	, m_pCBGM			()
	, m_bPlayingBGM		()
	, m_PlayingBGMNum	(0)
	, m_PlayingBGMVolume(VOLUME_MAX)
	, m_pCSE			()
	, m_bPlayingSE		()
	, m_PlaySECnt		()
	, m_PlayingSEVolume	()
{
}

CPlaySoundManager::~CPlaySoundManager()
{
}

//=======================================.
//		初期化処理関数.
//=======================================.
HRESULT CPlaySoundManager::Init(HWND hWnd)
{
	//サウンド読み込みクラス.
	m_pCSoundResource = std::make_unique<CSoundResource>();
	//初期化処理関数.
	m_pCSoundResource->Init(hWnd);
	//読み込み処理関数.
	m_pCSoundResource->Load();

	//BGMの初期化処理関数.
	InitBGM();

	//SEの初期化処理関数.
	InitSE();

	return S_OK;
}

//=======================================.
//		更新処理関数.
//=======================================.
void CPlaySoundManager::Update()
{
	//SEの再生.
	for (int se = 0; se < m_pCSoundResource->SE_TYPE_MAX; se++) {
		PlaySE(se);
	}

	//BGMの最大値.
	const int BGM_MAX = static_cast<int>(m_pCBGM.size());
	for (int bgm = 0; bgm < BGM_MAX; bgm++) {
		//BGMの再生.
		PlayBGM(bgm);
	}
	//再生中のBGMの音量調整.
	m_pCBGM[m_PlayingBGMNum]->VolumeConvert(m_PlayingBGMVolume);
}

//=======================================.
//		再生BGMの変更処理関数.
//=======================================.
void CPlaySoundManager::ChangePlayingBGM(const enBGMType& enBGMType) 
{
	m_bPlayingBGM[m_PlayingBGMNum] = false;
	m_bPlayingBGM[static_cast<int>(enBGMType)] = true;
}

//=======================================.
//		BGMの初期化処理関数.
//=======================================.
void CPlaySoundManager::InitBGM()
{
	//BGMの最大数.
	const int BGM_MAX = m_pCSoundResource->GetBGMMax();
	//BGMの初期設定処理.
	for (int bgm = 0; bgm < BGM_MAX; bgm++) {
		//BGMの取得.
		m_pCBGM.push_back(m_pCSoundResource->GetBGM(bgm));
		m_bPlayingBGM.push_back(false);
	}
}

//=======================================.
//		SEの初期化処理関数.
//=======================================.
void CPlaySoundManager::InitSE()
{
	//SEの合計の最大値.
	const int SE_MAX = m_pCSoundResource->GetSEMax();
	for (int se = 0; se < SE_MAX; se++) {
		m_pCSE.push_back(m_pCSoundResource->GetSE(se));

		if (se >= m_pCSoundResource->SE_TYPE_MAX) {
			continue;
		}
		//SE種類ごとの数値の設定.
		m_bPlayingSE.push_back(false);
		m_PlaySECnt.push_back(0);
		m_PlayingSEVolume.push_back(VOLUME_MAX);
	}
}

//=======================================.
//		BGMの再生処理関数.
//=======================================.
void CPlaySoundManager::PlayBGM(const int& bgm)
{
	if (m_bPlayingBGM[bgm] == true) {
		//再生処理.
		if (m_pCBGM[bgm]->IsStopped() == true) {
			//初めに戻す.
			m_pCBGM[bgm]->SeekToStart();
			//再生.
			m_pCBGM[bgm]->Play();
			//再生中のBGM番号の取得.
			m_PlayingBGMNum = bgm;
		}
		return;
	}

	//停止処理.
	if (m_pCBGM[bgm]->IsPlaying() == true) {
		m_pCBGM[bgm]->Stop();
	}

}

//========================================.
//		SEの再生処理関数.
//========================================.
void CPlaySoundManager::PlaySE(const int& se)
{
	if (m_bPlayingSE[se] == true) {
		//全ての中でのSE番号.
		const int SE_NUM = (se * m_pCSoundResource->SE_RESEVE) + m_PlaySECnt[se];
		if (m_pCSE[SE_NUM]->IsStopped() == true) {
			//初めに戻す.
			m_pCSE[SE_NUM]->SeekToStart();
			//再生.
			m_pCSE[SE_NUM]->Play();
			//音量調整.
			m_pCSE[SE_NUM]->VolumeConvert(m_PlayingSEVolume[se]);
			//ずっと鳴らしっぱなし防ぎ.
			m_bPlayingSE[se] = false;
		}

		//同じ種類の中で次のストックのSEへ.
		m_PlaySECnt[se]++;
		if (m_PlaySECnt[se] >= m_pCSoundResource->SE_RESEVE) {
			m_PlaySECnt[se] = 0;
		}
	}
}