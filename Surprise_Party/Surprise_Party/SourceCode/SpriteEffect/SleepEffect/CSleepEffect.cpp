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
	for(unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++){

		static bool flag = false;
		if (GetAsyncKeyState(VK_F1) & 0x0001) {
			if (flag == false) {
				flag = true;
			}
			else {
				flag = false;
			}
		}

		D3DXVECTOR3 vChange;
		if (flag == false) {
			vChange = m_vPos[sprite];
		}
		else {
			vChange = m_vRot[sprite];
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			vChange.x += 0.01f;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			vChange.x -= 0.01f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			vChange.y += 0.01f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			vChange.y -= 0.01f;
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			vChange.z += 0.01f;
		}
		if (GetAsyncKeyState('X') & 0x8000) {
			vChange.z -= 0.01f;
		}

		if (flag == false) {
			m_vPos[sprite] = vChange;
		}
		else {
			m_vRot[sprite] = vChange;
		}

		if (m_bDispFlag[sprite] == false) {
			m_vPos[sprite] = m_vCenterPos + INIT_LOCAL_POS;
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