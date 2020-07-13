#include "CLowEvaluationString.h"

/********************************************
*		��]������UI�����N���X.
*****************/
CLowEvaluationString::CLowEvaluationString()
{
	//�����������֐�.
	Init();
}

CLowEvaluationString::~CLowEvaluationString()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�X�V����.
//===========================================.
void CLowEvaluationString::Update()
{
	if (m_bFinishedAllDispFlag == true) {
		return;
	}

	if (m_bDisplayAllAtOnce == true) {
		//��C�ɕ\�����鏈���֐�.
		DisplayAllAtOnce();
		return;
	}

	if (m_ActFlag & DISP_FLAG) {
		//�ړ��O�̍��W�ݒ菈���֐�.
		MoveBeforePos();
	}


	if (m_ActFlag & MOVE_FLAG) {
		//�ړ������֐�.
		Move();
	}

	if (m_ActFlag & TRANSPARENT_FLAG) {
		//���ߏ����֐�.
		Transparent();
	}

	if (m_ActFlag == 0) {
		m_ActFlag = DISP_FLAG;
		m_UpdateNum++;
		//�S�Ă̕������o���I�������I��.
		if (m_UpdateNum >= static_cast<int>(m_pCEvaluationUI.size())) {
			m_bFinishedAllDispFlag = true;
		}
	}
}

//===========================================.
//		�����������֐�.
//===========================================.
void CLowEvaluationString::Init()
{
	//�X�v���C�g���.
	m_stSpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::LowEvaluationString);
	
	//�X�v���C�gUI�̐ݒ�.
	const int ELEMENT_MAX = static_cast<int>(m_pCResourceManager->GetSpriteUIState(enSpriteUI::LowEvaluationString).Frame.w);
	for (int element = 0; element < ELEMENT_MAX; element++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::LowEvaluationString));
	}

	//�v�f���Ə����l�ݒ菈���@�֐�.
	InitElementCount();

	//�����l�̐ݒ�.
	for (int element = 0; element < ELEMENT_MAX; element++) {
		m_fEvaluationAlpha[element]	= ALPHA_MIN;
		m_vEvaluationPos[element]	= FINSH_BASE_POS;
		m_vEvaluationPos[element].y -= m_stSpriteState.Disp.h;
		m_vEvaluationUV[element].x	+= element;
	}

	//�\���t���O����J�n.
	m_ActFlag = DISP_FLAG;
}

//===========================================.
//		��������֐�.
//===========================================.
void CLowEvaluationString::Release()
{

}

//===========================================.
//		�ړ������֐�.
//===========================================.
void CLowEvaluationString::Move()
{
	//�c�ړ�.
	bool m_bVerticalMoveFinish = false;
	m_vEvaluationPos[m_UpdateNum].y += VERTICAL_MOVE_SPEED;
	if (m_vEvaluationPos[m_UpdateNum].y >= FINSH_BASE_POS.y) {
		m_vEvaluationPos[m_UpdateNum].y = FINSH_BASE_POS.y;
		m_bVerticalMoveFinish = true;
	}

	//���ړ�.
	m_fAngle += ANGLE_SPEED;
	if (m_fAngle >= ANGLE_MAX) {
		m_fAngle = 0.0f;

		//�c�ړ����I�������牡�ړ����I��.
		if (m_bVerticalMoveFinish == true) {
			m_ActFlag &= ~MOVE_FLAG;
			m_ActFlag &= ~TRANSPARENT_FLAG;
		}
	}

	m_vEvaluationPos[m_UpdateNum].x += static_cast<float>(cos(D3DXToRadian(m_fAngle)) * MOVE_HORIZON_WIDTH);
}

//===========================================.
//		���ߏ����֐�.
//===========================================.
void CLowEvaluationString::Transparent()
{
	//�ړ�����.
	const float MOVED_DISTANCE = fabsf(-m_stSpriteState.Disp.h - m_vEvaluationPos[m_UpdateNum].y);
	//�ŏI���W�̋���.
	const float FINISH_MOVE_DINSTANCE = fabsf(-m_stSpriteState.Disp.h - FINSH_BASE_POS.y);
	
	m_fEvaluationAlpha[m_UpdateNum] = ALPHA_MAX * (MOVED_DISTANCE / FINISH_MOVE_DINSTANCE);
	
	if (m_fEvaluationAlpha[m_UpdateNum] >= ALPHA_MAX) {
		m_ActFlag &= ~TRANSPARENT_FLAG;
	}
}

//===========================================.
//		�ړ��O�̍��W�ݒ菈���֐�.
//===========================================.
void CLowEvaluationString::MoveBeforePos()
{
	//x���ꕶ�����Y����.
	m_vEvaluationPos[m_UpdateNum].x += m_stSpriteState.Disp.w * m_UpdateNum;
	//�ړ��Ɠ��ߏ����J�n.
	m_ActFlag = MOVE_FLAG | TRANSPARENT_FLAG;
}

//============================================.
//		��C�ɕ\�����鏈���֐�.
//============================================.
void CLowEvaluationString::DisplayAllAtOnce()
{
	//��C�ɍŏI�n�_�ɂ܂ŕύX.
	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite] = FINSH_BASE_POS;
		//�ꕶ�����Y����.
		m_vEvaluationPos[sprite].x += m_stSpriteState.Disp.h * sprite;
		m_fEvaluationAlpha[sprite] = ALPHA_MAX;
		m_vEvaluationScale[sprite] = EATCH_SCALE_MAX;
	}

	//�S�ĕ\���I��.
	m_bFinishedAllDispFlag = true;
}