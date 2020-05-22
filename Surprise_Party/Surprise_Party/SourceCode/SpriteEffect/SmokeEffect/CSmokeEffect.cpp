#include "CSmokeEffect.h"

/*************************************
*		煙エフェクトクラス.
**********/
CSmokeEffect::CSmokeEffect()
	: m_MoveDirection	(0)
{
	//初期化処理関数.
	Init();
}

CSmokeEffect::~CSmokeEffect()
{

}

//======================================.
//		更新処理関数.
//======================================.
void CSmokeEffect::Update()
{
	if (m_bPlayFlag == true) {
		for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
			//エフェクト開始処理関数.
			PlayStartInit(sprite);

			//表示判定処理関数.
			AppeartJudgement(sprite);
		}
	}

	if (m_bRenderFlag == false) {
		return;
	}

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		//移動処理関数.
		Move(sprite);

		//拡縮透過処理関数.
		ScalingTransparent(sprite);
	}
}

//======================================.
//		エフェクト開始処理化処理関数.
//======================================.
void CSmokeEffect::PlayStartInit(const int& num)
{
	//初期値設定.
	SettingDefaultValue(num);
	m_fAngle[num] = 90.0f;
	//配置.
	m_vPos[num] = m_vCenterPos;
}

//======================================.
//		初期化処理関数.
//======================================.
void CSmokeEffect::Init()
{
	//要素数の設定.
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	SettingElementsCount();
	m_MoveDirection.resize(m_pCSprite.size());

	//初期値設定.
	for (unsigned int SpriteNum = 0; SpriteNum < m_pCSprite.size(); SpriteNum++) {
		SettingDefaultValue(SpriteNum);
		m_fAngle[SpriteNum] = 90.0f;

		//左右の方向の数値に分ける.
		m_MoveDirection[SpriteNum] = -1 + (2 * SpriteNum);
	}
	m_bRenderFlag = true;
	m_fAlphaSpeed = 0.02f;
	m_fScalingSpeed = 0.02f;
}

//======================================.
//		解放処理関数.
//======================================.
void CSmokeEffect::Release()
{

}

//======================================.
//		表示判定処理関数.
//======================================.
void CSmokeEffect::AppeartJudgement(const int& num)
{
	m_bRenderFlag = true;
}

//======================================.
//		移動処理関数.
//======================================.
void CSmokeEffect::Move(const int& num)
{
	m_fAngle[num] += 0.8f;
	if (m_fAngle[num] > 360.0f) {
		m_fAngle[num] = 90.0f;
	}
	const float Angle = static_cast<float>(D3DXToRadian(m_fAngle[num]));

	m_vPos[num].x += 0.05f * m_MoveDirection[num];
	m_vPos[num].y += sinf(Angle) * 0.05f;

}

//========================================.
//		回転処理関数.
//========================================.
void CSmokeEffect::Rotation(const int& num)
{

}