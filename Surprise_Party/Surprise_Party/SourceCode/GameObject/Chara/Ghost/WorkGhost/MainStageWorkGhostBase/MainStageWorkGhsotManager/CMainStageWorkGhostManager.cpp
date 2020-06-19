#include "CMainStageWorkGhostManager.h"

/*************************************************
*		���C���X�e�[�W�̓����������Ǘ��N���X.
*******************/
CMainStageWorkGhostManager::CMainStageWorkGhostManager()
	: m_pCWorkGhost			()
	, m_vGimmickPos			()
	, m_vPeoplePos			()
	//, m_tObjUpDownFlag		()
	, m_tUseGimmick			()
	, m_UpDownFlag			()
	, m_fStageDistanceMax	(0.0f)
	, m_TutorialFlag		(0)
	, m_SelectNum			(0)
{
}

CMainStageWorkGhostManager::~CMainStageWorkGhostManager()
{
	//��������֐�.
	Release();
}

//================================================.
//		�����������֐�.
//================================================.
void CMainStageWorkGhostManager::Init(const int& StageType, const int& StageNum, const float& PosWidth)
{
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();

	for (int stage = 0; stage < m_pCFileResource->GetStageMax(StageType); stage++) {
		switch (m_pCFileResource->GetStageNum(StageType, StageNum, stage) - 1) {
		case 0:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageDispGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 0.0f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(m_vWorkGhostPos[m_pCWorkGhost.size() - 1]);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		case 1:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageSwitchGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 3.5f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(m_vWorkGhostPos[m_pCWorkGhost.size() - 1]);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		}
	}
	//�������̍��W.
	//m_vWorkGhostPos.resize(m_pCWorkGhost.size());
	//�グ�����t���O.
	//m_tObjUpDownFlag.resize(m_pCWorkGhost.size());
	m_UpDownFlag.resize(m_pCWorkGhost.size());
	//�g�p�M�~�b�N.
	m_tUseGimmick.resize(m_pCWorkGhost.size());

}

//================================================.
//		�X�V�����֐�.
//================================================.
void CMainStageWorkGhostManager::Update()
{
	//������.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {

		//�������̍��W�擾.
		m_vWorkGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();

		//�X�e�[�W�S�̂̋����擾.
		m_pCWorkGhost[ghost]->SetStageDistanceMax(m_fStageDistanceMax);

		//�M�~�b�N�Ɛl�̍��W�擾.
		m_pCWorkGhost[ghost]->SetSurprisePosInfo(m_vGimmickPos, m_vPeoplePos);

		if (m_TutorialFlag & TUTORIAL_STAGE_FLAG) {
			if (m_TutorialFlag & EXPLAINING_FLAG) {
				//�`���[�g���A���t���O.
				m_pCWorkGhost[ghost]->SetTutorialFlag(true);

				//�I������t���O�ݒ�.
				if (m_TutorialFlag & GHOST_DECIDE_FLAG) {
					m_pCWorkGhost[ghost]->SetDecideSelectFlag(true);
				}
				else {
					m_pCWorkGhost[ghost]->SetDecideSelectFlag(false);
				}
			}
			else {
				m_pCWorkGhost[ghost]->SetTutorialFlag(false);
				m_pCWorkGhost[ghost]->SetDecideSelectFlag(true);
			}
			if (m_TutorialFlag & SELECT_WAIT_FLAG) {
				break;
			}
		}
		//�������X�V�����֐�.
		m_pCWorkGhost[ghost]->Update();

		//�������̍��W�擾.
		m_vWorkGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();
		D3DXVECTOR3 vTargetPos;
		std::unique_ptr<CMainStageWorkGhostBase> pTmp;
		//�������̗v�f���ϊ�����.
		if (ghost < m_pCWorkGhost.size() - 1) {
			//������E.
			vTargetPos = m_pCWorkGhost[ghost + 1]->GetPos();
			if (m_vWorkGhostPos[ghost].x > vTargetPos.x) {
				//�������̕ύX.
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost + 1]);
				m_pCWorkGhost[ghost + 1].swap(pTmp);

				//�J�[�\�������鎞�͔ԍ����ړ�������.
				if (m_SelectNum == ghost) {
					m_SelectNum = ghost + 1;
				}
			}
		}
		if (ghost > 0) {
			//�E���獶.
			vTargetPos = m_pCWorkGhost[ghost - 1]->GetPos();
			if (m_vWorkGhostPos[ghost].x < vTargetPos.x) {
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost - 1]);
				m_pCWorkGhost[ghost - 1].swap(pTmp);

				if (m_SelectNum == ghost) {
					m_SelectNum = ghost - 1;
				}
			}
		}

		//�g�p���Ă���M�~�b�N�ݒ�.
		if (m_pCWorkGhost[ghost]->GetUseGimmickNum() >= 0) {
			m_tUseGimmick[ghost] = std::tuple<int, bool>(m_pCWorkGhost[ghost]->GetUseGimmickNum(), true);
		}

		//�M�~�b�N�̈ړ��t���O�ݒ�.
		int UseGimmickNum = m_pCWorkGhost[ghost]->GetUseGimmickNum();

		if (UseGimmickNum < 0) {
			//m_tObjUpDownFlag[ghost] = std::tuple<int, unsigned int>(UseGimmickNum, 0);
			m_UpDownFlag[ghost] = 0;
			continue;
		}

		//�I�u�W�F�N�g�����鏈��.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->DOWN_FLAG) {
			//m_tObjUpDownFlag[ghost] = std::tuple<int, unsigned int>(UseGimmickNum, OBJ_DOWN_FLAG);
			m_UpDownFlag[ghost] = OBJ_DOWN_FLAG;
			continue;
		}

		//�I�u�W�F�N�g�グ�鏈��.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->UP_FLAG) {
			//m_tObjUpDownFlag[ghost] = std::tuple<int, unsigned int>(UseGimmickNum, OBJ_UP_FLAG);
			m_UpDownFlag[ghost] = OBJ_UP_FLAG;
		}
	}

	//�������A�C�R�����I�΂�Ă���t���O.
	m_pCWorkGhost[m_SelectNum]->SetGhostSelectIcon(true);

}

