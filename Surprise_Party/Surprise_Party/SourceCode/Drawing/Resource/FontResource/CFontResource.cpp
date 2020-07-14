#include "CFontResource.h"

CFontResource::CFontResource()
	: m_pDevice11	(nullptr)
	, m_pContext11	(nullptr)
	, m_pCFont		()
	, m_StrLength	(0)
	, m_vStartPos	(0.0f, 0.0f, 0.0f)
	, m_vPos		()
	, m_hFont		(nullptr)
	, m_hdc			(nullptr)
	, m_fFontScale	(0.0f)
	, m_fAlpha		()
	, m_fWidthMax	(0.0f)
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
		TEXT("Data\\Font\\SNsanafonmaru.ttf"),
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
		_T("���ȃt�H����")
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
void CFontResource::Load(std::string str, bool InputPictureFlag)
{

	//���������擾�i�S�p�����̂݁j.
	m_StrLength = str.length() / 2;
	if (static_cast<int>(m_pCFont.size()) < m_StrLength) {
		//�������m��.
		m_pCFont.reserve(m_StrLength);
		//�O��̃t�H���g�ő�l.
		const int m_StartPos = m_pCFont.size();
		for (int size = m_StartPos; size <= m_StrLength; size++) {
			m_pCFont.push_back(nullptr);
		}
	}
	else {
		//�g���Ȃ����͉��.
		for (unsigned int size = m_StrLength; size < m_pCFont.size(); size++) {
			m_pCFont[size].reset();
		}
	}
	//���ߒl�T�C�Y�ݒ�.
	m_fAlpha.resize(m_pCFont.size());
	//���W�T�C�Y�w��.
	m_vPos.resize(m_pCFont.size());
	m_InputPictureNum.clear();
	m_PictureTypeNum.clear();

	//���A����.
	int widh, hight;
	widh = hight = 0;

	//�����̃e�N�X�`���쐬.
	bool bLineFeed = false;
	for (int size = 0; size < m_StrLength; size++) {
		//��������P�����ɕ���.
		std::string cda = str.substr(size * 2, 2);

		m_pCFont[size].reset(new CFont());

		//�A�C�R��������ꍇ�͂O�`�X�����ɓ����.
		if (InputPictureFlag == true) {
			if (cda >= "�O" && cda <= "�X") {
				m_InputPictureNum.push_back(size);
				m_PictureTypeNum.push_back(cda);
				cda = "�@";
			}
		}

		bLineFeed = false;
		if (cda == "��") {
			cda = "�@";
			bLineFeed = true;
		}

		const char* c = cda.c_str();
		//�����������֐�.
		m_pCFont[size]->Init(m_pDevice11, m_pContext11, c, m_hFont, m_hdc);
		m_fAlpha[size] = 0.0f;


		//�����̍��W.
		const float FONT_WIDTH = widh * (BASIC_WIDTH * m_fFontScale);
		const float	FONT_HEIGHT = hight * (BASIC_WIDTH * m_fFontScale);
		m_vPos[size] = D3DXVECTOR3(m_vStartPos.x + FONT_WIDTH, m_vStartPos.y + FONT_HEIGHT, m_vStartPos.z);
		//���s.
		if (FONT_WIDTH > m_fWidthMax || bLineFeed == true) {
			widh = 0;
			hight++;
		}
		else {
			widh++;
		}

	}


}

//===================================.
//		������`�揈���֐�.
//===================================.
void CFontResource::String_Render()
{
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();

	for (int size = 0; size < m_StrLength; size++) {
		//�ʒu�ݒ菈���֐�.
		m_pCFont[size]->SetPosition(m_vPos[size]);
		//�����̑傫���ݒ菈���֐�.
		m_pCFont[size]->SetScale(m_fFontScale);
		//�����̓��ߒl.
		m_pCFont[size]->SetAlpha(m_fAlpha[size]);
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
	//�t�H���g���쐬����ĂȂ���Ώ����I��.
	if (m_pCFont.size() <= 0) {
		return;
	}
	//�v�f���̏�����.
	m_pCFont.clear();
	m_pCFont.shrink_to_fit();
}

//===================================.
//		��������֐�.
//===================================.
void CFontResource::Release()
{

	//�t�H���g���.
	DeleteObject(m_hFont);
	//�f�o�C�X�R���e�L�X�g���.
	ReleaseDC(NULL, m_hdc);

	//�t�H���g�ǂݍ��݉��.
	DESIGNVECTOR design;
	RemoveFontResourceEx(
		TEXT("Data\\Font\\SNsanafonmaru.ttf"),
		FR_PRIVATE,
		&design);
}

