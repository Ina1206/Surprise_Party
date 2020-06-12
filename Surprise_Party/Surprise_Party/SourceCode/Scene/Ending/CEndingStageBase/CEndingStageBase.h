#ifndef CENDING_STAGE_BASE_H
#define CENDING_STAGE_BASE_H

#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\EndingWorkGhost\EndingDispGhost\CEndingDispGhost.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\EndingWorkGhost\EndingSwitchGhost\CEndingSwitchGhost.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Object\StaticObject\Light\BackstageLight\CBackstageLight.h"
#include "..\..\Camera\CameraEnding\CCameraEnding.h"
#include "..\..\UI\Fade\WhiteScreenFade\CWhiteScreenFade.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
class CEndingStageBase
{
public:
	CEndingStageBase();
	virtual ~CEndingStageBase();

	//===================�萔======================//.
	const float	ALPHA_MAX			= 1.0f;	//���ߒl�ő�l.
	const float ALPHA_MIN			= 0.0f;	//���ߒl�ŏ��l.
	const int	INIT_EVALUATION_NUM = -1;	//�����]���ԍ�.

	//========================�֐�=============================//.
	virtual void Update() = 0;								//�X�V�����֐�.
	virtual void Render() = 0;								//�`�揈���֐�.
	
	void RenderInitSetting(const D3DXMATRIX& mProj);		//�`�揉���ݒ菈���֐�.

	//==================���u�������֐�=======================//.
	//�]��.
	void SetEvaluation(const int& Evaluation) { m_Evaluation = Evaluation; }

	//==================���擾�����֐�=======================//.
	//�X�e�[�W�ύX�t���O.
	bool GetChangeStage() const { return m_bChangeStage; }

protected:
	//========================�֐�=============================//.
	virtual void Init() = 0;								//�����������֐�.
	virtual void Release() = 0;								//��������֐�.

	void RenderFloor();										//���̕`�揈���֐�.
	void RenderGhost();										//�������`�揈���֐�.
	void UpdatePushEnter();									//PushEnter�̍X�V�����֐�.

	//========================�ϐ�=============================//.
	D3DXMATRIX											m_mView;					//�r���[�s��.
	D3DXMATRIX											m_mProj;					//�v���W�F�N�V�����s��.
	std::unique_ptr<CBackstageLight>					m_pCBackstageLight;			//���䗠���C�g�N���X.
	std::vector<std::unique_ptr<CGhostBase>>			m_pCGhost;					//�������N���X.
	std::unique_ptr<CCameraEnding>						m_pCCameraEnding;			//�G���f�B���O�J����.
	std::unique_ptr<CWhiteScreenFade>					m_pCWhiteScreenFade;		//����ʂ̃t�F�[�h.
	int													m_Evaluation;				//�]��.
	int													m_OldEvaluation;			//�����p�]��.
	bool												m_bChangeStage;				//�X�e�[�W�ύX�t���O.
	D3DXVECTOR3											m_vObjLookPos;				//�I�u�W�F�N�g������ꏊ.
private:
	//========================�֐�=============================//.
	void InitCommonValue();									//���ʒl�̏����������֐�.
	void CreateInstanceFronClass(const int& num);			//�N���X����C���X�^���X���쐬���鏈���֐�.

	//========================�ϐ�=============================//.
	std::unique_ptr<CFloor>		m_pCFloor;					//���N���X.
	CSpriteUI*					m_pCPushEnterUI;			//SpriteUI�N���X(PushEnter�̕���).
	float						m_fPushEnterUIAlpha;		//SpriteUI�̓��ߒl.
	int							m_AlphaAddDecDirect;		//���ߒl�̉��Z���Z����.
};

#endif	//#ifndef CENDING_STAGE_BASE_H.