#include "CGimmickIcon.h"

CGimmickIcon::CGimmickIcon()
	: CGimmickIcon(0)
{

}

CGimmickIcon::CGimmickIcon(int GimmickNum)
	: m_GimmickType	(0)
{
	m_GimmickType = GimmickNum;
	//初期化処理関数.
	Init();
}

CGimmickIcon::~CGimmickIcon()
{
	//解放処理関数.
	Release();
}

//=====================================.
//		更新処理関数.
//=====================================.
void CGimmickIcon::UpDate()
{
	//ゲーム内からマップ内に座標変換処理関数.
	GameMapConversion();

	//選択中の表示処理関数.
	SelectingDisplay();
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CGimmickIcon::Init()
{
	switch (static_cast<enGimmickType>(m_GimmickType)) {
	case enGimmickType::DispGhost:
		m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::DispGimmick_Iccon);
		break;
	default:
		m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Switch_Icon);
		break;
	}
	m_vPos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
}

//======================================.
//		解放処理関数.
//======================================.
void CGimmickIcon::Release()
{
	m_pCSpriteUI = nullptr;
}