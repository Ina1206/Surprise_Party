#include "CGhostIcon.h"

/*************************************
*		�������p�A�C�R���N���X.
*******/
CGhostIcon::CGhostIcon()
	: m_fStrength	(0.0f)
	, m_fStrengthMax(0.0f)
	, m_FaceType	(0)
{
	//�����������֐�.
	Init();
}

CGhostIcon::~CGhostIcon()
{
	//��������֐�.
	Release();
}

//====================================.
//		�X�V�����֐�.
//====================================.
void CGhostIcon::UpDate()
{
	//�Q�[��������}�b�v���ɍ��W�ϊ������֐�.
	GameMapConversion();

	//�I�𒆂̕\�������֐�.
	SelectingDisplay();

	//�I�΂ꂽ��̏���.
	if (m_bSelectedFlag == true) {
		m_vPattarn = SELECTED_FACE;
		return;
	}

	if (m_RestFlag == true) {
		m_vPattarn = REST_FACE;
		m_FaceType = static_cast<int>(enFaceType::Great_Face);
		return;
	}

	//�\��ύX�����֐�.
	ChangeFace();
	

}

//====================================.
//		�����������֐�.
//====================================.
void CGhostIcon::Init()
{
	m_vPattarn = GREAT_FACE;

	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Ghost_Icon);
	m_pCSpriteUI->SetPattern(m_vPattarn);

	//��ԏ��߂̕\��.
	m_FaceType = static_cast<int>(enFaceType::Great_Face);
}

//====================================.
//		��������֐�.
//====================================.
void CGhostIcon::Release()
{
	m_pCSpriteUI = nullptr;
}

//====================================.
//		�\��ύX�����֐�.
//====================================.
void CGhostIcon::ChangeFace()
{
	//�̗͂ŕ\��v�Z.
	if (m_fStrength <= m_fStrengthMax * (m_FaceType / STRENGTH_FACE_MAX)) {
		m_FaceType--;
		if (m_FaceType <= static_cast<int>(enFaceType::Bad_Face)) {
			m_FaceType = static_cast<int>(enFaceType::Bad_Face);
		}
	}

	//�\��ݒ�.
	switch (static_cast<enFaceType>(m_FaceType)) {
	case enFaceType::Bad_Face:
		m_vPattarn = BAD_FACE;
		break;
	case enFaceType::Normal_Face:
		m_vPattarn = NORMAL_FACE;
		break;
	case enFaceType::Good_Face:
		m_vPattarn = GOOD_FACE;
		break;
	case enFaceType::Great_Face:
		m_vPattarn = GREAT_FACE;
		break;
	}
}