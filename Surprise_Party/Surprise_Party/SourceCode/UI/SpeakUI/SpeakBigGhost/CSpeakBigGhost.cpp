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
			//読み込み処理関数.
			m_SpeakNum++;
			if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
				m_SpeakNum = 0;
				m_SelectCnt = 0;
			}
			//選択文章判定処理.
			DecisionSelectString();
			
			m_ChangingFontNum = 0;
			m_fFontAlpha = 0.0f;
			m_StringFlag &= ~TRANSPARENTING_FLAG;
		}
		else {
			m_StringFlag |= TRANSPARENTING_FLAG;
		}
	}
	//文字透過処理関数.
	TransparentFont();

	if (m_StringFlag & SELECT_FLAG) {
		SelectingMove();
	}
}

//====================================.
//		描画処理関数.
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

	//文字の描画.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}
	m_pCFontResource->SetFontScale(FONT_SCALE);
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
	m_pCFontResource->String_Render();
}

//====================================.
//		初期化処理関数.
//====================================.
void CSpeakBigGhost::Init()
{
	m_pCSpriteUI.resize(5);
	m_vPos.resize(m_pCSpriteUI.size());
	m_vRot.resize(m_pCSpriteUI.size());
	m_fAlpha.resize(m_pCSpriteUI.size());
	m_fScale.resize(m_pCSpriteUI.size());

	//テキストボックス番号.
	const int TextBoxNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_pCSpriteUI[TextBoxNum] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBox);
	m_vPos[TextBoxNum] = D3DXVECTOR3(50.0f, 450.0f, 0.0f);
	//選択肢関連の画像初期設定.
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size() - 1; ui++) {
		//初期位置.
		m_vPos[ui] = D3DXVECTOR3(500.0f, 150.0f + (150.0f * (ui % 2)), 0.0f);

		//小さいテキストボックス.
		if (ui < 2) {
			m_pCSpriteUI[ui] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBoxSmall);
			continue;
		}
		//回答文字.
		const int SpriteNum = static_cast<int>(enSpriteUI::AnswerYes) + (ui - 2);
		m_pCSpriteUI[ui] = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
		//微調整文字.
		m_vPos[ui].x += 90.0f - (ui * 10.0f);
		m_vPos[ui].y += 15.0f;
	}

	
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_fScale[ui] = 1.0f;
		m_fAlpha[ui] = 1.0f;
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

	//ファイルの中の全文章設定.
	for (int splite = 0; splite < m_pCFileReosource->GetSringMax(0); splite++) {
		m_stSpeakString.push_back(m_pCFileReosource->GetSpeakString(0, splite, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileReosource->GetSpeakString(0, splite, CFileString::enStringType::SelectString));
	}

	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//読み込み処理関数.
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	//位置設定処理関数
	m_pCFontResource->SetStartPos(D3DXVECTOR3(90.0f, 480.0f, 0.0f));
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
	//一文字目の文章.
	const int FIRST_CHARACTER_NUM = 0;
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

	NextCharacterNum = m_SpeakNum + 1;
	if (IsDBCSLeadByte(m_stSpeakString[NextCharacterNum][FIRST_CHARACTER_NUM]) == 0) {
		if (std::to_string(m_SelectNum) == m_stSpeakString[NextCharacterNum]) {
			return;
		}
		if (m_stSpeakString[NextCharacterNum] == "finish") {
			return;
		}

		for (unsigned int str = NextCharacterNum; str < m_stSpeakString.size(); str++) {
			if (m_stSpeakString[str] == "finish") {
				continue;
			}

			if (IsDBCSLeadByte(m_stSpeakString[str][FIRST_CHARACTER_NUM]) != 0) {
				m_SpeakNum = str - 1;
				break;
			}
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
		SelectNum--;

		if (SelectNum < 0) {
			SelectNum = 0;
			//SE入れる.
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		SelectNum++;

		if (SelectNum >= SELECT_MAX) {
			SelectNum = 1;
			//SE入れる.
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