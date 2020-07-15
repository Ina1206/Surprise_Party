#ifndef CPLAY_SOUND_MANAGER_H
#define CPLAY_SOUND_MANAGER_H

#include "..\SoundResource\CSoundResource.h"

/**************************************
*		�T�E���h�Đ��Ǘ��N���X.
**/
class CPlaySoundManager
{
public:
	CPlaySoundManager();
	~CPlaySoundManager();

	//==================�萔==================//.
	const int VOLUME_MAX			= 1000;													//�T�E���h�̍ő剹��.
	const int VOLUME_STANDERD_MAX	= 1000;

	//=============�V���O���g����==============//.
	static CPlaySoundManager* GetSEPlayManagerInstance()
	{
		static CPlaySoundManager s_Instance;
		return &s_Instance;
	}

	//==================�֐�==================//.
	HRESULT Init(HWND hWnd);							//�����������֐�.
	void	Update();									//�X�V�����֐�.

	//�`���u�������֐��`.
	//SE�Đ��t���O.
	void SetPlaySE(const CSoundResource::enSEType enSEType) { m_bPlayingSE[static_cast<int>(enSEType)] = true; }
	//BGM�Đ��t���O.
	void SetPlayingBGM(const CSoundResource::enBGMType& LoopSE, const bool& flag) { m_bPlayingBGM[static_cast<int>(LoopSE)] = flag;}
	//�Đ�����BGM�̉���.
	void SetPlayingBGMVolume(const int& volume) { m_PlayingBGMVolume = volume; }
	//SE�̉��ʒu�������֐�.
	void SetSEVolume(const CSoundResource::enSEType& SoundSE, const int& Volume) { m_PlayingSEVolume[static_cast<int>(SoundSE)] = Volume; }
	//�Đ�BGM�̕ύX�����֐�.
	void ChangePlayingBGM(const CSoundResource::enBGMType& BGMTYpe);
private:
	//==================�֐�==================//.
	void InitBGM();										//BGM�̏����������֐�.
	void InitSE();										//SE�̏����������֐�.
	void PlayBGM(const int& bgm);						//BGM�̍Đ������֐�.
	void PlaySE(const int& se);							//SE�̍Đ������֐�

	//==================�ϐ�==================//.
	std::unique_ptr<CSoundResource>	m_pCSoundResource;	//�T�E���h�ǂݍ��݃N���X.
	
	std::vector<clsSound*>			m_pCBGM;			//BGM�̃T�E���h�N���X.
	std::vector<bool>				m_bPlayingBGM;		//BGM�̍Đ��t���O.
	int								m_PlayingBGMNum;	//�Đ�����BGM�ԍ�.
	int								m_PlayingBGMVolume;	//�Đ�����BGM�̉���.

	std::vector<clsSound*>			m_pCSE;				//SE�̃T�E���h�N���X.
	std::vector<bool>				m_bPlayingSE;		//SE�̍Đ��t���O.
	std::vector<int>				m_PlaySECnt;		//SE�Đ��J�E���g.
	std::vector<int>				m_PlayingSEVolume;	//�Đ�����SE�̉���.
};

#endif	//#ifndef CPLAY_SOUND_MANAGER_H.