#ifndef CTITLE_H
#define CTITLE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Camera\CameraTitle\CCameraTitle.h"
#include "..\..\GameObject\Object\StaticObject\Light\FrontstageLight\CFrontstageLight.h"
#include "..\..\GameObject\Object\StaticObject\StaticObjectManager\CStaticObjectManager.h"
#include "..\..\GameObject\Object\MoveObject\MoveObjectManager\CMoveObjectManager.h"
#include "..\..\GameObject\Chara\Ghost\WorkGhost\MainStageWorkGhostBase\MainStageWorkGhsotManager\CMainStageWorkGhostManager.h"
#include "..\..\UI\SceneUI\TitleUI\CTitleUI.h"

/**********************************
*		�^�C�g���N���X.
******/
class CTitle
	: public CSceneBase
{
public:
	CTitle();
	~CTitle();

	//====================�֐�========================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.
protected:
	//====================�֐�========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void SettingView();	//�r���[�s��̐ݒ菈���֐�.

	//====================�ϐ�========================//.
	std::unique_ptr<CCameraTitle>				m_pCCameraTitle;			//�^�C�g���p�J�����N���X.
	std::unique_ptr<CFrontstageLight>			m_pCFrontstageLight;		//�\����̃��C�g�N���X
	std::unique_ptr<CStaticObjectManager>		m_pCStaticObjectManager;	//�ÓI�I�u�W�F�N�g�̊Ǘ��N���X.
	std::unique_ptr<CMoveObjectManager>			m_pCMoveObjectManager;		//���I�I�u�W�F�N�g�̊Ǘ��N���X.
	std::unique_ptr<CMainStageWorkGhostManager>	m_pCWorkGhostManager;		//�����������Ǘ��N���X.
	std::unique_ptr<CTitleUI>					m_pCTitleUI;				//�^�C�g��UI.
};


#endif	//#ifndef CTITLE_H.