#ifndef CPAUSE_H
#define CPAUSE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Drawing\Resource\CResourceManager.h"

/****************************************
*		�ꎞ��~�N���X.
************/
class CPause
	: public CSceneBase
{
public:
	CPause();
	~CPause();

	//=====================�萔=====================//.
	//const int	UI_MAX				= 4;		//UI�ő吔.
	//const int	SELECT_STRING_MAX	= 2;		//�I���X�v���C�g.
	//const int	CURSOR_NUM			= 2;		//�J�[�\���ԍ�.
	const int	PAUSE_NUM			= 3;		//�|�[�Y�ԍ�.
	//const float	SELECT_STRING_WIDHT = 100.0f;	//�I�𕶏͕�.
	const float CHANGE_CNT_MAX		= 10;		//�ύX�J�E���g�ő吔.

	//const D3DXVECTOR3	SELECT_STRING_POS	= D3DXVECTOR3(700.0f, 400.0f, 0.0f);	//�I�𕶏͍��W.
	//const D3DXVECTOR3	CURSOR_POS			= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//�J�[�\�����W.
	//const D3DXVECTOR3	INIT_POS			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W.
	//const D3DXVECTOR3	INIT_ROT			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����p�x.
	//const D3DXVECTOR3	CURSOR_ROT			= D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//�J�[�\���p�x.
	//const D3DXVECTOR2	INIT_UV				= D3DXVECTOR2(0.0f, 0.0f);				//����UV���W.
	//const D3DXVECTOR2	NORMAL_UV_POS		= D3DXVECTOR2(0.0f, 0.0f);				//�ʏ�UV���W.
	//const D3DXVECTOR2	ENTER_UV_POS		= D3DXVECTOR2(0.0f, 1.0f);				//���莞��UV���W.

	//=====================�֐�=====================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=====================�֐�=====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=====================�萔=====================//.
	//std::vector<CSpriteUI*>			m_pCSpriteUI;		//�X�v���C�gUI.
	//std::unique_ptr<D3DXVECTOR3[]>	m_vPos;				//���W.
	//std::unique_ptr<D3DXVECTOR3[]>	m_vRot;				//�p�x.
	//std::unique_ptr<D3DXVECTOR2[]>	m_vUV;				//UV���W.
	//CResourceManager*				m_pCResourceManager;//�ǂݍ��݊Ǘ��N���X.
	//CDepth_Stencil*					m_pCDepthStenceil;	//�f�v�X�X�e���V��.

	//int								m_SelectNum;		//�I��ԍ�.
	//int								m_ChangeCnt;		//�ύX�J�E���g.
};

#endif	//#ifndef CPAUSE_H.