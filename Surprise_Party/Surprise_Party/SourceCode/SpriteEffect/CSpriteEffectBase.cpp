#include "CSpriteEffectBase.h"

/*********************************************
*		�X�v���C�g�̃G�t�F�N�g���N���X.
********/
CSpriteEffectBase::CSpriteEffectBase()
	: m_pCSprite			()
	, m_vPos				()
	, m_vRot				()
	, m_fScale				()
	, m_fAlpha				()
	, m_fAngle				()
	, m_vPart				()
	, m_vCenterPos			(0.0f, 0.0f, 0.0f)
	, m_fAlphaSpeed			(0.0f)
	, m_fScalingSpeed		(0.0f)
	, m_pCResourceManager	(nullptr)
	, m_pCDepthStencil		(nullptr)
	, m_bDispFlag			()
	, m_DispTime			(0)
	, m_ChangeAddSub		()
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
}

CSpriteEffectBase::~CSpriteEffectBase()
{
	m_pCDepthStencil = nullptr;
	m_pCResourceManager = nullptr;
}

//============================================.
//		�`�揈���֐�.
//============================================.
void CSpriteEffectBase::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos)
{
	//�����Ȃ���Ώ����I��.
	if (m_pCSprite.size() == 0) {
		_ASSERT_EXPR(nullptr, L"m_pCSprite.size() == 0");
		return;
	}

	//�`�揈��.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		
		_ASSERT_EXPR(m_pCSprite[sprite] != nullptr, L"CSpriteEffect��m_pCSprite == nullptr");

		m_pCSprite[sprite]->SetScale(D3DXVECTOR3(m_fScale[sprite], m_fScale[sprite], m_fScale[sprite]));
		m_pCSprite[sprite]->SetRotation(m_vRot[sprite]);
		m_pCSprite[sprite]->SetPosition(m_vPos[sprite]);
		m_pCSprite[sprite]->SetAlpha(m_fAlpha[sprite]);
		m_pCSprite[sprite]->SetPatternNo(m_vPart[sprite]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSprite[sprite]->Render(mView, mProj, vCameraPos);
		m_pCDepthStencil->SetDepth(true);
	}
}

//=============================================.
//		�v�f���ݒ菈���֐�.
//=============================================.
void CSpriteEffectBase::SettingElementsCount()
{
	//�����Ȃ���ΏI��.
	if (m_pCSprite.size() == 0) {
		_ASSERT_EXPR(nullptr, L"m_pCSprite.size() == 0");
		return;
	}

	m_vPos.resize(m_pCSprite.size());
	m_fScale.resize(m_pCSprite.size());
	m_vRot.resize(m_pCSprite.size());
	m_fAlpha.resize(m_pCSprite.size());
	m_fAngle.resize(m_pCSprite.size());
	m_vPart.resize(m_pCSprite.size());
	m_bDispFlag.resize(m_pCSprite.size());
	m_ChangeAddSub.resize(m_pCSprite.size());
}

//==========================================.
//		���ߏ����֐�.
//==========================================.
bool CSpriteEffectBase::ScalingTransparent(const int& num)
{
	//���ߏ���.
	m_fAlpha[num] += m_fAlphaSpeed * m_ChangeAddSub[num];
	//�g�k����.
	m_fScale[num] += m_fScalingSpeed * m_ChangeAddSub[num];


	//���Z�����ύX����.
	if (m_fAlpha[num] >= ALPHA_MAX) {
		m_ChangeAddSub[num] *= CHANGE_ADD_SUB;
		return false;
	}

	if (m_ChangeAddSub[num] > CHANGE_ADD_SUB) {
		return false;
	}

	//�\���I��.
	if (m_fAlpha[m_fAlpha.size() - 1] <= ALPHA_MIN) {
		return true;
	}
	return false;
}

//===========================================.
//		�����l�ݒ菈���֐�.
//===========================================.
void CSpriteEffectBase::SettingDefaultValue(const int& num)
{
	m_bDispFlag[num] = false;
	m_vPos[num] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRot[num] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale[num] = SCALE_MIN;
	m_fAlpha[num] = ALPHA_MIN;
	m_ChangeAddSub[num] = ADDITION_NUM;
	m_vPart[num] = D3DXVECTOR2(0.0f, 0.0f);
}