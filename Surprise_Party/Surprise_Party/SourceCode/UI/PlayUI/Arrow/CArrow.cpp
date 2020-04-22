#include "CArrow.h"

/**********************************************
*			���N���X.
*****************/
CArrow::CArrow()
	: m_vCenterPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_UsingArrowFlag	(0)
	, m_fDistance		(0.0f)
	, m_fDirect			(0)
	, m_fMoveSpeed		(0.0f)
{
	//�����������֐�.
	Init();
}

CArrow::~CArrow()
{
	//��������֐�.
	Release();
}

//=============================================.
//		�X�V�����֐�.
//=============================================.
void CArrow::Update()
{
	//���W�ݒ菈���֐�.
	SettingPos();
	
	//���ړ������֐�.
	MoveArrow();
}

//=============================================.
//		���W�ݒ菈���֐�.
//=============================================.
void CArrow::SettingPos()
{
	const unsigned int BOTH_ARROW_FLAG = USING_LEFT_FLAG | USING_RIGHT_FLAG;
	if (m_UsingArrowFlag == BOTH_ARROW_FLAG) {
		for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
			m_vUIPos[arrow] = BASE_POS;
			m_vUIPos[arrow].x += ARROW_WIDTH * arrow;
		}
		return;
	}
	
	//���W������.
	const SPRITE_STATE ArrowState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Arrow);
	for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
		m_vUIPos[arrow] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vUIPos[arrow].x -= ArrowState.Disp.w;
	}

	if (m_UsingArrowFlag & USING_LEFT_FLAG) {
		m_vUIPos[LEFT_ARROW_NUM] = m_vCenterPos;
		return;
	}

	if (m_UsingArrowFlag & USING_RIGHT_FLAG) {
		m_vUIPos[RIGHT_ARROW_NUM] = m_vCenterPos;
	}


}

//=============================================.
//		�����������֐�.
//=============================================.
void CArrow::Init()
{
	for (int arrow = 0; arrow < ARROW_MAX; arrow++) {
		m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Arrow));
	}
	//�����ݒ�֐�.
	SettingInit();

	m_vUIRot[LEFT_ARROW_NUM].y = LEFT_ARROW_ROT_Y;

	m_fDirect = MOVE_OUTSIDE_DIRECT;
}

//=============================================.
//		��������֐�.
//=============================================.
void CArrow::Release()
{

}

//=============================================.
//		���ړ������֐�.
//=============================================.
void CArrow::MoveArrow()
{
	//�ړ����x������������.
	m_fMoveSpeed += ACCELERATION_SPEED * m_fDirect;
	m_fDistance += m_fMoveSpeed;

	if (m_fDirect > 0.0f) {
		if (m_fDistance > MOVE_DISTANCE_MAX) {
			m_fDirect *= CHANGE_DIRECT;
			m_fDistance = MOVE_DISTANCE_MAX;
		}
	}
	else {
		if (m_fDistance < MOVE_DISTANCE_MIN) {
			m_fDirect *= CHANGE_DIRECT;
			m_fDistance = MOVE_DISTANCE_MIN;
			m_fMoveSpeed = 0.0f;
		}
	}

	//���̎�ނ��Ƃ̈ړ�����.
	if (m_UsingArrowFlag & USING_LEFT_FLAG) {
		m_vUIPos[LEFT_ARROW_NUM].x += m_fDistance * MOVE_LEFT_DIRECT;
	}
	if (m_UsingArrowFlag & USING_RIGHT_FLAG) {
		m_vUIPos[RIGHT_ARROW_NUM].x += m_fDistance;
	}
}