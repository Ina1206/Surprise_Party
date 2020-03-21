#include "CGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
	: CGhostSpeakStage	(0)
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum)	
	: m_pCFontResource		(nullptr)
	, changestr				()
	, m_pCFloor				(nullptr)
	, m_pCBigGhost			(nullptr)
	, m_pCSpeakBigGhost		(nullptr)
	, m_MoveCameraDirection	(GET_CLOSER_CAMERA_DIRECT)
{
	m_StageNum = stageNum;
	//初期化処理関数.
	Init();
}

CGhostSpeakStage::~CGhostSpeakStage()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CGhostSpeakStage::UpDate(const bool& ControlFlag)
{


	//大きいお化け更新処理関数.
	m_pCBigGhost->Update();

	if (m_pCBigGhost->GetDispFlag() == true) {
		//カメラ移動処理関数.
		CameraMove();
		return;
	}

	//操作処理関数.
	if (ControlFlag == true) {
		Control();
	}

	static int num = 0;
	if (GetAsyncKeyState(VK_F3) & 0x0001) {
		//読み込み処理関数.
		m_pCFontResource->Load(changestr[num]);
		num++;
		//大きさ設定処理関数.
		float Scale = num * 10.0f;
		m_pCFontResource->SetFontScale(Scale);
		if (num >= static_cast<int>(changestr.size())) {
			num = 0;
		}
	}

	//大きいお化け会話更新処理クラス.
	m_pCSpeakBigGhost->Update();


}

//=========================================.
//		描画処理関数.
//=========================================.
void CGhostSpeakStage::Render()
{
	//床の描画.
	m_pCFloor->SetCameraPos(m_Camera.vPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_stLight);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

	//大きいお化け描画.
	m_pCBigGhost->SetCameraPos(m_Camera.vPos);
	m_pCBigGhost->RenderInitSetting(m_mView, m_mProj, m_stLight);
	m_pCBigGhost->Render();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		return;
	}

	//大きいお化け会話クラス.
	m_pCSpeakBigGhost->Render();

	//文字の描画.
	if (m_pCFontResource != nullptr) {
		m_pCFontResource->String_Render();
	}


}

//=========================================.
//		初期化処理関数.
//=========================================.
void CGhostSpeakStage::Init()
{

	//床.
	m_pCFloor.reset(new CFloor());
	m_pCFloor->SetScale(0.5f);

	//大きいお化け.
	m_pCBigGhost.reset(new CBigGhost());

	//大きいお化け会話クラス.
	m_pCSpeakBigGhost.reset(new CSpeakBigGhost());

	//文章読み込み処理関数.
	LoadSpeakString();

	m_stLight.fIntensity = 10.0f;
	m_stLight.fLightPosWidth = 20.0f;
	m_stLight.m_fLightWidth = 10.0f;
	m_stLight.m_fLightMax = 1.0f;
	m_stLight.vLightColor = D3DXVECTOR3(1.0f, 201.0f /255.0f, 14.0f / 255.0f);
	m_stLight.vLightColor = D3DXVECTOR3(243.0f / 255.0f, 232.0f / 255.0f, 12.0f / 255.0f);
	m_stLight.vPos = D3DXVECTOR3(26.2f, 11.7f, 6.7f);
	D3DXMatrixRotationYawPitchRoll(&m_stLight.mRot, 0.0f, 0.0f, 0.0f);
	m_stLight.fIntensity = 27.0f;
	m_stLight.m_fLightWidth = 6.2f;

	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);
}

//=========================================.
//		解放処理関数.
//=========================================.
void CGhostSpeakStage::Release()
{
	m_pCFontResource->Destroy();
}

//=========================================.
//		操作処理関数.
//=========================================.
void CGhostSpeakStage::Control()
{

}

//=========================================.
//		文章読み込み処理関数.
//=========================================.
void CGhostSpeakStage::LoadSpeakString()
{
	//ファイル読み込み.
	CFile* m_pCFile = new CFile();
	m_pCFile->FileInput("Data\\File\\Test.csv");

	//ファイルの中の全文章設定.
	for (int splite = 0; splite < m_pCFile->GetColumnMax(); splite++) {
		changestr.push_back(m_pCFile->GetLineData(splite));
	}
	m_pCFile->Close();
	SAFE_DELETE(m_pCFile);


	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//読み込み処理関数.
	m_pCFontResource->Load(changestr[0]);
	//位置設定処理関数
	m_pCFontResource->SetStartPos(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
}

//===========================================.
//		カメラ移動処理関数.
//===========================================.
void CGhostSpeakStage::CameraMove()
{

	//カメラの移動処理.
	const float CAMERA_POS_LENGTH = D3DXVec3Length(&CAMERA_POS_DISTANCE);			//ベクトルの長さ.
	const D3DXVECTOR3	CAMERA_POS_UNIT = CAMERA_POS_DISTANCE / CAMERA_POS_LENGTH;	//単位ベクトル.
	m_Camera.vPos += CAMER_MOVE_SPEED * CAMERA_POS_UNIT * static_cast<float>(m_MoveCameraDirection);

	//カメラの注視点移動処理.
	const float CAMERA_LOOK_LENGTH = D3DXVec3Length(&CAMERA_LOOK_DISTANCE);				//ベクトルの長さ.
	const D3DXVECTOR3	CAMERA_LOOK_UNIT = CAMERA_LOOK_DISTANCE / CAMERA_LOOK_LENGTH;	//単位ベクトル.
	const float	CAMERA_LENGTH_RATIO = CAMERA_LOOK_LENGTH / CAMERA_POS_LENGTH;			//長さの比率.
	m_Camera.vLook += CAMER_MOVE_SPEED * CAMERA_LOOK_UNIT * static_cast<float>(m_MoveCameraDirection) * CAMERA_LENGTH_RATIO;

	//カメラの接近する上限処理.
	if (m_MoveCameraDirection == GET_CLOSER_CAMERA_DIRECT) {
		if (m_Camera.vPos.x > SPEAK_START_POS.x) {
			m_Camera.vPos = SPEAK_START_POS;
			m_MoveCameraDirection = FAR_AWAY_CAMERA_DIRECT;
		}

		if (m_Camera.vLook.x > SPEAK_START_LOOK.x) {
			m_Camera.vLook = SPEAK_START_LOOK;
		}
		return;
	}

	//カメラが遠のく上限処理.
	if (m_Camera.vPos.x < INIT_CAMERA_POS.x) {
		m_Camera.vPos = INIT_CAMERA_POS;
	}

	if (m_Camera.vLook.x < INIT_CAMERA_LOOK.x) {
		m_Camera.vLook = INIT_CAMERA_LOOK;
	}
}