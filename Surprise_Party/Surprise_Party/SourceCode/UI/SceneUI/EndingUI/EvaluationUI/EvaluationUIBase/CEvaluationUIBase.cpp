#include "CEvaluationUIBase.h"

/****************************************
*		]¿UIÌîêNX.
*******************/
CEvaluationUIBase::CEvaluationUIBase()
	: m_pCEvaluationUI		()
	, m_vEvaluationPos		()
	, m_vPrePos				()
	, m_vEvaluationRot		()
	, m_vEvaluationScale	()
	, m_vEvaluationUV		()
	, m_fEvaluationAlpha	()
	, m_bFinishedAllDispFlag(false)
	, m_bDisplayAllAtOnce	(false)
	, m_UpdateNum			(0)
{

}

CEvaluationUIBase::~CEvaluationUIBase()
{

}

//=======================================.
//		`æÖ.
//=======================================.
void CEvaluationUIBase::Render()
{

}