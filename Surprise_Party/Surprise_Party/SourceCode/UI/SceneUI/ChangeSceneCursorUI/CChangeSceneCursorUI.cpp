#include "CChangeSceneCursorUI.h"

/****************************************
*		�V�[���ύX�p�J�[�\��UI�N���X.
*****************/
CChangeSceneCursorUI::CChangeSceneCursorUI()
	: m_pCSpriteUI				(nullptr)
	, m_vUV						(0.0f, 0.0f)
	, m_vPrePos					(0.0f, 0.0f, 0.0f)
	, m_bSelectFinishFlag		(false)
	, m_bControlFlag			(false)
	, m_ChangeCnt				(0)
	, m_SelectNum				(0)
	, m_fAngle					(0)
	, m_fAcc					(0.0f)
	, m_vJumpBeforePos			(0.0f, 0.0f, 0.0f)
	, m_MaxJump					(1)
	, m_JumpCnt					(0)
	, m_MoveDirect				(RIGHT_DIRECT_NUM)
	, m_bChangeDirect			(false)
	, m_vChangeDirectBeforeRot	(0.0f, 0.0f, 0.0f)
	, m_MoveWaitCnt				(0)
	, m_bArrivalFlga			(false)
	, m_vCarryStartPos			(0.0f, 0.0f, 0.0f)
	, m_CarryFlag				(0)
	, m_FetchFlag				(0)
	, m_fCarryDisntace			(0.0f)
	, m_MoveType				(0)
	, m_OutSidePos				(false)
{
	//�����������֐�.
	Init();
}

