#include "CHightEvaluationString.h"

/**********************************************
*		���]�������N���X.
*********************/
CHightEvaluationString::CHightEvaluationString()
	: m_fAcc		(0.0f)
	, m_JumpCnt		(0)
	, m_BoundCnt	(0)
	, m_BoundFlag	(0)
{
	//�����������֐�.
	Init();
}

CHightEvaluationString::~CHightEvaluationString()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CHightEvaluationString::Update()
{
	if (m_bFinishedAllDispFlag == true) {
		return;
	}

	if (m_bDisplayAllAtOnce == true) {
		//��C�ɕ\�����鏈���֐�.
		DisplayAllAtOnce();
		return;
	}

	//�\�������֐�.
	Disp();

	//�ړ������֐�.
	Move();

	if (m_BoundFlag == 0) {
		//�W�����v�����֐�.
		Jump();
		return;
	}

	//�o�E���h�����֐�.
	Bound();
}

//=========================================.
//		�����������֐�.
//=========================================.
void CHightEvaluationString::Init()
{
	m_stSpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
	for (int string = 0; string < m_stSpriteState.Frame.w; string++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::HightEvaluationString));
	}

	//�v�f���̏����������֐�.
	InitElementCount();

	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite] = INIT_POS;
		m_vEvaluationUV[sprite].x = sprite;
		m_vEvaluationScale[sprite] = EATCH_SCALE_MIN;
	}

}

//=========================================.
//		��������֐�.
//=========================================.
void CHightEvaluationString::Release()
{

}

//=========================================.
//		�\�������֐�.
//=========================================.
void CHightEvaluationString::Disp()
{
	//x������.
	m_vEvaluationScale[m_UpdateNum].x += DISP_SPEED;
	if (m_vEvaluationScale[m_UpdateNum].x >= EATCH_SCALE_MAX.x) {
		m_vEvaluationScale[m_UpdateNum].x = EATCH_SCALE_MAX.x;
		//x���̏������I�����Ă�����y���̏����͑��̏����ƃo�b�e�B���O���Ȃ����߂ɏ����I��.
		return;
	}

	//y������.
	m_vEvaluationScale[m_UpdateNum].y += DISP_SPEED;
	if (m_vEvaluationScale[m_UpdateNum].y >= EATCH_SCALE_MAX.y) {
		m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MAX.y;
	}
}

//=========================================.
//		�ړ������֐�.
//=========================================.
void CHightEvaluationString::Move()
{
	//�ŏI�n�_.
	const float	FINISH_POS = FINISH_BASE_POS.x + (m_stSpriteState.Disp.w * m_UpdateNum);
	//����.
	const float RAITO = FINISH_POS / FINISH_BASE_POS.x;

	m_vEvaluationPos[m_UpdateNum].x += MOVE_SPEED * RAITO;

	//�ŏI�n�_�Ɉړ��I��.
	if (m_vEvaluationPos[m_UpdateNum].x >= FINISH_POS) {
		m_vEvaluationPos[m_UpdateNum].x = FINISH_POS;
	}
}

//=========================================.
//		�W�����v�����֐�.
//=========================================.
void CHightEvaluationString::Jump()
{
	//���̕����֕ύX����.
	if (m_JumpCnt >= JUMP_CNT_MAX) {
		//����������.
		m_JumpCnt = 0;
		m_fAcc = 0.0f;
		m_vEvaluationPos[m_UpdateNum] = FINISH_BASE_POS;
		m_vEvaluationPos[m_UpdateNum].x += m_stSpriteState.Disp.w * m_UpdateNum;
		
		//���̕�����.
		m_UpdateNum++;
		if (m_UpdateNum >= static_cast<int>(m_pCEvaluationUI.size())) {
			m_bFinishedAllDispFlag = true;
		}
		return;
	}

	m_fAcc += ADD_ACC_SPEED;

	m_vEvaluationPos[m_UpdateNum].y += m_fAcc - GRAVITY;

	if (m_vEvaluationPos[m_UpdateNum].y > FINISH_BASE_POS.y) {
		//����̂݃o�E���h������.
		if (m_JumpCnt == 0) {
			m_BoundFlag = BOUND_DOWN_FLAG;
		}

		m_fAcc = 0.0f;
		m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y;
		m_JumpCnt++;
	}
}

//=========================================.
//		�o�E���h�����֐�.
//=========================================.
void CHightEvaluationString::Bound()
{
	//�����鏈��.
	if (m_BoundFlag & BOUND_DOWN_FLAG) {
		m_vEvaluationScale[m_UpdateNum].y -= BOUND_SPEED;
		m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y + (m_stSpriteState.Disp.h * (EATCH_SCALE_MAX.y - m_vEvaluationScale[m_UpdateNum].y));
		//�オ�鏈���ɕύX���鏈��.
		if (m_vEvaluationScale[m_UpdateNum].y <= EATCH_SCALE_MIN.y) {
			m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MIN.y;
			m_BoundFlag = BOUND_UP_FALG;
			//���]��������SE.
			m_pCPlaySoundManager->SetPlaySE(enSEType::HightString);
		}
		return;
	}

	//�オ�鏈��.
	m_vEvaluationScale[m_UpdateNum].y += BOUND_SPEED;
	m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y + (m_stSpriteState.Disp.h * (EATCH_SCALE_MAX.y - m_vEvaluationScale[m_UpdateNum].y));
	//�o�E���h�����I��.
	if (m_vEvaluationScale[m_UpdateNum].y >= EATCH_SCALE_MAX.y) {
		m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MAX.y;
		m_BoundFlag = 0;
	}

}

//===========================================.
//		��C�ɕ\�����鏈���֐�.
//===========================================.
void CHightEvaluationString::DisplayAllAtOnce()
{
	//��C�ɍŏI�n�_�܂ňړ����鏈��.
	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite]	= FINISH_BASE_POS;
		m_vEvaluationPos[sprite].x += m_stSpriteState.Disp.w * sprite;
		m_vEvaluationScale[sprite]	= EATCH_SCALE_MAX;
	}
	m_bFinishedAllDispFlag = true;
}