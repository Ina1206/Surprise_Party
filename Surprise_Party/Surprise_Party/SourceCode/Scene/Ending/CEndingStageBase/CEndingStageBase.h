#ifndef CENDING_STAGE_BASE_H
#define CENDING_STAGE_BASE_H

#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\EndingWorkGhost\EndingDispGhost\CEndingDispGhost.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\EndingWorkGhost\EndingSwitchGhost\CEndingSwitchGhost.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Object\StaticObject\Light\BackstageLight\CBackstageLight.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
class CEndingStageBase
{
public:
	CEndingStageBase();
	virtual ~CEndingStageBase();

	//========================�֐�=============================//.
	virtual void Update() = 0;								//�X�V�����֐�.
	virtual void Render() = 0;								//�`�揈���֐�.
	
	void RenderInitSetting(const D3DXMATRIX& mProj);		//�`�揉���ݒ菈���֐�.

protected:
	//========================�֐�=============================//.
	virtual void Init() = 0;								//�����������֐�.
	virtual void Release() = 0;								//��������֐�.

	void RenderFloor();										//���̕`�揈���֐�.
	void RenderBigGhost();									//�r�b�O�S�[�X�g�`�揈���֐�.
	void RenderWorkGhost();									//�����������`�揈���֐�.
	void RenderGhost();										//�������`�揈���֐�.

	//========================�ϐ�=============================//.
	D3DXMATRIX											m_mView;					//�r���[�s��.
	D3DXMATRIX											m_mProj;					//�v���W�F�N�V�����s��.
	CAMERA												m_Camera;					//�J�����\����.
	std::unique_ptr<CBackstageLight>					m_pCBackstageLight;			//���䗠���C�g�N���X.
	std::unique_ptr<CBigGhost>							m_pCBigGhost;				//�r�b�O�S�[�X�g�N���X.
	std::vector<std::unique_ptr<CEndingWorkGhostBase>>	m_pCEndingWorkGhostBase;	//�����������N���X.
	std::vector<std::unique_ptr<CGhostBase>>			m_pCGhost;					//�������N���X.

private:
	//========================�֐�=============================//.
	void InitCommonValue();									//���ʒl�̏����������֐�.
	void CreateInstanceFronClass(const int& num);			//�N���X����C���X�^���X���쐬���鏈���֐�.

	//========================�ϐ�=============================//.
	std::unique_ptr<CFloor>				m_pCFloor;			//���N���X.

};

#endif	//#ifndef CENDING_STAGE_BASE_H.