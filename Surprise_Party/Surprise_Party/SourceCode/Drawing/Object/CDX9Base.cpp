#include "CDX9Base.h"

/***************************************
*	DirectX9DrawŠî’êƒNƒ‰ƒX.
***************/
CDX9Base::CDX9Base()
	: m_hWnd				(nullptr)
	, m_pDevice9			(nullptr)
	, m_pDevice11			(nullptr)
	, m_pContext11			(nullptr)
	, m_pVertexShader		(nullptr)
	, m_pVertexLayout		(nullptr)
	, m_pPixelShader		(nullptr)
	, m_pCBufferPerMesh		(nullptr)
	, m_pCBufferPerMaterial	(nullptr)
	, m_pCBufferPerFrame	(nullptr)
	, m_vPos				(0.0f, 0.0f, 0.0f)
	, m_vRot				(0.0f, 0.0f, 0.0f)
	, m_fScale				(1.0f)
	, m_vPrePos				(0.0f, 0.0f, 0.0f)
	, m_vPreRot				(0.0f, 0.0f, 0.0f)
	, m_fAlpha				(1.0f)
	, m_vUV					(0.0f, 0.0f)
	, m_pCObjectAlphaBlend	(new CObjectAlphaBlend())
	, m_bSpotLightUseFlag	(false)
{

}

CDX9Base::~CDX9Base()
{

}