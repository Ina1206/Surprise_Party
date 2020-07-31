#include "CEndingStageBase.h"

/*******************************************
*		エンディングステージ基底クラス.
*****************/
CEndingStageBase::CEndingStageBase()
	: CEndingStageBase(0)
{

}

CEndingStageBase::CEndingStageBase(const int& EvaluationNum)
	: m_mView					()
	, m_mProj					()
	, m_pCBackstageLight		(nullptr)
	, m_pCGhost					(0)
	, m_pCCameraEnding			(nullptr)
	, m_pCWhiteScreenFade		(nullptr)
	, m_Evaluation				(EvaluationNum)
	, m_OldEvaluation			(INIT_EVALUATION_NUM)
	, m_bChangeStage			(false)
	, m_vObjLookPos				(0.0f, 0.0f, 0.0f)
	, m_UpdateFlag				(0)
	, m_bDisplayAllAtOnce		(false)
	, m_pCFloor					(nullptr)
	, m_pCPlaySoundManager		(nullptr)
{
	//共通の値の初期化処理関数.
	InitCommonValue();
}

CEndingStageBase::~CEndingStageBase()
{

}

//=========================================.
//		描画初期化処理関数.
//=========================================.
void CEndingStageBase::RenderInitSetting( const D3DXMATRIX& mProj)
{
	m_mProj = mProj;

	const D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//上方(ベクトル).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)ビュー計算結果.
		&m_pCCameraEnding->GetPos(), &m_pCCameraEnding->GetLook(), &vUpVec);
}

//=========================================.
//		床の描画処理関数.
//=========================================.
void CEndingStageBase::RenderFloor()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	m_pCFloor->SetScale(SCALE);
	m_pCFloor->SetCameraPos(m_pCCameraEnding->GetPos());
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(FLOOR_POS);
	m_pCFloor->Render();

}

//=========================================.
//		お化け描画処理関数.
//=========================================.
void CEndingStageBase::RenderGhost()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
		m_pCGhost[ghost]->SetCameraPos(m_pCCameraEnding->GetPos());
		m_pCGhost[ghost]->Render();
	}
}

//=========================================.
//		BGMの音量を設定処理関数.
//=========================================.
void CEndingStageBase::SettingBGMVolume()
{
	m_BGMVolume = m_pCPlaySoundManager->VOLUME_MAX;
	//透過値でBGMを調整.
	if (m_pCWhiteScreenFade->GetFadeFlag() != 0) {
		m_BGMVolume = static_cast<int>(m_pCWhiteScreenFade->GetAlphaRatio() * m_pCPlaySoundManager->VOLUME_MAX);
	}

	m_pCPlaySoundManager->SetPlayingBGMVolume(m_BGMVolume);
}

//=========================================.
//		共通値の初期化処理関数.
//=========================================.
void CEndingStageBase::InitCommonValue()
{
	//インスタンス化.
	m_pCFloor.reset(new CFloor());
	m_pCBackstageLight.reset(new CBackstageLight());
	m_pCCameraEnding.reset(new CCameraEnding());
	m_pCWhiteScreenFade.reset(new CWhiteScreenFade());

	//曲再生管理クラス.
	m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();

	m_vObjLookPos = LOOK_POS;

	for (int ghost = 0; ghost < GHOST_MAX; ghost++) {
		//クラスからインスタンスを作成する処理関数.
		CreateInstanceFronClass(ghost);

		const float			RADIAN	= static_cast<float>(D3DXToRadian(START_RADIAN + (ghost * RADIAN_WIDTH)));
		const D3DXVECTOR3	vPos	= (D3DXVECTOR3(cos(RADIAN), 0.0f, sin(RADIAN)) * POS_WIDTH) + D3DXVECTOR3(ADD_POS.x, ADD_POS.y + ((ghost % 2) * ADD_HIGHT), ADD_POS.z);

		m_pCGhost[ghost]->SetPos(vPos);
		m_pCGhost[ghost]->SetChangeBeforePos(vPos);
		//感情番号.
		const int m_EmotionType = static_cast<int>(CGhostBase::enEmotionType::ViewSmartphone);
		m_pCGhost[ghost]->SetEmotionNum(m_EmotionType);

		m_pCGhost[ghost]->SetLookAtPos(m_vObjLookPos);

		//一度だけ更新処理を行う.
		m_pCGhost[ghost]->Update();
	}

}

//==========================================.
//	クラスからインスタンスを作成する処理関数.
//==========================================.
void CEndingStageBase::CreateInstanceFronClass(const int& num)
{
	if (num == BIG_GHOST_NUM) {
		m_pCGhost.emplace_back(new CBigGhost());
		return;
	}

	if (num % WORK_GHOST_TYPE_MAX == 0) {
		m_pCGhost.emplace_back(new CEndingDispGhost());
		return;
	}
	m_pCGhost.emplace_back(new CEndingSwitchGhost());
	
}