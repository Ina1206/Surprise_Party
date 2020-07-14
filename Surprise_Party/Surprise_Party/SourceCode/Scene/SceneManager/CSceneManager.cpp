#include "CSceneManager.h"

CSceneManager::CSceneManager()
	: m_pDevice11			(nullptr)
	, m_pContext11			(nullptr)
	, m_pCDepthStencil		(nullptr)
	, m_pCSceneBase			()
	, m_Color				(0.0f, 0.0f, 0.0f, 0.0f)
	, m_ChangeSceneCnt		(0)
	, m_SceneType			(0)
	, m_PausingFlag			(false)
	, m_StartFlag			(0)
	, m_pCDebugText			(nullptr)
	, m_FlyToSceneNum		(0)
	, m_FlyToSceneMax		(0)
	, m_bFlyToSceneFlag		(false)
	, m_pCPlaySoundManager	(nullptr)
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
	CSoundPlayManager* m_pCSoundPlayManager = CSoundPlayManager::GetSEPlayManagerInstance();
	m_pCSoundPlayManager->SetLoopSEPlay(CSoundResource::enBGM::Title, true);
	m_pCSoundPlayManager->Play();

	//�V�[���t�F�[�h�X�V�����֐�.
	m_pCSceneFade->Update();

	m_Color = m_pCSceneBase[NORMAL_SCENE_NUM]->GetBackColor();

	//�V�[���ɔ�ԏ����֐�.
	FlyToScene();

	if (m_pCSceneFade->GetShutterFlag() & m_pCSceneFade->CHANGE_SCENE_FLAG) {
		//�V�[���ύX�����֐�.
		ChangeScene();
	}

	//�t�F�[�h���̓V�[���֌W�̏����������Ȃ�.
	if (m_pCSceneFade->GetShutterFlag() != 0) {
		if (m_StartFlag & INIT_SETTED_FLAG) {
			return;
		}
		m_StartFlag = INIT_SETTED_FLAG;
	}

#ifdef _DEBUG
	m_pCSceneBase[NORMAL_SCENE_NUM]->DebugSceneChange();
#endif	//#ifdef _DEBUG.

	//�V�[���ύX���̓V�[���X�V�����������Ȃ�.
	if (m_pCSceneBase[NORMAL_SCENE_NUM]->GetChangeSceneFlag() == true) {
		m_pCSceneFade->SetShutterFlag(m_pCSceneFade->CLOSE_FLAG);
		return;
	}

	//�|�[�Y�����֐�.
	Pause();

	//�V�[���̍X�V�����֐�.
	int m_UsingSceneNum = NORMAL_SCENE_NUM;
	for (unsigned int scene = 0; scene < m_pCSceneBase.size(); scene++) {
		m_pCSceneBase[scene]->SetPauseFlag(m_PausingFlag);
	}
	if (m_PausingFlag == true) {
		m_UsingSceneNum = PAUSE_SCENE_NUM;
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

	//�f�o�b�O�p�̃t�H���g�`�揈���֐�.
	if (m_bFlyToSceneFlag == true) {
		RenderDebugFont();
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

	CSoundPlayManager* m_pCPlaySoundManager = CSoundPlayManager::GetSEPlayManagerInstance();
	m_pCPlaySoundManager->Init(m_hWnd);


	//�f�v�X�X�e���V��.
	m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->Init(m_pDevice11, m_pContext11);

	//�t�F�[�h.
	m_pCSceneFade.reset(new CSceneFade());

	//�f�o�b�O�e�L�X�g.
	m_pCDebugText = m_pCResourceManager->GetDebugText();


	//�V�[�������ݒ�.
	m_SceneType = static_cast<int>(enSceneType::Title);
	m_pCSceneBase.emplace_back(std::make_unique<CTitle>());

	m_pCSceneBase.emplace_back(std::make_unique<CPause>());

	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);

}

