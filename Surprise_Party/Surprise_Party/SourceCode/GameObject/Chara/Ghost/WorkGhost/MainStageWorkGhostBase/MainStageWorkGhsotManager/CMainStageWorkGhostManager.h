#ifndef CMAINSTAGE_WORKGHOST_MANAGER_H
#define CMAINSTAGE_WORKGHOST_MANAGER_H

#include "..\MainStageDispGhost\CMainStageDispGhost.h"
#include "..\MainStageSwitchGhost\CMainStageSwitchGhost.h"
#include <tuple>

/*************************************************
*		���C���X�e�[�W�̓����������Ǘ��N���X.
*******************/
class CMainStageWorkGhostManager
{
public:
	CMainStageWorkGhostManager();
	~CMainStageWorkGhostManager();

	//====================�萔=========================//.
	const unsigned int OBJ_DOWN_FLAG		= (1 << 0);	//�I�u�W�F�N�g��������t���O.
	const unsigned int OBJ_UP_FLAG			= (1 << 1);	//�I�u�W�F�N�g���グ��t���O.

	const unsigned int TUTORIAL_STAGE_FLAG	= (1 << 0);	//�`���[�g���A���X�e�[�W�t���O.
	const unsigned int EXPLAINING_FLAG		= (1 << 1);	//�������Ă���t���O.
	const unsigned int GHOST_DECIDE_FLAG	= (1 << 2);	//�����������߂�t���O.
	const unsigned int SELECT_WAIT_FLAG		= (1 << 3);	//�I����ҋ@����t���O.

	//=======================�֐�======================//.
	void Init(const int& StageType, const int& StageNum, const float& PosWidth);																										//�����������֐�.
	void Update();																										//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& Light, const D3DXVECTOR3& vCameraPos);	//�`�揈���֐�.
	void RenderIcon();																									//�A�C�R���`�揈���֐�.
	void RenderSelectUI();																								//�I��UI�`�揈���֐�.
	bool DecisionSelectRest();																							//�I���������̋x�e���菈���֐�.
	bool DecisionSelectSurprise();																						//�I���������̋��������菈���֐�.
	bool SelectGhost();																									//�������I�������֐�.

	//=================���u�������֐�================//.
	//�M�~�b�N�̍��W.
	void SetGimmickPos(const std::vector<D3DXVECTOR3>& vPos) { m_vGimmickPos = vPos; }
	//�X�e�[�W�̋����ő�l.
	void SetStageDisntaceMax(const float& fDistance) { m_fStageDistanceMax = fDistance; }
	//�l�̍��W.
	void SetPeoplePos(const std::vector<D3DXVECTOR3>& vPos) { m_vPeoplePos = vPos; }
	//�������I���t���O.
	void SetSelectFlag(const bool& bFlag) { m_pCWorkGhost[m_SelectNum]->SetSelectFlag(bFlag); }
	//�������I�𒆎~�t���O.
	void SetSelectStop() { m_pCWorkGhost[m_SelectNum]->SetSelectStop(); }
	//�M�~�b�N�ύX�t���O.
	void SetChangeGimmickSelect(const bool& bFlag) { m_pCWorkGhost[m_SelectNum]->SetChangeGimmickSelect(bFlag); }
	//�ړI�M�~�b�N���W.
	void SetObjectiveGimmickPos(const D3DXVECTOR3& vPos) { m_pCWorkGhost[m_SelectNum]->SetObjectiveGimmickPos(vPos); }
	//�`���[�g���A���t���O���Ă�.
	void SetTutorialFlag(const unsigned int& flag) { m_TutorialFlag |= flag; }
	//�`���[�g���A���t���O���~�낷.
	void UnloadTutorialFlag(const unsigned int& flag) { m_TutorialFlag &= ~flag; }

	//=================���擾�����֐�================//.
	//�߂��ɂ���l�̔ԍ�.
	std::vector<int> GetNearPeopleNum(const int& ghostNum) const { return m_pCWorkGhost[ghostNum]->GetNearHumanNum(); }
	//�����������̑�����.
	unsigned int GetAllGhostNum() const { return m_pCWorkGhost.size(); }
	//�����������S���̍��W.
	std::vector<D3DXVECTOR3> GetAllGhostPos() const { return m_vWorkGhostPos; }
	//�I�����Ă��邨�����̍��W.
	D3DXVECTOR3 GetSelectGhostPos() const { return m_vWorkGhostPos[m_SelectNum]; }
	//�I�u�W�F�N�g�̏グ�����t���O.
	std::tuple<int, unsigned int> GetObjUpDownFlag(const int& ghostNum) const { return m_tObjUpDownFlag[ghostNum]; }
	//�g�p���Ă���M�~�b�N.
	std::tuple<int, bool> GetUseGimmick(const int& ghostNum) const { return m_tUseGimmick[ghostNum]; }
	//�`���[�g���A�����ɃR�����g�𑝂₷�t���O.
	bool GetTutorialAddCommentFlag(const int& ghostNum) const { return m_pCWorkGhost[ghostNum]->GetTutorialAddCommentFlag(); }
	//�I�����Ă��邨�����̑I���t���O.
	bool GetSelectGhostFlag() const { return m_pCWorkGhost[m_SelectNum]->GetSelectFlag(); }
	//�I�����Ă���M�~�b�N��ύX�t���O.
	bool GetChangeGimmickSelectFlag() const { return m_pCWorkGhost[m_SelectNum]->GetChangeGimmickSelect(); }
	//�������I�u�W�F�N�g�^�C�v.
	CGameObject::enSurpriseObjectType GetSurpriseObjectType() const { return m_pCWorkGhost[m_SelectNum]->GetSurpriseObjectType(); }
	//�g�p�M�~�b�N�ԍ�.
	int GetUseGimmickNum() const { return m_pCWorkGhost[m_SelectNum]->GetUseGimmickNum(); }


private:
	//=======================�֐�======================//.
	void Release();		//��������֐�.

	//====================�ϐ�=========================//.
	std::vector<std::unique_ptr<CMainStageWorkGhostBase>>	m_pCWorkGhost;			//����������.
	std::vector<D3DXVECTOR3>								m_vGimmickPos;			//�M�~�b�N�̍��W.
	std::vector<D3DXVECTOR3>								m_vPeoplePos;			//�l�̍��W.
	std::vector<D3DXVECTOR3>								m_vWorkGhostPos;		//�����������̍��W.

	std::vector<std::tuple<int, unsigned int>>				m_tObjUpDownFlag;		//�I�u�W�F�N�g�グ��������.
	std::vector<std::tuple<int, bool>>						m_tUseGimmick;			//�g�p���Ă���M�~�b�N.
	
	float													m_fStageDistanceMax;	//�X�e�[�W�̋����ő�l.
	
	unsigned int											m_TutorialFlag;			//�`���[�g���A���t���O.

	int														m_SelectNum;			//�������̑I��ԍ�.
};

#endif	//#ifndef CMAINSTAGE_WORKGHOST_MANAGER_H.