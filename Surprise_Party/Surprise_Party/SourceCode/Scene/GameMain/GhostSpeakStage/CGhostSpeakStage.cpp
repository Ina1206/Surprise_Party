#include "CGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum)
{
	m_StageNum = stageNum;
	//�����������֐�.
	Init();
}

CGhostSpeakStage::~CGhostSpeakStage()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CGhostSpeakStage::UpDate(const bool& ControlFlag)
{
	//���쏈���֐�.
	if (ControlFlag == true) {
		Control();
	}


	static int num = 0;
	if (GetAsyncKeyState(VK_F3) & 0x0001) {
		//�폜�����֐�.
		if (m_pCFontResource->GetFont() != nullptr) {
			m_pCFontResource->Destroy();
		}
		//�ǂݍ��ݏ����֐�.
		m_pCFontResource->Load(changestr[num]);
		num++;
		//�傫���ݒ菈���֐�.
		float Scale = num * 10.0f;
		m_pCFontResource->SetFontScale(Scale);
		if (num >= static_cast<int>(changestr.size())) {
			num = 0;
		}
	}

}

//=========================================.
//		�`�揈���֐�.
//=========================================.
void CGhostSpeakStage::Render()
{

	if (m_pCFontResource != nullptr) {
		m_pCFontResource->String_Render();
	}



}

//=========================================.
//		�����������֐�.
//=========================================.
void CGhostSpeakStage::Init()
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//�ʒu�ݒ菈���֐�
	m_pCFontResource->SetStartPos(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	std::string str = "����";
	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(str);

	//�t�@�C���ǂݍ���.
	CFile* m_pCFile = new CFile();
	m_pCFile->FileInput("Data\\File\\Test.csv");

	for (int splite = 0; splite < m_pCFile->GetColumnMax(); splite++) {
		changestr.push_back(m_pCFile->GetLineData(splite));
	}
	m_pCFile->Close();
	SAFE_DELETE(m_pCFile);

}

//=========================================.
//		��������֐�.
//=========================================.
void CGhostSpeakStage::Release()
{
	m_pCFontResource->Destroy();
}

//=========================================.
//		���쏈���֐�.
//=========================================.
void CGhostSpeakStage::Control()
{

}