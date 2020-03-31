#include "CClosedTime.h"

CClosedTime::CClosedTime()
	: CClosedTime(0)
{

}

CClosedTime::CClosedTime(int MaxTime)
	: m_TimeUpToClose	(MaxTime)
	, m_TimeReduceCnt	(0)
	, m_GiveBornusTime	(false)
	, m_bClosedFlag		(false)
{
	//初期化処理関数.
	Init();
}

CClosedTime::~CClosedTime()
{
	//解放処理関数.
	Release();
}

//=====================================.
//		更新処理関数.
//=====================================.
void CClosedTime::UpDate()
{
	//時間計算処理関数.
	TitmeCalc();

	//時間を減らす処理.
	if (m_TimeReduceCnt > TIME_REDUCE_DELIMITER) {
		m_TimeUpToClose--;
		m_TimeReduceCnt = 0;
	}

	//最小値処理.
	if (m_TimeUpToClose <= TIME_MIN) {
		m_TimeUpToClose = TIME_MIN;
		m_bClosedFlag	= true;
	}

	//カウント処理.
	m_TimeReduceCnt++;
}

//======================================.
//		追加時間与える処理関数.
//======================================.
void CClosedTime::GiveBornusTime(const bool& flag) 
{
	//取得フラグが降ろされていたら例外処理.
	if (flag == false) {
		return;
	}

	if (m_GiveBornusTime == false) {
		m_TimeUpToClose += TIME_REDUCE_DELIMITER * BONUS_TIME_ADD;

		m_GiveBornusTime = true;
	}

}

//======================================.
//		初期化処理関数.
//======================================.
void CClosedTime::Init()
{
	//サイズ.
	m_pCSpriteUI.resize(TIME_UI_MAX);
	m_vPatternNo.resize(m_pCSpriteUI.size());
	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIScale.resize(m_pCSpriteUI.size());
	m_fUIAlpha.resize(m_pCSpriteUI.size());

	//アドレス取得.
	//時間.
	for (unsigned int time = TIME_START_NUM; time < m_pCSpriteUI.size(); time++) {
		m_pCSpriteUI[time] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Time);
	}
	//木の板.
	m_pCSpriteUI[TREE_BORD] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TreeBord);
	//閉店文字.
	m_pCSpriteUI[CLOSED_STRING_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::ClosedString);

	//～～コロン、木の板の画像～～.
	//コロン番号.
	const int COLON_NUM = m_pCSpriteUI.size() - 1;

	//パターン設定.
	m_vPatternNo[COLON_NUM]			= COLON_PATTARN_NO;
	m_vPatternNo[TREE_BORD]			= TREE_PATTARN_NO;
	m_vPatternNo[CLOSED_STRING_NUM] = INIT_PATTARN_NO;

	//座標設定.
	m_vUIPos[COLON_NUM]			= COLON_POS;
	m_vUIPos[TREE_BORD]			= TREE_BORD_POS;
	m_vUIPos[CLOSED_STRING_NUM] = CLOSED_STRING_POS;

	for (int time = TIME_START_NUM; time < COLON_NUM; time++) {
		//時間の座標設定.
		m_vUIPos[time] = TIME_POS;
		m_vUIPos[time].x += TIME_INTERVAL * (time - TIME_START_NUM);
		//パターン初期化.
		m_vPatternNo[time] = INIT_PATTARN_NO;
	}

	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		//大きさ.
		m_vUIScale[ui] = SCALE_MAX;
		//透過値.
		m_fUIAlpha[ui] = ALPHA_MAX;
	}

	//時間計算処理関数.
	TitmeCalc();
}

//======================================.
//		解放処理関数.
//======================================.
void CClosedTime::Release()
{
	for (int ui = static_cast<int>(m_pCSpriteUI.size() - 1); ui <= 0; ui--) {
		m_pCSpriteUI[ui] = nullptr;
	}
}

//=======================================.
//		時間(h)計算処理関数.
//=======================================.
void CClosedTime::HourCalc(int time) 
{
	int hour = m_TimeUpToClose / HOUR_DELIMITER;

	//十の位数値.
	m_vPatternNo[time].x = static_cast<float>(hour / NUM_RANK_DELIMITER);
	//一の位数値.
	m_vPatternNo[time + 1].x = static_cast<float>(hour % NUM_RANK_DELIMITER);
}

//=======================================.
//		分(m)計算処理関数.
//=======================================.
void CClosedTime::MinutesCalc(int time)
{
	//分(m).
	int minutes = m_TimeUpToClose % HOUR_DELIMITER;

	//十の位数値.
	m_vPatternNo[time].x = static_cast<float>(minutes / NUM_RANK_DELIMITER);
	//一の位数値.
	m_vPatternNo[time + 1].x = static_cast<float>(minutes % NUM_RANK_DELIMITER);
}

//========================================.
//		時間計算処理関数.
//========================================.
void CClosedTime::TitmeCalc()
{
	//時間(h)計算フラグ.
	bool HourCalcFlag = false;

	for (unsigned int time = TIME_START_NUM; time < m_pCSpriteUI.size() - 1; time += 2) {
		//時間(h)の数値計算処理.
		if (HourCalcFlag == false) {
			HourCalc(time);

			HourCalcFlag = true;
			continue;
		}

		//分(m)の数値計算処理関数.
		MinutesCalc(time);
	}
}