#include "CSpriteResource.h"

template <class Sprite, class SpriteType>
CSprite_Resource<Sprite, SpriteType>::CSprite_Resource()
	: m_ppSprite	(nullptr)
	, m_pSpriteState(nullptr)
{

}

template<class Sprite, class SpriteType>
CSprite_Resource<Sprite, SpriteType>::~CSprite_Resource()
{
	//解放処理関数.
	for (int sprite = m_ResourceMax - 1; sprite >= 0; sprite--) {
		Release(static_cast<SpriteType>(sprite));
	}
	//配列解放.
	SAFE_DELETE_ARRAY(m_ppSprite);
}

//==============================================.
//		初期化処理関数.
//==============================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Init(int max)
{
	//最大数設定.
	m_ResourceMax = max;


	m_ppSprite		= new Sprite*[m_ResourceMax]();

	//初期化処理.
	for (int sprite = 0; sprite < m_ResourceMax; sprite++) {
		m_ppSprite[sprite] = nullptr;
	}

	return S_OK;
}

//============================================.
//		読み込み処理関数.
//============================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Load(std::vector<std::string> vecFileName)
{
	//ファイルパス.
	const char** fileName = nullptr;
	fileName = new const char*[m_ResourceMax]();

	for (int sprite = 0; sprite < m_ResourceMax; sprite++) {
		fileName[sprite] = vecFileName[sprite].c_str();
		//作成処理関数.
		Create(static_cast<SpriteType>(sprite), fileName[sprite]);
	}

	SAFE_DELETE_ARRAY(fileName);

	return S_OK;
}

//===================================================.
//		解放呼び出し処理関数.
//===================================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::ReleaseCalling()
{
	for (int sprite = m_ResourceMax - 1; sprite >= 0; sprite--) {
		//解放処理関数.
		Release(static_cast<SpriteType>(sprite));
	}
	return S_OK;
}

//====================================================.
//	スプライト系のクラスのアドレスが取得処理関数.
//====================================================.
template<class Sprite, class SpriteType>
Sprite* CSprite_Resource<Sprite, SpriteType>::GetSprite(SpriteType enSpriteType) 
{
	//範囲確認処理関数.
	if (FAILED(Check_SpriteRange(enSpriteType))) {
		return nullptr;
	}

	if (m_ppSprite[static_cast<int>(enSpriteType)] == nullptr) {
		return nullptr;
	}

	return m_ppSprite[static_cast<int>(enSpriteType)];
}

//==================================================.
//		作成処理関数.
//==================================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Create(SpriteType enSpriteType, const char* pfileName)
{
	//範囲確認処理関数.
	if (FAILED(Check_SpriteRange(enSpriteType))) {
		return E_FAIL;
	}

	if (m_ppSprite[static_cast<int>(enSpriteType)] != nullptr) {
		return E_FAIL;
	}

	if (m_pSpriteState == nullptr) {
		_ASSERT_EXPR(m_pSpriteState != nullptr, "m_pSpriteState == nullptr");
		return E_FAIL;
	}
	SPRITE_STATE ss = m_pSpriteState[static_cast<int>(enSpriteType)];

	_ASSERT_EXPR(ss.Base.w != 0.0f, L"ss.Base.w == 0.0f");
	m_ppSprite[static_cast<int>(enSpriteType)] = new Sprite();
	//初期化処理関数.
	if (FAILED(m_ppSprite[static_cast<int>(enSpriteType)]->Init(m_pDevice11, m_pContext11, pfileName, &ss))) {
		return E_FAIL;
	}

	return S_OK;
}

//===================================================.
//		解放処理関数.
//===================================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Release(SpriteType enSpriteType)
{
	//範囲確認処理関数.
	if (FAILED(Check_SpriteRange(enSpriteType))) {
		return E_FAIL;
	}

	//nullptrだったら終了.
	if (m_ppSprite[static_cast<int>(enSpriteType)] == nullptr) {
		return S_OK;
	}

	//解放処理関数.
	m_ppSprite[static_cast<int>(enSpriteType)]->Release();
	SAFE_DELETE(m_ppSprite[static_cast<int>(enSpriteType)]);

	return S_OK;
}

//======================================.
//	スプライトの範囲を確認処理関数.
//======================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Check_SpriteRange(SpriteType enSpriteType)
{
	if (static_cast<int>(enSpriteType) < 0 || m_ResourceMax <= static_cast<int>(enSpriteType)) {
		return E_FAIL;
	}

	return S_OK;
}

//================クラスの実体化=================//.
template class CSprite_Resource<CSprite, enSprite>;
template class CSprite_Resource<CSpriteUI, enSpriteUI>;