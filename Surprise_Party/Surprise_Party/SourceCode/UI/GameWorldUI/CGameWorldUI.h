#ifndef CGAME_WORLD_UI_H
#define CGAME_WORLD_UI_H

#include "..\CUI.h"

/***************************************
*		�Q�[�����ł�UI�N���X.
************/
class CGameWorldUI
	: public CUI
{
public:
	CGameWorldUI();
	virtual ~CGameWorldUI();

	//======================�֐�============================//.
	void RenderSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//�`��ݒ菈���֐�.
	void Render();																							//�`�揈���֐�.

	//================���u�������֐�======================//.
	//�L�����N�^�̍��W.
	void SetCharacterPos(const D3DXVECTOR3& vCharaPos) { m_vCharacterPos = vCharaPos; }

protected:
	//======================�ϐ�============================//.
	CSprite*	m_pCSprite;			//�X�v���C�g�N���X.
	D3DXMATRIX	m_mView;			//�r���[�s��.
	D3DXMATRIX	m_mProj;			//�v���W�F�N�V�����s��.
	D3DXVECTOR3	m_vCameraPos;		//�J�������W.
	D3DXVECTOR3	m_vCharacterPos;	//�L�����N�^���W.
	D3DXVECTOR3 m_vColor;			//�F.
	D3DXVECTOR2	m_vPattarn;			//�p�^�[��.
	bool		m_bDepth;			//�f�v�X.

};

#endif //#ifndef CGAME_WORLD_UI_H.