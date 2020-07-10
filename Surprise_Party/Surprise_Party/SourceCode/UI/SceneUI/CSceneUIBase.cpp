#include "CSceneUIBase.h"

/*****************************************
*		�V�[��UI�̊��N���X.
****************/
CSceneUIBase::CSceneUIBase()
	: m_pCSpriteUI			()
	, m_pCCursor			(nullptr)
	, m_pCSelectStringUI	(nullptr)
{
	m_pCCursor.reset(new CChangeSceneCursorUI());
}

CSceneUIBase::~CSceneUIBase()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CSceneUIBase::Render()
{
	//�V�[���^�C�g���`�揈���֐�.
	RenderSceneTitle();

	//�I�𕶏�UI�`�揈���֐�.
	m_pCSelectStringUI->Render();

	//�J�[�\���̕`��.
	m_pCCursor->Render();

}

//===========================================.
//		��������֐�.
//===========================================.
void CSceneUIBase::Release()
{

}