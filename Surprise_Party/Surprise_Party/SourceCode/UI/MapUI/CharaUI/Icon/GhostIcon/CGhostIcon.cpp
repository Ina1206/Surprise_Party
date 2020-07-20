#include "CGhostIcon.h"

/*************************************
*		お化け用アイコンクラス.
*******/
CGhostIcon::CGhostIcon()
	: m_fStrength	(0.0f)
	, m_fStrengthMax(0.0f)
	, m_FaceType	(0)
{
	//初期化処理関数.
	Init();
}

CGhostIcon::~CGhostIcon()
{
	//解放処理関数.
	Release();
}

//====================================.
//		更新処理関数.
//====================================.
void CGhostIcon::UpDate()
{
	//ゲーム内からマップ内に座標変換処理関数.
	GameMapConversion();

	//選択中の表示処理関数.
	SelectingDisplay();

	//選ばれた後の処理.
	if (m_bSelectedFlag == true) {
		m_vPattarn = SELECTED_FACE;
		return;
	}

	if (m_RestFlag == true) {
		m_vPattarn = REST_FACE;
		m_FaceType = static_cast<int>(enFaceType::Great_Face);
		return;
	}

	//表情変更処理関数.
	ChangeFace();
	

}

//====================================.
//		初期化処理関数.
//====================================.
void CGhostIcon::Init()
{
	m_vPattarn = GREAT_FACE;

	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Ghost_Icon);
	m_pCSpriteUI->SetPattern(m_vPattarn);

	//一番初めの表情.
	m_FaceType = static_cast<int>(enFaceType::Great_Face);
}

//====================================.
//		解放処理関数.
//====================================.
void CGhostIcon::Release()
{
	m_pCSpriteUI = nullptr;
}

//====================================.
//		表情変更処理関数.
//====================================.
void CGhostIcon::ChangeFace()
{
	//体力で表情計算.
	if (m_fStrength <= m_fStrengthMax * (m_FaceType / STRENGTH_FACE_MAX)) {
		m_FaceType--;
		if (m_FaceType <= static_cast<int>(enFaceType::Bad_Face)) {
			m_FaceType = static_cast<int>(enFaceType::Bad_Face);
		}
	}

	//表情設定.
	switch (static_cast<enFaceType>(m_FaceType)) {
	case enFaceType::Bad_Face:
		m_vPattarn = BAD_FACE;
		break;
	case enFaceType::Normal_Face:
		m_vPattarn = NORMAL_FACE;
		break;
	case enFaceType::Good_Face:
		m_vPattarn = GOOD_FACE;
		break;
	case enFaceType::Great_Face:
		m_vPattarn = GREAT_FACE;
		break;
	}
}