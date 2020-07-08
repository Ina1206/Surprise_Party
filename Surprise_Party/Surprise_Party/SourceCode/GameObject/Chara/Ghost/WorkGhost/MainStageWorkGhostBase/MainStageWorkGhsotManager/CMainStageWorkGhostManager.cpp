#include "CMainStageWorkGhostManager.h"

/*************************************************
*		���C���X�e�[�W�̓����������Ǘ��N���X.
*******************/
CMainStageWorkGhostManager::CMainStageWorkGhostManager()
	: m_pCWorkGhost			()
	, m_vGimmickPos			()
	, m_vPeoplePos			()
	, m_UpDownFlag			()
	, m_fStageDistanceMax	(0.0f)
	, m_TutorialFlag		(0)
	, m_SelectNum			(0)
	, m_bPauseFlag			(false)
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

	for (int stage = 0; stage < m_pCFileResource->GetStageMax(StageType, 0); stage++) {
		const int CharaPosNum = m_pCFileResource->GetStageNum(StageType, StageNum, stage) - 1;
		if (CharaPosNum < 0 || CharaPosNum > 1) {
			continue;
		}

		switch (CharaPosNum) {
		case 0:
			//�����ݒ�.
			m_pCWorkGhost.emplace_back(new CMainStageDispGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 0.0f, 3.5f));
			break;
		case 1:
			m_pCWorkGhost.emplace_back(new CMainStageSwitchGhost());
			m_vWorkGhostPos.push_back(D3DXVECTOR3(stage * PosWidth, 3.5f, 3.5f));
			break;
		}
		//�v�f��.
		const int ElementNum = static_cast<int>(m_pCWorkGhost.size() - 1);
		m_pCWorkGhost[ElementNum]->SetPos(m_vWorkGhostPos[ElementNum]);
		m_pCWorkGhost[ElementNum]->SetInitMovePos();
	}

	m_UpDownFlag.resize(m_pCWorkGhost.size());

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

		//�`���[�g���A�������֐�(true���������Ă���Ώ����I��).
		if (m_TutorialFlag & TUTORIAL_STAGE_FLAG) {
			if (Tutorial(ghost)) break;
		}

		//�������X�V�����֐�.
		m_pCWorkGhost[ghost]->Update();

		//�������̍��W�擾.
		m_vWorkGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();

		//�v�f���ύX�����֐�.
		ChangeElementNum(ghost);

		//�I�u�W�F�N�g�㉺�����֐�.
		UpDownObuject(ghost);
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
		//�|�[�Y�t���O.
		m_pCWorkGhost[ghost]->SetPauseFlag(m_bPauseFlag);
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
//	�I�����Ă��邨�����̋x�e�t���O�擾�����֐�.
//================================================.
bool CMainStageWorkGhostManager::GetRestSelectGhostFlag() const
{
	if (m_pCWorkGhost[m_SelectNum]->GetMoveFlag() & m_pCWorkGhost[m_SelectNum]->REST_FLAG) {
		return true;
	}
	return false;
}

//================================================.
//		�`���[�g���A�������֐�.
//================================================.
bool CMainStageWorkGhostManager::Tutorial(const int& GhostNum)
{
	//�I��ҋ@���͏������I��������.
	if (m_TutorialFlag & SELECT_WAIT_FLAG) {
		return true;
	}

	if (m_TutorialFlag & EXPLAINING_FLAG) {
		//�`���[�g���A���t���O.
		m_pCWorkGhost[GhostNum]->SetTutorialFlag(true);

		//�I������t���O�ݒ�.
		if (m_TutorialFlag & GHOST_DECIDE_FLAG) {
			m_pCWorkGhost[GhostNum]->SetDecideSelectFlag(true);
			return false;
		}
		m_pCWorkGhost[GhostNum]->SetDecideSelectFlag(false);
		
		return false;
	}

	//�����I����.
	m_pCWorkGhost[GhostNum]->SetTutorialFlag(false);
	m_pCWorkGhost[GhostNum]->SetDecideSelectFlag(true);

	return false;
}

