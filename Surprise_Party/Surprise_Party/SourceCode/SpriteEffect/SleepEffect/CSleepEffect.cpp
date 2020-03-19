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
	m_DispTime++;

	for(unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++){
		if (m_bDispFlag[sprite] == true) {

			//�g�k���ߏ���.
			if (ScalingTransparent(sprite) == true) {
				//�\���I������.
				m_bDispFlag[sprite] = false;
				//�����l�ݒ菈���֐�.
				SettingDefaultValue(sprite);
			}

			//�ړ�����.
			Move(sprite);
			continue;
		}

		if (m_DispTime >= APPEAR_TIME) {
			//�\�����f�����֐�.
			AppeartJudgement(sprite);
			m_DispTime = 0;
		}
	}
}

//===================================.
//		�����������֐�.
//===================================.
void CSleepEffect::Init()
{
	//�v�f���ݒ菈��.
	m_pCSprite.resize(ALL_SPRITE_MAX);
	SettingElementsCount();

	//�����l�ݒ�.
	for (int sprite = 0; sprite < ALL_SPRITE_MAX; sprite++) {
		SettingDefaultValue(sprite);
		m_DispTime = APPEAR_TIME;
		//����̐����}�[�N.
		if (sprite % LINE_MAX == SLEEP_Z_NUM) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::SleepZ);
			continue;
		}
		//�A.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Bubble);
	}

	m_fAlphaSpeed = ALPHA_SPEED;
	m_fScalingSpeed = SCALE_SPEED;
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
	//�\���J�n�ʒu�ɐݒ�.
	if (m_bDispFlag[num] == false) {
		m_vPos[num] = m_vCenterPos + INIT_LOCAL_POS;
	}

	m_bDispFlag[num] = true;
}

//=======================================.
//		�ړ������֐�.
//=======================================.
void CSleepEffect::Move(const int& num)
{
	const float angle = START_ANGLE - ((num % LINE_MAX) * ANGLE_WIDTH);	//�p�x.
	const float rad = (angle) / CIRCLE_HALF_ANGLE * PI;					//���W�A��.
	//�ړ�.
	m_vPos[num].y += sin(rad) * MOVE_SPEED;
	m_vPos[num].x -= cos(rad) * MOVE_SPEED;

	//����}�[�N�͏I��.
	if (num % LINE_MAX == SLEEP_Z_NUM) {
		return;
	}

	//�A�̂ݗh���.
	m_fAngle[num] += ANGLE_MOVE_SPEED;
	m_vPos[num].x -= cos(m_fAngle[num] / CIRCLE_HALF_ANGLE * PI) * MOVE_SPEED;

}

