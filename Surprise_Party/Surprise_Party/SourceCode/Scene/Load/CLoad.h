#ifndef CLOAD_H
#define CLOAD_H

#include "..\..\Drawing\Sprite\SpriteUI\CSpriteUI.h"

/*********************************
*		�ǂݍ��݃V�[���N���X.
***********/
class CLoad
{
public:
	CLoad();
	~CLoad();

	//=======================�萔============================//.
	const float			FRAME_MAX	= 1.0f;								//�t���[���ő吔.
	const D3DXVECTOR3	POS			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���W.

	//=======================�֐�============================//.
	void Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//�����������֐�.
	void Render();																	//�`�揈���֐�.

private:
	//=======================�֐�============================//.
	void Release();				//��������֐�.

	//=======================�ϐ�============================//.
	std::unique_ptr<CSpriteUI>	m_pCSpriteUI;	//�X�v���C�gUI.
};

#endif	//#ifndef CLOAD_H.