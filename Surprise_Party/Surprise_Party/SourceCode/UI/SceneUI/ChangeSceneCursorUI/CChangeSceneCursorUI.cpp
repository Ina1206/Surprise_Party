#include "CChangeSceneCursorUI.h"

/****************************************
*		�V�[���ύX�p�J�[�\��UI�N���X.
*****************/
CChangeSceneCursorUI::CChangeSceneCursorUI()
	: m_pCSpriteUI			(nullptr)
	, m_vUV					(0.0f, 0.0f)
	, m_vPrePos				(0.0f, 0.0f, 0.0f)
	, m_bSelectFinishFlag	(false)
	, m_bControlFlag		(false)
	, m_ChangeCnt			(0)
	, m_SelectNum			(0)
	, m_fAngle				(0)
	, m_fAcc				(0.0f)
	, m_vJumpBeforePos		(0.0f, 0.0f, 0.0f)
	, m_MoveDirect			(RIGHT_DIRECT_NUM)
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
		////�㉺���V�����֐�.
		//UpDownFloat();

		//Jump();

		static bool aa = false;
		static int OldDirect = m_MoveDirect;

		if (m_MoveDirect != OldDirect) {
			aa = false;
		}
		OldDirect = m_MoveDirect;

		if(GetAsyncKeyState('O') & 0x0001){
			if (aa == false) {
				aa = true;
				m_vChangeDirectBeforeRot = m_vRot;
			}
		}
		if (aa == true) {
			ChangeMoveDirect();
		}

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
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	m_vPos = D3DXVECTOR3(WND_W / 2.0f, WND_H / 2.0f, 0.0f);
	m_vRot = RIGHT_CURSOR_ROT;
	m_vUV = NORMAL_UV_POS;

	m_vJumpBeforePos = m_vPos;

	//�X�v���C�gUI�̏��擾.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::GhostCursor);
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
void CChangeSceneCursorUI::Jump()
{
	m_fAcc += ADD_ACC_SPEED;

	m_vPos.y += m_fAcc - GRAVITY;
	if (m_vPos.y > m_vJumpBeforePos.y) {
		m_vPos.y = m_vJumpBeforePos.y;
		m_fAcc = 0.0f;
	}
}

//=======================================.
//		�ړ������ύX�����֐�.
//=======================================.
void CChangeSceneCursorUI::ChangeMoveDirect()
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
			return;
		}

		//������.
		m_vRot = LEFT_CURSOR_ROT;
	}
}