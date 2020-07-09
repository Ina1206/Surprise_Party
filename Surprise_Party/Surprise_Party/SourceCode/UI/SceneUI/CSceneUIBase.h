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
	const D3DXVECTOR3	SELECT_STRING_POS	= D3DXVECTOR3(700.0f, 400.0f, 0.0f);	//�I�𕶏͍��W.
	const D3DXVECTOR3	CURSOR_POS			= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//�J�[�\�����W.
	const D3DXVECTOR3	INIT_POS			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W.
	const D3DXVECTOR3	INIT_ROT			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����p�x.
	const D3DXVECTOR3	RIGHT_CURSOR_ROT	= D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//�J�[�\���p�x.
	const D3DXVECTOR3	LEFT_CURSOR_ROT		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�J�[�\���p�x.
	const D3DXVECTOR2	INIT_UV				= D3DXVECTOR2(0.0f, 0.0f);				//����UV���W.
	const D3DXVECTOR2	NORMAL_UV_POS		= D3DXVECTOR2(0.0f, 0.0f);				//�ʏ�UV���W.
	const D3DXVECTOR2	ENTER_UV_POS		= D3DXVECTOR2(0.0f, 1.0f);				//���莞��UV���W.
	const float			SELECT_STRING_WIDHT = 100.0f;								//�I�𕶏͕�.
	const int			UI_MAX				= 4;									//UI�ő吔.
	const int			SELECT_STRING_MAX	= 2;									//�I���X�v���C�g.
	const int			CHANGE_CNT_MAX		= 10;									//�ύX�J�E���g�ő吔.

	//===================�֐�========================//.
	virtual void Update() = 0;							//�X�V�����֐�.
	void Render();										//�`�揈���֐�.

	//=============���擾�����֐�==================//.
	//�I���I���t���O.
	bool GetSelectFinishFlag() const { return m_bSelectFinishFlag; }

protected:
	//===================�֐�========================//.
	void Control(const bool& bChangeWaitFlag);			//���쏈���֐�.
	void InitElementCounts();							//�v�f�������������֐�.
	void ControlSelectStringPos();						//���쎞�I�𕶏͍��W�ݒ菈���֐�.
	void InitCursor();									//�J�[�\�������ݒ菈���֐�.

	//===================�ϐ�========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;			//�X�v���C�gUI.
	int							m_SelectNum;			//�I��ԍ�.
	bool						m_bSelectFinishFlag;	//�I���I���t���O.
	std::vector<D3DXVECTOR3>	m_vUIPos;				//���W.
	std::vector<D3DXVECTOR2>	m_vUV;					//UV���W.
	std::vector<D3DXVECTOR3>	m_vUIRot;				//�p�x.

private:
	//===================�֐�========================//.
	void Release();										//��������֐�.

	//===================�ϐ�========================//.
	int							m_ChangeCnt;			//�ύX�J�E���g.
};

#endif	//#ifndef CSCENE_UI_BASE_H.