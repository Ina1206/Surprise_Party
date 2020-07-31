#include "CSpeakBigGhost.h"

CSpeakBigGhost::CSpeakBigGhost()
	: CSpeakBigGhost(0, 0)
{

}

CSpeakBigGhost::CSpeakBigGhost(const int& StageNum, const int& BeforeEndingTypeNum)
	: m_mView				()
	, m_mProj				()
	, m_vCameraPos			()
	, m_pCNextSpeakCursor	(nullptr)
	, m_pCSpriteUI			(nullptr)
	, m_pCSprite			()
	, m_vSelectPos			()
	, m_vSelectRot			()
	, m_fSelectAlpha		()
	, m_fSelectScale		()
	, m_EmotionNum			()
	, m_StringFlag			(0)
	, m_SelectNum			(1)
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
	//�`���[�g���A���I���シ�����̕��͕\��.
	if (m_StringFlag & TUTORIAL_FLAG) {
		//�t�H���g�v���p�e�B�ݒ菈���֐�.
		SettingFontProperty();

		//���͕ύX�����֐�.
		ChangeString();

		m_StringFlag &= ~TUTORIAL_FLAG;
	}
	
	//��b���X�V�����֐�.
	UpdateSpeakString();

	//�I�����͏������I��.
	if (m_FinishFlag != 0) {
		m_ChangingFontNum = m_pCFontResource->GetStrLength();
		return;
	}

	//�������ߏ����֐�.
	TransparentFont();

	//�t�H���g�̓��ߒl�����֐�.
	FontAlpha();

	//���̕��͂̃J�[�\���X�V����.
	m_pCNextSpeakCursor->SetDispFlag(m_bFinishAppearancedAllFont);
	if (m_bFinishAppearancedAllFont == true) {
		D3DXVECTOR3 vFontPos = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
		vFontPos.x += FONT_SCALE;
		m_pCNextSpeakCursor->SetDispPos(vFontPos);
	}
	m_pCNextSpeakCursor->Update();


	if (m_StringFlag & SELECT_FLAG) {
		//�S���o���I���܂ő���s��.
		if (m_bFinishAppearancedAllFont == false) {
			return;
		}
		//�I�𒆈ړ������֐�.
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
	RenderFont();

	//���̉�b���̃J�[�\���`��.
	m_pCNextSpeakCursor->Render();

	//�����Đ�����UI�`�揈���֐�.
	if (m_AutoFlag & AUTO_FLAG && !(m_AutoFlag & AUTO_SUSPEND_FLAG)) {
		m_pCAutoUI->Render();
	}

	//�I�����Ă���Ƃ��ȊO�������Ȃ�.
	if (!(m_StringFlag & SELECT_FLAG) || m_bFinishAppearancedAllFont == false) {
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
	m_vPos = TEXT_BOX_POS;

	//�I���X�v���C�g�����ݒ�.
	m_pCSprite.resize(SPRITE_MAX);
	m_vSelectPos.resize(m_pCSprite.size());
	m_vSelectRot.resize(m_pCSprite.size());
	m_fSelectAlpha.resize(m_pCSprite.size());
	m_fSelectScale.resize(m_pCSprite.size());

	//�I�����֘A�̉摜�����ݒ�.
	for (unsigned int ui = 0; ui < m_pCSprite.size(); ui++) {
		//�����ʒu.
		m_vSelectPos[ui] = INIT_SELECT_BOX_POS;
		m_vSelectPos[ui].y += SELECT_BOX_HEIGHT * (ui % 2);

		//�������e�L�X�g�{�b�N�X.
		if (ui < static_cast<unsigned int>(SELECT_BOX_MAX)) {
			m_pCSprite[ui] = m_pCResourceManager->GetSprite(enSprite::TextBoxSmall);
			continue;
		}
		//�񓚕���.
		const int SpriteNum = static_cast<int>(enSprite::AnswerNo) + (ui - 2);
		m_pCSprite[ui] = m_pCResourceManager->GetSprite(static_cast<enSprite>(SpriteNum));
	}

	//���̉�b���̃J�[�\���̃C���X�^���X��.
	m_pCNextSpeakCursor.reset(new CNextSpeakCursor());
	
	for (unsigned int ui = 0; ui < m_pCSprite.size(); ui++) {
		m_fSelectScale[ui] = STANDERD_SCALE_SIZE;
		m_fSelectAlpha[ui] = ALPHA_MAX;
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
//		��b���X�V�����֐�.
//=====================================.
void CSpeakBigGhost::UpdateSpeakString()
{
	//�����Đ������֐�.
	if (AutomaticReproducing() == true) {
		//���͕ύX�����֐�.
		DesicionChangeString();
		//���͕ύX�����֐�.
		ChangeString();
		return;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		//�S�Ă̎����Đ��t���O.
		const int AllAutoFlag = AUTO_FLAG | AUTO_SUSPEND_FLAG;
		if (m_AutoFlag & AllAutoFlag) {
			m_AutoFlag &= ~AUTO_SUSPEND_FLAG;
			return;
		}

		if (m_AutoFlag & AUTO_FLAG) {
			return;
		}
		
		//���͕ύX�����֐�.
		if (DesicionChangeString() == true) {
			ChangeString();
			//���̃t�H���g�ւ�SE.
			m_pCPlaySoundManager->SetPlaySE(enSEType::NextString);
		}
	}

}

//=====================================.
//		��b���͓ǂݍ��ݏ����֐�.
//=====================================.
void CSpeakBigGhost::LoadSpeakString()
{

	//�X�e�[�W������ł͖�����Γǂݍ��ރt�@�C����ʕ��Ƃ���.
	if (m_StageNum > 0) {
		m_LoadFileNum++;
	}

	//�t�@�C�����S�Ă̕��͂̐�.
	const int AllStringInFile = m_pCFileResource->GetSringMax(m_LoadFileNum);
	//�t�@�C���̒��̑S���͐ݒ�.
	for (int splite = 0; splite < AllStringInFile; splite++) {
		m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileResource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::SelectString));
		m_EmotionNum.push_back(atoi(m_pCFileResource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::EmotionNum).c_str()));
	}

	//int�^����string�^��.
	std::ostringstream oss;
	oss << m_StageNum;

	if (m_StageNum > 0) {
		const int FirstStringNum = 0;
		m_stSpeakString[FirstStringNum] = ChangeFullwidth(oss.str().c_str()) + m_stSpeakString[FirstStringNum];
	}

	//�t�H���g�v���p�e�B�ݒ菈���֐�.
	SettingFontProperty();
	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
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

	
	//�I���������̕���.
	if (m_StringFlag & SELECT_FLAG) {
		for (unsigned int str = m_SpeakNum; str < m_stSpeakString.size(); str++) {
			if (IsDBCSLeadByte(m_stSpeakString[str][FIRST_CHARACTER_NUM]) == 0) {
				//�����������������.
				if (std::to_string(m_SelectNum) == m_stSpeakString[str]) {
					m_SpeakNum = str;
					m_StringFlag &= ~SELECT_FLAG;
					m_AutoFlag &= ~AUTO_SUSPEND_FLAG;
					break;
				}
				continue;
			}
			//�I�𕪊򂪖����ꍇ.
			m_SpeakNum = str;
			m_StringFlag &= ~SELECT_FLAG;
			m_AutoFlag &= ~AUTO_SUSPEND_FLAG;
			break;
		}
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
			if (!(m_StringFlag & EVALUTION_FLAG)) {
				m_StringFlag |= SELECT_FLAG;
				if (m_AutoFlag != 0) {
					m_AutoFlag |= AUTO_SUSPEND_FLAG;
				}
			}
		}
		//���̕��͂��]�����e�̏ꍇ.
		const int NextSelectStringNum = atoi(m_stSelectString[NextCharacterNum].c_str());
		if (NextSelectStringNum > 0) {
			m_StringFlag |= EVALUTION_FLAG;
		}
		return;
	}



	m_pCFontResource->Load(m_stSelectString[m_SpeakNum]);

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
			//��O�̕��͂ɐݒ肷��.
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
	bool bLimitFlag = false;
	int SelectNum = m_SelectNum % SELECT_MAX;
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		SelectNum++;

		if (SelectNum >= SELECT_MAX) {
			SelectNum = 1;
			//����ړ�SE�Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::LimitMoveCursor);
			bLimitFlag = true;
		}
		if (bLimitFlag == false) {
			//�J�[�\���ړ�SE�Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::MoveCursor);
		}

	}

	bLimitFlag = false;
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		SelectNum--;

		if (SelectNum < 0) {
			SelectNum = 0;
			//����ړ�SE�Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::LimitMoveCursor);
			bLimitFlag = true;
		}
		if (bLimitFlag == false) {
			//�J�[�\���ړ�SE�Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::MoveCursor);
		}

	}
	m_SelectNum = SelectNum + (m_SelectCnt * SELECT_MAX);

	for (unsigned int select = 0; select < m_pCSprite.size(); select++ ) {
		m_fSelectScale[select] = STANDERD_SCALE_SIZE;
		m_fSelectAlpha[select] = NOT_SELECT_ALPHA;
		//�I������Ă���ꍇ.
		if (select % SELECT_MAX == m_SelectNum % SELECT_MAX) {
			m_fSelectScale[select] = SELECT_SCALE_SIZE;
			m_fSelectAlpha[select] = ALPHA_MAX;
		}
	}
}

