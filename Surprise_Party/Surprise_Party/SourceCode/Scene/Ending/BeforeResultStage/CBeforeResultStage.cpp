#include "CBeforeResultStage.h"

/********************************************
*		���ʔ��\�O�̃X�e�[�W�N���X.
******************/
CBeforeResultStage::CBeforeResultStage()
{
	//�����������֐�.
	Init();
}

CBeforeResultStage::~CBeforeResultStage()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CBeforeResultStage::Update()
{

	const unsigned int X = 1 << 0;
	const unsigned int Y = 1 << 1;
	const unsigned int Z = 1 << 2;
	static int	Count = 0;
	if (GetAsyncKeyState('1') & 0x0001) {
		Count++;
	}
	if (Count >= 3) {
		Count = 0;
	}

	unsigned int m_Flag = 1 << Count;
	static D3DXVECTOR3 vPos = D3DXVECTOR3(5.0f, -0.8f, 5.0f);
	float Pos = 0.0f;
	if (m_Flag & X) {
		Pos = vPos.x;
	}
	else if (m_Flag & Y) {
		Pos = vPos.y;
	}
	else {
		Pos = vPos.z;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		Pos += 0.5f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		Pos -= 0.5f;
	}


	if (m_Flag & X) {
		vPos.x = Pos;
	}
	else if (m_Flag & Y) {
		vPos.y = Pos;
	}
	else {
		vPos.z = Pos;
	}

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
		m_pCGhost[ghost]->SetLookAtPos(vPos);
		//m_pCGhost[ghost]->SetLookAtPos(D3DXVECTOR3(5.0f, -0.8f, 5.0f));
	}
	

}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CBeforeResultStage::Render()
{
	//���̕`�揈���֐�.
	RenderFloor();

	//�r�b�O�S�[�X�g�`�揈���֐�.
	//RenderBigGhost();

	//�������`�揈���֐�.
	RenderGhost();

}

//=======================================.
//		�����������֐�.
//=======================================.
void CBeforeResultStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);

}

//=======================================.
//		��������֐�.
//=======================================.
void CBeforeResultStage::Release()
{

}