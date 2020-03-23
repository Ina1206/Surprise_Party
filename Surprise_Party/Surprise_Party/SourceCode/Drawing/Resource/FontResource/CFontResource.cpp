#include "CFontResource.h"

CFontResource::CFontResource()
	: m_pDevice11	(nullptr)
	, m_pContext11	(nullptr)
	, m_pCFont		()
	, m_StrLength	(0)
	, m_vStartPos	(0.0f, 0.0f, 0.0f)
	, m_hFont		(nullptr)
	, m_hdc			(nullptr)
	, m_fFontScale	(1.0f)
{

}

CFontResource::~CFontResource()
{
	//��������֐�.
	Release();
}

//===================================.
//		�����������֐�.
//===================================.
void CFontResource::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	//ttf�t�@�C���ǂݍ���.
	DESIGNVECTOR design;
	AddFontResourceEx(
		TEXT("Data\\Font\\APJapanesefontF.ttf"),
		FR_PRIVATE,
		&design);

	//�t�H���g�쐬.
	LOGFONT lf = {
		FONT_SIZE,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		_T("���񂸂����X")
	};

	if (!(m_hFont = CreateFontIndirect(&lf))) {
		_ASSERT_EXPR(m_hFont != nullptr, L"�����쐬���s");
	}
	//�f�o�C�X�R���e�L�X�g�쐬.
	m_hdc = GetDC(nullptr);
}

//===================================.
//		�ǂݍ��ݏ����֐�.
//===================================.
void CFontResource::Load(std::string str)
{
	//���������擾�i�S�p�����̂݁j.
	m_StrLength = str.length() / 2;
	if (static_cast<int>(m_pCFont.size()) < m_StrLength) {
		//�������m��.
		m_pCFont.reserve(m_StrLength);
		for (int size = 0; size <= m_StrLength; size++) {
			m_pCFont.push_back(nullptr);
		}
	}

	//�����̃e�N�X�`���쐬.
	for (int size = 0; size < m_StrLength; size++) {
		m_pCFont[size].reset(new CFont());
		//��������P�����ɕ���.
		std::string cda = str.substr(size * 2, 2);
		const char* c = cda.c_str();
		//�����������֐�.
		m_pCFont[size]->Init(m_pDevice11, m_pContext11, c, m_hFont, m_hdc);

	}


}

//===================================.
//		������`�揈���֐�.
//===================================.
void CFontResource::String_Render()
{
	//���A����.
	int widh, hight;
	widh = hight = 0;

	for (int size = 0; size < m_StrLength; size++) {
		CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
		//���s.
		if (widh * (BASIC_WIDTH * m_fFontScale) > WND_W - 150.0f) {
			widh = 0;
			hight++;
		}
		else {
			widh++;
		}
		//�ʒu�ݒ菈���֐�.
		m_pCFont[size]->SetPosition(D3DXVECTOR3(m_vStartPos.x + (widh * (BASIC_WIDTH * m_fFontScale)), m_vStartPos.y + (hight * (BASIC_WIDTH * m_fFontScale)), m_vStartPos.z));
		//�����̑傫���ݒ菈���֐�.
		m_pCFont[size]->SetScale(m_fFontScale);
		//�`�揈���֐�.
		m_pCDepthStencil->SetDepth(false);
		m_pCFont[size]->Render();
		m_pCDepthStencil->SetDepth(true);

	}
}

//===================================.
//		�폜�����֐�.
//===================================.
void CFontResource::Destroy()
{
	//�t�H���g�N���X�̉�������֐�.
	//for (int size = m_StrLength - 1; size >= 0; size--) {
	//	SAFE_DELETE(m_pCFont[size]);
	//}
	//�v�f���̏�����.
	m_pCFont.clear();
	m_pCFont.shrink_to_fit();
}

//===================================.
//		��������֐�.
//===================================.
void CFontResource::Release()
{
	////�폜�����֐�.
	//Destroy();

	//�t�H���g���.
	DeleteObject(m_hFont);
	//�f�o�C�X�R���e�L�X�g���.
	ReleaseDC(NULL, m_hdc);

	//�t�H���g�ǂݍ��݉��.
	DESIGNVECTOR design;
	RemoveFontResourceEx(
		TEXT("Data\\Font\\APJapanesefontF.ttf"),
		FR_PRIVATE,
		&design);
}