//=========================================.
//		���͕ύX�����֐�.
//=========================================.
void CSpeakBigGhost::ChangeString()
{
	//�I���t���O�������Ă���ꍇ�͗�O����.
	if (m_FinishFlag != 0) {
		return;
	}

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
		//�]�����͎��̃X�e�[�W��.
		if (m_StringFlag & EVALUTION_FLAG) {
			m_FinishFlag = FINISH_NEXT_GAME;
			return;
		}
		//����ȊO�̓^�C�g����.
		m_FinishFlag = FINISH_NEXT_TITLE;
		return;
	}

	//�`���[�g���A��.
	bool m_bOldTutorialFlag = m_bTutorialFlag;
	if (m_stSpeakString[m_SpeakNum] == "tutorial") {
		if (m_bTutorialFlag == false) {
			m_bTutorialFlag = true;
			m_StringFlag |= TUTORIAL_FLAG;
		}
	}


	//�I�𕶏͔��菈��.
	DecisionSelectString();

	//�`���[�g���A����̕��͐ݒ�.
	if (m_bTutorialFlag != m_bOldTutorialFlag) {
		m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	}

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

			//3���ڂ݈̂Ⴄ���͂ɂ���.
			if (m_StageNum >= LAST_STAGE_NUM) {
				if (atoi(m_stSelectString[str].c_str()) == LAST_SPEAK_NUM) {
					m_SpeakNum = str;
					break;
				}
				continue;
			}

			//���̃X�e�[�W�Ɍ����ẴR�����g�T��.
			const int SELECT_NUM = m_EndingTypeNum + 1 + LAST_STAGE_NUM;
			if (atoi(m_stSelectString[str].c_str()) == SELECT_NUM) {
				m_SpeakNum = str;
				break;
			}

			//�]�����I��������̏���.
			if (atoi(m_stSelectString[str].c_str()) == NEXT_SPEAK_NUM) {
				m_SpeakNum = str;
				m_StringFlag &=  ~IN_EVALUTION_FLAG;
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

//===========================================.
//		�t�H���g�v���p�e�B�ݒ菈���֐�.
//===========================================.
void CSpeakBigGhost::SettingFontProperty()
{
	//�\���J�n�ʒu.
	m_pCFontResource->SetStartPos(START_FONT_POS);
	//�傫��.
	m_pCFontResource->SetFontScale(FONT_SCALE);
	//�\�����ő�.
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
}