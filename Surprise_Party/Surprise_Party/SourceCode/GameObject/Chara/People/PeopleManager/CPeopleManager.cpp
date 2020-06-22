#include "CPeopleManager.h"
#include <random>

CPeopleManager::CPeopleManager()
	: m_pCFileResource		(nullptr)
	, m_HumanAppOrder		()
	, m_pCPeopleBase		()
	, m_bDispFlag			()
	, m_vHumanPos			()
	, m_fStageDistanceMax	(0.0f)
	, m_CreateHumanMax		(0)
	, m_bSurpriseFlag		()
	, m_DispCnt				(DISP_TIME)
	, m_AppHumanNum			(0)
	, m_SurpriseHumanNum	()
	, m_AddSurprisePoint	(0)
	, m_pCPeopleIcon		()
	, m_bPauseFlag			(false)
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
void CPeopleManager::Init(int FileNum, int max, float StageMax)
{
	//�t�@�C���̓ǂݍ��݃A�h���X�擾.
	m_pCFileResource = CFileResource::GetResourceInstance();
	//�l�̃N���X���C���X�^���X������ő吔.
	m_CreateHumanMax = max;
	
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> IntervalRand(0, 2);
	int m_column = IntervalRand(mt);

	//�l�̎�ޔԍ��擾.
	for (int people = 0; people < m_pCFileResource->GetStageMax(FileNum); people++) {
		m_HumanAppOrder.push_back(m_pCFileResource->GetStageNum(FileNum, m_column, people) - 1);
	}

	//�l�Ɛl�̃A�C�R���̃C���X�^���X��.
	for (int people = 0; people < max; people++) {
		m_pCPeopleBase.push_back(nullptr);
		m_bDispFlag.push_back(false);
		m_pCPeopleIcon.push_back(nullptr);

		//�����F���̎q�A��F�j�̎q.
		if (people % 2 == 0) {
			m_pCPeopleBase[m_pCPeopleBase.size() - 1] = new CGirl();
			m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(StageMax);

			m_pCPeopleIcon[m_pCPeopleIcon.size() - 1].reset(new CGirlIcon());
			
			continue;
		}
		m_pCPeopleBase[m_pCPeopleBase.size() - 1] = new CBoy();
		m_pCPeopleBase[m_pCPeopleBase.size() - 1]->SetStageMax(StageMax);

		m_pCPeopleIcon[m_pCPeopleIcon.size() - 1].reset(new CBoyIcon());
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
	for (unsigned int human = 0; human < m_CreateHumanMax; human++) {
		if (m_bDispFlag[human] == true) {
			//�|�[�Y�t���O.
			m_pCPeopleBase[human]->SetPauseFlag(m_bPauseFlag);
			//�`�掞�ɕK�v�Ȓl�擾.
			m_pCPeopleBase[human]->SetCameraPos(vCameraPos);
			m_pCPeopleBase[human]->RenderInitSetting(mView, mProj, stLight);
			//�`�揈���֐�.
			m_pCPeopleBase[human]->Render();
		}
	}

	//�l�̃A�C�R���`�揈��.
	for (unsigned int icon = 0; icon < m_pCPeopleIcon.size(); icon++) {
		if (m_bDispFlag[icon] == true) {
			m_pCPeopleIcon[icon]->Render();
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
	for (int human = m_CreateHumanMax - 1; human >= 0; human--) {
		SAFE_DELETE(m_pCPeopleBase[human]);
	}
}

//=======================================.
//		�l�̕\�������֐�.
//=======================================.
void CPeopleManager::HumanApp()
{
	//�o�������鏈��.
	if (m_DispCnt == DISP_TIME) {
		for (unsigned int human = m_HumanAppOrder[m_AppHumanNum]; human < m_CreateHumanMax; human += 2) {
			//�l�����Ȃ��Ƃ��͏I��.
			if (m_HumanAppOrder[m_AppHumanNum] < 0) {
				break;
			}

			if (m_bDispFlag[human] == false) {
				m_pCPeopleBase[human]->SetPos(INIT_POS);
				m_bDispFlag[human] = true;
				m_pCPeopleBase[human]->SetDispFlag(true);
				break;
			}
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
	for (unsigned int human = 0; human < m_CreateHumanMax; human++) {
		if (m_bDispFlag[human] == true) {

			//�X�V�����֐�.
			m_pCPeopleBase[human]->Update();
			//�\���t���O�擾����.
			m_bDispFlag[human] = m_pCPeopleBase[human]->GetDispFlag();
			//�l�̍��W�擾.
			m_vHumanPos[human] = m_pCPeopleBase[human]->GetPos();
		}
	}
}
