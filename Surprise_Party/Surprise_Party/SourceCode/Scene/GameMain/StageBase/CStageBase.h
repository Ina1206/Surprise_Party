#ifndef CSTAGE_BASE_H
#define CSTAGE_BASE_H

#include "..\..\..\Global.h"
#include "..\..\..\Drawing\Resource\CResourceManager.h"

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


	//=====================�֐�=========================//.
	void RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);	//�`�揉���ݒ菈���֐�.
	void DebugStageChange();																												//�f�o�b�O�p�X�e�[�W�ύX�����֐�.

	virtual void UpDate(const bool& ControlFlag)	= 0;	//�X�V�����֐�.
	virtual void Render()							= 0;	//�`�揈���֐�.

	//===============���擾�����֐�===================//.
	//�X�e�[�W�ύX�t���O.
	bool GetChangeStageFlag() { return m_bChangeStageFlag; }
	//�O��̃X�e�[�W�G���f�B���O�^�C�v.
	enBeforeStageEndigneType GetBeforeStageEndingType() { return m_enBeforeStageEndingType; }
	
protected:
	//=====================�֐�=========================//.
	virtual void Init() = 0;		//�����������֐�.
	virtual void Release() = 0;		//��������֐�.
	virtual void Control() = 0;		//���쏈���֐�.

	//=====================�ϐ�=========================//.
	D3DXMATRIX					m_mView;					//�r���[�s��.
	D3DXMATRIX					m_mProj;					//�v���W�F�N�V�����s��.
	D3DXVECTOR3					m_vLightPos;				//���C�g���W.
	D3DXVECTOR3					m_vCameraPos;				//�J�������W.
	CAMERA						m_Camera;					//�J�����\����.

	bool						m_bChangeStageFlag;			//�X�e�[�W�ύX�t���O.
	int							m_StageNum;					//�X�e�[�W�ԍ�.

	enBeforeStageEndigneType	m_enBeforeStageEndingType;	//�O��̃X�e�[�W�̃G���f�B���O�^�C�v.
};

#endif	//#ifndef CSTAGE_BASE_H.