#include "CPause.h"

/****************************************
*		�ꎞ��~�N���X.
************/
CPause::CPause()
	: m_pCSpriteUI			()
	, m_vPos				(nullptr)
	, m_vRot				(nullptr)
	, m_vUV					(nullptr)
	, m_pCResourceManager	(nullptr)
	, m_pCDepthStenceil		(nullptr)
	, m_SelectNum			(0)
	, m_ChangeCnt			(0)
{
	//�����������֐�.
	Init();
}

CPause::~CPause()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CPause::UpDate()
{
	//�����̏���.
	if (m_ChangeCnt > 0) {
		m_ChangeCnt++;

		if (m_ChangeCnt >= CHANGE_CNT_MAX) {
			m_bPauseFlag = false;
			m_vUV[CURSOR_NUM] = NORMAL_UV_POS;
			m_ChangeCnt = 0;
		}
		return;
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_SelectNum--;
		if (m_SelectNum < 0) {
			m_SelectNum = 0;
			//SE.
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_SelectNum++;	
		if (m_SelectNum >= SELECT_STRING_MAX) {
			m_SelectNum = SELECT_STRING_MAX - 1;
			//SE.
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_vUV[CURSOR_NUM] = ENTER_UV_POS;
		//SE.
		m_ChangeCnt++;
	}


	m_vPos[CURSOR_NUM].y = CURSOR_POS.y + (SELECT_STRING_WIDHT * m_SelectNum);
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CPause::Render()
{
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		//UV���W�ݒ�.
		m_pCSpriteUI[sprite]->SetPattern(m_vUV[sprite]);
		//�p�x.
		m_pCSpriteUI[sprite]->SetRotation(m_vRot[sprite]);
		//���W.
		m_pCSpriteUI[sprite]->SetPosition(m_vPos[sprite]);
		//�`��.
		m_pCDepthStenceil->SetDepth(false);
		m_pCSpriteUI[sprite]->Render();
		m_pCDepthStenceil->SetDepth(true);
	}
}

//========================================.
//		�����������֐�.
//========================================.
void CPause::Init()
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDepthStenceil	= CDepth_Stencil::GetDepthStencilInstance();

	//�v�f���ݒ�.
	m_pCSpriteUI.resize(UI_MAX);
	m_vPos.reset(new D3DXVECTOR3[m_pCSpriteUI.size()]);
	m_vRot.reset(new D3DXVECTOR3[m_pCSpriteUI.size()]);
	m_vUV.reset(new D3DXVECTOR2[m_pCSpriteUI.size()]);

	//�X�v���C�g�ݒ�.
	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		//�I�𕶏�.
		int SpriteNum = static_cast<int>(enSpriteUI::Continue) + sprite;
		m_pCSpriteUI[sprite] = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
	}
	//�J�[�\��.
	m_pCSpriteUI[CURSOR_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	//�|�[�Y.
	m_pCSpriteUI[PAUSE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause);

	//������.
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		m_vUV[sprite] = INIT_UV;
		m_vRot[sprite] = INIT_ROT;

		if (static_cast<int>(sprite) < SELECT_STRING_MAX) {
			m_vPos[sprite] = SELECT_STRING_POS;
			m_vPos[sprite].y += SELECT_STRING_WIDHT * sprite;
			continue;
		}
		m_vPos[sprite] = INIT_POS;
	}
	m_vPos[CURSOR_NUM] = CURSOR_POS;
	m_vRot[CURSOR_NUM] = CURSOR_ROT;
}

//========================================.
//		��������֐�.
//========================================.
void CPause::Release()
{
	m_pCDepthStenceil = nullptr;
	m_pCResourceManager = nullptr;
}