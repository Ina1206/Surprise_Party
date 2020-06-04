#include "CBeforeResultStage.h"

/********************************************
*		結果発表前のステージクラス.
******************/
CBeforeResultStage::CBeforeResultStage()
{
	//初期化処理関数.
	Init();
}

CBeforeResultStage::~CBeforeResultStage()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CBeforeResultStage::Update()
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
	else if(1 << Cnt & LookFlag){
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
	else if(1 << Cnt & LookFlag){
		m_Camera.vLook = Tmp;
	}
	else {
		vLookPos = Tmp;
	}

	//const unsigned int X = 1 << 0;
	//const unsigned int Y = 1 << 1;
	//const unsigned int Z = 1 << 2;
	//static int	Count = 0;
	//if (GetAsyncKeyState('1') & 0x0001) {
	//	Count++;
	//}
	//if (Count >= 3) {
	//	Count = 0;
	//}

	//unsigned int m_Flag = 1 << Count;
	//static D3DXVECTOR3 vPos = D3DXVECTOR3(5.0f, -0.8f, 5.0f);
	//float Pos = 0.0f;
	//if (m_Flag & X) {
	//	Pos = vPos.x;
	//}
	//else if (m_Flag & Y) {
	//	Pos = vPos.y;
	//}
	//else {
	//	Pos = vPos.z;
	//}

	//if (GetAsyncKeyState(VK_UP) & 0x8000) {
	//	Pos += 0.5f;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
	//	Pos -= 0.5f;
	//}


	//if (m_Flag & X) {
	//	vPos.x = Pos;
	//}
	//else if (m_Flag & Y) {
	//	vPos.y = Pos;
	//}
	//else {
	//	vPos.z = Pos;
	//}

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
		//m_pCGhost[ghost]->SetLookAtPos(vLookPos);
		//m_pCGhost[ghost]->SetLookAtPos(D3DXVECTOR3(5.0f, -0.8f, 5.0f));
	}
	

}

//=======================================.
//		描画処理関数.
//=======================================.
void CBeforeResultStage::Render()
{
	//床の描画処理関数.
	RenderFloor();

	//ビッグゴースト描画処理関数.
	//RenderBigGhost();

	//お化け描画処理関数.
	RenderGhost();

}

//=======================================.
//		初期化処理関数.
//=======================================.
void CBeforeResultStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);

}

//=======================================.
//		解放処理関数.
//=======================================.
void CBeforeResultStage::Release()
{

}