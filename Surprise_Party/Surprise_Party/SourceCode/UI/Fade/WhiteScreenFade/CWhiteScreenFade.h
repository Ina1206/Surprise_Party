#ifndef CWHITE_SCREEN_FADE_H
#define CWHITE_SCREEN_FADE_H

#include "..\CFade.h"

/******************************************
*		���X�N���[���t�F�[�h�N���X.
************/
class CWhiteScreenFade
	: public CFade
{
public:
	CWhiteScreenFade();
	~CWhiteScreenFade();

	//========================�萔=========================//.
	const unsigned int FADE_IN_FLAG		= (1 << 0);		//�t�F�[�h�C���t���O.
	const unsigned int FADE_OUT_FLAG	= (1 << 1);		//�t�F�[�h�A�E�g�t���O.
	const unsigned int FADE_FINISH_FLAG = (1 << 2);		//�t�F�[�h�I���t���O.

	const float			ALPHA_MIN	= 0;			//���ߒl�ŏ��l.
	const float			ALPHA_SPEED = 0.009f;		//���ߑ��x.

	//========================�֐�=========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//==================���u�������֐�===================//.
	//�t�F�[�h�t���O.
	void SetFadeFlag(const unsigned int& FadeFlag) { m_FadeFlag = FadeFlag; }

	//==================���擾�����֐�===================//.
	//�t�F�[�h�t���O.
	unsigned int GetFadeFlag() const { return m_FadeFlag; }
	//���ߒl�̊���.
	float GetAlphaRatio() const { return m_fAlphaRatio; }

private:
	//========================�֐�=========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void FadeIn();		//�t�F�[�h�C�������֐�.
	void FadeOut();		//�t�F�[�h�A�E�g�����֐�.
	void InitFade();	//�t�F�[�h�O�̏����������֐�.

	//========================�ϐ�=========================//.
	CSpriteUI*		m_pCSpriteUI;		//�X�v���C�gUI�N���X.
	D3DXVECTOR3		m_vPos;				//���W.
	float			m_fAlpha;			//���ߒl.
	unsigned int	m_FadeFlag;			//�t�F�[�h�t���O.			
	unsigned int	m_OldFadeFlag;		//�����p�t�F�[�h�t���O.
	float			m_fAlphaRatio;		//���ߒl�̊���.
};

#endif	//#ifndef CWHITE_SCREEN_FADE_H.