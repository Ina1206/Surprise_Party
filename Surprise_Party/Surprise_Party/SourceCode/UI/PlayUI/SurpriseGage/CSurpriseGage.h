#ifndef CSURPRISE_GAGE_H
#define CSURPRISE_GAGE_H

#include "..\CPlayUI.h"

class CSurpriseGage
	: public CPlayUI
{
public:
	CSurpriseGage();
	CSurpriseGage(int SurprisePointMax);
	~CSurpriseGage();

	//===================�萔======================//.
	const int	UI_MAX						= 4;		//UI�ő吔.
	const int	GAGE_GROUND_NUM				= 0;		//�Q�[�W���n�ԍ�.
	const int	GAGE_NUM					= 1;		//�Q�[�W�ԍ�.
	const int	STAMP_NUM					= 2;		//�������n���R�ԍ�.
	const int	INFOM_NUM					= 3;		//�ʒm�ԍ�.
	const float	INFOM_MOVE_SPEED			= 0.5f;		//�ʒm�ړ����x.
	const float INFOM_ALPHA_SPEED			= 0.005f;	//�ʒm���ߑ��x.
	const float	CHANGE_ALPHA_HEIGHT			= 300.0f;	//���ߕύX����.
	const float	GET_BONUS_POINT_RATIO		= 0.7f;		//�{�[�i�X�Ⴆ��|�C���g����.

	const D3DXVECTOR3	GAGE_GROUND_POS		= D3DXVECTOR3(20.0f, 640.0f, 0.0f);		//�Q�[�W���n���W.
	const D3DXVECTOR3	GAGE_POS			= D3DXVECTOR3(50.0f, 663.0f, 0.0f);		//�Q�[�W���W.
	const D3DXVECTOR3	STAMP_POS			= D3DXVECTOR3(960.0f, 530.0f, 0.0f);	//�������n���R���W.
	const D3DXVECTOR3	INFOM_POS			= D3DXVECTOR3(1080.0f, 180.0f, 0.0f);	//�ʒm���W.

	const D3DXVECTOR3	SHRINK_STOP_SCALE	= D3DXVECTOR3(0.6f, 0.6f, 0.0f);		//�k�ނ̂��~������T�C�Y.
	const D3DXVECTOR3	SHRINK_SPEED		= D3DXVECTOR3(0.05f, 0.05f, 0.0f);		//�k�ޑ��x.

	const unsigned int BAD_FLAG				= (1 << 0);	//Bad�t���O.
	const unsigned int GOOD_FLAG			= (1 << 1);	//Good�t���O.
	const unsigned int GREAT_FLAG			= (1 << 2);	//Great�t���O.

	//===================�֐�======================//.
	void Update();						//�X�V�����֐�.
	void AddSurprisePoint(int Point);	//�����|�C���g�ǉ������֐�.

	//=============���擾�����֐�================//.
	//�����|�C���g�ő吔�ɂȂ����t���O.
	bool GetSurprisePointMax() const { return m_bSurprisePointMax; }
	//�{�[�i�X�擾�t���O.
	bool GetBornusGetFlag() const { return m_bBorusGetFlag; }
	//�]���t���O.
	unsigned int GetEvalutionFlag() const { return m_EvalutionFlag; }

private:
	//===================�֐�======================//.
	void Init();						//�����������֐�.
	void Release();						//��������֐�.
	void StampDisp();					//�X�^���v�\�������֐�.
	void InfomMove();					//�ʒm�ړ������֐�.
	void EvalutionSurprisePoint();		//�����|�C���g�]�������֐�.

	//===================�ϐ�======================//.
	int				m_SurprisePoint;	//�������|�C���g.
	int				m_SurprisePointMax;	//�������|�C���g�ő吔.
	bool			m_bSurprisePointMax;//�����|�C���g�ő吔�ɂȂ����t���O.
	bool			m_bBorusGetFlag;	//�{�[�i�X�擾�t���O.
	unsigned int 	m_EvalutionFlag;	//�]���t���O.
};


#endif	//#ifndef CSURPRISE_GAGE_H.