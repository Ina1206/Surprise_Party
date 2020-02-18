#ifndef CSTAGE_MANAGER_H
#define CSTAGE_MANAGER_H

#include "..\MainStage\CMainStage.h"
#include "..\GhostSpeakStage\CGhostSpeakStage.h"	
#include "..\..\..\UI\Fade\StageFade\CStageFade.h"

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

		Max,						//�ő吔.
		Start = GhostSpeakStage,	//����.
	};

	//====================�֐�=========================//.
	void Init();																													//�����������֐�.
	void UpDate();																													//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);		//�`�揈���֐�.
	void Release();																													//��������֐�.

private:
	//====================�֐�=========================//.
	void ChangeStage();								//�X�e�[�W�ύX�����֐�.

	//====================�ϐ�=========================//.
	std::unique_ptr<CStageBase>				m_pCStageBase;			//�X�e�[�W�N���X.
	int										m_StageType;			//�X�e�[�W���.
	int										m_StageNum;				//�X�e�[�W�ԍ�.
	CMainStage::enBeforeStageEndigneType	m_enBeforeEndingType;	//�O��̃X�e�[�W�G���f�B���O�^�C�v.
	std::unique_ptr<CStageFade>				m_pCStageFade;			//�X�e�[�W�t�F�[�h.
};

#endif	//#ifndef CSTAGE_MANAGER_H.