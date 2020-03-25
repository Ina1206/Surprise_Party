#ifndef CSTAGE_MANAGER_H
#define CSTAGE_MANAGER_H

#include "..\MainStage\CMainStage.h"
#include "..\GhostSpeakStage\CGhostSpeakStage.h"	
#include "..\..\..\UI\Fade\StageFade\CStageFade.h"
#include "..\..\Scene\Tutorial\CTutorial.h"

/**************************************************
*		�X�e�[�W�Ǘ��N���X.
********/
class CStageManager
{
public:
	CStageManager();
	~CStageManager();
	//===================�񋓑�========================//.
	//�X�e�[�W���.
	enum class enStageType {
		GhostSpeakStage,			//�������Ɖ�b����X�e�[�W.
		MainStage,					//���C���X�e�[�W.

		Tutorial,					//�`���[�g���A��.
		NormalStageMax = Tutorial,	//�ő吔.

		Start = GhostSpeakStage,	//����.
	};

	//=====================�萔=========================//.
	const unsigned int	FINISH_NEXT_ENDING	= (1 << 0);		//�����^�C�g���ł̏I��.
	const unsigned int	FINISH_NEXT_GAME	= (1 << 1);		//�����Q�[���ł̏I��.
	const int			NORMAL_STAGE_NUM	= 0;			//�ʏ�X�e�[�W�ԍ�.

	//====================�֐�=========================//.
	void Init();																													//�����������֐�.
	void UpDate();																													//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);		//�`�揈���֐�.
	void Release();																													//��������֐�.

	//==============���l�������֐�===================//.
	unsigned int GetFinishFlag() const { return m_FinishFlag; }

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
	bool										m_bOldTutorialFlag;		//�`���[�g���A���t���O.
};

#endif	//#ifndef CSTAGE_MANAGER_H.