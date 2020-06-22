#ifndef CSTAGE_BASE_H
#define CSTAGE_BASE_H

#include "..\..\..\Global.h"
#include "..\..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\Camera\CCameraBase.h"

/*****************************************
*		�X�e�[�W���N���X.
********/
class CStageBase
{
public:
	CStageBase();
	virtual ~CStageBase();

	//===================�񋓑�========================//.
	//�O��̃X�e�[�W�̃G���f�B���O�^�C�v.
	enum class enBeforeStageEndigneType {
		Great = 0,	//�f���炵��.
		Good,		//�ǂ�.
		Bad,		//����.
		Nothing,	//�Ȃ�.
	};
	//�X�e�[�W���.
	enum class enStageType {
		GhostSpeakStage = 0,		//�������Ɖ�b����X�e�[�W.
		MainStage,					//���C���X�e�[�W.

		Tutorial,					//�`���[�g���A��.
		NormalStageMax = Tutorial,	//�ő吔.

		Start = GhostSpeakStage,	//����.
	};

	//=====================�萔=========================//.
	const unsigned int	FINISH_NEXT_ENDING	= (1 << 0);		//�����^�C�g���ł̏I��.
	const unsigned int	FINISH_NEXT_TITLE	= (1 << 1);		//�����Q�[���ł̏I��.

	const unsigned int TUTORIAL_START		= (1 << 0);		//�`���[�g���A���J�n.
	const unsigned int TUTORIAL_FINISH		= (1 << 1);		//�`���[�g���A���I��


	//=====================�֐�=========================//.
	void RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj);	//�`�揉���ݒ菈���֐�.
	void DebugStageChange();													//�f�o�b�O�p�X�e�[�W�ύX�����֐�.

	virtual void UpDate(const bool& ControlFlag)	= 0;	//�X�V�����֐�.
	virtual void Render()							= 0;	//�`�揈���֐�.

	//===============���擾�����֐�===================//.
	//�X�e�[�W�ύX�t���O.
	bool GetChangeStageFlag() const { return m_bChangeStageFlag; }
	//�O��̃X�e�[�W�G���f�B���O�^�C�v.
	enBeforeStageEndigneType GetBeforeStageEndingType() const { return m_enBeforeStageEndingType; }
	//�I���t���O.
	unsigned int GetFinishFlag() const { return m_FinishFlag; }
	//�`���[�g���A���t���O.
	unsigned int GetTutorialFlag() const { return m_TutorialFlag; }

	//===============���u�������֐�====================//.
	//�`���[�g���A���t���O.
	void SetTutorialFlag(const unsigned int& flag) { m_TutorialFlag = flag; }
	//�|�[�Y�t���O.
	void SetPauseFlag(const bool& bflag) { m_bPauseFlag = bflag; }

protected:
	//=====================�֐�=========================//.
	virtual void Init() = 0;		//�����������֐�.
	virtual void Release() = 0;		//��������֐�.
	virtual void Control() = 0;		//���쏈���֐�.

	//=====================�ϐ�=========================//.
	D3DXMATRIX						m_mView;					//�r���[�s��.
	D3DXMATRIX						m_mProj;					//�v���W�F�N�V�����s��.

	bool							m_bChangeStageFlag;			//�X�e�[�W�ύX�t���O.
	int								m_StageNum;					//�X�e�[�W�ԍ�.

	enBeforeStageEndigneType		m_enBeforeStageEndingType;	//�O��̃X�e�[�W�̃G���f�B���O�^�C�v.
	unsigned int					m_FinishFlag;				//�I���t���O.
	unsigned int					m_TutorialFlag;				//�`���[�g���A���t���O.

	std::unique_ptr<CCameraBase>	m_pCCamera;					//�J�����N���X.

	bool							m_bPauseFlag;				//�|�[�Y�t���O.
};

#endif	//#ifndef CSTAGE_BASE_H.