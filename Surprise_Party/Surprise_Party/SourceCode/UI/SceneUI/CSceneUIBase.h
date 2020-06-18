#ifndef CSCENE_UI_BASE_H
#define CSCENE_UI_BASE_H

#include "..\CUI.h"

/*****************************************
*		�V�[��UI�̊��N���X.
****************/
class CSceneUIBase
	: public CUI
{
public:
	CSceneUIBase();
	virtual ~CSceneUIBase();

	//===================�萔========================//.
	const D3DXVECTOR3	SELECT_STRING_POS = D3DXVECTOR3(700.0f, 400.0f, 0.0f);	//�I�𕶏͍��W.
	const D3DXVECTOR3	CURSOR_POS = D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//�J�[�\�����W.
	const D3DXVECTOR3	INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W.
	const D3DXVECTOR3	INIT_ROT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����p�x.
	const D3DXVECTOR3	CURSOR_ROT = D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//�J�[�\���p�x.
	const D3DXVECTOR2	INIT_UV = D3DXVECTOR2(0.0f, 0.0f);				//����UV���W.
	const D3DXVECTOR2	NORMAL_UV_POS = D3DXVECTOR2(0.0f, 0.0f);				//�ʏ�UV���W.
	const D3DXVECTOR2	ENTER_UV_POS = D3DXVECTOR2(0.0f, 1.0f);				//���莞��UV���W.
	const float	SELECT_STRING_WIDHT = 100.0f;	//�I�𕶏͕�.
	const int	UI_MAX = 4;		//UI�ő吔.
	const int	SELECT_STRING_MAX = 2;		//�I���X�v���C�g.
	const int	CURSOR_NUM = 2;		//�J�[�\���ԍ�.
	const int	CHANGE_CNT_MAX = 10;		//�ύX�J�E���g�ő吔.

	//===================�֐�========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//=============���擾�����֐�==================//.
	//�I���I���t���O.
	bool GetSelectFinishFlag() const { return m_bSelectFinishFlag; }

protected:
	//===================�ϐ�========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//�X�v���C�gUI.

private:
	//===================�֐�========================//.
	void InitPos();		//�������W�ݒ菈���֐�.

	//===================�ϐ�========================//.
	std::vector<D3DXVECTOR3>	m_vUIPos;				//���W.
	std::vector<D3DXVECTOR2>	m_vUV;					//UV���W.
	std::vector<D3DXVECTOR3>	m_vUIRot;				//�p�x.

	int							m_SelectNum;			//�I��ԍ�.
	int							m_ChangeCnt;			//�ύX�J�E���g.
	bool						m_bSelectFinishFlag;	//�I���I���t���O.
};

#endif	//#ifndef CSCENE_UI_BASE_H.