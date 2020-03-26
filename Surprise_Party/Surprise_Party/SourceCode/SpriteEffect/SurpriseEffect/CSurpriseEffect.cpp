#include "CSurpriseEffect.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
CSurpriseEffect::CSurpriseEffect()
	: m_DispCnt	(0)
{
	//�����������֐�.
	Init();
}

CSurpriseEffect::~CSurpriseEffect()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CSurpriseEffect::Update()
{
	if (m_bAllDispFlag == false) {
		return;
	}

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite)) {
				//�\���I��.
				//�����l�ݒ�.
				SettingDefaultValue(sprite);
				m_bAllDispFlag = false;
				m_DispCnt = 0;
			}
			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		//�\�����菈��
		if (m_DispCnt <= 3) {
			AppeartJudgement(sprite);
			//if (m_DispCnt >= 3) {
			//	m_DispCnt = 0;
			//	m_DispTime = 0;
			//}
		}

	}
}

//=============================================.
//		�Đ��J�n�����������������֐�.
//=============================================.
void CSurpriseEffect::PlayStartInit(const int& num)
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
		m_fDistance[sprite] = 0.0f;
	}
}

//=============================================.
//		�����������֐�.
//=============================================.
void CSurpriseEffect::Init()
{
	m_pCSprite.resize(3);
	m_fDistance.resize(m_pCSprite.size());
	SettingElementsCount();

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);

		if (sprite % 2 == 1) {
			m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Shock);
			continue;
		}

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
}

//==============================================.
//		��������֐�.
//==============================================.
void CSurpriseEffect::Release()
{

}

//===============================================.
//		�\�����菈���֐�.
//===============================================.
void CSurpriseEffect::AppeartJudgement(const int& num)
{
	//�����ʒu.
	m_vPos[num] = m_vCenterPos;
	//�p�x.
	m_vRot[num].z = -60.0f + ((num % 3)* 60.0f);

	m_fDistance[num] = 0.0f;

	m_DispCnt++;
	m_bDispFlag[num] = true;

}

//================================================.
//		�ړ������֐�.
//================================================.
void CSurpriseEffect::Move(const int& num)
{
	//�p�x.
	const float angle = 60.0f + (30.0f * (num % 3));
	//���W�A��.
	const float radian = angle / CIRCLE_HALF_ANGLE * PI;

	m_fDistance[num] += 0.02f;

	m_vPos[num].x = cos(radian) + m_fDistance[num] + m_vCenterPos.x;
	m_vPos[num].y = sin(radian) + m_fDistance[num] + m_vCenterPos.y;

}