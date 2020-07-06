#include "CPeopleManager.h"
#include <random>

CPeopleManager::CPeopleManager()
	: m_pCFileResource		(nullptr)
	, m_HumanAppOrder		()
	, m_pCPeopleBase		()
	, m_bDispFlag			()
	, m_vHumanPos			()
	, m_DisplayableHumanNum	()
	, m_fStageDistanceMax	(0.0f)
	, m_bSurpriseFlag		()
	, m_DispCnt				(DISP_TIME)
	, m_AppHumanNum			(0)
	, m_SurpriseHumanNum	()
	, m_AddSurprisePoint	(0)
	, m_pCPeopleIcon		()
	, m_bPauseFlag			(false)
	, m_bNotRenderIcon		(false)
{

}

CPeopleManager::~CPeopleManager()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�����������֐�.
//=======================================.
void CPeopleManager::Init(int FileNum, int StageNum, float StageMax)
{
	//�t�@�C���̓ǂݍ��݃A�h���X�擾.
	m_pCFileResource = CFileResource::GetResourceInstance();
	//�X�e�[�W�̒����ő�l��ݒ�.
	m_fStageDistanceMax = StageMax;
	
	//�l�̎�ޔԍ��擾.
	for (int people = 0; people < m_pCFileResource->GetStageMax(FileNum, StageNum); people++) {
		m_HumanAppOrder.push_back(m_pCFileResource->GetStageNum(FileNum, StageNum, people) - 1);
	}

	//�l���쐬�����֐�.
	for (int people = 0; people < 10; people++) {
		CreatHuman(people);
	}

	//�l�̍��W�v�f���擾.
	m_vHumanPos.resize(m_pCPeopleBase.size());
	//�����t���O�v�f���擾.
	m_bSurpriseFlag.resize(m_pCPeopleBase.size());

}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CPeopleManager::Update()
{
	//�����l�Ԃ̔ԍ��̍ő�l����.
	if (m_AppHumanNum >= m_HumanAppOrder.size()) {
		m_AppHumanNum = 0;
	}

	//�l�̕\�������֐�.
	HumanApp();

	//�l�̈ړ������֐�.
	HumanMove();

	//�l�̃A�C�R���X�V�����֐�.
	for (unsigned int icon = 0; icon < m_pCPeopleIcon.size(); icon++) {
		m_pCPeopleIcon[icon]->SetStageMax(m_fStageDistanceMax);
		m_pCPeopleIcon[icon]->SetCharaPos(m_pCPeopleBase[icon]->GetPos());
		m_pCPeopleIcon[icon]->UpDate();
	}
}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CPeopleManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos, const LIGHT& stLight)
{
	//�l�̕`�揈��.
	for (unsigned int human = 0; human < m_pCPeopleBase.size(); human++) {
		
		if (m_bDispFlag[human] == false) {
			//�`�悵�Ȃ�.
			continue;
		}

		//�|�[�Y�t���O.
		m_pCPeopleBase[human]->SetPauseFlag(m_bPauseFlag);
		//�`�掞�ɕK�v�Ȓl�擾.
		m_pCPeopleBase[human]->SetCameraPos(vCameraPos);
		m_pCPeopleBase[human]->RenderInitSetting(mView, mProj, stLight);
		//�`�揈���֐�.
		m_pCPeopleBase[human]->Render();
	}

	//�A�C�R���͕`�悵�Ȃ��悤�ɂ��鏈��.
	if (m_bNotRenderIcon == true) {
		return;
	}

	//�l�̃A�C�R���`�揈��.
	for (unsigned int icon = 0; icon < m_pCPeopleIcon.size(); icon++) {
		if (m_bDispFlag[icon] == true) {
			m_pCPeopleIcon[icon]->Render();
			m_pCPeopleIcon[icon]->RenderEffect();
		}
	}
}

