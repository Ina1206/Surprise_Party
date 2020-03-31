#include "CClosedTime.h"

CClosedTime::CClosedTime()
	: CClosedTime(0)
{

}

CClosedTime::CClosedTime(int MaxTime)
	: m_TimeUpToClose	(MaxTime)
	, m_TimeReduceCnt	(0)
	, m_GiveBornusTime	(false)
	, m_bClosedFlag		(false)
{
	//�����������֐�.
	Init();
}

CClosedTime::~CClosedTime()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CClosedTime::UpDate()
{
	//���Ԍv�Z�����֐�.
	TitmeCalc();

	//���Ԃ����炷����.
	if (m_TimeReduceCnt > TIME_REDUCE_DELIMITER) {
		m_TimeUpToClose--;
		m_TimeReduceCnt = 0;
	}

	//�ŏ��l����.
	if (m_TimeUpToClose <= TIME_MIN) {
		m_TimeUpToClose = TIME_MIN;
		m_bClosedFlag	= true;
	}

	//�J�E���g����.
	m_TimeReduceCnt++;
}

//======================================.
//		�ǉ����ԗ^���鏈���֐�.
//======================================.
void CClosedTime::GiveBornusTime(const bool& flag) 
{
	//�擾�t���O���~�낳��Ă������O����.
	if (flag == false) {
		return;
	}

	if (m_GiveBornusTime == false) {
		m_TimeUpToClose += TIME_REDUCE_DELIMITER * BONUS_TIME_ADD;

		m_GiveBornusTime = true;
	}

}

//======================================.
//		�����������֐�.
//======================================.
void CClosedTime::Init()
{
	//�T�C�Y.
	m_pCSpriteUI.resize(TIME_UI_MAX);
	m_vPatternNo.resize(m_pCSpriteUI.size());
	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIScale.resize(m_pCSpriteUI.size());
	m_fUIAlpha.resize(m_pCSpriteUI.size());

	//�A�h���X�擾.
	//����.
	for (unsigned int time = TIME_START_NUM; time < m_pCSpriteUI.size(); time++) {
		m_pCSpriteUI[time] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Time);
	}
	//�؂̔�.
	m_pCSpriteUI[TREE_BORD] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TreeBord);
	//�X����.
	m_pCSpriteUI[CLOSED_STRING_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::ClosedString);

	//�`�`�R�����A�؂̔̉摜�`�`.
	//�R�����ԍ�.
	const int COLON_NUM = m_pCSpriteUI.size() - 1;

	//�p�^�[���ݒ�.
	m_vPatternNo[COLON_NUM]			= COLON_PATTARN_NO;
	m_vPatternNo[TREE_BORD]			= TREE_PATTARN_NO;
	m_vPatternNo[CLOSED_STRING_NUM] = INIT_PATTARN_NO;

	//���W�ݒ�.
	m_vUIPos[COLON_NUM]			= COLON_POS;
	m_vUIPos[TREE_BORD]			= TREE_BORD_POS;
	m_vUIPos[CLOSED_STRING_NUM] = CLOSED_STRING_POS;

	for (int time = TIME_START_NUM; time < COLON_NUM; time++) {
		//���Ԃ̍��W�ݒ�.
		m_vUIPos[time] = TIME_POS;
		m_vUIPos[time].x += TIME_INTERVAL * (time - TIME_START_NUM);
		//�p�^�[��������.
		m_vPatternNo[time] = INIT_PATTARN_NO;
	}

	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		//�傫��.
		m_vUIScale[ui] = SCALE_MAX;
		//���ߒl.
		m_fUIAlpha[ui] = ALPHA_MAX;
	}

	//���Ԍv�Z�����֐�.
	TitmeCalc();
}

//======================================.
//		��������֐�.
//======================================.
void CClosedTime::Release()
{
	for (int ui = static_cast<int>(m_pCSpriteUI.size() - 1); ui <= 0; ui--) {
		m_pCSpriteUI[ui] = nullptr;
	}
}

//=======================================.
//		����(h)�v�Z�����֐�.
//=======================================.
void CClosedTime::HourCalc(int time) 
{
	int hour = m_TimeUpToClose / HOUR_DELIMITER;

	//�\�̈ʐ��l.
	m_vPatternNo[time].x = static_cast<float>(hour / NUM_RANK_DELIMITER);
	//��̈ʐ��l.
	m_vPatternNo[time + 1].x = static_cast<float>(hour % NUM_RANK_DELIMITER);
}

//=======================================.
//		��(m)�v�Z�����֐�.
//=======================================.
void CClosedTime::MinutesCalc(int time)
{
	//��(m).
	int minutes = m_TimeUpToClose % HOUR_DELIMITER;

	//�\�̈ʐ��l.
	m_vPatternNo[time].x = static_cast<float>(minutes / NUM_RANK_DELIMITER);
	//��̈ʐ��l.
	m_vPatternNo[time + 1].x = static_cast<float>(minutes % NUM_RANK_DELIMITER);
}

//========================================.
//		���Ԍv�Z�����֐�.
//========================================.
void CClosedTime::TitmeCalc()
{
	//����(h)�v�Z�t���O.
	bool HourCalcFlag = false;

	for (unsigned int time = TIME_START_NUM; time < m_pCSpriteUI.size() - 1; time += 2) {
		//����(h)�̐��l�v�Z����.
		if (HourCalcFlag == false) {
			HourCalc(time);

			HourCalcFlag = true;
			continue;
		}

		//��(m)�̐��l�v�Z�����֐�.
		MinutesCalc(time);
	}
}