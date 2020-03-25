#include "CSpeakBigGhost.h"

CSpeakBigGhost::CSpeakBigGhost()
	: m_pCSpriteUI			()
	, m_vPos				()
	, m_vRot				()
	, m_fAlpha				()
	, m_fScale				()
	, m_stSpeakString		()
	, m_SpeakNum			(0)
	, m_fFontAlpha			(0.0f)
	, m_ChangingFontNum		(0)
	, m_StringFlag			(0)
	, m_SelectNum			(0)
	, m_SelectCnt			(0)
{
	//�����������֐�.
	Init();
}

CSpeakBigGhost::~CSpeakBigGhost()
{
	//��������֐�.
	Release();
}

//====================================.
//		�X�V�����֐�.
//====================================.
void CSpeakBigGhost::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
			//�ǂݍ��ݏ����֐�.
			m_SpeakNum++;
			if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
				m_SpeakNum = 0;
				m_SelectCnt = 0;
			}
			//�I�𕶏͔��菈��.
			DecisionSelectString();
			
			m_ChangingFontNum = 0;
			m_fFontAlpha = 0.0f;
			m_StringFlag &= ~TRANSPARENTING_FLAG;
		}
		else {
			m_StringFlag |= TRANSPARENTING_FLAG;
		}
	}
	//�������ߏ����֐�.
	TransparentFont();

	if (m_StringFlag & SELECT_FLAG) {
		SelectingMove();
	}
}

//====================================.
//		�`�揈���֐�.
//====================================.
void CSpeakBigGhost::Render()
{
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		if (!(m_StringFlag & SELECT_FLAG)) {
			ui = m_pCSpriteUI.size() - 1;
		}
		m_pCSpriteUI[ui]->SetAlpha(m_fAlpha[ui]);
		m_pCSpriteUI[ui]->SetScale(m_fScale[ui]);
		m_pCSpriteUI[ui]->SetPosition(m_vPos[ui]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[ui]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	//�����̕`��.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}
	m_pCFontResource->SetFontScale(FONT_SCALE);
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
	m_pCFontResource->String_Render();
}

//====================================.
//		�����������֐�.
//====================================.
void CSpeakBigGhost::Init()
{
	m_pCSpriteUI.resize(5);
	m_vPos.resize(m_pCSpriteUI.size());
	m_vRot.resize(m_pCSpriteUI.size());
	m_fAlpha.resize(m_pCSpriteUI.size());
	m_fScale.resize(m_pCSpriteUI.size());

	//�e�L�X�g�{�b�N�X�ԍ�.
	const int TextBoxNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_pCSpriteUI[TextBoxNum] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBox);
	m_vPos[TextBoxNum] = D3DXVECTOR3(50.0f, 450.0f, 0.0f);
	//�I�����֘A�̉摜�����ݒ�.
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size() - 1; ui++) {
		//�����ʒu.
		m_vPos[ui] = D3DXVECTOR3(500.0f, 150.0f + (150.0f * (ui % 2)), 0.0f);

		//�������e�L�X�g�{�b�N�X.
		if (ui < 2) {
			m_pCSpriteUI[ui] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBoxSmall);
			continue;
		}
		//�񓚕���.
		const int SpriteNum = static_cast<int>(enSpriteUI::AnswerYes) + (ui - 2);
		m_pCSpriteUI[ui] = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
		//����������.
		m_vPos[ui].x += 90.0f - (ui * 10.0f);
		m_vPos[ui].y += 15.0f;
	}

	
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_fScale[ui] = 1.0f;
		m_fAlpha[ui] = 1.0f;
	}

	//��b���͓ǂݍ��ݏ����֐�.
	LoadSpeakString();
}

//====================================.
//		��������֐�.
//====================================.
void CSpeakBigGhost::Release()
{
	//�폜�����֐�.
	m_pCFontResource->Destroy();
}

