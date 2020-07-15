#ifndef CSTAGE_MANAGER_H
#define CSTAGE_MANAGER_H

#include "..\MainStage\CMainStage.h"
#include "..\GhostSpeakStage\CGhostSpeakStage.h"	
#include "..\..\..\UI\Fade\StageFade\CStageFade.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/**************************************************
*		�X�e�[�W�Ǘ��N���X.
********/
class CStageManager
{
public:
	CStageManager();
	~CStageManager();

	//=====================�萔=========================//.
	const unsigned int	FINISH_NEXT_ENDING	= (1 << 0);		//�I�����G���f�B���O�ֈړ�.
	const unsigned int	FINISH_NEXT_TITLE	= (1 << 1);		//�I�����^�C�g���ֈړ�.
	const int			NORMAL_STAGE_NUM	= 0;			//�ʏ�X�e�[�W�ԍ�.

	//====================�֐�=========================//.
	void Init();													//�����������֐�.
	void UpDate();													//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj);	//�`�揈���֐�.
	void Release();													//��������֐�.

	//==============���l�������֐�===================//.
	unsigned int GetFinishFlag() const { return m_FinishFlag; }
	int	GetAverageEvaluation() const { return m_AllEndingType / 3; }

	//==============���u�������֐�===================//.
	void SetPauseFlag(const bool& bFlag) { m_bPauseFlag = bFlag; }

private:
	//====================�֐�=========================//.
	void ChangeStage();								//�X�e�[�W�ύX�����֐�.

	//====================�ϐ�=========================//.
	std::vector<std::unique_ptr<CStageBase>>	m_pCStageBase;			//�X�e�[�W�N���X.
	int											m_StageType;			//�X�e�[�W���.
	int											m_StageNum;				//�X�e�[�W�ԍ�.
	CMainStage::enBeforeStageEndigneType		m_enBeforeEndingType;	//�O��̃X�e�[�W�G���f�B���O�^�C�v.
	std::unique_ptr<CStageFade>					m_pCStageFade;			//�X�e�[�W�t�F�[�h.
	unsigned int								m_FinishFlag;			//�I���t���O.
	unsigned int								m_bOldTutorialFlag;		//�`���[�g���A���t���O.
	int											m_AllEndingType;		//�S�ẴG���f�B���O�^�C�v�̍��v.
	bool										m_bPauseFlag;			//�|�[�Y�t���O.
	CPlaySoundManager*							m_pCPlaySoundManager;	//�ȍĐ��Ǘ��N���X.
};

#endif	//#ifndef CSTAGE_MANAGER_H.