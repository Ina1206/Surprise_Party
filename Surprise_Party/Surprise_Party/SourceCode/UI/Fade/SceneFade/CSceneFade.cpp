#include "CSceneFade.h"

CSceneFade::CSceneFade()
	: m_pCSpriteUI				(nullptr)
	, m_vPos					(0.0f, 0.0f, 0.0f)
	, m_ShutterFlag				(0)
	, m_WaitChangeCnt			(0)
	, m_fMoveSpeed				(0.0f)
	, m_fFinishPoDistanceRatio	(0.0f)
{
	//初期化処理関数.
	Init();
}

CSceneFade::~CSceneFade()
{
	//解放処理関数.
	Release();
}

//=====================================.
//		更新処理関数.
//=====================================.
void CSceneFade::Update()
{
	if (m_ShutterFlag == 0) {
		return;
	}

	//移動速度の加速処理.
	m_fMoveSpeed += ADD_MOVE_SPEED;

	if (m_ShutterFlag & CLOSE_FLAG) {
		//シャッター下げる処理関数.
		ShutterDown();

		return;
	}

	//シャッター上げる処理関数.
	ShutterUp();
}

//=====================================.
//		描画処理関数.
//=====================================.
void CSceneFade::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetScale(0.8f);
	m_pCSpriteUI->Render();
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CSceneFade::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Shutter);
	m_ShutterFlag = OPEN_FLAG;
	m_vPos = SHUTTER_INIT_POS;
}

//=====================================.
//		解放処理関数.
//=====================================.
void CSceneFade::Release()
{
	m_pCSpriteUI = nullptr;
}

//=====================================.
//		シャッター下げる処理関数.
//=====================================.
void CSceneFade::ShutterDown()
{
	m_vPos.y += m_fMoveSpeed;
	//最終地点までの距離.
	const float INIT_FINISH_POS_DISNTANCE = fabsf(SHUTTER_HEIGHT_MIN - SHUTTER_INIT_POS.y);
	m_fFinishPoDistanceRatio = fabsf(m_vPos.y - SHUTTER_INIT_POS.y) / INIT_FINISH_POS_DISNTANCE;

	if (m_vPos.y >= SHUTTER_INIT_POS.y) {
		m_vPos.y = SHUTTER_INIT_POS.y;

		m_WaitChangeCnt++;
	}

	//少し待ってからシーン変更.
	if (m_WaitChangeCnt >= WAIT_CHANGE_SCENE_TIME) {
		m_ShutterFlag = CHANGE_SCENE_FLAG;
		m_WaitChangeCnt = 0;
		m_fMoveSpeed = 0.0f;
	}
}

//=====================================.
//		シャッター上げる処理関数.
//=====================================.
void CSceneFade::ShutterUp()
{
	m_vPos.y -= m_fMoveSpeed;

	//最終地点までの距離.
	const float INIT_FINISH_POS_DISTANCE = fabsf(SHUTTER_INIT_POS.y - SHUTTER_HEIGHT_MIN);
	m_fFinishPoDistanceRatio = 1.0f - fabsf(m_vPos.y - SHUTTER_HEIGHT_MIN) / INIT_FINISH_POS_DISTANCE;

	//上げる処理終了.
	if (m_vPos.y <= SHUTTER_HEIGHT_MIN) {
		m_vPos.y = SHUTTER_HEIGHT_MIN;
		m_ShutterFlag = 0;
		m_fMoveSpeed = 0.0f;
	}
}