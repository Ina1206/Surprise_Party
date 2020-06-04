#include "CCameraEnding.h"

/******************************************
*		エンディングカメラクラス.
***************/
CCameraEnding::CCameraEnding()
{
	//初期化処理関数.
	Init();
}

CCameraEnding::~CCameraEnding()
{
	//解放処理関数.
	Release();
}

//=============================================.
//			更新処理関数.
//=============================================.
void CCameraEnding::Update()
{
	const unsigned int PosFlag = (1 << 0);
	const unsigned int LookFlag = (1 << 1);
	static int Cnt = 0;
	static D3DXVECTOR3 vLookPos = D3DXVECTOR3(5.0f, -0.8f, 5.0f);
	if (GetAsyncKeyState('1') & 0x0001) {
		Cnt++;
		if (Cnt > 1) {
			Cnt = 0;
		}
	}

	D3DXVECTOR3 Tmp;
	if (1 << Cnt & PosFlag) {
		Tmp = m_Camera.vPos;
	}
	else if (1 << Cnt & LookFlag) {
		Tmp = m_Camera.vLook;
	}
	else {
		Tmp = vLookPos;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		Tmp.y += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		Tmp.y -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		Tmp.x += 0.1f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		Tmp.x -= 0.1f;
	}
	if (GetAsyncKeyState('Z') & 0x8000) {
		Tmp.z += 0.1f;
	}
	if (GetAsyncKeyState('X') & 0x8000) {
		Tmp.z -= 0.1f;
	}

	if (1 << Cnt & PosFlag) {
		m_Camera.vPos = Tmp;
	}
	else if (1 << Cnt & LookFlag) {
		m_Camera.vLook = Tmp;
	}
	else {
		vLookPos = Tmp;
	}


}

//=============================================.
//			初期化処理関数.
//=============================================.
void CCameraEnding::Init()
{
	m_Camera.vPos = D3DXVECTOR3(23.9f, 5.0f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);

}

//=============================================.
//			解放処理関数.
//=============================================.
void CCameraEnding::Release()
{

}