//=======================================.
//���u�������֐�(�����Ă���l�ԍ�).
//=======================================.
void CPeopleManager::SetNowHumanSurprise(const std::vector<int>& HumanNum)
{
	//�ǉ��|�C���g������.
	m_AddSurprisePoint = 0;

	if (HumanNum.size() <= 0) {
		return;
	}

	for (unsigned int human = 0; human < HumanNum.size(); human++) {
		//�ǉ��|�C���g��.
		m_AddSurprisePoint += m_pCPeopleBase[HumanNum[human]]->GetAddPointQuantity(human);

		m_bSurpriseFlag[HumanNum[human]] = true;
		//�������t���O�擾.
		m_pCPeopleBase[HumanNum[human]]->SetSurpriseFlag(m_bSurpriseFlag[HumanNum[human]]);
		m_pCPeopleIcon[HumanNum[human]]->SetSurpriseFlag(m_bSurpriseFlag[HumanNum[human]]);

		//�߂��̐l�ԍ��擾.
		m_pCPeopleBase[HumanNum[human]]->SetHumanNearNum(human);

		//�������l�̍ő吔.
		m_pCPeopleBase[HumanNum[human]]->SetSurpriseHumanMax(HumanNum.size());
	}
}

//=======================================.
//		��������֐�.
//=======================================.
void CPeopleManager::Release()
{

}

//=======================================.
//		�l�̕\�������֐�.
//=======================================.
void CPeopleManager::HumanApp()
{
	if (m_DispCnt == DISP_TIME) {
		//�쐬�t���O.
		bool m_bCreatFlag = true;

		for (unsigned int people = 0; people < m_pCPeopleBase.size(); people++) {
			if (m_HumanAppOrder[m_AppHumanNum] < 0) {
				//�҂����ԂȂ̂ō쐬���Ȃ�.
				m_bCreatFlag = false;
				break;
			}

			if (m_HumanAppOrder[m_AppHumanNum] != m_DisplayableHumanNum[people]) {
				continue;
			}

			//�o�������鏈��.
			if (m_bDispFlag[people] == false) {
				m_pCPeopleBase[people]->SetPos(INIT_POS);
				m_bDispFlag[people] = true;
				m_pCPeopleBase[people]->SetDispFlag(true);
				m_bCreatFlag = false;
				break;
			}
		}

		//�l���쐬�����֐�.
		if (m_bCreatFlag == true) {
			CreatHuman(m_AppHumanNum);
		}

		m_AppHumanNum++;
		m_DispCnt = 0;
	}

	//�J�E���g����.
	m_DispCnt++;
}

//=======================================.
//		�l�̈ړ������֐�.
//=======================================.
void CPeopleManager::HumanMove()
{
	for (unsigned int human = 0; human < m_pCPeopleBase.size(); human++) {
		
		if (m_bDispFlag[human] == false) {
			//�ړ������Ȃ�.
			continue;
		}

		//�X�V�����֐�.
		m_pCPeopleBase[human]->Update();
		//�\���t���O�擾����.
		m_bDispFlag[human] = m_pCPeopleBase[human]->GetDispFlag();
		//�l�̍��W�擾.
		m_vHumanPos[human] = m_pCPeopleBase[human]->GetPos();
	}
}

//========================================.
//		�l���쐬�����֐�.
//========================================.
void CPeopleManager::CreatHuman(const int& HumanNum)
{
	m_bDispFlag.push_back(false);
	m_DisplayableHumanNum.push_back(m_HumanAppOrder[HumanNum]);
	//�l�̍��W�v�f���擾.
	m_vHumanPos.push_back(INIT_POS);
	//�����t���O�v�f���擾.
	m_bSurpriseFlag.push_back(false);

	//��.
	if (m_HumanAppOrder[HumanNum] == 0) {
		m_pCPeopleBase.emplace_back(new CGirl());
		m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(m_fStageDistanceMax);
		m_pCPeopleIcon.emplace_back(new CGirlIcon());
		return;
	}

	//�j.
	m_pCPeopleBase.emplace_back(new CBoy());
	m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(m_fStageDistanceMax);
	m_pCPeopleIcon.emplace_back(new CBoyIcon());

}