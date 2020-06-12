#include "CEndingSwitchGhost.h"

/*******************************************
*		�G���f�B���O�X�C�b�`�������N���X.
******************/
CEndingSwitchGhost::CEndingSwitchGhost()
	: m_MoveDirect	(1)
	, m_bSetDirect	(false)
{
	//�����������֐�.
	Init();
}

CEndingSwitchGhost::~CEndingSwitchGhost()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�X�V�����֐�.
//===========================================.
void CEndingSwitchGhost::Update()
{
	//�G�t�F�N�g�ύX�����֐�.
	ChangeEffect();

	if (m_pCSpriteEffect != nullptr) {
		m_pCSpriteEffect->SetCenterPos(m_vPos);
		m_pCSpriteEffect->Update();
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		//��ъ���s�������֐�.
		ActRejoiceEmotion();
		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::GoodFeeling)) {
		//�㉺�ړ������֐�.
		MoveUpDown();

		//���@�����̍s�������֐�.
		ActGoodFeeling();

		//�G�t�F�N�g�Đ��Ǘ������֐�.
		PlayEffectManager();
		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::HaveTrounble)) {
		ActHaveTrouble();
	}

	//�ړ��p�x�����֐�.
	MoveRotation(m_vPos, m_vLookAtPos);

}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CEndingSwitchGhost::Render()
{
	//�X�C�b�`�������`�揈���֐�.
	RenderSwitchGhost(m_vPos);

	//�G�t�F�N�g�`�揈���֐�.
	if (m_pCSpriteEffect != nullptr) {
		m_pCSpriteEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//===========================================.
//		�����������֐�.
//===========================================.
void CEndingSwitchGhost::Init()
{
	//�ÓI�I�u�W�F�N�g�����������������֐�.
	InitStaticMeshGhost();

	m_fScale = SCALE;
	m_vPrePos.y = PRE_POS_Y;

	//�W�����v��������.
	m_fAccMax	= ACC_MAX;
	m_fAcc		= m_fAccMax;
	m_fAccSpeed = ACC_SPEED;
	m_fGravity	= GRAVITY;

}

//===========================================.
//		��������֐�.
//===========================================.
void CEndingSwitchGhost::Release()
{

}

//===========================================.
//		��ъ���s����������.
//===========================================.
void CEndingSwitchGhost::ActRejoiceEmotion()
{
	//�����ݒ菈���֐�.
	SettingInitDirect();

	//�W�����v�����֐�.
	Jump();

	m_vPos.x += MOVE_SPEED * m_MoveDirect;

	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_MoveDirect *= CHANGE_DIRECT;
	}
}

//===========================================.
//		���������ݒ菈���֐�.
//===========================================.
void CEndingSwitchGhost::SettingInitDirect()
{
	if (m_bSetDirect == true) {
		return;
	}

	if (m_vPos.x < m_vLookAtPos.x) {
		m_MoveDirect *= CHANGE_DIRECT;
	}
	m_bSetDirect = true;
}

//===========================================.
//		������������֐�.
//===========================================.
void CEndingSwitchGhost::ActHaveTrouble()
{
	//�����鏈��.
	m_vPos.y -= DOWN_SPEED;
	if (m_vPos.y < 0.0f) {
		m_vPos.y = 0.0f;

		return;
	}

	//������ԉ��ړ�����.
	const float m_Distance = m_vPos.x - m_vLookAtPos.x;
	const float	m_Direct = m_Distance / fabsf(m_Distance);
	m_vPos.x += MOVE_SPEED * m_Direct;
}