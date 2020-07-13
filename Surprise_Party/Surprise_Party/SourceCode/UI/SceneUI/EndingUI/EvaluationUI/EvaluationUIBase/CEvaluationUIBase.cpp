#include "CEvaluationUIBase.h"

/****************************************
*		評価UIの基底クラス.
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
//		描画処理関数.
//=======================================.
void CEvaluationUIBase::Render()
{
	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		//初期座標.
		m_pCEvaluationUI[sprite]->SetPrePos(m_vPrePos);
		//角度.
		m_pCEvaluationUI[sprite]->SetRotation(m_vEvaluationRot[sprite]);
		//大きさ.
		m_pCEvaluationUI[sprite]->SetEachSizeScale(m_vEvaluationScale[sprite]);
		//座標.
		m_pCEvaluationUI[sprite]->SetPosition(m_vEvaluationPos[sprite]);
		//UV座標.
		m_pCEvaluationUI[sprite]->SetPattern(m_vEvaluationUV[sprite]);
		//透過値.
		m_pCEvaluationUI[sprite]->SetAlpha(m_fEvaluationAlpha[sprite]);
		//描画.
		m_pCDepthStencil->SetDepth(false);
		m_pCEvaluationUI[sprite]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//=======================================.
//		要素数と初期値の初期化処理関数.
//=======================================.
void CEvaluationUIBase::InitElementCount()
{
	const int ElementSize = m_pCEvaluationUI.size();

	m_vEvaluationPos.resize(ElementSize);
	m_vEvaluationRot.resize(ElementSize);
	m_vEvaluationScale.resize(ElementSize);
	m_vEvaluationUV.resize(ElementSize);
	m_fEvaluationAlpha.resize(ElementSize);

	//初期値代入.
	for (int UI = 0; UI < ElementSize; UI++) {
		m_vEvaluationPos[UI]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vEvaluationRot[UI]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vEvaluationScale[UI]	= EATCH_SCALE_MAX;
		m_vEvaluationUV[UI]		= D3DXVECTOR2(0.0f, 0.0f);
		m_fEvaluationAlpha[UI]	= ALPHA_MAX;
	}
}