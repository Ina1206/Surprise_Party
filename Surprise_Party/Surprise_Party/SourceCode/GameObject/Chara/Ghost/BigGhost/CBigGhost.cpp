#include "CBigGhost.h"

CBigGhost::CBigGhost()
	: m_pCSkinMesh			(nullptr)
	, m_dCntAnimSpeed		(0.0)
	, m_fAnimSpeed			(0.0f)
	, m_AnimNum				(0)
	, m_WakeUpCnt			(0)
	, m_LeanDirect			(1)
	, m_UpDownDirect		(1)
	, m_HaveTroubleActFlag	(0)
	, m_ChangeEmotionFlag	(false)
	, m_pCSpriteEffect		()
	, m_UsingEffectNum		(0)
	, m_OldEmotionNum		(0)
	, m_pCSmartPhone		(nullptr)
	, m_bSleepFlag			(true)
{
	//初期化処理関数.
	Init();
}

CBigGhost::~CBigGhost()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		更新処理関数.
//==========================================.
void CBigGhost::Update()
{
	//static bool flag = false;
	//if (GetAsyncKeyState(VK_F2) & 0x0001) {
	//	if (flag == false) {
	//		flag = true;
	//	}
	//	else {
	//		flag = false;
	//	}
	//}

	//D3DXVECTOR3 vChange;
	//if (flag == false) {
	//	vChange = m_vPos;
	//}
	//else {
	//	vChange = m_vRot;
	//}

	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	//	vChange.x += 0.01f;
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
	//	vChange.x -= 0.01f;
	//}
	//if (GetAsyncKeyState(VK_UP) & 0x8000) {
	//	vChange.y += 0.01f;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
	//	vChange.y -= 0.01f;
	//}
	//if (GetAsyncKeyState('Z') & 0x8000) {
	//	vChange.z += 0.01f;
	//}
	//if (GetAsyncKeyState('X') & 0x8000) {
	//	vChange.z -= 0.01f;
	//}

	//if (flag == false) {
	//	m_vPos = vChange;
	//}
	//else {
	//	m_vRot = vChange;
	//}

	//if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
	//	m_ChangeEmotionFlag = true;
	//}

	//HaveTroubleEmotion();
	//RejoiceEmotion();
	//WakeUp();
	//Sleep();

	//エフェクト変更処理関数.
	if (m_EmotionNum != m_OldEmotionNum) {
		ChangeEffect();
		m_OldEmotionNum = m_EmotionNum;
	}
	//感情移動処理関数.
	EmotionMove();

	//エフェクト更新処理関数.
	if (m_UsingEffectNum < static_cast<int>(m_pCSpriteEffect.size())) {
		m_pCSpriteEffect[m_UsingEffectNum]->Update();
	}

}

//==========================================.
//		描画処理関数.
//==========================================.
void CBigGhost::Render()
{
	//ビッグゴーストの描画.
	m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	m_pCSkinMesh->SetScale(0.1f);
	m_pCSkinMesh->SetPosition(m_vPos);
	m_pCSkinMesh->SetRotation(m_vRot);
	m_pCSkinMesh->SetPreRot(WAKE_UP_ROT);
	m_pCSkinMesh->SetPrePos(m_vPrePos);
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);

	if (m_pCSmartPhone != nullptr) {
		m_pCSmartPhone->SetPos(m_vLookAtPos);
		m_pCSmartPhone->RenderInitSetting(m_mView, m_mProj, m_stLight);
		m_pCSmartPhone->SetCameraPos(m_vCameraPos);
		m_pCSmartPhone->Render();
	}

	//エフェクト描画.
	if (m_UsingEffectNum < static_cast<int>(m_pCSpriteEffect.size())) {
		m_pCSpriteEffect[m_UsingEffectNum]->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//==========================================.
//		初期化処理関数.
//==========================================.
void CBigGhost::Init()
{
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::BigGhost);
	m_vPos = SLEEP_POS;
	m_vRot = SLEEP_ROT;

	m_fAnimSpeed = SLEEP_ANIM_SPEED;

	m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
	m_vPos = WAKE_UP_POS;
	m_vRot = WAKE_UP_ROT;

	//エフェクト初期化処理.
	m_pCSpriteEffect.emplace_back(new CSleepEffect());
	m_pCSpriteEffect.emplace_back(new CHaveTroubleEffect());
	m_pCSpriteEffect.emplace_back(new CRejoiceEffect());
	m_pCSpriteEffect.emplace_back(new CQuestionEffect());


	m_EmotionNum = static_cast<int>(enEmotionType::Sleep);
	m_OldEmotionNum = m_EmotionNum;
}

//==========================================.
//		解放処理関数.
//==========================================.
void CBigGhost::Release()
{

}

