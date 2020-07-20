#include "CLoad.h"

/*********************************
*		�ǂݍ��݃V�[���N���X.
***********/
CLoad::CLoad()
{

}

CLoad::~CLoad()
{
	//��������֐�.
	Release();
}

//===================================.
//		�����������֐�.
//===================================.
void CLoad::Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pCSpriteUI = std::make_unique<CSpriteUI>();
	SPRITE_STATE ss;
	ss.Base.w = WND_W;
	ss.Base.h = WND_H;
	ss.Stride.w = ss.Base.w;
	ss.Stride.h = ss.Base.h;
	ss.Frame.w = FRAME_MAX;
	ss.Frame.h = FRAME_MAX;
	ss.Disp.w = WND_W;
	ss.Disp.h = WND_H;
	
	//�p�X.
	const std::string PATH = "Data\\Texture\\UI\\Game\\LoadShutter.png";
	//�����������֐�.
	m_pCSpriteUI->Init(pDevice11, pContext11, PATH.c_str(), &ss);
}

//===================================.
//		�`�揈���֐�.
//===================================.
void CLoad::Render()
{
	m_pCSpriteUI->SetPosition(POS);
	//�`�揈���֐�.
	m_pCSpriteUI->Render();
}

//====================================.
//		��������֐�.
//====================================.
void CLoad::Release()
{

}