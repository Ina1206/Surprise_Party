#include "CSurpriesDegreeString.h"

/**********************************************
*		�������x���̓N���X.
*******************/
CSurpriseDegreeString::CSurpriseDegreeString()
{
	//�����������֐�.
	Init();
}

CSurpriseDegreeString::~CSurpriseDegreeString()
{
	//��������֐�.
	Release();
}

//==================================================.
//		�X�V�����֐�.
//==================================================.
void CSurpriseDegreeString::Update()
{
	//�ړ������֐�.
	Move();

	//���ߏ����֐�.
	Transparent();
}

//==================================================.
//		�����������֐�.
//==================================================.
void CSurpriseDegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
	m_vEatchSizeScale = EATCH_SCALE_MAX;
	m_vPos = INIT_POS;

	m_fAlpha = ALPHA_MIN;
}

//==================================================.
//		��������֐�.
//==================================================.
void CSurpriseDegreeString::Release()
{

}

//==================================================.
//		�ړ������֐�.
//==================================================.
void CSurpriseDegreeString::Move()
{
	m_vPos.y += MOVE_SPEED;

	if (m_vPos.y >= FINISH_POS.y) {
		m_vPos = FINISH_POS;
	}
}

//===================================================.
//		���ߏ����֐�.
//===================================================.
void CSurpriseDegreeString::Transparent()
{
	//����.
	const float DISTANCE = FINISH_POS.y - INIT_POS.y;
	//����.
	const float TIME = DISTANCE / MOVE_SPEED;
	//���x.
	const float SPEED = ALPHA_MAX / TIME;
	//���ߏ���.
	m_fAlpha += SPEED;
	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_bDispFlag = true;
	}
}