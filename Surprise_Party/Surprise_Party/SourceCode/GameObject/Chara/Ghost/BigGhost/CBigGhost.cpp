#include "CBigGhost.h"

/******************************************
*		大きいお化けクラス.
**********/
CBigGhost::CBigGhost()
	: m_pCSkinMesh			(nullptr)
	, m_dCntAnimSpeed		(0.0)
	, m_fAnimSpeed			(0.0f)
	, m_AnimNum				(0)
	, m_vPreRot				(0.0f, 0.0f, 0.0f)
	, m_WakeUpCnt			(0)
	, m_LeanDirect			(1)
	, m_UpDownDirect		(1)
	, m_HaveTroubleActFlag	(0)
	, m_ChangeEmotionFlag	(false)
	, m_pCSpriteEffect		()
	, m_UsingEffectNum		(0)
	, m_OldEmotionNum		(0)
	, m_bSleepFlag			(true)
	, m_bSkipFlag			(false)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
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
	if (m_bPauseFlag == false) {
		m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	}
	else {
		m_pCSkinMesh->SetAnimSpeed(PAUSE_ANIM_SPEED);
	}
	m_pCSkinMesh->SetScale(SCALE);
	m_pCSkinMesh->SetPosition(m_vPos);
	m_pCSkinMesh->SetRotation(m_vRot);
	m_pCSkinMesh->SetPreRot(m_vPreRot);
	m_pCSkinMesh->SetPrePos(m_vPrePos);
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);

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
	//お化けの初期設定.
	m_pCSkinMesh	= m_pCResourceManager->GetSkinMesh(enSkinMeshType::BigGhost);
	m_vPos			= SLEEP_POS;
	m_vRot			= SLEEP_ROT;
	m_fAnimSpeed	= SLEEP_ANIM_SPEED;
	m_EmotionNum	= static_cast<int>(enEmotionType::WakeUp);
	m_OldEmotionNum = m_EmotionNum;

	//エフェクト初期化処理.
	m_pCSpriteEffect.emplace_back(new CSleepEffect());
	m_pCSpriteEffect.emplace_back(new CHaveTroubleEffect());
	m_pCSpriteEffect.emplace_back(new CRejoiceEffect());
	m_pCSpriteEffect.emplace_back(new CQuestionEffect());

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
	//スキップした場合.
	if (m_bSkipFlag == true) {
		m_WakeUpCnt = WAKE_UP_TIMING;
		m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
	}

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
	FallDown(WAKE_UP_DIRECT);

	//鼻提灯最小の時のアニメーション.
	m_pCSkinMesh->ChangeAnimSet_StartPos(m_AnimNum, WAKE_UP_ANIM_POS);

}

//==========================================.
//		困る感情処理関数.
//==========================================.
void CBigGhost::HaveTroubleEmotion()
{
	//感情変更処理.
	if (m_ChangeEmotionFlag == true) {
		m_HaveTroubleActFlag	= 0;
		m_ChangeEmotionFlag		= false;
		m_vPos					= WAKE_UP_POS;
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
			//方向変更.
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

	//位置.
	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_UpDownDirect *= CHANGE_DIRECTION;
		m_vPos.y		= m_vChangeBeforePos.y;
	}

	//角度.
	m_vRot.y += REJOICE_ROT_SPEED * m_LeanDirect;
	if (fabsf(m_vRot.y) > REJOICE_ROT_MAX) {
		m_LeanDirect	*= CHANGE_DIRECTION;
		m_UpDownDirect	*= CHANGE_DIRECTION;
		//喜びSE再生.
		m_pCPlaySoundManager->SetPlaySE(enSEType::Redjuice);
	}

	
}

//==========================================.
//		疑問感情処理関数.
//==========================================.
void CBigGhost::QuestionEmotion()
{
	m_vRot.z -= QUESTION_LEAN_SPEED;

	//傾き最小値.
	const float LEAN_ROT_MIN = static_cast<float>(D3DXToRadian(QUESTION_LEAN_MIN));
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
	//倒れる処理関数.
	FallDown(SLEEP_DIRECT);
}