//================================================.
//		�`�揈���֐�.
//================================================.
void CMainStageWorkGhostManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& Light, const D3DXVECTOR3& vCameraPos)
{
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//�������{�̂̕`�揈���֐�.
		m_pCWorkGhost[ghost]->SetCameraPos(vCameraPos);
		m_pCWorkGhost[ghost]->RenderInitSetting(mView, mProj, Light);
		m_pCWorkGhost[ghost]->Render();
	}

}

//================================================.
//		�A�C�R���`�揈���֐�.
//================================================.
void CMainStageWorkGhostManager::RenderIcon()
{
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		m_pCWorkGhost[ghost]->StrengthIconRender();
	}
}

//================================================.
//		�I��UI�`�揈���֐�.
//================================================.
void CMainStageWorkGhostManager::RenderSelectUI()
{
	m_pCWorkGhost[m_SelectNum]->SelectRender();
}

//================================================.
//		�I���������̋x�e���菈���֐�.
//================================================.
bool CMainStageWorkGhostManager::DecisionSelectRest()
{
	//�x�e����.
	if (m_pCWorkGhost[m_SelectNum]->GetMoveFlag() & m_pCWorkGhost[m_SelectNum]->REST_FLAG) {
		return true;
	}

	return false;
}

//================================================.
//		�I���������̋��������菈���֐�.
//================================================.
bool CMainStageWorkGhostManager::DecisionSelectSurprise()
{
	if (m_pCWorkGhost[m_SelectNum]->GetMoveFlag() &	m_pCWorkGhost[m_SelectNum]->SURPRISE_FLAG) {
		return true;
	}

	return false;
}

//================================================.
//		�������I�������֐�.
//================================================.
bool CMainStageWorkGhostManager::SelectGhost()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum++;

		if (m_SelectNum >= static_cast<int>(m_pCWorkGhost.size())) {
			m_SelectNum = m_pCWorkGhost.size() - 1;
		}
		return true;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum--;

		if (m_SelectNum < 0) {
			m_SelectNum = 0;
		}
		return true;
	}

	return false;
}

//================================================.
//		��������֐�.
//================================================.
void CMainStageWorkGhostManager::Release()
{

}