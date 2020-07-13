#include "CEvaluationUIBase.h"

/****************************************
*		�]��UI�̊��N���X.
*******************/
CEvaluationUIBase::CEvaluationUIBase()
	: m_pCEvaluationUI		()
	, m_vEvaluationPos		()
	, m_vPrePos				()
	, m_vEvaluationRot		()
	, m_vEvaluationScale	()
	, m_vEvaluationUV		()
	, m_fEvaluationAlpha	()
	, m_stSpriteState		()
	, m_bFinishedAllDispFlag(false)
	, m_bDisplayAllAtOnce	(false)
	, m_UpdateNum			(0)
{

}

CEvaluationUIBase::~CEvaluationUIBase()
{

}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CEvaluationUIBase::Render()
{
	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		//�������W.
		m_pCEvaluationUI[sprite]->SetPrePos(m_vPrePos);
		//�p�x.
		m_pCEvaluationUI[sprite]->SetRotation(m_vEvaluationRot[sprite]);
		//�傫��.
		m_pCEvaluationUI[sprite]->SetEachSizeScale(m_vEvaluationScale[sprite]);
		//���W.
		m_pCEvaluationUI[sprite]->SetPosition(m_vEvaluationPos[sprite]);
		//UV���W.
		m_pCEvaluationUI[sprite]->SetPattern(m_vEvaluationUV[sprite]);
		//���ߒl.
		m_pCEvaluationUI[sprite]->SetAlpha(m_fEvaluationAlpha[sprite]);
		//�`��.
		m_pCDepthStencil->SetDepth(false);
		m_pCEvaluationUI[sprite]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//=======================================.
//		�v�f���Ə����l�̏����������֐�.
//=======================================.
void CEvaluationUIBase::InitElementCount()
{
	const int ElementSize = m_pCEvaluationUI.size();

	m_vEvaluationPos.resize(ElementSize);
	m_vEvaluationRot.resize(ElementSize);
	m_vEvaluationScale.resize(ElementSize);
	m_vEvaluationUV.resize(ElementSize);
	m_fEvaluationAlpha.resize(ElementSize);

	//�����l���.
	for (int UI = 0; UI < ElementSize; UI++) {
		m_vEvaluationPos[UI]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vEvaluationRot[UI]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vEvaluationScale[UI]	= EATCH_SCALE_MAX;
		m_vEvaluationUV[UI]		= D3DXVECTOR2(0.0f, 0.0f);
		m_fEvaluationAlpha[UI]	= ALPHA_MAX;
	}
}