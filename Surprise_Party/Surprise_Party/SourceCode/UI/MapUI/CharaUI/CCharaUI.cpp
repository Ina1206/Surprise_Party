#include "CCharaUI.h"

CCharaUI::CCharaUI()
	: m_vCharaPos	(0.0f, 0.0f, 0.0f)
	, m_fStageMax	(0.0f)
{

}

CCharaUI::~CCharaUI()
{

}

//==============================================.
//	�Q�[��������}�b�v���ɍ��W�ϊ������֐�
//==============================================.
void CCharaUI::GameMapConversion()
{
	//�L�����N�^��x���W���}�b�v�̕��̍��W�ɍ��킹��.
	m_vPos.x = (MAP_DISTANCE_MAX * m_vCharaPos.x) / m_fStageMax;
}