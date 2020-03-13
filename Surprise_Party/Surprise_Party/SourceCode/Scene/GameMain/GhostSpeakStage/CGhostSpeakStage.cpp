#include "CGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
	: CGhostSpeakStage	(0)
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum)	
	: m_pCFontResource	(nullptr)
	, changestr			()
	, m_pCFloor			(nullptr)
	, m_pCBigGhost		(nullptr)
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
	//操作処理関数.
	if (ControlFlag == true) {
		Control();
	}

	//大きいお化け更新処理関数.
	m_pCBigGhost->Update();

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

	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	//	m_stLight.m_fLightWidth += 0.1f;
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
	//	m_stLight.m_fLightWidth -= 0.1f;
	//}
	//if (GetAsyncKeyState(VK_UP) & 0x8000) {
	//	m_stLight.fIntensity += 0.1f;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
	//	m_stLight.fIntensity -= 0.1f;
	//}
	//if (GetAsyncKeyState('Z') & 0x8000) {
	//	m_stLight.vPos.y += 0.1f;
	//}
	//if (GetAsyncKeyState('X') & 0x8000) {
	//	m_stLight.vPos.y -= 0.1f;
	//}
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

	//文章読み込み処理関数.
	LoadString();

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
void CGhostSpeakStage::LoadString()
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