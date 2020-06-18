#include "CSceneUIBase.h"

/*****************************************
*		�V�[��UI�̊��N���X.
****************/
CSceneUIBase::CSceneUIBase()
	: m_pCSpriteUI			()
	, m_vUIPos				()
	, m_vUV					()
	, m_SelectNum			(0)
	, m_ChangeCnt			(0)
	, m_bSelectFinishFlag	(false)
{
	//�������W�ݒ菈���֐�.
	InitPos();
}

CSceneUIBase::~CSceneUIBase()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CSceneUIBase::Update()
{
	m_bSelectFinishFlag = false;

	//�����̏���.
	if (m_ChangeCnt > 0) {
		m_ChangeCnt++;

		//�I���I��.
		if (m_ChangeCnt >= CHANGE_CNT_MAX) {
			m_bSelectFinishFlag = true;
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


	m_vUIPos[CURSOR_NUM].y = CURSOR_POS.y + (SELECT_STRING_WIDHT * m_SelectNum);

}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CSceneUIBase::Render()
{
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		//UV���W�ݒ�.
		m_pCSpriteUI[sprite]->SetPattern(m_vUV[sprite]);
		//�p�x.
		m_pCSpriteUI[sprite]->SetRotation(m_vUIRot[sprite]);
		//���W.
		m_pCSpriteUI[sprite]->SetPosition(m_vUIPos[sprite]);
		//�`��.
		CDepth_Stencil* m_pCDepthStenceil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepthStenceil->SetDepth(false);
		m_pCSpriteUI[sprite]->Render();
		m_pCDepthStenceil->SetDepth(true);
	}

}

//==========================================.
//		�������W�ݒ菈���֐�.
//==========================================.
void CSceneUIBase::InitPos()
{
	//�v�f���ݒ�.
	m_pCSpriteUI.resize(UI_MAX);
	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIRot.resize(m_pCSpriteUI.size());
	m_vUV.resize(m_pCSpriteUI.size());

	//������.
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		m_vUV[sprite] = INIT_UV;
		m_vUIRot[sprite] = INIT_ROT;

		if (static_cast<int>(sprite) < SELECT_STRING_MAX) {
			m_vUIPos[sprite] = SELECT_STRING_POS;
			m_vUIPos[sprite].y += SELECT_STRING_WIDHT * sprite;
			continue;
		}
		m_vUIPos[sprite] = INIT_POS;
	}
	m_vUIPos[CURSOR_NUM] = CURSOR_POS;
	m_vUIRot[CURSOR_NUM] = CURSOR_ROT;

	//�J�[�\��.
	m_pCSpriteUI[CURSOR_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
}

//===========================================.
//		��������֐�.
//===========================================.
void CSceneUIBase::Release()
{

}