//=============================================.
//		�V�[���ύX�����֐�.
//=============================================.
void CSceneManager::ChangeScene()
{
	if (m_bFlyToSceneFlag == false) {
		//���̃V�[���ɐi�ޏ����֐�.
		NextScene();
	}


	switch (static_cast<enSceneType>(m_SceneType)) {
	case enSceneType::Title:
		m_pCSceneBase[NORMAL_SCENE_NUM].reset();
		m_pCSceneBase[NORMAL_SCENE_NUM] = std::make_unique<CTitle>();
		break;
	case enSceneType::GameMain:
		m_pCSceneBase[NORMAL_SCENE_NUM].reset();
		m_pCSceneBase[NORMAL_SCENE_NUM] = std::make_unique<CGameMain>();
		break;
	case enSceneType::Ending:
		const int Evaluation = m_pCSceneBase[NORMAL_SCENE_NUM]->GetEvaluation();
		m_pCSceneBase[NORMAL_SCENE_NUM].reset();
		m_pCSceneBase[NORMAL_SCENE_NUM] = std::make_unique<CEnding>();
		m_pCSceneBase[NORMAL_SCENE_NUM]->SetEvaluation(Evaluation);
		if (m_bFlyToSceneFlag == true) {
			m_pCSceneBase[NORMAL_SCENE_NUM]->SetEvaluation(m_FlyToSceneEvaluation);
		}
		break;
	}

	m_StartFlag = 0;
	//�t�F�[�h�J���鏈��.
	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);

	//�V�[���֔�񂾏ꍇ�̓t���O���~�낷.
	if (m_bFlyToSceneFlag == true) {
		m_bFlyToSceneFlag = false;
	}
}

//==========================================.
//		���̃V�[���ɐi�ޏ����֐�.
//==========================================.
void CSceneManager::NextScene()
{
	//���̃V�[����.
	m_SceneType++;
	if (m_SceneType >= static_cast<int>(enSceneType::Max)) {
		m_SceneType = static_cast<int>(enSceneType::Start);
	}

	//�^�C�g���Ɉړ�.
	if (m_pCSceneBase[NORMAL_SCENE_NUM]->GetTitleFlag() == true) {
		m_SceneType = static_cast<int>(enSceneType::Title);
	}
}

//==========================================.
//		�|�[�Y�����֐�.
//==========================================.
void CSceneManager::Pause()
{
	//�Q�[�����C���ȊO�ł͏������Ȃ�.
	if (m_SceneType != static_cast<int>(enSceneType::GameMain)) {
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

}

//===========================================.
//		�V�[���ɔ�ԏ����֐�.
//===========================================.
void CSceneManager::FlyToScene()
{
	//�V�[���ɔ�ԏ����J�n.
	if (GetAsyncKeyState(VK_F2) & 0x0001) {
		if (m_bFlyToSceneFlag == true) {
			m_bFlyToSceneFlag = false;
			return;
		}
		m_bFlyToSceneFlag = true;
	}

	//��O����.
	if (m_bFlyToSceneFlag == false) {
		return;
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_FlyToSceneNum--;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_FlyToSceneNum++;
	}

	//����ݒ�.
	if (m_FlyToSceneNum < 0) {
		m_FlyToSceneNum = 0;
	}
	if (m_FlyToSceneNum > m_FlyToSceneMax - 1) {
		m_FlyToSceneNum = m_FlyToSceneMax - 1;
	}

	//��ԃV�[�����菈��.
	if(GetAsyncKeyState(VK_RETURN) & 0x0001){
		//�V���b�^�[�����悤����.
		m_pCSceneFade->SetShutterFlag(m_pCSceneFade->CLOSE_FLAG);

		//�G���f�B���O��3�̐ݒ菈��.
		if (m_FlyToSceneNum >= static_cast<int>(enSceneType::Ending)) {
			m_SceneType = static_cast<int>(enSceneType::Ending);
			m_FlyToSceneEvaluation = m_FlyToSceneNum - m_SceneType;
			return;
		}

		m_SceneType = m_FlyToSceneNum;
	}
}

//===========================================.
//		�f�o�b�O�p�̃t�H���g�`�揈���֐�.
//===========================================.
void CSceneManager::RenderDebugFont()
{
	//��ԃV�[����.
	const std::vector<std::string> stSceneName = {
		"Title",
		"GameMain",
		"LowEvaluationEnding",
		"IntermediateEvaluationEnding",
		"HightEvaluationEnding",
		">"
	};

	//��ԃV�[�����ő�l.
	const int SceneMax = static_cast<int>(stSceneName.size()) - 1;
	//�J�[�\���ԍ�.
	const int CursorNum = static_cast<int>(stSceneName.size()) - 1;
	//�`�揈��.
	m_pCDepthStencil->SetDepth(false);
	for (int Scene = 0; Scene < SceneMax; Scene++) {
		m_pCDebugText->Render(stSceneName[Scene].c_str(), 50.0f, 200.0f + (30.0f * Scene));
	}
	m_pCDebugText->Render(stSceneName[CursorNum].c_str(), 20.0f, 200.0f + (30.0f * m_FlyToSceneNum));
	m_pCDepthStencil->SetDepth(true);

	m_FlyToSceneMax = SceneMax;
}