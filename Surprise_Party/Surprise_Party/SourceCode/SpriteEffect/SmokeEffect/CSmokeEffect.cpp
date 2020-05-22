#include "CSmokeEffect.h"

/*************************************
*		���G�t�F�N�g�N���X.
**********/
CSmokeEffect::CSmokeEffect()
	: m_MoveDirection	(0)
{
	//�����������֐�.
	Init();
}

CSmokeEffect::~CSmokeEffect()
{

}

//======================================.
//		�X�V�����֐�.
//======================================.
void CSmokeEffect::Update()
{
	if (m_bPlayFlag == true) {
		for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
			//�G�t�F�N�g�J�n�����֐�.
			PlayStartInit(sprite);

			//�\�����菈���֐�.
			AppeartJudgement(sprite);
		}
	}

	if (m_bRenderFlag == false) {
		return;
	}

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		//�ړ������֐�.
		Move(sprite);

		//�g�k���ߏ����֐�.
		ScalingTransparent(sprite);
	}
}

//======================================.
//		�G�t�F�N�g�J�n�����������֐�.
//======================================.
void CSmokeEffect::PlayStartInit(const int& num)
{
	//�����l�ݒ�.
	SettingDefaultValue(num);
	m_fAngle[num] = 90.0f;
	//�z�u.
	m_vPos[num] = m_vCenterPos;
}

//======================================.
//		�����������֐�.
//======================================.
void CSmokeEffect::Init()
{
	//�v�f���̐ݒ�.
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	SettingElementsCount();
	m_MoveDirection.resize(m_pCSprite.size());

	//�����l�ݒ�.
	for (unsigned int SpriteNum = 0; SpriteNum < m_pCSprite.size(); SpriteNum++) {
		SettingDefaultValue(SpriteNum);
		m_fAngle[SpriteNum] = 90.0f;

		//���E�̕����̐��l�ɕ�����.
		m_MoveDirection[SpriteNum] = -1 + (2 * SpriteNum);
	}
	m_bRenderFlag = true;
	m_fAlphaSpeed = 0.02f;
	m_fScalingSpeed = 0.02f;
}

//======================================.
//		��������֐�.
//======================================.
void CSmokeEffect::Release()
{

}

//======================================.
//		�\�����菈���֐�.
//======================================.
void CSmokeEffect::AppeartJudgement(const int& num)
{
	m_bRenderFlag = true;
}

//======================================.
//		�ړ������֐�.
//======================================.
void CSmokeEffect::Move(const int& num)
{
	m_fAngle[num] += 0.8f;
	if (m_fAngle[num] > 360.0f) {
		m_fAngle[num] = 90.0f;
	}
	const float Angle = static_cast<float>(D3DXToRadian(m_fAngle[num]));

	m_vPos[num].x += 0.05f * m_MoveDirection[num];
	m_vPos[num].y += sinf(Angle) * 0.05f;

}

//========================================.
//		��]�����֐�.
//========================================.
void CSmokeEffect::Rotation(const int& num)
{

}