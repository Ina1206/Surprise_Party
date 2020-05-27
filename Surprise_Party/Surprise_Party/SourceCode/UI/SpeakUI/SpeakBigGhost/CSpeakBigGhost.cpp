#include "CSpeakBigGhost.h"

CSpeakBigGhost::CSpeakBigGhost()
	: CSpeakBigGhost(0, 0)
{

}

CSpeakBigGhost::CSpeakBigGhost(const int& StageNum, const int& BeforeEndingTypeNum)
	: m_mView				()
	, m_mProj				()
	, m_vCameraPos			()
	, m_pCSpriteUI			(nullptr)
	, m_pCSprite			()
	, m_vSelectPos			()
	, m_vSelectRot			()
	, m_fSelectAlpha		()
	, m_fSelectScale		()
	, m_EmotionNum			()
	, m_StringFlag			(0)
	, m_SelectNum			(0)
	, m_SelectCnt			(0)
	, m_FinishFlag			(0)
	, m_bTutorialFlag		(false)
	, m_StageNum			(StageNum)
	, m_LoadFileNum			(0)
	, m_EndingTypeNum		(BeforeEndingTypeNum)
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
			//���͕ύX�����֐�.
			ChangeString();
		}
		else {
			m_StringFlag |= TRANSPARENTING_FLAG;
		}
	}
	//�������ߏ����֐�.
	TransparentFont();

	//�I�𒆈ړ������֐�.
	if (m_StringFlag & SELECT_FLAG) {
		SelectingMove();
	}
}

//====================================.
//		�`�揈���֐�.
//====================================.
void CSpeakBigGhost::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->Render();

	//�����̕`��.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}
	m_pCFontResource->String_Render();

	//�I�����Ă���Ƃ��ȊO�������Ȃ�.
	if (!(m_StringFlag & SELECT_FLAG)) {
		return;
	}
	for (unsigned int ui = 0; ui < m_pCSprite.size(); ui++) {
		m_pCSprite[ui]->SetAlpha(m_fSelectAlpha[ui]);
		m_pCSprite[ui]->SetScale(D3DXVECTOR3(m_fSelectScale[ui], m_fSelectScale[ui], m_fSelectScale[ui]));
		m_pCSprite[ui]->SetPosition(m_vSelectPos[ui]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSprite[ui]->Render(m_mView, m_mProj, m_vCameraPos);
		m_pCDepthStencil->SetDepth(true);
	}
}

//====================================.
//		�`�揉���ݒ菈���֐�.
//====================================.
void CSpeakBigGhost::RenderInit(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos)
{
	m_mView = mView;
	m_mProj = mProj;
	m_vCameraPos = vCameraPos;
}

