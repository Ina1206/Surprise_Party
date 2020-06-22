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
	void SetStartPos(const D3DXVECTOR3& vPos) { m_vStartPos = vPos; }
	void RenderInit(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vPos) { m_mView = mView;  m_mProj = mProj; m_vCameraPos = vPos; }
private:
	//=================�֐�====================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.

	//==================�ϐ�====================//.
	CSprite*	m_pCSprite;		//�X�v���C�g.
	D3DXMATRIX	m_mView;		//�r���[�s��.
	D3DXMATRIX	m_mProj;		//�v���W�F�N�V����.
	D3DXVECTOR3 m_vCameraPos;	//�J�������W.
	D3DXVECTOR3 m_vStartPos;	//�������W.
	bool		m_bDispFlag;	//�\���t���O.
	float		m_fAcc;			//�����x.
};

#endif	//#ifndef CNEXT_SPEAK_CURSOR_H.