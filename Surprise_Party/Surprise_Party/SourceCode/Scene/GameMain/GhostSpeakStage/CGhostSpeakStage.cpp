#include "CGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum)
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


	static int num = 0;
	if (GetAsyncKeyState(VK_F3) & 0x0001) {
		//削除処理関数.
		if (m_pCFontResource->GetFont() != nullptr) {
			m_pCFontResource->Destroy();
		}
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

}

//=========================================.
//		描画処理関数.
//=========================================.
void CGhostSpeakStage::Render()
{

	if (m_pCFontResource != nullptr) {
		m_pCFontResource->String_Render();
	}



}

//=========================================.
//		初期化処理関数.
//=========================================.
void CGhostSpeakStage::Init()
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//位置設定処理関数
	m_pCFontResource->SetStartPos(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	std::string str = "眠い";
	//読み込み処理関数.
	m_pCFontResource->Load(str);

	//ファイル読み込み.
	CFile* m_pCFile = new CFile();
	m_pCFile->FileInput("Data\\File\\Test.csv");

	for (int splite = 0; splite < m_pCFile->GetColumnMax(); splite++) {
		changestr.push_back(m_pCFile->GetLineData(splite));
	}
	m_pCFile->Close();
	SAFE_DELETE(m_pCFile);

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