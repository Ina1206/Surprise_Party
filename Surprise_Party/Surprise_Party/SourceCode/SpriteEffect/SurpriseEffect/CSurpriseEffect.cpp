#include "CSurpriseEffect.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
CSurpriseEffect::CSurpriseEffect()
	: m_DispCnt			(0)
	, m_bAllDispFlag	(false)
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


	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bAllDispFlag == false) {
			//�\���I��.
			//�����l�ݒ�.
			SettingDefaultValue(sprite);
			m_DispCnt = 0;
			continue;
		}

		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite)) {
				m_bAllDispFlag = false;
			}
			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		//�\�����菈��
		if (m_DispCnt <= 3) {
			AppeartJudgement(sprite);
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

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}

	m_fScalingSpeed = 0.08f;
	m_fAlphaSpeed = 0.08f;
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
	m_vRot[num].y = 3.1f;

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
	const float angle = 120.0f + (30.0f * (num % 3));
	//���W�A��.
	const float radian = angle / CIRCLE_HALF_ANGLE * PI;

	m_fDistance[num] += 0.005f;

	m_vPos[num].x += (cos(radian) * m_fDistance[num]) ;
	m_vPos[num].y += (sin(radian) * m_fDistance[num]) ;

}