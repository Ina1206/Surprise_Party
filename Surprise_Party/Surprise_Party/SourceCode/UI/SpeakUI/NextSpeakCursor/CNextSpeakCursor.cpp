#include "CNextSpeakCursor.h"

/*****************************************
*		���̉�b�̃J�[�\���N���X.
*****************/
CNextSpeakCursor::CNextSpeakCursor()
	: m_pCSpriteUI	(nullptr)
	, m_vDispPos	(0.0f, 0.0f, 0.0f)
	, m_bDispFlag	(false)
{
	//�����������֐�.
	Init();
}

CNextSpeakCursor::~CNextSpeakCursor()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CNextSpeakCursor::Update()
{
	//�`�悵�Ă��Ȃ��ꍇ�͏����I��.
	if (m_bDispFlag == false) {
		m_vPos = m_vDispPos;
		m_fAcc = 0.0f;
		return;
	}

	if (m_fAcc < ACC_SPEED) {
		m_vPos.y = m_vDispPos.y;
	}

	//�㉺�ړ�.
	m_vPos.x = m_vDispPos.x;
	m_fAcc += ACC_SPEED;
	if (m_vPos.y > m_vDispPos.y) {
		m_fAcc = 0.0f;
	}

	m_vPos.y += m_fAcc - GRAVITY;
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CNextSpeakCursor::Render()
{
	//�`�悵�Ă��Ȃ��ꍇ�͏����I��.
	if (m_bDispFlag == false) {
		return;
	}

	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetScale(m_fScale);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//========================================.
//		�����������֐�.
//========================================.
void CNextSpeakCursor::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::NextSpeakCursor);

	m_fAcc = 0.0f;

	m_fAlpha = ALPHA_MAX;
	m_fScale = SCALE_MAX;
}

//========================================.
//		��������֐�.
//========================================.
void CNextSpeakCursor::Release()
{

}