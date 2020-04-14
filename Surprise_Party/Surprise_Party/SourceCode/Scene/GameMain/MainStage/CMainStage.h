#ifndef CMAIN_STAGE_H
#define CMAIN_STAGE_H

#include "..\StageBase\CStageBase.h"
#include "..\..\..\GameObject/Object/StaticObject/StaticObjectManager/CStaticObjectManager.h"
#include "..\..\..\GameObject/Object/MoveObject/MoveObjectManager/CMoveObjectManager.h"
#include "..\..\..\FileLoad/FileResource/CFileResource.h"
#include "..\..\..\GameObject/Chara/Ghost/WorkGhost/DispGhost/CDispGhost.h"
#include "..\..\..\GameObject/Chara/Ghost/WorkGhost/SwitchGhost/CSwitchGhost.h"
#include "..\..\..\GameObject/Chara/People/PeopleManager/CPeopleManager.h"

#include "..\..\..\UI\MapUI\StageMap\CStageMap.h"
#include "..\..\..\UI\MapUI\CharaUI\MapCursor\MapGhostCursor\CMapGhostCursor.h"
#include "..\..\..\UI\MapUI\CharaUI\MapCursor\MapGimmickCursor\CMapGimmickCursor.h"
#include "..\..\..\UI\GameWorldUI\GameWorldCursor\GameGhostCursor\CGameGhostCursor.h"
#include "..\..\..\UI\PlayUI\ClosedTime\CClosedTime.h"
#include "..\..\..\UI\PlayUI\SurpriseGage\CSurpriseGage.h"

#include "..\..\..\UI\SpeakUI\SpeakTutorial\CSpeakTutorial.h"
#include "..\..\..\UI\SpeakUI\SpeakWorkGhost\CSpeakWorkGhost.h"
#include "..\..\..\UI\PlayUI\Arrow\CArrow.h"

/************************************
*		���C���X�e�[�W�N���X.
********/
class CMainStage
	: public CStageBase
{
public:

	CMainStage();
	CMainStage(int stageNum, enStageType enStage, enBeforeStageEndigneType enType);
	~CMainStage();

	//====================�萔=========================//.
	const D3DXVECTOR3	CAMERA_START_POS		= D3DXVECTOR3(11.9f, 7.5f, -19.9f);
	const D3DXVECTOR3	CAMERA_START_LOOK		= D3DXVECTOR3(11.9f, 5.3f, 4.0f);

	const unsigned int	GHOST_SELECTION_FLAG	= (1 << 0);		//�������I���t���O.
	const unsigned int	GHOST_ACT_SELECT_FLAG	= (1 << 1);		//�������̍s���I���t���O.
	const unsigned int	GIMMICK_SELECTION_FLAG	= (1 << 2);		//�M�~�b�N�I���t���O.

	const unsigned int	EXPLAINING_FLAG			= (1 << 0);		//�������t���O.
	const unsigned int	EXPLAINED_GHOST_FLAG	= (1 << 1);		//����������������t���O.
	const unsigned int	EXPLAINED_GIMMICK_FLAG	= (1 << 2);		//�M�~�b�N����������t���O.
	const unsigned int	EXPLAINED_MAP_FLAG		= (1 << 3);		//�}�b�v����������t���O.
	const unsigned int	EXPLAINED_GAGE_FLAG		= (1 << 4);		//�Q�[�W����������t���O.
	const unsigned int	EXPLAINED_CLOSE_FLAG	= (1 << 5);		//�X�̐��������t���O.

	const int			SLECTION_MAX			= 2;			//�I���ő��.
	const int			GHOST_NUM				= 0;			//�������ԍ�.
	const int			GIMMICK_NUM				= 1;			//�M�~�b�N�ԍ�.
	const int			TIME_DELIMITER			= 60;			//���ԋ�؂�.

	const int			START_TIME_UP_MAX		= 6;			//�J�n���̐������ԍő吔.
	const int			ADD_TIME_UP				= 1;			//�������Ԓǉ���.
	const int			BENEFITS_PREVIOS_RESULT	= 1;			//�O��̌��ʂ̓��T.

	const int			START_SUPRISE_GAGE_MAX	= 50;			//�J�n���̋����Q�[�W�̍ő吔.
	const int			SURPRISE_GAGE_ADD		= 20;			//�����Q�[�W�ǉ���.

	//====================�֐�=========================//.
	void UpDate(const bool& ControlFlag);			//�X�V�����֐�.
	void Render();									//�`�揈���֐�.
	void Control();									//���쏈���֐�.

private:
	//====================�֐�==========================//.
	void Init();									//�����������֐�.
	void Release();									//��������֐�.
	void GhostSelect();								//�������I�������֐�.
	void GimmickSelect();							//�M�~�b�N�I�������֐�.
	template <typename T>
	void GhostElementSort(T pClass, int array);		//�������v�f���ϊ������֐�.
	void CameraMove();								//�J�����ړ�����.
	void SpotLightUpdate();							//�X�|�b�g���C�g�X�V�����֐�.

	//===================�ϐ�=======================//.
	std::unique_ptr<CStaticObjectManager>			m_pCStaticObjectManager;	//�ÓI�I�u�W�F�N�g�Ǘ��N���X.
	std::unique_ptr<CMoveObjectManager>				m_pCMoveObjectManager;		//���I�I�u�W�F�N�g�Ǘ��N���X.
	std::vector<std::unique_ptr<CWorkGhostBase>>	m_pCWorkGhost;				//�����������N���X.
	std::unique_ptr<CPeopleManager>					m_pCPeopleManager;			//�l�Ǘ��N���X.

	std::unique_ptr<CStageMap>						m_pCStageMap;				//�X�e�[�W�}�b�v.
	std::unique_ptr<CMapCursor>						m_pCMapGhostCursor;			//�}�b�v��̂������̃J�[�\���N���X.

	std::vector<int>								m_SelectNum;				//�I��ԍ�.
	unsigned int									m_ObjectSelectFlag;			//�I�u�W�F�N�g�I���t���O.

	std::unique_ptr<CGameGhostCursor>				m_pCGameGhostCursor;		//�Q�[�����̂������̃J�[�\���N���X.

	std::unique_ptr<CClosedTime>					m_pCClosedTime;				//�X�܂ł̎��ԃN���X.
	std::unique_ptr<CSurpriseGage>					m_pCSurpriseGage;			//�����Q�[�W�N���X.
	
	std::vector<D3DXVECTOR3>						m_vLightPos;				//���C�g���W.

	enStageType										m_enStageType;				//�X�e�[�W�^�C�v.
	unsigned int									m_ExplainFlag;				//�����t���O.
	bool											m_bDispTextFlag;			//�e�L�X�g�\���t���O.

	std::unique_ptr<CSpeakTutorial>					m_pCSpeakTutorial;			//�`���[�g���A����b��.
	std::unique_ptr<CSpeakWorkGhost>				m_pCSpeakWorkGhost;			//������������b�N���X.
	std::unique_ptr<CArrow>							m_pCArrow;					//���N���X.
};

#endif	//#ifndef CMAIN_STAGE_H.