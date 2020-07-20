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

	//�`�悵�Ȃ��Ȃ珈���I��.
	if (m_bRenderFlag == false) {
		return;
	}

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		//�ړ������֐�.
		Move(sprite);

		//�g�k���ߏ����֐�.
		if (ScalingTransparent(sprite) == true) {
			m_bRenderFlag = false;
		}

		//��]�����֐�.
		Rotation(sprite);
	}
}

//======================================.
//		�G�t�F�N�g�J�n�����������֐�.
//======================================.
void CSmokeEffect::PlayStartInit(const int& num)
{
	//�����l�ݒ�.
	SettingDefaultValue(num);
	m_fAngle[num] = INIT_ANGLE;
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
		m_fAngle[SpriteNum] = INIT_ANGLE;

		//���E�̕����̐��l�ɕ�����.
		m_MoveDirection[SpriteNum] = -1 + (2 * SpriteNum);
	}
	m_fAlphaSpeed = ALPHA_SPEED;
	m_fScalingSpeed = SCALING_SPEED;
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
	m_fAngle[num] += ANGLE_SPEED;
	if (m_fAngle[num] > ANGLE_MAX) {
		m_fAngle[num] = INIT_ANGLE;
	}
	const float Angle = static_cast<float>(D3DXToRadian(m_fAngle[num]));

	m_vPos[num].x += HORIZON_SPEED * m_MoveDirection[num];
	m_vPos[num].y += sinf(Angle) * VERTICAL_SPEED;

}

//========================================.
//		��]�����֐�.
//========================================.
void CSmokeEffect::Rotation(const int& num)
{
	m_vRot[num].z += ROT_SPEED * m_MoveDirection[num];
}