//====================================.
//		�����������֐�.
//====================================.
void CSpeakBigGhost::Init()
{
	//�e�L�X�g�{�b�N�X�����ݒ�.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBox);
	m_vPos = D3DXVECTOR3(50.0f, 450.0f, 0.0f);

	//�I���X�v���C�g�����ݒ�.
	m_pCSprite.resize(4);
	m_vSelectPos.resize(m_pCSprite.size());
	m_vSelectRot.resize(m_pCSprite.size());
	m_fSelectAlpha.resize(m_pCSprite.size());
	m_fSelectScale.resize(m_pCSprite.size());

	//�I�����֘A�̉摜�����ݒ�.
	for (unsigned int ui = 0; ui < m_pCSprite.size(); ui++) {
		//�����ʒu.
		m_vSelectPos[ui] = D3DXVECTOR3(6.0f, 2.0f + (1.5f * (ui % 2)), 10.0f);

		//�������e�L�X�g�{�b�N�X.
		if (ui < 2) {
			m_pCSprite[ui] = m_pCResourceManager->GetSprite(enSprite::TextBoxSmall);
			continue;
		}
		//�񓚕���.
		const int SpriteNum = static_cast<int>(enSprite::AnswerNo) + (ui - 2);
		m_pCSprite[ui] = m_pCResourceManager->GetSprite(static_cast<enSprite>(SpriteNum));
	}

	
	for (unsigned int ui = 0; ui < m_pCSprite.size(); ui++) {
		m_fSelectScale[ui] = 1.0f;
		m_fSelectAlpha[ui] = 1.0f;
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

	//�X�e�[�W������ł͖�����Γǂݍ��ރt�@�C����ʕ��Ƃ���.
	if (m_StageNum > 0) {
		m_LoadFileNum++;
	}

	//�t�@�C�����S�Ă̕��͂̐�.
	const int AllStringInFile = m_pCFileReosource->GetSringMax(m_LoadFileNum);
	//�t�@�C���̒��̑S���͐ݒ�.
	for (int splite = 0; splite < AllStringInFile; splite++) {
		m_stSpeakString.push_back(m_pCFileReosource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileReosource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::SelectString));
		m_EmotionNum.push_back(atoi(m_pCFileReosource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::EmotionNum).c_str()));
	}

	//int�^����string�^��.
	std::ostringstream oss;
	oss << m_StageNum;

	if (m_StageNum > 0) {
		const int FirstStringNum = 0;
		m_stSpeakString[FirstStringNum] = ChangeFullwidth(oss.str().c_str()) + m_stSpeakString[FirstStringNum];
	}

	//�ʒu�ݒ菈���֐�
	m_pCFontResource->SetStartPos(D3DXVECTOR3(90.0f, 480.0f, 0.0f));
	m_pCFontResource->SetFontScale(FONT_SCALE);
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
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
	if (m_StringFlag & EVALUTION_FLAG) {
		//�]�����͌����鏈���֐�.
		FindEvalutionString();
	}

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
		//���̕��͂��]�����e�̏ꍇ.
		const int NextSelectStringNum = atoi(m_stSelectString[NextCharacterNum].c_str());
		if (NextSelectStringNum > 0) {
			m_StringFlag |= EVALUTION_FLAG;
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

	//if (std::any_of(m_stSpeakString[m_SpeakNum].cbegin(), m_stSpeakString[m_SpeakNum].cend(), isalpha)) {
	//	return;
	//}

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
			break;
		}

		if (IsDBCSLeadByte(m_stSpeakString[str][FIRST_CHARACTER_NUM]) != 0) {
			m_SpeakNum = str;
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
		SelectNum++;

		if (SelectNum >= SELECT_MAX) {
			SelectNum = 1;
			//SE�����.
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		SelectNum--;

		if (SelectNum < 0) {
			SelectNum = 0;
			//SE�����.
		}
	}
	m_SelectNum = SelectNum + (m_SelectCnt * SELECT_MAX);

	for (unsigned int select = 0; select < m_pCSprite.size(); select++ ) {
		m_fSelectScale[select] = 1.0f;
		m_fSelectAlpha[select] = 0.5f;
		if (select % SELECT_MAX == m_SelectNum % SELECT_MAX) {
			m_fSelectScale[select] = 1.2f;
			m_fSelectAlpha[select] = 1.0f;
		}
	}
}

//=========================================.
//		���͕ύX�����֐�.
//=========================================.
void CSpeakBigGhost::ChangeString()
{
	//�ǂݍ��ݏ����֐�.
	m_SpeakNum++;

	//�I������.
	if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
		m_FinishFlag = FINISH_NEXT_GAME;
		m_SpeakNum = m_stSpeakString.size() - 1;
		return;
	}

	//�I������.
	if (m_stSpeakString[m_SpeakNum] == "finish") {
		m_FinishFlag = FINISH_NEXT_TITLE;
		return;
	}

	//�`���[�g���A��.
	bool m_bOldTutorialFlag = m_bTutorialFlag;
	if (m_stSpeakString[m_SpeakNum] == "tutorial") {
		if (m_bTutorialFlag == false) {
			m_bTutorialFlag = true;
		}
	}

	//�I�𕶏͔��菈��.
	DecisionSelectString();

	//�`���[�g���A����̕��͐ݒ�.
	if (m_bTutorialFlag != m_bOldTutorialFlag) {
		m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	}

	m_ChangingFontNum = 0;
	m_fFontAlpha = 0.0f;
	m_StringFlag &= ~TRANSPARENTING_FLAG;
}

//===========================================.
//		�S�p�ύX�����֐�.
//===========================================.
std::string CSpeakBigGhost::ChangeFullwidth(const char* str)
{
	char ret_str[CHAR_MAX];
	LCMapString(GetUserDefaultLCID(), LCMAP_FULLWIDTH, str, sizeof(ret_str), ret_str, sizeof(ret_str));

	return ret_str;
}

//===========================================.
//		�]�����͌����鏈���֐�.
//===========================================.
void CSpeakBigGhost::FindEvalutionString()
{
	//�]���I��ԍ�.
	const int SelectionNum = atoi(m_stSelectString[m_SpeakNum].c_str());
	for (unsigned int str = m_SpeakNum; str < m_stSpeakString.size(); str++) {
		//�]�����̎�.
		if (m_StringFlag & IN_EVALUTION_FLAG) {
			if (SelectionNum == m_EndingTypeNum + 1) {
				break;
			}

			//�]�����I��������̏���.
			if (atoi(m_stSelectString[str].c_str()) == 0) {
				m_SpeakNum = str;
				m_StringFlag &= ~EVALUTION_FLAG | ~IN_EVALUTION_FLAG;
				break;
			}

			continue;
		}

		//�]������.
		if (m_EndingTypeNum + 1 == atoi(m_stSelectString[str].c_str())) {
			m_SpeakNum = str;
			m_StringFlag |= IN_EVALUTION_FLAG;
			break;
		}
	}
}