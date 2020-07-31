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

	//======================�萔=========================//.
	const D3DXVECTOR3	GAGE_ARROW_POS	= D3DXVECTOR3(500.0f, -30.0f, 0.0f);//�Q�[�W�̖����W.
	const D3DXVECTOR3	CLOSE_ARROW_POS = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);	//��������W.

	//======================�֐�=========================//.
	void Update();															//�X�V�����֐�.
	void Render();															//�`�揈���֐�.

	//================���u�������֐�===================//.
	//�������W.
	void SetCenterPos(const D3DXVECTOR3& vGagePos, const D3DXVECTOR3& vTimePos);
	//�R�����g��i�߂鏈��.
	void SetAdvanceComment() { m_pCSpeakTutorial->AdvanceOnceComment(); }
	//�I���ړ��J�E���g�ǉ�����.
	void SetAddSelectMoveCount() { m_pCSpeakTutorial->AddSelectMoveCount(); }
	//�R�����g�ǉ��t���O.
	void SetAdvanceCommentFlag(const bool& flag) { m_pCSpeakTutorial->SetAdvanceCommentFlag(flag); }

	//================���擾�����֐�===================//.
	//�R�����g�ǉ��t���O.
	bool GetAdvanceCommentFlag() const { return m_pCSpeakTutorial->GetAdvanceCommentFlag(); }
	//�`���[�g���A���t���O.
	unsigned int GetTutorialFlag() const { return m_pCSpeakTutorial->GetTutorialFlag(); }
	//�J�n���O�t���O.
	unsigned int GetStartLatestFlag() const { return m_pCSpeakTutorial->GetStartLatestFlag(); }
	//�����I���t���O.
	bool GetDescriptionEndFlag() const { return m_pCSpeakTutorial->GetDescriptionEndFlag(); }
	//�S�Ẵt�H���g�\���t���O.
	bool GetAppearancedAllFont() const { return m_pCSpeakTutorial->GetAppearancedAllFont(); }

private:
	//======================�֐�=========================//.
	void Init();															//�����������֐�.
	void Release();															//��������֐�.
	D3DXVECTOR3 SettingArrowPos();											//�����W�ݒ菈���֐�.
	unsigned int SettingArrowFlag();										//���t���O�ݒ菈���֐�.
	void JudgeDescription();												//�������菈���֐�.

	//======================�ϐ�=========================//.
	std::unique_ptr<CArrow>						m_pCArrow;					//���N���X.
	std::unique_ptr<CTutorialBlackScreen>		m_pCTutorialBlackScreen;	//�`���[�g���A�������.
	std::unique_ptr<CSpeakTutorial>				m_pCSpeakTutorial;			//�`���[�g���A����b.
	D3DXVECTOR3									m_vCenterPos;				//���S���W.
	bool										m_bRenderArrowFlag;			//�����̖��̕`��t���O.
};

#endif	//#ifndef CDESCRIPTION_UI_MANAGER_H.