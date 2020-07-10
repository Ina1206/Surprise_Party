#include "CSceneUIBase.h"

/*****************************************
*		�V�[��UI�̊��N���X.
****************/
CSceneUIBase::CSceneUIBase()
	: m_pCSpriteUI			()
	, m_vUIPos				()
	, m_vUV					()
	, m_vUIRot				()
	, m_pCCursor			(nullptr)
{
	m_pCCursor.reset(new CChangeSceneCursorUI());
}

CSceneUIBase::~CSceneUIBase()
{
	//��������֐�.
	Release();
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

	//�ق��̂��̕`�揈���֐�.
	RenderOther();
	//�J�[�\���̕`��.
	m_pCCursor->Render();

}

//==========================================.
//		�v�f�������������֐�.
//==========================================.
void CSceneUIBase::InitElementCounts()
{
	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIRot.resize(m_pCSpriteUI.size());
	m_vUV.resize(m_pCSpriteUI.size());

	//�����l�ݒ�.
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_vUIPos[ui]	= INIT_POS;
		m_vUIRot[ui]	= INIT_ROT;
		m_vUV[ui]		= INIT_UV;
	}
}

//==========================================.
//		���쎞�I�𕶏͍��W�ݒ菈���֐�.
//==========================================.
void CSceneUIBase::ControlSelectStringPos()
{
	//������.
	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		m_vUIPos[sprite]	= SELECT_STRING_POS;
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
		m_vUIPos[sprite].y += SpriteState.Disp.h * sprite;
	}

}

//===========================================.
//		��������֐�.
//===========================================.
void CSceneUIBase::Release()
{

}