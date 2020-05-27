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
	//初期化処理関数.
	Init();
}

CSpeakBigGhost::~CSpeakBigGhost()
{
	//解放処理関数.
	Release();
}

//====================================.
//		更新処理関数.
//====================================.
void CSpeakBigGhost::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
			//文章変更処理関数.
			ChangeString();
		}
		else {
			m_StringFlag |= TRANSPARENTING_FLAG;
		}
	}
	//文字透過処理関数.
	TransparentFont();

	//選択中移動処理関数.
	if (m_StringFlag & SELECT_FLAG) {
		SelectingMove();
	}
}

//====================================.
//		描画処理関数.
//====================================.
void CSpeakBigGhost::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->Render();

	//文字の描画.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}
	m_pCFontResource->String_Render();

	//選択しているとき以外処理しない.
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
//		描画初期設定処理関数.
//====================================.
void CSpeakBigGhost::RenderInit(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos)
{
	m_mView = mView;
	m_mProj = mProj;
	m_vCameraPos = vCameraPos;
}

//====================================.
//		初期化処理関数.
//====================================.
void CSpeakBigGhost::Init()
{
	//テキストボックス初期設定.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBox);
	m_vPos = D3DXVECTOR3(50.0f, 450.0f, 0.0f);

	//選択スプライト初期設定.
	m_pCSprite.resize(4);
	m_vSelectPos.resize(m_pCSprite.size());
	m_vSelectRot.resize(m_pCSprite.size());
	m_fSelectAlpha.resize(m_pCSprite.size());
	m_fSelectScale.resize(m_pCSprite.size());

	//選択肢関連の画像初期設定.
	for (unsigned int ui = 0; ui < m_pCSprite.size(); ui++) {
		//初期位置.
		m_vSelectPos[ui] = D3DXVECTOR3(6.0f, 2.0f + (1.5f * (ui % 2)), 10.0f);

		//小さいテキストボックス.
		if (ui < 2) {
			m_pCSprite[ui] = m_pCResourceManager->GetSprite(enSprite::TextBoxSmall);
			continue;
		}
		//回答文字.
		const int SpriteNum = static_cast<int>(enSprite::AnswerNo) + (ui - 2);
		m_pCSprite[ui] = m_pCResourceManager->GetSprite(static_cast<enSprite>(SpriteNum));
	}

	
	for (unsigned int ui = 0; ui < m_pCSprite.size(); ui++) {
		m_fSelectScale[ui] = 1.0f;
		m_fSelectAlpha[ui] = 1.0f;
	}

	//会話文章読み込み処理関数.
	LoadSpeakString();
}

//====================================.
//		解放処理関数.
//====================================.
void CSpeakBigGhost::Release()
{
	//削除処理関数.
	m_pCFontResource->Destroy();
}

//=====================================.
//		会話文章読み込み処理関数.
//=====================================.
void CSpeakBigGhost::LoadSpeakString()
{
	CFileResource*	m_pCFileReosource = CFileResource::GetResourceInstance();

	//ステージが初回では無ければ読み込むファイルを別物とする.
	if (m_StageNum > 0) {
		m_LoadFileNum++;
	}

	//ファイル内全ての文章の数.
	const int AllStringInFile = m_pCFileReosource->GetSringMax(m_LoadFileNum);
	//ファイルの中の全文章設定.
	for (int splite = 0; splite < AllStringInFile; splite++) {
		m_stSpeakString.push_back(m_pCFileReosource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileReosource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::SelectString));
		m_EmotionNum.push_back(atoi(m_pCFileReosource->GetSpeakString(m_LoadFileNum, splite, CFileString::enStringType::EmotionNum).c_str()));
	}

	//int型からstring型へ.
	std::ostringstream oss;
	oss << m_StageNum;

	if (m_StageNum > 0) {
		const int FirstStringNum = 0;
		m_stSpeakString[FirstStringNum] = ChangeFullwidth(oss.str().c_str()) + m_stSpeakString[FirstStringNum];
	}

	//位置設定処理関数
	m_pCFontResource->SetStartPos(D3DXVECTOR3(90.0f, 480.0f, 0.0f));
	m_pCFontResource->SetFontScale(FONT_SCALE);
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
	//読み込み処理関数.
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
}

//======================================.
//		文字透過処理関数.
//======================================.
void CSpeakBigGhost::TransparentFont()
{
	//例外処理.
	if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
		return;
	}

	//次の文字に変更.
	if (m_fFontAlpha == ALPHA_MAX) {
		m_ChangingFontNum++;
		m_fFontAlpha = ALPHA_MIN;
	}
	
	//一気に透過値最大値へ.
	if (m_StringFlag & TRANSPARENTING_FLAG) {
		m_fFontAlpha = ALPHA_MAX;
	}

	m_fFontAlpha += ALPHA_SPEED;

	//上限処理.
	if (m_fFontAlpha > ALPHA_MAX) {
		m_fFontAlpha = ALPHA_MAX;

		//ここにSE入れる？.
	}
}