//==========================================.
//		起床処理関数.
//==========================================.
void CBigGhost::WakeUp()
{
	//起きるまでの待機.
	m_WakeUpCnt++;
	if (m_WakeUpCnt <= WAKE_UP_TIMING) {
		return;
	}

	//起きるときのアニメーションタイミング.
	if (m_fAnimSpeed > WAKE_UP_ANIM_SPEED) {
		if (m_pCSkinMesh->GetAnimPeriod(m_AnimNum) - m_pCSkinMesh->GetAnimSpeed() <= m_dCntAnimSpeed) {
			m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
		}
		m_dCntAnimSpeed += m_pCSkinMesh->GetAnimSpeed();
		return;
	}

	//倒れる処理関数.
	FallDown(1);

	//鼻提灯最小の時のアニメーション.
	m_pCSkinMesh->ChangeAnimSet_StartPos(m_AnimNum, 1.1);

}

//==========================================.
//		困る感情処理関数.
//==========================================.
void CBigGhost::HaveTroubleEmotion()
{
	//感情変更処理.
	if (m_ChangeEmotionFlag == true) {
		m_HaveTroubleActFlag = 0;
		m_ChangeEmotionFlag = false;
	}

	if (m_HaveTroubleActFlag & (MOVING_ROT_FLAG | MOVING_POS_FLAG)) {
		//斜めになる処理.
		Lean(FALL_DOWN_DIRECTION);
		return;
	}

	if (m_HaveTroubleActFlag & SWING_FLAG) {
		//揺れる処理.
		m_vRot.y += HAVE_TROUBLE_SPEED * m_LeanDirect;
		m_vRot.z += HAVE_TROUBLE_SPEED * m_LeanDirect;
		if (fabsf(m_vRot.y) > HAVE_TROUBLE_ROT_MAX) {
			m_LeanDirect *= CHANGE_DIRECTION;

		}
		return;
	}
	
	if (m_HaveTroubleActFlag == 0) {
		//元の体勢に戻る処理.
		Lean(UP_DIRECTION);
	}
}

//==========================================.
//		喜ぶ感情処理関数.
//==========================================.
void CBigGhost::RejoiceEmotion()
{
	//元の場所に戻る.
	if (m_ChangeEmotionFlag == true) {
		m_vPos = WAKE_UP_POS;
		m_vRot = WAKE_UP_ROT;
		return;
	}

	//喜び感情表現処理.
	m_vPos.y += REJOICE_MOVE_SPEED * m_UpDownDirect;
	m_vPos.x += REJOICE_MOVE_SPEED * m_LeanDirect;

	if (m_vPos.y <= WAKE_UP_POS.y) {
		m_UpDownDirect *= CHANGE_DIRECTION;
		m_vPos.y = WAKE_UP_POS.y;
	}

	//角度.
	m_vRot.y += 0.01f * m_LeanDirect;
	if (fabsf(m_vRot.y) > REJOICE_ROT_MAX) {
		m_LeanDirect *= CHANGE_DIRECTION;
		m_UpDownDirect *= CHANGE_DIRECTION;
	}

	
}

//==========================================.
//		疑問感情処理関数.
//==========================================.
void CBigGhost::QuestionEmotion()
{
	m_vRot.z -= 0.02f;

	//傾き最小値.
	const float LEAN_ROT_MIN = static_cast<float>(D3DXToRadian(-30.0f));
	if (m_vRot.z < LEAN_ROT_MIN) {
		m_vRot.z = LEAN_ROT_MIN;
	}
}

//==========================================.
//		寝る処理関数.
//==========================================.
void CBigGhost::Sleep()
{
	m_fAnimSpeed = SLEEP_ANIM_SPEED;
	FallDown(-1);
}

//==========================================.
//		傾く処理関数.
//==========================================.
void CBigGhost::Lean(const int& Direction)
{
	const float			fPosLength	= D3DXVec3Length(&(HAVE_TROUBLE_POS - WAKE_UP_POS));
	const D3DXVECTOR3	vPosUnit	= (HAVE_TROUBLE_POS - WAKE_UP_POS) / fPosLength;
	const float			fRotLength	= D3DXVec3Length(&(HAVE_TROUBLE_ROT - WAKE_UP_ROT));
	const D3DXVECTOR3	vRotUnit	= (HAVE_TROUBLE_ROT - WAKE_UP_ROT) / fRotLength;

	m_vRot += LEAN_SPEED * vRotUnit * static_cast<float>(Direction);
	m_vPos += LEAN_SPEED * vPosUnit * static_cast<float>(Direction);

	if (Direction >= 1) {
		if (m_vRot.x <= HAVE_TROUBLE_ROT.x) {
			m_vRot = HAVE_TROUBLE_ROT;
			m_HaveTroubleActFlag &= ~MOVING_ROT_FLAG;
		}
		if(m_vPos.y >= HAVE_TROUBLE_POS.y){
			m_vPos = HAVE_TROUBLE_POS;
			m_HaveTroubleActFlag &= ~MOVING_POS_FLAG;
		}
		if (m_HaveTroubleActFlag == 0) {
			m_HaveTroubleActFlag = SWING_FLAG;
		}
		return;
	}

	if (m_vRot.x >= WAKE_UP_ROT.x) {
		m_vRot = WAKE_UP_ROT;
	}
	if (m_vPos.y <= WAKE_UP_POS.y) {
		m_vPos = WAKE_UP_POS;
	}
}

