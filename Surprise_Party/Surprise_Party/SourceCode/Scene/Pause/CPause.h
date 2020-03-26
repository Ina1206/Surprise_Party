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
	const int UI_MAX			= 4;	//UI�ő吔.
	const int SELECT_STRING_MAX = 2;	//�I���X�v���C�g.
	const int CURSOR_NUM		= 2;	//�J�[�\���ԍ�.
	const int PAUSE_NUM			= 3;	//�|�[�Y�ԍ�.

	//=====================�֐�=====================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=====================�֐�=====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=====================�萔=====================//.
	std::vector<CSpriteUI*>			m_pCSpriteUI;		//�X�v���C�gUI.
	std::unique_ptr<D3DXVECTOR3[]>	m_vPos;				//���W.
	std::unique_ptr<D3DXVECTOR3[]>	m_vRot;				//�p�x.
	std::unique_ptr<D3DXVECTOR2[]>	m_vUV;				//UV���W.
	CResourceManager*				m_pCResourceManager;//�ǂݍ��݊Ǘ��N���X.
	CDepth_Stencil*					m_pCDepthStenceil;	//�f�v�X�X�e���V��.

	int								m_SelectNum;		//�I��ԍ�.
	int								m_ChangeCnt;		//�ύX�J�E���g.
};

#endif	//#ifndef CPAUSE_H.