#include "CObjectAlphaBlend.h"

CObjectAlphaBlend::CObjectAlphaBlend()
	: m_pDevice11		(nullptr)
	, m_pContext11		(nullptr)
	, m_pBlendState		(nullptr)
	, m_pNoBlendState	(nullptr)
{

}

CObjectAlphaBlend::~CObjectAlphaBlend()
{
	SAFE_RELEASE(m_pNoBlendState);
	SAFE_RELEASE(m_pBlendState);
}

//==========================================.
//		‰Šú‰»ˆ—ŠÖ”.
//==========================================.
HRESULT CObjectAlphaBlend::InitAlpha(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	D3D11_BLEND_DESC	BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));

	BlendDesc.AlphaToCoverageEnable					= TRUE;
	BlendDesc.IndependentBlendEnable				= FALSE;
	BlendDesc.RenderTarget[0].BlendEnable			= TRUE;
	BlendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice11->CreateBlendState(&BlendDesc, &m_pBlendState))) {
		_ASSERT_EXPR(false, L"[“xÝ’èŽ¸”s");

		return E_FAIL;
	}

	BlendDesc.RenderTarget[0].BlendEnable = false;

	if (FAILED(m_pDevice11->CreateBlendState(&BlendDesc, &m_pNoBlendState))) {
		_ASSERT_EXPR(false, L"[“xÝ’èŽ¸”s");
		return E_FAIL;
	}

	return S_OK;
}

//==========================================.
//		“§‰ßÝ’èˆ—ŠÖ”.
//==========================================.
void CObjectAlphaBlend::SetAlphaDepth(bool flag)
{
	const UINT msk = 0xffffffff;
	if (flag == true) {
		//“§‰ßˆ—.
		m_pContext11->OMSetBlendState(m_pBlendState, nullptr, msk);
	}
	else {
		m_pContext11->OMSetBlendState(m_pNoBlendState, nullptr, msk);
	}
}