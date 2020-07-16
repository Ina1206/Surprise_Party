#ifndef CSCENE_UI_BASE_H
#define CSCENE_UI_BASE_H

#include "..\CUI.h"
#include "ChangeSceneCursorUI\CChangeSceneCursorUI.h"
#include "SelectStringUI\CSelectStringUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*****************************************
*		�V�[��UI�̊��N���X.
****************/
class CSceneUIBase
	: public CUI
{
public:
	CSceneUIBase();
	virtual ~CSceneUIBase();

	//===================�֐�========================//.
	virtual void Update() = 0;										//�X�V�����֐�.
	void Render();													//�`�揈���֐�.

	//=============���擾�����֐�==================//.
	//�I���I���t���O.
	bool GetSelectFinishFlag() const { return m_pCCursor->GetSelectFinishFlag(); }

protected:
	//===================�֐�========================//.
	virtual void RenderSceneTitle();								//�V�[���^�C�g���`�揈���֐�.

	//===================�ϐ�========================//.
	CSpriteUI*								m_pCSpriteUI;			//�X�v���C�gUI.
	std::unique_ptr<CChangeSceneCursorUI>	m_pCCursor;				//�J�[�\���N���X.
	std::unique_ptr<CSelectStringUI>		m_pCSelectStringUI;		//�I�𕶏�UI�N���X.
	CPlaySoundManager*						m_pCPlaySoundManager;	//���Đ��Ǘ��N���X.

private:
	//===================�֐�========================//.
	void Release();													//��������֐�.

};

#endif	//#ifndef CSCENE_UI_BASE_H.