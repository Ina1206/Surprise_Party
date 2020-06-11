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
		return;
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