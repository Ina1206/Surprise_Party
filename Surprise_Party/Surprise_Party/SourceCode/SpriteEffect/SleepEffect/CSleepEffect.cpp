#include "CSleepEffect.h"

/********************************************
*		�Q�Ă���G�t�F�N�g�N���X.
****************/
CSleepEffect::CSleepEffect()
{
	//�����������֐�.
	Init();
}

CSleepEffect::~CSleepEffect()
{
	//��������֐�.
	Release();
}

//===================================.
//		�X�V�����֐�.
//===================================.
void CSleepEffect::Update()
{
	m_DispCnt++;

	for(unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++){
		if (m_bDispFlag[sprite] == true) {
			m_vPos[sprite].y += 0.05f;
			m_vPos[sprite].x -= 0.05f;
			continue;
		}

		if (m_DispCnt >= 30) {
			AppeartJudgement(sprite);
			m_DispCnt = 0;
		}
	}
}

//===================================.
//		�����������֐�.
//===================================.
void CSleepEffect::Init()
{
	//�v�f���ݒ�.
	m_pCSprite.resize(ALL_SPRITE_MAX);
	m_vPos.resize(m_pCSprite.size());
	m_vScale.resize(m_pCSprite.size());
	m_vRot.resize(m_pCSprite.size());
	m_fAlpha.resize(m_pCSprite.size());
	m_bDispFlag.resize(m_pCSprite.size());

	//�����l�ݒ�.
	for (int sprite = 0; sprite < ALL_SPRITE_MAX; sprite++) {
		//m_vScale[sprite] = SCALE_MIN;
		//m_fAlpha[sprite] = ALPHA_MIN;
		m_bDispFlag[sprite] = false;
		m_vScale[sprite] = SCALE_MAX;
		m_fAlpha[sprite] = ALPHA_MAX;
		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�A.
		if (sprite < BUBBLE_MAX) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Bubble);
			continue;
		}
		//����̐����}�[�N.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::SleepZ);
	}
}

//====================================.
//		��������֐�.
//====================================.
void CSleepEffect::Release()
{
	for (unsigned int sprite = m_pCSprite.size() - 1; ; sprite--) {
		m_pCSprite[sprite] = nullptr;

		//�����鏈��.
		if(sprite == 0){
			break;
		}
	}
}

//======================================.
//		�\�����f�����֐�.
//======================================.
void CSleepEffect::AppeartJudgement(const int& num)
{
	if (m_bDispFlag[num] == false) {
		m_vPos[num] = m_vCenterPos + INIT_LOCAL_POS;
	}

	m_bDispFlag[num] = true;
}