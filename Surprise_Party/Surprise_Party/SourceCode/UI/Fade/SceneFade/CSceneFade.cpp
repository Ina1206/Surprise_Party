#include "CSceneFade.h"

CSceneFade::CSceneFade()
	: m_pCSpriteUI				(nullptr)
	, m_vPos					(0.0f, 0.0f, 0.0f)
	, m_ShutterFlag				(0)
	, m_WaitChangeCnt			(0)
	, m_fMoveSpeed				(0.0f)
	, m_fFinishPoDistanceRatio	(0.0f)
{
	//�����������֐�.
	Init();
}

CSceneFade::~CSceneFade()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CSceneFade::Update()
{
	if (m_ShutterFlag == 0) {
		return;
	}

	//�ړ����x�̉�������.
	m_fMoveSpeed += ADD_MOVE_SPEED;

	if (m_ShutterFlag & CLOSE_FLAG) {
		//�V���b�^�[�����鏈���֐�.
		ShutterDown();

		return;
	}

	//�V���b�^�[�グ�鏈���֐�.
	ShutterUp();
}

//=====================================.
//		�`�揈���֐�.
//=====================================.
void CSceneFade::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetScale(0.8f);
	m_pCSpriteUI->Render();
}

//=====================================.
//		�����������֐�.
//=====================================.
void CSceneFade::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Shutter);
	m_ShutterFlag = OPEN_FLAG;
	m_vPos = SHUTTER_INIT_POS;
}

//=====================================.
//		��������֐�.
//=====================================.
void CSceneFade::Release()
{
	m_pCSpriteUI = nullptr;
}

//=====================================.
//		�V���b�^�[�����鏈���֐�.
//=====================================.
void CSceneFade::ShutterDown()
{
	m_vPos.y += m_fMoveSpeed;
	//�ŏI�n�_�܂ł̋���.
	const float INIT_FINISH_POS_DISNTANCE = fabsf(SHUTTER_HEIGHT_MIN - SHUTTER_INIT_POS.y);
	m_fFinishPoDistanceRatio = fabsf(m_vPos.y - SHUTTER_INIT_POS.y) / INIT_FINISH_POS_DISNTANCE;

	if (m_vPos.y >= SHUTTER_INIT_POS.y) {
		m_vPos.y = SHUTTER_INIT_POS.y;

		m_WaitChangeCnt++;
	}

	//�����҂��Ă���V�[���ύX.
	if (m_WaitChangeCnt >= WAIT_CHANGE_SCENE_TIME) {
		m_ShutterFlag = CHANGE_SCENE_FLAG;
		m_WaitChangeCnt = 0;
		m_fMoveSpeed = 0.0f;
	}
}

//=====================================.
//		�V���b�^�[�グ�鏈���֐�.
//=====================================.
void CSceneFade::ShutterUp()
{
	m_vPos.y -= m_fMoveSpeed;

	//�ŏI�n�_�܂ł̋���.
	const float INIT_FINISH_POS_DISTANCE = fabsf(SHUTTER_INIT_POS.y - SHUTTER_HEIGHT_MIN);
	m_fFinishPoDistanceRatio = 1.0f - fabsf(m_vPos.y - SHUTTER_HEIGHT_MIN) / INIT_FINISH_POS_DISTANCE;

	//�グ�鏈���I��.
	if (m_vPos.y <= SHUTTER_HEIGHT_MIN) {
		m_vPos.y = SHUTTER_HEIGHT_MIN;
		m_ShutterFlag = 0;
		m_fMoveSpeed = 0.0f;
	}
}