//======================================.
//		選択文章処理関数.
//======================================.
void CSpeakBigGhost::DecisionSelectString()
{
	if (m_StringFlag & EVALUTION_FLAG) {
		//評価文章見つける処理関数.
		FindEvalutionString();
	}

	//次の文字番号.
	int NextCharacterNum = m_SpeakNum + 1;
	//メイン文章.
	if (IsDBCSLeadByte(m_stSpeakString[m_SpeakNum][FIRST_CHARACTER_NUM]) != 0) {
		m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
		//最後の文章例外処理.
		if (m_SpeakNum >= static_cast<int>(m_stSpeakString.size()) - 1) {
			return;
		}
		//次の文章が数字の時選択.
		if (IsDBCSLeadByte(m_stSpeakString[NextCharacterNum][FIRST_CHARACTER_NUM]) == 0) {
			m_StringFlag |= SELECT_FLAG;
		}
		//次の文章が評価内容の場合.
		const int NextSelectStringNum = atoi(m_stSelectString[NextCharacterNum].c_str());
		if (NextSelectStringNum > 0) {
			m_StringFlag |= EVALUTION_FLAG;
		}
		return;
	}

	//選択したもの文章.
	if (m_StringFlag & SELECT_FLAG) {
		m_SelectCnt++;
		for (unsigned int str = m_SpeakNum; str < m_stSpeakString.size(); str++) {
			if (IsDBCSLeadByte(m_stSpeakString[str][FIRST_CHARACTER_NUM]) == 0) {
				//同じ文字列を見つける.
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

	//次の文字番号.
	NextCharacterNum = m_SpeakNum + 1;
	if (IsDBCSLeadByte(m_stSpeakString[NextCharacterNum][FIRST_CHARACTER_NUM]) == 0) {
		//次の文章を見つける処理関数.
		FindNextString(NextCharacterNum);
	}

}

//========================================.
//		次の文章を見つける処理関数.
//========================================.
void CSpeakBigGhost::FindNextString(const int& NextStringNum)
{
	if (std::to_string(m_SelectNum) == m_stSpeakString[NextStringNum]) {
		return;
	}
	//例外処理(半角アルファベット).
	if (std::any_of(m_stSpeakString[NextStringNum].cbegin(), m_stSpeakString[NextStringNum].cend(), isalpha)) {
		return;
	}

	//分岐結合時の開始文章設定処理.
	for (unsigned int str = NextStringNum; str < m_stSpeakString.size(); str++) {
		//例外処理(半角アルファベット).
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
//		選択中移動処理関数.
//========================================.
void CSpeakBigGhost::SelectingMove()
{
	int SelectNum = m_SelectNum % SELECT_MAX;
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		SelectNum++;

		if (SelectNum >= SELECT_MAX) {
			SelectNum = 1;
			//SE入れる.
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		SelectNum--;

		if (SelectNum < 0) {
			SelectNum = 0;
			//SE入れる.
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
//		文章変更処理関数.
//=========================================.
void CSpeakBigGhost::ChangeString()
{
	//読み込み処理関数.
	m_SpeakNum++;

	//終了処理.
	if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
		m_FinishFlag = FINISH_NEXT_GAME;
		m_SpeakNum = m_stSpeakString.size() - 1;
		return;
	}

	//終了処理.
	if (m_stSpeakString[m_SpeakNum] == "finish") {
		m_FinishFlag = FINISH_NEXT_TITLE;
		return;
	}

	//チュートリアル.
	bool m_bOldTutorialFlag = m_bTutorialFlag;
	if (m_stSpeakString[m_SpeakNum] == "tutorial") {
		if (m_bTutorialFlag == false) {
			m_bTutorialFlag = true;
		}
	}

	//選択文章判定処理.
	DecisionSelectString();

	//チュートリアル後の文章設定.
	if (m_bTutorialFlag != m_bOldTutorialFlag) {
		m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	}

	m_ChangingFontNum = 0;
	m_fFontAlpha = 0.0f;
	m_StringFlag &= ~TRANSPARENTING_FLAG;
}

//===========================================.
//		全角変更処理関数.
//===========================================.
std::string CSpeakBigGhost::ChangeFullwidth(const char* str)
{
	char ret_str[CHAR_MAX];
	LCMapString(GetUserDefaultLCID(), LCMAP_FULLWIDTH, str, sizeof(ret_str), ret_str, sizeof(ret_str));

	return ret_str;
}

//===========================================.
//		評価文章見つける処理関数.
//===========================================.
void CSpeakBigGhost::FindEvalutionString()
{
	//評価選択番号.
	const int SelectionNum = atoi(m_stSelectString[m_SpeakNum].c_str());
	for (unsigned int str = m_SpeakNum; str < m_stSpeakString.size(); str++) {
		//評価中の時.
		if (m_StringFlag & IN_EVALUTION_FLAG) {
			if (SelectionNum == m_EndingTypeNum + 1) {
				break;
			}

			//評価し終わった時の処理.
			if (atoi(m_stSelectString[str].c_str()) == 0) {
				m_SpeakNum = str;
				m_StringFlag &= ~EVALUTION_FLAG | ~IN_EVALUTION_FLAG;
				break;
			}

			continue;
		}

		//評価処理.
		if (m_EndingTypeNum + 1 == atoi(m_stSelectString[str].c_str())) {
			m_SpeakNum = str;
			m_StringFlag |= IN_EVALUTION_FLAG;
			break;
		}
	}
}