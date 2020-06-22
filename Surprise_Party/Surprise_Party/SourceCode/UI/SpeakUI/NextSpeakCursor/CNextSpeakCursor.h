#ifndef CNEXT_SPEAK_CURSOR_H
#define CNEXT_SPEAK_CURSOR_H

#include "..\..\CUI.h"

/*****************************************
*		���̉�b�̃J�[�\���N���X.
*****************/
class CNextSpeakCursor
	: public CUI
{
public:
	CNextSpeakCursor();
	~CNextSpeakCursor();

	//=================�֐�====================//.
	void Update();				//�X�V�����֐�.
	void Render();				//�`�揈���֐�.

	//===========���u�������֐�==============//.
	//�������W.
	void SetStartPos(const D3DXVECTOR3& vPos) { m_vStartPos = vPos; }
	//�\���t���O.
	void SetDispFlag(const bool& bFlag) { m_bDispFlag = bFlag; }

private:
	//=================�֐�====================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.

	//==================�ϐ�====================//.
	CSpriteUI*	m_pCSpriteUI;	//�X�v���C�gUI.
	D3DXVECTOR3 m_vStartPos;	//�������W.
	bool		m_bDispFlag;	//�\���t���O.
	float		m_fAcc;			//�����x.
};

#endif	//#ifndef CNEXT_SPEAK_CURSOR_H.