//================================================.
//		�v�f���ϊ������֐�.
//================================================.
void CMainStageWorkGhostManager::ChangeElementNum(const int& GhostNum) 
{
		
	D3DXVECTOR3 vTargetPos;							//�ڕW���W.
	std::unique_ptr<CMainStageWorkGhostBase> pTmp;	//�ύX�p�ϐ�.


	const int GHOST_MAX_NUM = m_pCWorkGhost.size() - 1;
	if (GhostNum < GHOST_MAX_NUM) {
		
		//�E�̂������̔ԍ�.
		const int RightGhostNum = GhostNum + 1;

		//������E.
		vTargetPos = m_pCWorkGhost[RightGhostNum]->GetPos();
		if (m_vWorkGhostPos[GhostNum].x > vTargetPos.x) {
			//�������̕ύX.
			pTmp.swap(m_pCWorkGhost[GhostNum]);
			m_pCWorkGhost[GhostNum].swap(m_pCWorkGhost[RightGhostNum]);
			m_pCWorkGhost[RightGhostNum].swap(pTmp);
	
			//�J�[�\�������鎞�͔ԍ����ړ�������.
			if (m_SelectNum == GhostNum) {
				m_SelectNum = RightGhostNum;
				return;
			}

			if (fabs(m_SelectNum - RightGhostNum) != 0) {
				return;
			}
			//�E�ɃJ�[�\��������ꍇ�͑I��ԍ��ύX.
			if (m_SelectNum == RightGhostNum) {
				m_SelectNum = GhostNum;
			}
		}
	}

	if (GhostNum > 0) {
	
		//���̂������̔ԍ�.
		const int LeftGhostNum = GhostNum - 1;
		
		//�E���獶.
		vTargetPos = m_pCWorkGhost[LeftGhostNum]->GetPos();
		if (m_vWorkGhostPos[GhostNum].x < vTargetPos.x) {
			pTmp.swap(m_pCWorkGhost[GhostNum]);
			m_pCWorkGhost[GhostNum].swap(m_pCWorkGhost[LeftGhostNum]);
			m_pCWorkGhost[LeftGhostNum].swap(pTmp);
	
			if (m_SelectNum == GhostNum) {
				m_SelectNum = LeftGhostNum;
				return;
			}
			if (fabs(m_SelectNum - LeftGhostNum) != 0) {
				return;
			}
			//���ɃJ�[�\��������ꍇ�͑I��ԍ��ύX.
			if (m_SelectNum == LeftGhostNum) {
				m_SelectNum = GhostNum;
			}
		}
	}

}

//================================================.
//		�I�u�W�F�N�g�㉺�����֐�.
//================================================.
void CMainStageWorkGhostManager::UpDownObuject(const int& GhostNum)
{
	//�M�~�b�N�̈ړ��t���O�ݒ�.
	int UseGimmickNum = m_pCWorkGhost[GhostNum]->GetUseGimmickNum();

	if (UseGimmickNum < 0) {
		m_UpDownFlag[GhostNum] = 0;
		return;
	}

	//�I�u�W�F�N�g�����鏈��.
	if (m_pCWorkGhost[GhostNum]->GetUpDownFlag() & m_pCWorkGhost[GhostNum]->DOWN_FLAG) {
		m_UpDownFlag[GhostNum] = OBJ_DOWN_FLAG;
		return;
	}

	//�I�u�W�F�N�g�グ�鏈��.
	if (m_pCWorkGhost[GhostNum]->GetUpDownFlag() & m_pCWorkGhost[GhostNum]->UP_FLAG) {
		m_UpDownFlag[GhostNum] = OBJ_UP_FLAG;
	}

}

//================================================.
//		��������֐�.
//================================================.
void CMainStageWorkGhostManager::Release()
{

}