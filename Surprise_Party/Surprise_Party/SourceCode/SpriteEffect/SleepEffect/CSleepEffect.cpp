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
			//���ߒl�Ƒ傫��.
			m_fAlpha[sprite] += ALPHA_SPEED * m_ChangeAddSub[sprite];
			m_fScale[sprite] += SCALE_SPEED * m_ChangeAddSub[sprite];
			
			if (m_fAlpha[sprite] >= ALPHA_MAX) {
				m_ChangeAddSub[sprite] *= CHANGE_ADD_SUB;
			}

			if (m_fAlpha[sprite] <= ALPHA_MIN) {
				m_bDispFlag[sprite] = false;
				//����������
				m_vPos[sprite] = m_vCenterPos + INIT_LOCAL_POS;
				m_fAlpha[sprite] = ALPHA_MIN;
				m_fScale[sprite] = SCALE_MIN;
				m_ChangeAddSub[sprite] *= CHANGE_ADD_SUB;
				m_fAngle[sprite] = 0.0f;
			}

			//�ړ�����.
			Move(sprite);
			continue;
		}

		if (m_DispCnt >= APPEAR_TIME) {
			//�\�����f�����֐�.
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
	m_fAngle.resize(m_pCSprite.size());
	m_bDispFlag.resize(m_pCSprite.size());
	m_ChangeAddSub.resize(m_pCSprite.size());

	//�����l�ݒ�.
	for (int sprite = 0; sprite < ALL_SPRITE_MAX; sprite++) {
		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fScale[sprite] = SCALE_MIN;
		m_fAlpha[sprite] = ALPHA_MIN;
		m_bDispFlag[sprite] = false;
		m_ChangeAddSub[sprite] = 1;

		//����̐����}�[�N.
		if (sprite % 3 == 1) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::SleepZ);
			continue;
		}
		//�A.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Bubble);
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