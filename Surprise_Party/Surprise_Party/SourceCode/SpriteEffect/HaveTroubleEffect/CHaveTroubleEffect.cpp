#include "CHaveTroubleEffect.h"

/******************************************
*		困りエフェクトクラス.
************/
CHaveTroubleEffect::CHaveTroubleEffect()
{
	//初期化処理関数.
	Init();
}

CHaveTroubleEffect::~CHaveTroubleEffect()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		更新処理関数.
//===========================================.
void CHaveTroubleEffect::Update()
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		static bool flag = false;
		if (GetAsyncKeyState(VK_F1) & 0x0001) {
			if (flag == false) {
				flag = true;
			}
			else {
				flag = false;
			}
		}

		D3DXVECTOR3 vChange;
		if (flag == false) {
			vChange = m_vPos[sprite];
		}
		else {
			vChange = m_vRot[sprite];
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			vChange.x += 0.01f;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			vChange.x -= 0.01f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			vChange.y += 0.01f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			vChange.y -= 0.01f;
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			vChange.z += 0.01f;
		}
		if (GetAsyncKeyState('X') & 0x8000) {
			vChange.z -= 0.01f;
		}

		if (flag == false) {
			m_vPos[sprite] = vChange;
		}
		else {
			m_vRot[sprite] = vChange;
		}

		if (m_vPos[sprite] == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) {
			m_vPos[sprite] = m_vCenterPos + INT_LOCAL_POS;
		}
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CHaveTroubleEffect::Init()
{
	//要素数設定.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		m_fAlpha[sprite] = ALPHA_MAX;
		m_fScale[sprite] = SCALE_MAX;
		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
}

//===========================================.
//		解放処理関数.
//===========================================.
void CHaveTroubleEffect::Release()
{

}