CChangeSceneCursorUI::~CChangeSceneCursorUI()
{
	//��������֐�.
	Release();
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CChangeSceneCursorUI::Update()
{
	if (m_bControlFlag == false) {
		//�ړ������֐�.
		Act();
		return;
	}

	//���쏈���֐�.
	Control();
}

//======================================.
//		�`�揈���֐�.
//======================================.
void CChangeSceneCursorUI::Render()
{
	//���O���W.
	m_pCSpriteUI->SetPrePos(m_vPrePos);
	//���W.
	m_pCSpriteUI->SetPosition(m_vPos);
	//�p�x.
	m_pCSpriteUI->SetRotation(m_vRot);
	//UV���W.
	m_pCSpriteUI->SetPattern(m_vUV);
	//�`��.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//======================================.
//		�����������֐�.
//======================================.
void CChangeSceneCursorUI::Init()
{
	//�X�v���C�gUI�̏��擾.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::GhostCursor);
	m_OutSidePos = -SpriteState.Disp.w / 2.0f;

	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	//�[�����ɐݒ�.
	m_vPos = D3DXVECTOR3(-SpriteState.Disp.w / 2.0f, WND_H / 2.0f, 0.0f);
	m_vRot = RIGHT_CURSOR_ROT;
	m_vUV = NORMAL_UV_POS;

	m_vJumpBeforePos = m_vPos;

	//y����]���ɉ�]���𒆉��Ɏ����Ă����.
	m_vPrePos = D3DXVECTOR3(-SpriteState.Disp.w / 2.0f, 0.0f, 0.0f);
}

//======================================.
//		��������֐�.
//======================================.
void CChangeSceneCursorUI::Release()
{

}

//======================================.
//		�s�������֐�.
//======================================.
void CChangeSceneCursorUI::Act()
{
	switch (static_cast<enMoveType>(m_MoveType)) {
	case enMoveType::StartMove:
		//�㉺���V�����֐�.
		UpDownFloat();
		//�ړ������֐�(��ʒ����܂�).
		if (Move(WND_W / 2.0f) == true) {
			m_vChangeDirectBeforeRot = m_vRot;
			m_vJumpBeforePos = m_vPos;
			m_MoveType++;
		}
		break;
	case enMoveType::Surprise:
		if (m_bChangeDirect == false) {
			//�ړ������ύX�����֐�.
			m_bChangeDirect = ChangeMoveDirect();
			break;
		}
		m_vUV = SURPRISE_UV_POS;
		//�W�����v�����֐�.
		if (Jump() == true) {
			m_vUV = HAVE_TROUBLE_UV_POS;
			m_bChangeDirect = false;
			m_FetchFlag = LEFT_TITLE_FETCH_FLAG;
			m_MoveType++;
		}
		break;
	case enMoveType::LeftTitleFetch:
		//�㉺���V�����֐�.
		UpDownFloat();

		//�ړ������֐�.
		if (Move(m_OutSidePos) == true) {
			if (ChangeMoveDirect() == true) {
				m_vPos = m_vCarryStartPos;
				m_vPos.x += m_OutSidePos;
				m_fCarryDisntace = 0.0f;
				m_CarryFlag = LEFT_TITLE_CARRY_FLAG;
				m_MoveType++;
			}
		}

		break;
	case enMoveType::LeftTitleCarry:
		//�ړ������֐�.
		Move(-1000.0f);

		m_fCarryDisntace = m_vPos.x - m_vCarryStartPos.x;

		if (m_CarryFlag == 0) {
			m_MoveType++;
			m_FetchFlag = RIGHT_TITLE_FETCH_FLAG;
		}

		break;
	case enMoveType::RightTitleFetch:
		//�㉺���V�����֐�.
		UpDownFloat();

		//�ړ������֐�.
		if (Move(WND_W - m_OutSidePos) == true) {
			if (ChangeMoveDirect() == true) {
				m_vPos = m_vCarryStartPos;
				m_vPos.x -= m_OutSidePos;
				m_fCarryDisntace = 0.0f;
				m_CarryFlag = RIGHT_TITLE_CARRY_FLAG;
				m_MoveType++;
			}
		}
		break;
	case enMoveType::RightTitleCarry:
		//�ړ������֐�.
		Move(-1000.0f);

		m_fCarryDisntace = m_vPos.x - m_vCarryStartPos.x;

		if (m_CarryFlag == 0) {
			m_MoveType++;
			m_FetchFlag = 0;
			m_vUV = NORMAL_UV_POS;
			m_bArrivalFlga = false;
		}

		break;
	case enMoveType::Rejoice:
	{
		const D3DXVECTOR3	vTargetPos = D3DXVECTOR3(WND_W / 2.0f, WND_H / 2.0f, 0.0f);

		if (m_bArrivalFlga == false) {
			m_vJumpBeforePos = m_vPos;
		}

		if (MoveToDestination(vTargetPos) == true) {
			m_vUV = ENTER_UV_POS;
			if (Jump() == true) {
				m_MoveType++;
				m_FetchFlag = SELECT_FEATCH_FLAG;
				m_vUV = NORMAL_UV_POS;
				m_vChangeDirectBeforeRot = m_vRot;
			}
		}
	}
		break;
	case enMoveType::SelectFetch:
		if (m_bChangeDirect == false) {
			m_bChangeDirect = ChangeMoveDirect();
			break;
		}

		if (Move(WND_W - m_OutSidePos) == true) {
			if (ChangeMoveDirect() == true) {
				m_vPos = m_vCarryStartPos;
				m_vPos.x -= m_OutSidePos;
				m_fCarryDisntace = 0.0f;
				m_FetchFlag = 0;
				m_CarryFlag = SELECT_CARRY_FLAG;
				m_MoveType++;
			}
		}

		break;
	case enMoveType::SelectCarry:

		break;
	case enMoveType::BecomeCursor:

		break;
	}
}

//======================================.
//		���쏈���֐�.
//======================================.
void CChangeSceneCursorUI::Control()
{
	m_bSelectFinishFlag = false;

	//�����̏���.
	if (m_ChangeCnt > 0) {
		if (m_bChangeWaitFlag == true) {
			m_ChangeCnt++;

			//�I���I��.
			if (m_ChangeCnt >= CHANGE_CNT_MAX) {
				m_bSelectFinishFlag = true;
				m_vUV = NORMAL_UV_POS;
				m_ChangeCnt = 0;
			}
			return;
		}

		m_bSelectFinishFlag = true;
		return;
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_SelectNum--;
		if (m_SelectNum < 0) {
			m_SelectNum = 0;
			//SE.

			return;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_SelectNum++;
		if (m_SelectNum >= SELECT_MAX) {
			m_SelectNum = SELECT_MAX - 1;
			//SE.

			return;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_vUV = ENTER_UV_POS;
		//SE.
		m_ChangeCnt++;
	}

	//�I�����̕����̏��擾.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	m_vPos.x = CONTROL_CURSOR_POS.x;
	m_vPos.y = CONTROL_CURSOR_POS.y + (SpriteState.Disp.h * m_SelectNum);

}

//======================================.
//		�ړ������֐�.
//======================================.
bool CChangeSceneCursorUI::Move(const float& MoveDistanceMax) 
{
	m_vPos.x += 3.5f * m_MoveDirect;
	
	//��O����.
	if (MoveDistanceMax < m_OutSidePos) {
		return false;
	}

	if (fabsf(MoveDistanceMax - m_vPos.x) <= 3.5f) {
		m_vPos.x = MoveDistanceMax;
		return true;
	}

	return false;
}

//======================================.
//		�ړI�n�ւ̈ړ������֐�.
//======================================.
bool CChangeSceneCursorUI::MoveToDestination(const D3DXVECTOR3& vTargetPos)
{
	if (m_bArrivalFlga == true) {
		return true;
	}

	const D3DXVECTOR3	vTargetGhostPos = vTargetPos - m_vPos;	//2�_�Ԃ̋���.
	const float			fLength = D3DXVec3Length(&vTargetGhostPos);	//����.
	const D3DXVECTOR3	vUnit = vTargetGhostPos / fLength;			//����.

	m_vPos += 3.5f * vUnit;

	if (fabsf(vTargetPos.x - m_vPos.x) <= 3.5f) {
		m_bArrivalFlga = true;
		return true;
	}

	return false;
}

//======================================.
//		�㉺���V�����֐�.
//======================================.
void CChangeSceneCursorUI::UpDownFloat()
{
	m_fAngle+= FLOATING_SPEED;
	if (m_fAngle > static_cast<float>(D3DXToRadian(ANGLE_MAX))) {
		m_fAngle = 0.0f;
	}
	m_vPos.y += sin(m_fAngle) * FLOATING_DISTANCE;
}

//=======================================.
//		�W�����v�����֐�.
//=======================================.
bool CChangeSceneCursorUI::Jump()
{
	//�ړ��ҋ@.
	if (m_MoveWaitCnt > 0) {
		
		m_MoveWaitCnt++;

		if (m_MoveWaitCnt > 30) {
			m_MoveWaitCnt = 0;
			m_fAcc = 0.0f;
			m_JumpCnt = 0;
			return true;
		}
		return false;
	}

	m_fAcc += ADD_ACC_SPEED;

	m_vPos.y += m_fAcc - GRAVITY;
	if (m_vPos.y > m_vJumpBeforePos.y) {
		m_vPos.y = m_vJumpBeforePos.y;

		//�W�����v�ő吔.
		m_JumpCnt++;
		if (m_JumpCnt >= m_MaxJump) {
			m_MaxJump++;
			//�ړ��ҋ@�J�E���g���Z.
			m_MoveWaitCnt++;
			return false;
		}

		m_fAcc = 0.0f;
	}

	return false;
}

//=======================================.
//		�ړ������ύX�����֐�.
//=======================================.
bool CChangeSceneCursorUI::ChangeMoveDirect()
{
	m_vRot.y -= ROTATION_SPEED * m_MoveDirect;
	
	//�E�ƍ��̕����̍���.
	const float DIFFERENCE_LEFT_RIGHT_ROT = fabsf(RIGHT_CURSOR_ROT.y - LEFT_CURSOR_ROT.y);

	if (fabsf(m_vRot.y - m_vChangeDirectBeforeRot.y) > DIFFERENCE_LEFT_RIGHT_ROT) {
		//�ړ������ύX.
		m_MoveDirect *= CHANGE_DIRECT;
		
		//�E����.
		if (m_MoveDirect == RIGHT_DIRECT_NUM) {
			m_vRot = RIGHT_CURSOR_ROT;
			return true;
		}

		//������.
		m_vRot = LEFT_CURSOR_ROT;
		return true;
	}

	return false;
}