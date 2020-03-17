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

	static float m[7];
	for(unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++){
		if (m_bDispFlag[sprite] == true) {
			m[sprite] += 5;
			m_vPos[sprite].y += sin((60.0f - ((sprite % 2) * 40)) / 180.0f * PI) * 0.01f;
			m_vPos[sprite].x -= cos((60.0f - ((sprite % 2) * 40)) / 180.0f * PI) * 0.01f;
			m_vPos[sprite].x -= cos(m[sprite] / 180.0f * PI) * 0.01f;

			m_fAlpha[sprite] += 0.005f * m_ChangeAddSub;
			m_fScale[sprite] += 0.005f * m_ChangeAddSub;
			
			if (m_fAlpha[sprite] >= 1.0f) {
				m_ChangeAddSub *= CHANGE_ADD_SUB;
			}

			if (m_fAlpha[sprite] <= ALPHA_MIN) {
				m_bDispFlag[sprite] = false;
			}
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
	m_fScale.resize(m_pCSprite.size());
	m_vRot.resize(m_pCSprite.size());
	m_fAlpha.resize(m_pCSprite.size());
	m_bDispFlag.resize(m_pCSprite.size());

	//�����l�ݒ�.
	for (int sprite = 0; sprite < ALL_SPRITE_MAX; sprite++) {
		m_fScale[sprite] = SCALE_MIN;
		m_fAlpha[sprite] = ALPHA_MIN;
		m_bDispFlag[sprite] = false;
		//m_vScale[sprite] = SCALE_MAX;
		//m_fAlpha[sprite] = ALPHA_MAX;
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