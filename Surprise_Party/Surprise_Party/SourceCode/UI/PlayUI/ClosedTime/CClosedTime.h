#ifndef CCLOSED_TIME_H
#define CCLOSED_TIME_H

#include "..\CPlayUI.h"

/************************************
*	�X����UI�N���X.
*********/
class CClosedTime
	: public CPlayUI
{
public:
	CClosedTime();
	CClosedTime(const int& StageNum);
	~CClosedTime();

	//====================�萔=====================//.
	const int			TIME_UI_MAX				= 7;	//����UI�ő吔.
	const int			TIME_START_NUM			= 2;	//���Ԃ̃X�v���C�g�J�n�ԍ�.
	const int			TREE_BORD				= 0;	//�؂̔ԍ�.
	const int			CLOSED_STRING_NUM		= 1;	//�X����.
	const int			HOUR_DELIMITER			= 60;	//����(h)��؂�.
	const int			NUM_RANK_DELIMITER		= 10;	//���l��؂�.
	const int			TIME_REDUCE_DELIMITER	= 60;	//���Ԍ��炷��؂�.
	const int			TIME_MIN				= 0;	//���ԍŏ��l.
	const int			BONUS_TIME_ADD			= 1;	//�{�[�i�X�ǉ�����.

	const D3DXVECTOR2	TREE_PATTARN_NO			= D3DXVECTOR2(1.0f, 0.0f);	//�؂̔̃p�^�[���ԍ�.
	const D3DXVECTOR2	COLON_PATTARN_NO		= D3DXVECTOR2(10.0f, 0.0f);	//�R�����p�^�[���ԍ�.
	
	const D3DXVECTOR3	COLON_POS				= D3DXVECTOR3(1110.0f, 640.0f, 0.0f);	//�؂̔̍��W.
	const D3DXVECTOR3	TREE_BORD_POS			= D3DXVECTOR3(980.0f, 580.0f, 0.0f);	//�R�����̍��W.
	const D3DXVECTOR3	CLOSED_STRING_POS		= D3DXVECTOR3(1080.0f, 580.0f, 0.0f);	//�X�����̍��W.
	const D3DXVECTOR3	TIME_POS				= D3DXVECTOR3(1055.0f, 640.0f, 0.0f);	//���Ԃ̍��W.
	
	const float			TIME_INTERVAL			= 50.0f;								//���Ԃ̊Ԋu.
	
	//====================�֐�=====================//.
	void Update();							//�X�V�����֐�.
	void GiveBornusTime(const bool& flag);	//�ǉ����ԗ^���鏈���֐�.

	//==============���擾�����֐�===============//.
	//�X�t���O.
	bool GetClosedFlag() { return m_bClosedFlag; }

private:
	//====================�֐�=====================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void HourCalc(int time);				//����(h)�v�Z�����֐�.
	void MinutesCalc(int time);				//��(m)�v�Z�����֐�.
	void TitmeCalc();						//���Ԍv�Z�����֐�.


	//====================�ϐ�=====================//.
	int		m_TimeUpToClose;				//�X�܂ł̎���.
	int		m_TimeReduceCnt;				//���Ԍ��炷�J�E���g.
	bool 	m_GiveBornusTime;				//�ǉ����ԗ^����t���O.
	bool	m_bClosedFlag;					//�X�t���O.
	int		m_StageNum;						//�X�e�[�W�ԍ�.
};

#endif	//#ifndef CCLOSED_TIME_H.