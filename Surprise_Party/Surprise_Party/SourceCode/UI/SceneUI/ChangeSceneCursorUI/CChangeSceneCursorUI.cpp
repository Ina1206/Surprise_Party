#include "CChangeSceneCursorUI.h"

/****************************************
*		�V�[���ύX�p�J�[�\��UI�N���X.
*****************/
CChangeSceneCursorUI::CChangeSceneCursorUI()
	: m_pCSpriteUI			(nullptr)
	, m_vUV					(0.0f, 0.0f)
	, m_bSelectFinishFlag	(false)
	, m_ChangeCnt			(0)
	, m_SelectNum			(0)
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
	//���쏈���֐�.
	Control();
}

//======================================.
//		�`�揈���֐�.
//======================================.
void CChangeSceneCursorUI::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetRotation(m_vRot);
	m_pCSpriteUI->SetPattern(m_vUV);
	m_pCSpriteUI->Render();
}

//======================================.
//		�����������֐�.
//======================================.
void CChangeSceneCursorUI::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRot = RIGHT_CURSOR_ROT;
	m_vUV = NORMAL_UV_POS;
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
	m_vPos.x = CURSOR_POS.x;
	m_vPos.y = CURSOR_POS.y + (SpriteState.Disp.h * m_SelectNum);

}