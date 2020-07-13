#include "CLowEvaluationString.h"

/********************************************
*		低評価時のUI文字クラス.
*****************/
CLowEvaluationString::CLowEvaluationString()
{
	//初期化処理関数.
	Init();
}

CLowEvaluationString::~CLowEvaluationString()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		更新処理.
//===========================================.
void CLowEvaluationString::Update()
{
	if (m_bFinishedAllDispFlag == true) {
		return;
	}

	if (m_bDisplayAllAtOnce == true) {
		//一気に表示する処理関数.
		DisplayAllAtOnce();
		return;
	}

	if (m_ActFlag & DISP_FLAG) {
		//移動前の座標設定処理関数.
		MoveBeforePos();
	}


	if (m_ActFlag & MOVE_FLAG) {
		//移動処理関数.
		Move();
	}

	if (m_ActFlag & TRANSPARENT_FLAG) {
		//透過処理関数.
		Transparent();
	}

	if (m_ActFlag == 0) {
		m_ActFlag = DISP_FLAG;
		m_UpdateNum++;
		//全ての文字を出し終わったら終了.
		if (m_UpdateNum >= static_cast<int>(m_pCEvaluationUI.size())) {
			m_bFinishedAllDispFlag = true;
		}
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CLowEvaluationString::Init()
{
	//スプライト情報.
	m_stSpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::LowEvaluationString);
	
	//スプライトUIの設定.
	const int ELEMENT_MAX = static_cast<int>(m_pCResourceManager->GetSpriteUIState(enSpriteUI::LowEvaluationString).Frame.w);
	for (int element = 0; element < ELEMENT_MAX; element++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::LowEvaluationString));
	}

	//要素数と初期値設定処理機関数.
	InitElementCount();

	//初期値の設定.
	for (int element = 0; element < ELEMENT_MAX; element++) {
		m_fEvaluationAlpha[element]	= ALPHA_MIN;
		m_vEvaluationPos[element]	= FINSH_BASE_POS;
		m_vEvaluationPos[element].y -= m_stSpriteState.Disp.h;
		m_vEvaluationUV[element].x	+= element;
	}

	//表示フラグから開始.
	m_ActFlag = DISP_FLAG;
}

//===========================================.
//		解放処理関数.
//===========================================.
void CLowEvaluationString::Release()
{

}

//===========================================.
//		移動処理関数.
//===========================================.
void CLowEvaluationString::Move()
{
	//縦移動.
	bool m_bVerticalMoveFinish = false;
	m_vEvaluationPos[m_UpdateNum].y += VERTICAL_MOVE_SPEED;
	if (m_vEvaluationPos[m_UpdateNum].y >= FINSH_BASE_POS.y) {
		m_vEvaluationPos[m_UpdateNum].y = FINSH_BASE_POS.y;
		m_bVerticalMoveFinish = true;
	}

	//横移動.
	m_fAngle += ANGLE_SPEED;
	if (m_fAngle >= ANGLE_MAX) {
		m_fAngle = 0.0f;

		//縦移動が終了したら横移動も終了.
		if (m_bVerticalMoveFinish == true) {
			m_ActFlag &= ~MOVE_FLAG;
			m_ActFlag &= ~TRANSPARENT_FLAG;
		}
	}

	m_vEvaluationPos[m_UpdateNum].x += static_cast<float>(cos(D3DXToRadian(m_fAngle)) * MOVE_HORIZON_WIDTH);
}

//===========================================.
//		透過処理関数.
//===========================================.
void CLowEvaluationString::Transparent()
{
	//移動距離.
	const float MOVED_DISTANCE = fabsf(-m_stSpriteState.Disp.h - m_vEvaluationPos[m_UpdateNum].y);
	//最終座標の距離.
	const float FINISH_MOVE_DINSTANCE = fabsf(-m_stSpriteState.Disp.h - FINSH_BASE_POS.y);
	
	m_fEvaluationAlpha[m_UpdateNum] = ALPHA_MAX * (MOVED_DISTANCE / FINISH_MOVE_DINSTANCE);
	
	if (m_fEvaluationAlpha[m_UpdateNum] >= ALPHA_MAX) {
		m_ActFlag &= ~TRANSPARENT_FLAG;
	}
}

//===========================================.
//		移動前の座標設定処理関数.
//===========================================.
void CLowEvaluationString::MoveBeforePos()
{
	//x軸一文字ずつズラす.
	m_vEvaluationPos[m_UpdateNum].x += m_stSpriteState.Disp.w * m_UpdateNum;
	//移動と透過処理開始.
	m_ActFlag = MOVE_FLAG | TRANSPARENT_FLAG;
}

//============================================.
//		一気に表示する処理関数.
//============================================.
void CLowEvaluationString::DisplayAllAtOnce()
{
	//一気に最終地点にまで変更.
	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite] = FINSH_BASE_POS;
		//一文字ずつズラす.
		m_vEvaluationPos[sprite].x += m_stSpriteState.Disp.h * sprite;
		m_fEvaluationAlpha[sprite] = ALPHA_MAX;
		m_vEvaluationScale[sprite] = EATCH_SCALE_MAX;
	}

	//全て表示終了.
	m_bFinishedAllDispFlag = true;
}