#ifndef CDESCRIPTION_UI_MANAGER_H
#define CDESCRIPTION_UI_MANAGER_H

#include "..\Arrow\CArrow.h"
#include "..\TutorialBlackScreen\CTutorialBlackScreen.h"
#include "..\..\SpeakUI\SpeakTutorial\CSpeakTutorial.h"

/*****************************************
*		����UI�Ǘ��N���X.
**************/
class CDescriptionUIManager
{
public:
	CDescriptionUIManager();
	~CDescriptionUIManager();

	//======================�֐�=========================//.
	void Update();					//�X�V�����֐�.
	void Render();					//�`�揈���֐�.

	//================���u�������֐�===================//.
	void SetCenterPos(const D3DXVECTOR3& vGagePos, const D3DXVECTOR3& vTimePos);
	void SetAdvanceComment() { m_pCSpeakTutorial->AdvanceOnceComment(); }
	void SetAddSelectMoveCount() { m_pCSpeakTutorial->AddSelectMoveCount(); }
	void SetAdvanceCommentFlag(const bool& flag) { m_pCSpeakTutorial->SetAdvanceCommentFlag(flag); }

	//================���擾�����֐�===================//.
	bool GetAdvanceCommentFlag() const { return m_pCSpeakTutorial->GetAdvanceCommentFlag(); }
	unsigned int GetTutorialFlag() const { return m_pCSpeakTutorial->GetTutorialFlag(); }
	unsigned int GetStartLatestFlag() const { return m_pCSpeakTutorial->GetStartLatestFlag(); }
	bool GetDescriptionEndFlag() const { return m_pCSpeakTutorial->GetDescriptionEndFlag(); }
	bool GetAppearancedAllFont() const { return m_pCSpeakTutorial->GetAppearancedAllFont(); }
private:
	//======================�֐�=========================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.
	D3DXVECTOR3 SettingArrowPos();	//�����W�ݒ菈���֐�.
	unsigned int SettingArrowFlag();//���t���O�ݒ菈���֐�.
	void JudgeDescription();		//�������菈���֐�.

	//======================�ϐ�=========================//.
	std::unique_ptr<CArrow>						m_pCArrow;					//���N���X.
	std::unique_ptr<CTutorialBlackScreen>		m_pCTutorialBlackScreen;	//�`���[�g���A�������.
	std::unique_ptr<CSpeakTutorial>				m_pCSpeakTutorial;			//�`���[�g���A����b.
	D3DXVECTOR3									m_vCenterPos;				//���S���W.
	bool										m_bRenderArrowFlag;			//�����̖��̕`��t���O.
};

#endif	//#ifndef CDESCRIPTION_UI_MANAGER_H.