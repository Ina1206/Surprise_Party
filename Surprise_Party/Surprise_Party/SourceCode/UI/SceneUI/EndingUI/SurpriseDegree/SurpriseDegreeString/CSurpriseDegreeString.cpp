#include "CSurpriesDegreeString.h"

/**********************************************
*		�������x���̓N���X.
*******************/
CSurpriseDegreeString::CSurpriseDegreeString()
{
	//�����������֐�.
	Init();
}

CSurpriseDegreeString::~CSurpriseDegreeString()
{
	//��������֐�.
	Release();
}

//==================================================.
//		�X�V�����֐�.
//==================================================.
void CSurpriseDegreeString::Update()
{
	static D3DXVECTOR3 Pos(0.0f, 0.0f, 0.0f);
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		Pos.y -= 0.5f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		Pos.y += 0.5f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		Pos.x -= 0.5f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		Pos.x += 0.5f;
	}
}

//==================================================.
//		�����������֐�.
//==================================================.
void CSurpriseDegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
	m_vEatchSizeScale = EATCH_SCALE_MAX;
}

//==================================================.
//		��������֐�.
//==================================================.
void CSurpriseDegreeString::Release()
{

}