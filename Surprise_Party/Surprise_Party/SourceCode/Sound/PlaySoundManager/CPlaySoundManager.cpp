#include "CPlaySoundManager.h"

/**************************************
*		�T�E���h�Đ��Ǘ��N���X.
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
//		�����������֐�.
//=======================================.
HRESULT CPlaySoundManager::Init(HWND hWnd)
{
	//�T�E���h�ǂݍ��݃N���X.
	m_pCSoundResource = std::make_unique<CSoundResource>();
	//�����������֐�.
	m_pCSoundResource->Init(hWnd);
	//�ǂݍ��ݏ����֐�.
	m_pCSoundResource->Load();

	//BGM�̏����������֐�.
	InitBGM();

	//SE�̏����������֐�.
	InitSE();

	return S_OK;
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CPlaySoundManager::Update()
{
	//SE�̍Đ�.
	for (int se = 0; se < m_pCSoundResource->SE_TYPE_MAX; se++) {
		PlaySE(se);
	}

	//BGM�̍ő�l.
	const int BGM_MAX = static_cast<int>(m_pCBGM.size());
	for (int bgm = 0; bgm < BGM_MAX; bgm++) {
		//BGM�̍Đ�.
		PlayBGM(bgm);
	}
	//�Đ�����BGM�̉��ʒ���.
	m_pCBGM[m_PlayingBGMNum]->VolumeConvert(m_PlayingBGMVolume);
}

//=======================================.
//		�Đ�BGM�̕ύX�����֐�.
//=======================================.
void CPlaySoundManager::ChangePlayingBGM(const enBGMType& enBGMType) 
{
	m_bPlayingBGM[m_PlayingBGMNum] = false;
	m_bPlayingBGM[static_cast<int>(enBGMType)] = true;
}

//=======================================.
//		BGM�̏����������֐�.
//=======================================.
void CPlaySoundManager::InitBGM()
{
	//BGM�̍ő吔.
	const int BGM_MAX = m_pCSoundResource->GetBGMMax();
	//BGM�̏����ݒ菈��.
	for (int bgm = 0; bgm < BGM_MAX; bgm++) {
		//BGM�̎擾.
		m_pCBGM.push_back(m_pCSoundResource->GetBGM(bgm));
		m_bPlayingBGM.push_back(false);
	}
}

//=======================================.
//		SE�̏����������֐�.
//=======================================.
void CPlaySoundManager::InitSE()
{
	//SE�̍��v�̍ő�l.
	const int SE_MAX = m_pCSoundResource->GetSEMax();
	for (int se = 0; se < SE_MAX; se++) {
		m_pCSE.push_back(m_pCSoundResource->GetSE(se));

		if (se >= m_pCSoundResource->SE_TYPE_MAX) {
			continue;
		}
		//SE��ނ��Ƃ̐��l�̐ݒ�.
		m_bPlayingSE.push_back(false);
		m_PlaySECnt.push_back(0);
		m_PlayingSEVolume.push_back(VOLUME_MAX);
	}
}

//=======================================.
//		BGM�̍Đ������֐�.
//=======================================.
void CPlaySoundManager::PlayBGM(const int& bgm)
{
	if (m_bPlayingBGM[bgm] == true) {
		//�Đ�����.
		if (m_pCBGM[bgm]->IsStopped() == true) {
			//���߂ɖ߂�.
			m_pCBGM[bgm]->SeekToStart();
			//�Đ�.
			m_pCBGM[bgm]->Play();
			//�Đ�����BGM�ԍ��̎擾.
			m_PlayingBGMNum = bgm;
		}
		return;
	}

	//��~����.
	if (m_pCBGM[bgm]->IsPlaying() == true) {
		m_pCBGM[bgm]->Stop();
	}

}

//========================================.
//		SE�̍Đ������֐�.
//========================================.
void CPlaySoundManager::PlaySE(const int& se)
{
	if (m_bPlayingSE[se] == true) {
		//�S�Ă̒��ł�SE�ԍ�.
		const int SE_NUM = (se * m_pCSoundResource->SE_RESEVE) + m_PlaySECnt[se];
		if (m_pCSE[SE_NUM]->IsStopped() == true) {
			//���߂ɖ߂�.
			m_pCSE[SE_NUM]->SeekToStart();
			//�Đ�.
			m_pCSE[SE_NUM]->Play();
			//���ʒ���.
			m_pCSE[SE_NUM]->VolumeConvert(m_PlayingSEVolume[se]);
			//�����Ɩ炵���ςȂ��h��.
			m_bPlayingSE[se] = false;
		}

		//������ނ̒��Ŏ��̃X�g�b�N��SE��.
		m_PlaySECnt[se]++;
		if (m_PlaySECnt[se] >= m_pCSoundResource->SE_RESEVE) {
			m_PlaySECnt[se] = 0;
		}
	}
}