//=============================================.
//		倒れる処理関数.
//=============================================.
void CBigGhost::FallDown(const int& Direction)
{
	//座標単位ベクトル計算.
	const float m_fPosLength = D3DXVec3Length(&(WAKE_UP_POS - SLEEP_POS));
	const D3DXVECTOR3 vPosUnit = (WAKE_UP_POS - SLEEP_POS) / m_fPosLength;
	//角度単位ベクトル計算.
	const float m_fRotLength = D3DXVec3Length(&(WAKE_UP_ROT - SLEEP_ROT));
	const D3DXVECTOR3 vRotUnit = (WAKE_UP_ROT - SLEEP_ROT) / m_fRotLength;

	m_vPos += WAKE_UPING_SPEED * vPosUnit * static_cast<float>(Direction);
	m_vRot += WAKE_UPING_SPEED * vRotUnit * static_cast<float>(Direction);

	if (Direction >= 1) {
		if (m_vPos.y >= WAKE_UP_POS.y) {
			m_vPos = WAKE_UP_POS;
		}
		if (m_vRot.y > WAKE_UP_ROT.y) {
			m_vRot = WAKE_UP_ROT;
			m_WakeUpCnt = 0;
			m_UsingEffectNum = static_cast<int>(enEmotionType::Nothing);
			m_bSleepFlag = false;
		}
		return;
	}

	if (m_vPos.y <= SLEEP_POS.y) {
		m_vPos = SLEEP_POS;
	}
	if (m_vRot.y < SLEEP_ROT.y) {
		m_vRot = SLEEP_ROT;
		m_bSleepFlag = true;
	}
}

//============================================.
//		エフェクト変更処理関数.
//============================================.
void CBigGhost::ChangeEffect()
{
	//初期化.
	if (m_EmotionNum != static_cast<int>(enEmotionType::ViewSmartphone)) {
		m_vPos = WAKE_UP_POS;
	}
	m_vRot = WAKE_UP_ROT;
	switch (static_cast<enEmotionType>(m_EmotionNum)) {
	case enEmotionType::Sleep:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Sleep);
		break;
	case enEmotionType::HaveTrounble:
		m_UsingEffectNum = static_cast<int>(enEmotionType::HaveTrounble);
		m_HaveTroubleActFlag = MOVING_ROT_FLAG | MOVING_POS_FLAG;
		break;
	case enEmotionType::Rejoice:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Rejoice);
		break;
	case enEmotionType::Question:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Question);
		break;
	case enEmotionType::ViewSmartphone:
		//移動角度処理関数.
		MoveRotation(m_vPos, m_vLookAtPos);
		m_vPrePos.z = 10.0f;

		if (m_pCSmartPhone == nullptr) {
			m_pCSmartPhone.reset(new CSmartPhone());
		}

		m_bSleepFlag = true;
		m_UsingEffectNum = static_cast<int>(enEmotionType::ViewSmartphone);
		break;
	default:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Nothing);
		break;
	}

	if(m_EmotionNum < static_cast<int>(m_pCSpriteEffect.size())){
		for (int sprite = 0; sprite < m_pCSpriteEffect[m_UsingEffectNum]->GetSpriteMax(); sprite++) {
			//エフェクト開始初期化処理関数.
			m_pCSpriteEffect[m_UsingEffectNum]->PlayStartInit(sprite);
		}
	}
}

//============================================.
//		感情移動処理関数.
//============================================.
void CBigGhost::EmotionMove()
{
	D3DXVECTOR3 vCenterPos;	//エフェクト出す中心座標.

	switch (static_cast<enEmotionType>(m_UsingEffectNum)) {
	case enEmotionType::Sleep:
		vCenterPos = m_vPos;
		if (m_bSleepFlag == true) {
			//起床処理関数.
			WakeUp();
			break;
		}
		//寝る処理関数.
		Sleep();
		break;
	case enEmotionType::HaveTrounble:
		//困る感情処理関数.
		HaveTroubleEmotion();
		m_pCSkinMesh->GetPosFromBone("joint12", &vCenterPos);
		break;
	case enEmotionType::Rejoice:
		//喜ぶ感情処理関数.
		RejoiceEmotion();
		m_pCSkinMesh->GetPosFromBone("joint12", &vCenterPos);
		break;
	case enEmotionType::Question:
		//疑問感情処理関数.
		QuestionEmotion();
		//上下移動処理関数.
		MoveUpDown();

		m_pCSkinMesh->GetPosFromBone("joint12", &vCenterPos);
		break;
	case enEmotionType::ViewSmartphone:
		
		if (m_pCSmartPhone != nullptr) {
			m_pCSmartPhone->Update();
		}

		break;
	case enEmotionType::Nothing:
		MoveUpDown();
		//通常座標.
		//m_vRot = WAKE_UP_ROT;
		break;
	}

	//エフェクト出す中心座標設定.
	if (m_UsingEffectNum < static_cast<int>(m_pCSpriteEffect.size())) {
		m_pCSpriteEffect[m_UsingEffectNum]->SetCenterPos(vCenterPos);
	}
}