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