#ifndef CCHANGE_SCENE_CURSOR_H
#define CCHANGE_SCENE_CURSOR_H

#include "..\..\CUI.h"

/****************************************
*		�V�[���ύX�p�J�[�\��UI�N���X.
*****************/
class CChangeSceneCursorUI
	: public CUI
{
public:
	CChangeSceneCursorUI();
	~CChangeSceneCursorUI();

	//===================�萔======================//.	
	const D3DXVECTOR3	CONTROL_CURSOR_POS	= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//�J�[�\�����W.
	
	const D3DXVECTOR3	RIGHT_CURSOR_ROT	= D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//�J�[�\���p�x.
	const D3DXVECTOR3	LEFT_CURSOR_ROT		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�J�[�\���p�x.
	const D3DXVECTOR2	NORMAL_UV_POS		= D3DXVECTOR2(0.0f, 0.0f);				//�ʏ�UV���W.
	const D3DXVECTOR2	ENTER_UV_POS		= D3DXVECTOR2(0.0f, 1.0f);				//���莞��UV���W.
	const int			CHANGE_CNT_MAX		= 10;									//�ύX�J�E���g�ő吔.
	const int			SELECT_MAX			= 2;									//�I�����ő吔.

	//===================�֐�======================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//=============���u�������֐�================//.
	//�ύX�ҋ@�t���O.
	void SetChangeWaitFlag(const bool& bFlag) { m_bChangeWaitFlag = bFlag; }

	//=============���擾�����֐�================//.
	//�I���I���t���O.
	bool GetSelectFinishFlag() const { return m_bSelectFinishFlag; }
	//�I��ԍ�.
	int	GetSelectNum()const { return m_SelectNum; }

private:
	//===================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void Control();		//���쏈���֐�.

	//===================�ϐ�======================//.
	CSpriteUI*	m_pCSpriteUI;			//�X�v���C�gUI.
	D3DXVECTOR2 m_vUV;					//UV���W.
	bool		m_bChangeWaitFlag;		//�ύX�ҋ@�t���O.
	bool		m_bSelectFinishFlag;	//�I���I���t���O.
	int			m_ChangeCnt;			//�ύX�J�E���g.
	int			m_SelectNum;			//�I��ԍ�.

};

#endif	//#ifndef CCHANGE_SCENE_CURSOR_H