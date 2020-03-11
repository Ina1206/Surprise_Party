#include "CGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
	: CGhostSpeakStage	(0)
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum)	
	: m_pCFontResource	(nullptr)
	, changestr			()
	, m_pCFloor			(nullptr)
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

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		m_stLight.m_fLightWidth += 0.1f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		m_stLight.m_fLightWidth -= 0.1f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		m_stLight.fIntensity += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		m_stLight.fIntensity -= 0.1f;
	}
	if (GetAsyncKeyState('Z') & 0x8000) {
		m_stLight.vPos.y += 0.1f;
	}
	if (GetAsyncKeyState('X') & 0x8000) {
		m_stLight.vPos.y -= 0.1f;
	}
}

//=========================================.
//		�`�揈���֐�.
//=========================================.
void CGhostSpeakStage::Render()
{
	//���̕`��.
	m_pCFloor->SetCameraPos(m_Camera.vPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_stLight);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -10.0f, 0.0f));
	m_pCFloor->Render();
	m_pCWall->SetCameraPos(m_Camera.vPos);
	m_pCWall->RenderInitSetting(m_mView, m_mProj, m_stLight);
	m_pCWall->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCWall->Render();

	//�����̕`��.
	if (m_pCFontResource != nullptr) {
		m_pCFontResource->String_Render();
	}


}

//=========================================.
//		�����������֐�.
//=========================================.
void CGhostSpeakStage::Init()
{

	//��.
	m_pCFloor.reset(new CFloor());
	m_pCFloor->SetScale(0.5f);

	m_pCWall.reset(new CWall());

	//���͓ǂݍ��ݏ����֐�.
	LoadString();

	m_stLight.fIntensity = 10.0f;
	m_stLight.fLightPosWidth = 20.0f;
	m_stLight.m_fLightWidth = 10.0f;
	m_stLight.m_fLightMax = 1.0f;
	m_stLight.vLightColor = D3DXVECTOR3(1.0f, 201.0f /255.0f, 14.0f / 255.0f);
	m_stLight.vPos = D3DXVECTOR3(26.2f, 3.6f, 6.7f);
	D3DXMatrixRotationYawPitchRoll(&m_stLight.mRot, 0.0f, 0.0f, 0.0f);
	m_stLight.fIntensity = 119.0f;
	m_stLight.m_fLightWidth = 6.2f;

	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.0f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 0.0f, 2.0f);
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

//=========================================.
//		���͓ǂݍ��ݏ����֐�.
//=========================================.
void CGhostSpeakStage::LoadString()
{
	//�t�@�C���ǂݍ���.
	CFile* m_pCFile = new CFile();
	m_pCFile->FileInput("Data\\File\\Test.csv");

	//�t�@�C���̒��̑S���͐ݒ�.
	for (int splite = 0; splite < m_pCFile->GetColumnMax(); splite++) {
		changestr.push_back(m_pCFile->GetLineData(splite));
	}
	m_pCFile->Close();
	SAFE_DELETE(m_pCFile);


	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(changestr[0]);
	//�ʒu�ݒ菈���֐�
	m_pCFontResource->SetStartPos(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
}