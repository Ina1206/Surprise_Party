#ifndef CBIG_GHOST_H
#define CBIG_GHOST_H

#include "..\CGhostBase.h"
#include "..\..\SpriteEffect\SleepEffect\CSleepEffect.h"
#include "..\..\SpriteEffect\HaveTroubleEffect\CHaveTroubleEffect.h"
#include "..\..\SpriteEffect\RejoiceEffect\CRejoiceEffect.h"
#include "..\..\SpriteEffect\QuestionEffect\CQuestionEffect.h"

/******************************************
*		�傫���������N���X.
**********/
class CBigGhost
	: public CGhostBase
{
public:
	CBigGhost();
	~CBigGhost();


	//=================�֐�====================//.
	const D3DXVECTOR3	BASE_PRE_POS		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��̍��W.
	const D3DXVECTOR3	BASE_PRE_ROT		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//
	const D3DXVECTOR3	SLEEP_POS			= D3DXVECTOR3(6.0f, -0.8f, 10.5f);	//�Q�Ă�ꏊ.
	const D3DXVECTOR3	SLEEP_ROT			= D3DXVECTOR3(0.0f, -1.35f, 0.0f);	//�Q�Ă�p�x.
	const D3DXVECTOR3	WAKE_UP_POS			= D3DXVECTOR3(6.0f, 0.7f, 11.2f);	//�N����ꏊ.
	const D3DXVECTOR3	WAKE_UP_ROT			= D3DXVECTOR3(-1.35f, 0.0f, 0.0f);	//�N����p�x.
	const D3DXVECTOR3	HAVE_TROUBLE_POS	= D3DXVECTOR3(6.0f, 1.5f, 11.2f);	//���銴��̍��W.
	const D3DXVECTOR3	HAVE_TROUBLE_ROT	= D3DXVECTOR3(-2.4f, 0.0f, 0.0f);	//���銴��̊p�x.
	const float			SLEEP_ANIM_SPEED	= 0.02f;							//�Q�Ă鎞�̃A�j���[�V�������x.
	const int			SLEEP_DIRECT		= -1;								//��������.
	const float			WAKE_UP_ANIM_SPEED	= 0.0f;								//�N���鎞�̃A�j���[�V�������x.
	const double		WAKE_UP_ANIM_POS	= -1.0;								//�N���Ă���Ƃ��̃A�j���[�V�����ʒu.
	const float			WAKE_UPING_SPEED	= 0.03f;							//�N���鑬�x.
	const int			WAKE_UP_TIMING		= 600;								//�N����^�C�~���O.
	const int			WAKE_UP_DIRECT		= 1;								//�N�������.
	const float			HAVE_TROUBLE_SPEED	= 0.025f;							//���銴��s�����x.
	const float			HAVE_TROUBLE_ROT_MAX= 0.7f;								//���銴��s���p�x�ő�l.
	const int			CHANGE_DIRECTION	= -1;								//�����ύX.

	const int			FALL_DOWN_DIRECTION = 1;								//�|������.
	const int			UP_DIRECTION		= -1;								//�オ�����.

	const float			LEAN_SPEED			= 0.05f;							//�X�����x.
	const float			REJOICE_MOVE_SPEED	= 0.02f;							//��шړ����x.
	const float			REJOICE_ROT_MAX		= 0.4f;								//��ъp�x�ő吔.
	const float			REJOICE_ROT_SPEED	= 0.01f;							//��ьX�����x.

	const float			QUESTION_LEAN_SPEED = 0.02f;							//�^��X�����x.
	const float			QUESTION_LEAN_MIN	= -30.0f;							//�^��X���ŏ��l.

	const float			VIEW_PRE_POS_Y		= 10.0f;							//����Ƃ��̍���.

	const float			SCALE				= 0.1f;								//�傫��.

	const unsigned int	MOVING_ROT_FLAG		= (1 << 0);							//�p�x�ړ��t���O.
	const unsigned int	MOVING_POS_FLAG		= (1 << 1);							//���W�ړ��t���O.
	const unsigned int	SWING_FLAG			= (1 << 2);							//�h���t���O.

	//=================�֐�====================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���Ȑ�.

	//===========���擾�����֐�==============//.
	bool GetSleepFlag() const { return m_bSleepFlag; }				//����t���O.
	bool GetSkipFlag() const { return m_bSkipFlag; }				//�X�L�b�v�t���O.

	//===========���u�������֐�==============//.
	void SetSkipFlag(const bool& bFlag) { m_bSkipFlag = bFlag; }	//�X�L�b�v�t���O.

private:
	//=================�֐�====================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void WakeUp();							//�N�������֐�.
	void HaveTroubleEmotion();				//���銴����֐�.
	void RejoiceEmotion();					//��Ԋ�����֐�.
	void QuestionEmotion();					//�^�⊴����֐�.
	void Sleep();							//�Q�鏈���֐�.
	void Lean(const int& Direction);		//�X�������֐�.
	void FallDown(const int& Direction);	//�|��鏈���֐�.
	void ChangeEffect();					//�G�t�F�N�g�ύX�����֐�.
	void EmotionMove();						//����ړ������֐�.

	//==================�ϐ�====================//.
	CDX9SkinMesh*									m_pCSkinMesh;			//�X�L�����b�V��.
	double											m_dCntAnimSpeed;		//�A�j���[�V�������x�J�E���g.
	float											m_fAnimSpeed;			//�A�j���[�V�������x.
	int												m_AnimNum;				//�A�j���[�V�����ԍ�.

	D3DXVECTOR3										m_vPreRot;				//�p�x�����ݒ�.

	int												m_WakeUpCnt;			//�N����J�E���g.
	int												m_LeanDirect;			//�X������.
	int												m_UpDownDirect;			//�㉺����.
	unsigned int									m_HaveTroubleActFlag;	//���銴��s���t���O.
	bool											m_ChangeEmotionFlag;	//����ύX�t���O.
	std::vector<std::unique_ptr<CSpriteEffectBase>>	m_pCSpriteEffect;		//�X�v���C�g�G�t�F�N�g.
	int												m_UsingEffectNum;		//�g���Ă���G�t�F�N�g�ԍ�.
	int												m_OldEmotionNum;		//�O�̊���ԍ�.

	bool											m_bSleepFlag;			//����t���O.
	bool											m_bSkipFlag;			//�X�L�b�v�t���O.
};


#endif	//#ifndef CBIG_GHOST_H.