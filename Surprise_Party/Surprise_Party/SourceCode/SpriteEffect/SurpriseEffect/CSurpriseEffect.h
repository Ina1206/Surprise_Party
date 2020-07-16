#ifndef CSURPRIES_EFFECT_H
#define CSURPRIES_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
class CSurpriseEffect
	: public CSpriteEffectBase
{
public:
	CSurpriseEffect();
	~CSurpriseEffect();

	//======================�萔===========================//.
	const int	SPRITE_MAX	= 3;		//�X�v���C�g�ő吔.
	const float SCALE_SPEED = 0.05f;	//�傫�����x.
	const float ALPHA_SPEED = 0.05f;	//���ߑ��x.
	const float ROT_Y		= 3.1f;		//y���̊p�x.
	const float LEFT_ANGLE	= 120.0f;	//�������̊p�x.
	const float RIGHT_ANGLE = 30.0f;	//�E�����̊p�x.
	const float ANGLE_WIDTH = 30.0f;	//�p�x��.
	const float MOVE_SPEED	= 0.03f;	//�ړ����x.

	//======================�֐�===========================//.
	void Update();							//�X�V�����֐�.
	void PlayStartInit(const int& num);		//�Đ��J�n�����������֐�.
	
	//================���l�������֐�=====================//.
	bool GetDispFlag() const { return m_bAllDispFlag; }

	//================���u�������֐�=====================//.
	void SetDispFlag(const bool& flag) { m_bAllDispFlag = flag; }
	void SetPlaySound(const bool& flag) { m_bPlaySound = flag; }

private:
	//======================�֐�===========================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.

	//======================�ϐ�===========================//.
	int					m_DispCnt;			//�\���J�E���g.
	bool				m_bAllDispFlag;		//�S�̕\���t���O.
	int					m_Direct;			//����.
	D3DXVECTOR3			m_vOldCenterPos;	//�O��̏ꏊ.
	bool				m_bPlaySound;		//�T�E���h�Đ��t���O.

};

#endif	//#ifndef CSURPRIES_EFFECT_H.