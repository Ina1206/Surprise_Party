#include "CSceneManager.h"

CSceneManager::CSceneManager()
	: m_pDevice11		(nullptr)
	, m_pContext11		(nullptr)
	, m_pCSceneBase		()
	, m_Color			(0.0f, 0.0f, 0.0f, 0.0f)
	, m_ChangeSceneCnt	(0)
	, m_SceneType		(0)
	, m_PausingFlag		(true)
{

}

CSceneManager::~CSceneManager()
{

}

//==========================================.
//		�����������֐�.
//==========================================.
void CSceneManager::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd			= hWnd;
	m_pDevice9		= pDevice9;
	m_pDevice11		= pDevice11;
	m_pContext11	= pContext11;
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CSceneManager::UpDate()
{

	//�V�[���t�F�[�h�X�V�����֐�.
	m_pCSceneFade->Update();

	m_Color = m_pCSceneBase[NORMAL_SCENE_NUM]->GetBackColor();

	if (m_pCSceneFade->GetShutterFlag() & m_pCSceneFade->CHANGE_SCENE_FLAG) {
		//�V�[���ύX�����֐�.
		ChangeScene();
	}

	//�t�F�[�h���̓V�[���֌W�̏����������Ȃ�.
	if (m_pCSceneFade->GetShutterFlag() != 0) {
		return;
	}

#ifdef _DEBUG
	m_pCSceneBase[NORMAL_SCENE_NUM]->DebugSceneChange();
#endif	//#ifdef _DEBUG.

	//�V�[���ύX���̓V�[���X�V�����������Ȃ�.
	if (m_pCSceneBase[NORMAL_SCENE_NUM]->GetChangeSceneFlag() == true) {
		m_pCSceneFade->SetShutterFlag(m_pCSceneFade->CLOSE_FLAG);
		return;
	}

	if (GetAsyncKeyState(VK_F1) & 0x0001) {
		if (m_PausingFlag == true) {
			m_PausingFlag = false;
		}
		else {
			m_PausingFlag = true;
		}
	}

	//�V�[���̍X�V�����֐�.
	int m_UsingSceneNum = NORMAL_SCENE_NUM;
	if (m_PausingFlag == true) {
		m_UsingSceneNum = PAUSE_SCENE_NUM;
		m_pCSceneBase[m_UsingSceneNum]->SetPauseFlag(m_PausingFlag);
	}
	m_pCSceneBase[m_UsingSceneNum]->UpDate();
	m_PausingFlag = m_pCSceneBase[m_UsingSceneNum]->GetPauseFlag();
}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CSceneManager::Render(const D3DXMATRIX& mProj)
{
	for (unsigned int scene = 0; scene < m_pCSceneBase.size(); scene++) {
		//�V�[���̕`�揉���ݒ菈���֐�.
		m_pCSceneBase[scene]->RenderInitSetting(mProj);
		//�V�[���̕`�揈���֐�.
		m_pCSceneBase[scene]->Render();

		if (m_PausingFlag == false) {
			break;
		}
	}

	//�t�F�[�h�`�揈���֐�.
	if (m_pCSceneFade->GetShutterFlag() != 0) {
		m_pCSceneFade->Render();
	}
}

//===========================================.
//		��������֐�.
//===========================================.
void CSceneManager::Release()
{
	//���\�[�X�N���X�폜.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCResourceManager->Release();

	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;
}

//============================================.
//		�ǂݍ��ݏ����֐�.
//============================================.
void CSceneManager::Load()
{
	//�`��p�̓ǂݍ��݊Ǘ��N���X�̓ǂݍ��ݏ����֐�.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCResourceManager->Load(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11);

	//�t�@�C���p�ǂݍ��݊Ǘ��N���X�̓ǂݍ��ݏ����֐�.
	CFileResource*	m_pCFileResource = CFileResource::GetResourceInstance();
	m_pCFileResource->Load();


	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->Init(m_pDevice11, m_pContext11);

	//�t�F�[�h.
	m_pCSceneFade.reset(new CSceneFade());



	//�V�[�������ݒ�.
	m_pCSceneBase.resize(2);
	m_SceneType = static_cast<int>(enSceneType::Title);
	m_pCSceneBase[NORMAL_SCENE_NUM].reset(new CTitle());
	//m_SceneType = static_cast<int>(enSceneType::GameMain);
	//m_pCSceneBase[NORMAL_SCENE_NUM].reset(new CGameMain());

	//m_SceneType = static_cast<int>(enSceneType::Ending);
	//m_pCSceneBase[NORMAL_SCENE_NUM].reset(new CEnding());

	m_pCSceneBase[PAUSE_SCENE_NUM].reset(new CPause());

	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);

}

//=============================================.
//		�V�[���ύX�����֐�.
//=============================================.
void CSceneManager::ChangeScene()
{
	//���̃V�[����.
	m_SceneType++;
	if (m_SceneType >= static_cast<int>(enSceneType::Max)) {
		m_SceneType = static_cast<int>(enSceneType::Start);
	}

	switch (static_cast<enSceneType>(m_SceneType)) {
	case enSceneType::Title:
		m_pCSceneBase[NORMAL_SCENE_NUM].reset(new CTitle());
		break;
	case enSceneType::GameMain:
		m_pCSceneBase[NORMAL_SCENE_NUM].reset(new CGameMain());
		break;
	case enSceneType::Ending:
		const int Evaluation = m_pCSceneBase[NORMAL_SCENE_NUM]->GetEvaluation();
		m_pCSceneBase[NORMAL_SCENE_NUM].reset(new CEnding());
		m_pCSceneBase[NORMAL_SCENE_NUM]->SetEvaluation(Evaluation);
		break;
	}

	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);
}