//==========================================.
//		傾く処理関数.
//==========================================.
void CBigGhost::Lean(const int& Direction)
{
	//座標.
	const float			fPosLength	= D3DXVec3Length(&(HAVE_TROUBLE_POS - m_vChangeBeforePos));	//長さ.
	const D3DXVECTOR3	vPosUnit	= (HAVE_TROUBLE_POS - m_vChangeBeforePos) / fPosLength;		//比率.
	//角度.
	const float			fRotLength	= D3DXVec3Length(&(HAVE_TROUBLE_ROT - WAKE_UP_ROT));		//長さ.
	const D3DXVECTOR3	vRotUnit	= (HAVE_TROUBLE_ROT - WAKE_UP_ROT) / fRotLength;			//比率.

	m_vRot += LEAN_SPEED * vRotUnit * static_cast<float>(Direction);
	m_vPos += LEAN_SPEED * vPosUnit * static_cast<float>(Direction);

	//倒れるとき.
	if (Direction >= FALL_DOWN_DIRECTION) {
		if (m_vRot.x <= HAVE_TROUBLE_ROT.x) {
			m_HaveTroubleActFlag	&= ~MOVING_ROT_FLAG;
			m_vRot	= HAVE_TROUBLE_ROT;
		}
		if(m_vPos.y >= HAVE_TROUBLE_POS.y){
			m_HaveTroubleActFlag &= ~MOVING_POS_FLAG;
			m_vPos		= m_vChangeBeforePos;
			m_vPos.y	= HAVE_TROUBLE_POS.y;
		}
		if (m_HaveTroubleActFlag == 0) {
			m_HaveTroubleActFlag = SWING_FLAG;
		}
		return;
	}

	//元の態勢に戻るとき.
	if (m_vRot.x >= m_vChangeBeforePos.x) {
		m_vRot = m_vChangeBeforePos;
	}
	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_vPos = m_vChangeBeforePos;
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

	//起きる方向の時.
	if (Direction >= WAKE_UP_DIRECT) {
		if (m_vRot.y > WAKE_UP_ROT.y ||
			m_vPos.y >= WAKE_UP_POS.y) {
			m_vRot				= WAKE_UP_ROT;
			m_WakeUpCnt			= 0;
			m_UsingEffectNum	= static_cast<int>(enEmotionType::Nothing);
			m_bSleepFlag		= false;
			m_bSkipFlag			= false;
		}
		return;
	}

	//眠る方向の時.
	if (m_vPos.y <= SLEEP_POS.y ||
		m_vRot.y < SLEEP_ROT.y) {
		m_vPos			= SLEEP_POS;
		m_vRot			= SLEEP_ROT;
		m_bSleepFlag	= true;
		m_bSkipFlag		= false;
	}
}

//============================================.
//		エフェクト変更処理関数.
//============================================.
void CBigGhost::ChangeEffect()
{
	//初期化.
	if (m_EmotionNum != static_cast<int>(enEmotionType::ViewSmartphone)) {
		m_vPos		= WAKE_UP_POS;
		m_vPrePos	= BASE_PRE_POS;
		m_vPreRot	= BASE_PRE_ROT;
	}
	m_vRot = WAKE_UP_ROT;

	//変更前の座標(外部編集用変数）.
	if (m_vChangeBeforePos.y > 0.0f) {
		m_vPos = m_vChangeBeforePos;
	}
	else {
		m_vChangeBeforePos = WAKE_UP_POS;
	}

	switch (static_cast<enEmotionType>(m_EmotionNum)) {
	case enEmotionType::Sleep:
	case enEmotionType::WakeUp:
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

		m_vPrePos.z = VIEW_PRE_POS_Y;
		m_vPreRot	= WAKE_UP_ROT;

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
	if (static_cast<enEmotionType>(m_UsingEffectNum) != enEmotionType::Sleep) {
		m_pCSkinMesh->ChangeAnimSet_StartPos(m_AnimNum, WAKE_UP_ANIM_POS);
		m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
	}

	D3DXVECTOR3 vCenterPos;	//エフェクト出す中心座標.
	m_pCSkinMesh->GetPosFromBone("joint12", &vCenterPos);

	switch (static_cast<enEmotionType>(m_UsingEffectNum)) {
	case enEmotionType::Sleep:
		vCenterPos = m_vPos;
		if (m_EmotionNum == static_cast<int>(enEmotionType::WakeUp)) {
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
		break;
	case enEmotionType::Rejoice:
		//喜ぶ感情処理関数.
		RejoiceEmotion();
		break;
	case enEmotionType::Question:
		//疑問感情処理関数.
		QuestionEmotion();
		//上下移動処理関数.
		MoveUpDown();
		break;
	case enEmotionType::ViewSmartphone:
		
		break;
	case enEmotionType::Nothing:
		//上下移動処理関数.
		MoveUpDown();
		break;
	}

	//エフェクト出す中心座標設定.
	if (m_UsingEffectNum < static_cast<int>(m_pCSpriteEffect.size())) {
		m_pCSpriteEffect[m_UsingEffectNum]->SetCenterPos(vCenterPos);
	}
}