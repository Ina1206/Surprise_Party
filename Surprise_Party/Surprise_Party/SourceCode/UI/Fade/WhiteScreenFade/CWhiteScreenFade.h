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
	const unsigned int FADE_IN_FLAG = (1 << 0);		//�t�F�[�h�C���t���O.

	const float			ALPHA_MIN	= 0;			//���ߒl�ŏ��l.
	const float			ALPHA_SPEED = 0.009f;		//���ߑ��x.

	//========================�֐�=========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//==================���u�������֐�===================//.
	void SetFadeFlag(const unsigned int& FadeFlag) { m_FadeFlag = FadeFlag; }

	//==================���擾�����֐�===================//.
	unsigned int GetFadeFlag() const { return m_FadeFlag; }

private:
	//========================�֐�=========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void FadeIn();		//�t�F�[�h�C�������֐�.
	void InitFade();	//�t�F�[�h�O�̏����������֐�.

	//========================�ϐ�=========================//.
	CSpriteUI*		m_pCSpriteUI;		//�X�v���C�gUI�N���X.
	D3DXVECTOR3		m_vPos;				//���W.
	float			m_fAlpha;			//���ߒl.
	unsigned int	m_FadeFlag;			//�t�F�[�h�t���O.			
	unsigned int	m_OldFadeFlag;		//�����p�t�F�[�h�t���O.
};

#endif	//#ifndef CWHITE_SCREEN_FADE_H.