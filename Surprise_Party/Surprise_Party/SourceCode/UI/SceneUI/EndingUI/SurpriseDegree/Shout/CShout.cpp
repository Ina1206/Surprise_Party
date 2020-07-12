#include "CShout.h"

/*****************************************
*		���уN���X.
********************/
CShout::CShout()
	: m_fAcc		(0.0f)
	, m_JumpCnt		(0)
	, m_BoundFlag	(0)
{
	//�����������֐�.
	Init();
}

CShout::~CShout()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CShout::Update()
{
	if (m_bDisplayAllAtOnce == true) {
		//��C�ɕ\�����鏈���֐�.
		DisplayAllAtOnce();
		return;
	}

	//�ړ������֐�.
	Move();

	//�\�������֐�.
	Disp();

	if (m_JumpCnt >= JUMP_MAX) {
		return;
	}

	if (m_BoundFlag != 0) {
		//�X�v���C�g�̃o�E���h�����֐�.
		BoundSprite();
		return;
	}

	//�W�����v�����֐�.
	Jump();
}

//=========================================.
//		�����������֐�.
//=========================================.
void CShout::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Shout);
	m_vPos = INIT_POS;

	//�d�͂Ɖ����x�̍�����0.0f�ɂȂ�悤��.
	m_fAcc = GRAVITY;
	
	m_JumpCnt = 0;
	m_vEatchSizeScale = EATCH_SCALE_MIN;
}

//==========================================.
//		��������֐�.
//==========================================.
void CShout::Release()
{

}

//==========================================.
//		�ړ������֐�.
//==========================================.
void CShout::Move()
{
	//�X�v���C�g���.
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Shout);
	//�ŏI���W.
	const float	FINISH_POS = FINISH_BASE_POS.x + (SpriteState.Disp.w * (m_DipslayNum - 1));
	//����.
	const float	RATIO = (FINISH_POS - INIT_POS.x) / (FINISH_BASE_POS.x - INIT_POS.x);

	m_vPos.x += MOVE_SPEED * RATIO;
	if (m_vPos.x > FINISH_POS) {
		m_vPos = FINISH_BASE_POS;
		m_vPos.x = FINISH_POS;
		m_bDispFlag = true;
	}
}

//===========================================.
//		�X�v���C�g�̃o�E���h�����֐�.
//===========================================.
void CShout::BoundSprite()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Shout);

	if (m_BoundFlag & BOUND_DOWN_FLAG) {
		m_vEatchSizeScale.y -= BOUND_SPEED;
		m_vPos.y = FINISH_BASE_POS.y + (SpriteState.Disp.h * ( EATCH_SCALE_MAX.y - m_vEatchSizeScale.y));
		if (m_vEatchSizeScale.y <= EATCH_SCALE_MIN.y) {
			m_vEatchSizeScale.y = EATCH_SCALE_MIN.y;
			m_BoundFlag = BOUND_UP_FALG;
		}
		return;
	}

	m_vEatchSizeScale.y += BOUND_SPEED;
	m_vPos.y = FINISH_BASE_POS.y + (SpriteState.Disp.h * ( EATCH_SCALE_MAX.y - m_vEatchSizeScale.y));
	if (m_vEatchSizeScale.y >= EATCH_SCALE_MAX.y) {
		m_vEatchSizeScale.y = EATCH_SCALE_MAX.y;
		m_BoundFlag = 0;
	}
}

//===========================================.
//		�\�������֐�.
//===========================================.
void CShout::Disp()
{
	m_vEatchSizeScale.x += DISP_SPEED;
	if (m_vEatchSizeScale.x > EATCH_SCALE_MAX.x) {
		m_vEatchSizeScale.x = EATCH_SCALE_MAX.x;
		return;
	}

	m_vEatchSizeScale.y += DISP_SPEED;
	if (m_vEatchSizeScale.y > EATCH_SCALE_MAX.y) {
		m_vEatchSizeScale.y = EATCH_SCALE_MAX.y;
	}
}

//===========================================.
//		�W�����v�����֐�.
//===========================================.
void CShout::Jump()
{
	m_fAcc += ACC_ADD_SPEED;

	m_vPos.y += m_fAcc - GRAVITY;
	if (m_vPos.y > FINISH_BASE_POS.y) {
		m_vPos.y = FINISH_BASE_POS.y;
		m_fAcc = 0.0f;
		m_JumpCnt++;

		//�o�E���h����.
		if (m_JumpCnt <= BOUND_MAX) {
			m_BoundFlag = BOUND_DOWN_FLAG;
		}
	}
}

//============================================.
//		��C�ɕ\�����鏈���֐�.
//============================================.
void CShout::DisplayAllAtOnce()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Shout);
	m_vPos = FINISH_BASE_POS;
	m_vPos.x += SpriteState.Disp.w * (m_DipslayNum - 1);
	m_vEatchSizeScale = EATCH_SCALE_MAX;
	m_bDispFlag = true;
}