//=====================================.
//		��b���͓ǂݍ��ݏ����֐�.
//=====================================.
void CSpeakBigGhost::LoadSpeakString()
{
	CFileResource*	m_pCFileReosource = CFileResource::GetResourceInstance();

	//�t�@�C���̒��̑S���͐ݒ�.
	for (int splite = 0; splite < m_pCFileReosource->GetSringMax(0); splite++) {
		m_stSpeakString.push_back(m_pCFileReosource->GetSpeakString(0, splite, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileReosource->GetSpeakString(0, splite, CFileString::enStringType::SelectString));
	}

	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	//�ʒu�ݒ菈���֐�
	m_pCFontResource->SetStartPos(D3DXVECTOR3(90.0f, 480.0f, 0.0f));
}

//======================================.
//		�������ߏ����֐�.
//======================================.
void CSpeakBigGhost::TransparentFont()
{
	//��O����.
	if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
		return;
	}

	//���̕����ɕύX.
	if (m_fFontAlpha == ALPHA_MAX) {
		m_ChangingFontNum++;
		m_fFontAlpha = ALPHA_MIN;
	}
	
	//��C�ɓ��ߒl�ő�l��.
	if (m_StringFlag & TRANSPARENTING_FLAG) {
		m_fFontAlpha = ALPHA_MAX;
	}

	m_fFontAlpha += ALPHA_SPEED;

	//�������.
	if (m_fFontAlpha > ALPHA_MAX) {
		m_fFontAlpha = ALPHA_MAX;

		//������SE�����H.
	}
}

//======================================.
//		�I�𕶏͏����֐�.
//======================================.
void CSpeakBigGhost::DecisionSelectString()
{
	//���̕����ԍ�.
	int NextCharacterNum = m_SpeakNum + 1;
	//���C������.
	if (IsDBCSLeadByte(m_stSpeakString[m_SpeakNum][FIRST_CHARACTER_NUM]) != 0) {
		m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
		//�Ō�̕��͗�O����.
		if (m_SpeakNum >= static_cast<int>(m_stSpeakString.size()) - 1) {
			return;
		}
		//���̕��͂������̎��I��.
		if (IsDBCSLeadByte(m_stSpeakString[NextCharacterNum][FIRST_CHARACTER_NUM]) == 0) {
			m_StringFlag |= SELECT_FLAG;
		}
		return;
	}

	//�I���������̕���.
	if (m_StringFlag & SELECT_FLAG) {
		m_SelectCnt++;
		for (unsigned int str = m_SpeakNum; str < m_stSpeakString.size(); str++) {
			if (IsDBCSLeadByte(m_stSpeakString[str][FIRST_CHARACTER_NUM]) == 0) {
				//�����������������.
				if (std::to_string(m_SelectNum) == m_stSpeakString[str]) {
					m_SpeakNum = str;
					break;
				}
				continue;
			}
			break;
		}
	}

	m_pCFontResource->Load(m_stSelectString[m_SpeakNum]);
	m_StringFlag &= ~SELECT_FLAG;

	//���̕����ԍ�.
	NextCharacterNum = m_SpeakNum + 1;
	if (IsDBCSLeadByte(m_stSpeakString[NextCharacterNum][FIRST_CHARACTER_NUM]) == 0) {
		//���̕��͂������鏈���֐�.
		FindNextString(NextCharacterNum);
	}

}

//========================================.
//		���̕��͂������鏈���֐�.
//========================================.
void CSpeakBigGhost::FindNextString(const int& NextStringNum)
{
	if (std::to_string(m_SelectNum) == m_stSpeakString[NextStringNum]) {
		return;
	}
	//��O����(���p�A���t�@�x�b�g).
	if (std::any_of(m_stSpeakString[NextStringNum].cbegin(), m_stSpeakString[NextStringNum].cend(), isalpha)) {
		return;
	}

	//���򌋍����̊J�n���͐ݒ菈��.
	for (unsigned int str = NextStringNum; str < m_stSpeakString.size(); str++) {
		//��O����(���p�A���t�@�x�b�g).
		if (std::any_of(m_stSpeakString[NextStringNum].cbegin(), m_stSpeakString[NextStringNum].cend(), isalpha)) {
			continue;
		}

		if (IsDBCSLeadByte(m_stSpeakString[str][FIRST_CHARACTER_NUM]) != 0) {
			m_SpeakNum = str - 1;
			break;
		}
	}

}

//========================================.
//		�I�𒆈ړ������֐�.
//========================================.
void CSpeakBigGhost::SelectingMove()
{
	int SelectNum = m_SelectNum % SELECT_MAX;
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		SelectNum--;

		if (SelectNum < 0) {
			SelectNum = 0;
			//SE�����.
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		SelectNum++;

		if (SelectNum >= SELECT_MAX) {
			SelectNum = 1;
			//SE�����.
		}
	}
	m_SelectNum = SelectNum + (m_SelectCnt * SELECT_MAX);

	for (unsigned int select = 0; select < m_pCSpriteUI.size() - 1; select++ ) {
		m_fScale[select] = 0.5f;
		if (select % SELECT_MAX == m_SelectNum % SELECT_MAX) {
			m_fScale[select] = 1.5f;
		}
	}
}