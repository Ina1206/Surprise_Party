#include "CArrow.h"

/**********************************************
*			矢印クラス.
*****************/
CArrow::CArrow()
	: m_vCenterPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_UsingArrowFlag	(0)
	, m_fDistance		(0.0f)
	, m_fDirect			(0)
	, m_fMoveSpeed		(0.0f)
{
	//初期化処理関数.
	Init();
}

CArrow::~CArrow()
{
	//解放処理関数.
	Release();
}

//=============================================.
//		更新処理関数.
//=============================================.
void CArrow::Update()
{
	
	for (unsigned int arrow = 0; arrow < m_pCSpriteUI.size(); arrow++) {
		m_vUIPos[arrow] = BASE_POS;
		m_vUIPos[arrow].x += ARROW_WIDTH * arrow;
	}
	
	//矢印移動処理関数.
	MoveArrow();
}

//=============================================.
//		初期化処理関数.
//=============================================.
void CArrow::Init()
{
	for (int arrow = 0; arrow < ARROW_MAX; arrow++) {
		m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Arrow));
	}
	//初期設定関数.
	SettingInit();

	m_vUIRot[LEFT_ARROW_NUM].y = LEFT_ARROW_ROT_Y;

	m_fDirect = MOVE_OUTSIDE_DIRECT;
}

//=============================================.
//		解放処理関数.
//=============================================.
void CArrow::Release()
{

}

//=============================================.
//		矢印移動処理関数.
//=============================================.
void CArrow::MoveArrow()
{
	//移動速度加速減速処理.
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

	//矢印の種類ごとの移動処理.
	if (m_UsingArrowFlag & USING_LEFT_FLAG) {
		m_vUIPos[LEFT_ARROW_NUM].x += m_fDistance * MOVE_LEFT_DIRECT;
	}
	if (m_UsingArrowFlag & USING_RIGHT_FLAG) {
		m_vUIPos[RIGHT_ARROW_NUM].x += m_fDistance;
	}
}