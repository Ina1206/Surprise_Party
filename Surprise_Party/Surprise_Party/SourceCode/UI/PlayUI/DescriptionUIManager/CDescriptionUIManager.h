#ifndef CDESCRIPTION_UI_MANAGER_H
#define CDESCRIPTION_UI_MANAGER_H

#include "..\Arrow\CArrow.h"
#include "..\TutorialBlackScreen\CTutorialBlackScreen.h"

/*****************************************
*		����UI�Ǘ��N���X.
**************/
class CDescriptionUIManager
{
public:
	CDescriptionUIManager();
	~CDescriptionUIManager();

	//======================�֐�=========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//================���u�������֐�===================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

private:
	//======================�֐�=========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//======================�ϐ�=========================//.
	std::unique_ptr<CArrow>						m_pCArrow;					//���N���X.
	std::unique_ptr<CTutorialBlackScreen>		m_pCTutorialBlackScreen;	//�`���[�g���A�������.
	D3DXVECTOR3									m_vCenterPos;				//���S���W.
};

#endif	//#ifndef CDESCRIPTION_UI_MANAGER_H.