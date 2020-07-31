#include "CResourceEffect.h"

/*****************************************
*		エフェクト読み込みクラス.
*****************/
CResourceEffect::CResourceEffect()
	: m_hWnd		(nullptr)
	, m_pDevice11	(nullptr)
	, m_pContext11	(nullptr)
	, m_ppCEffect	(nullptr)
{

}

CResourceEffect::~CResourceEffect()
{
	if (m_ppCEffect != nullptr)
	{
		for (int i = static_cast<int>(CResourceEffect::enEffect::Max) - 1; i >= 0; i--)
		{
			if (m_ppCEffect[i] != nullptr) {
				ReleaseEffect(static_cast<CResourceEffect::enEffect>(i));
			}
		}

		delete[] m_ppCEffect;
		m_ppCEffect = nullptr;
	}
}

//=============================================.
//		初期化処理関数.
//=============================================.
HRESULT CResourceEffect::Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd = hWnd;
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	//ｽﾀﾃｨｯｸﾒｯｼｭのﾎﾟｲﾝﾀのﾎﾟｲﾝﾀの領域確保.
	//※ﾎﾟｲﾝﾀ型の配列領域の確保.
	m_ppCEffect = new CEffect*[static_cast<int>(CResourceEffect::enEffect::Max)];
	for (int i = 0; i < static_cast<int>(CResourceEffect::enEffect::Max); i++)
	{
		//初期化:nullptrで埋める.
		m_ppCEffect[i] = nullptr;
	}
	return S_OK;

}

//=============================================.
//		Effectクラスのアドレス取得処理関数.
//=============================================.
CEffect* CResourceEffect::GetEffect(CResourceEffect::enEffect enEffectType)
{
	//範囲外なら終了.
	if (enEffectType < CResourceEffect::enEffect::Start || CResourceEffect::enEffect::Max <= enEffectType) {
		return nullptr;
	}
	const int EffectNo = static_cast<int>(enEffectType);
	//ﾓﾃﾞﾙが存在しないので終了.
	if (m_ppCEffect[EffectNo] == nullptr) {
		return nullptr;
	}

	return m_ppCEffect[EffectNo];

}

//=============================================.
//		読み込み処理関数.
//=============================================.
HRESULT CResourceEffect::LoadEffect()
{

	const EFK_CHAR* pathName[] = {
		(const EFK_CHAR*)L"Data\\Effect\\GimmickEffect\\DispGhost_Area.efk",
		(const EFK_CHAR*)L"Data\\Effect\\GimmickEffect\\ObjectMove_Area.efk",
		(const EFK_CHAR*)L"Data\\Effect\\GimmickEffect\\PlaySound_Area.efk",
	};

	int max = sizeof(pathName) / sizeof(pathName[0]);

	for (int i = 0; i < max; i++)
	{
		CreateEffect(static_cast<CResourceEffect::enEffect>(i), pathName[i]);
	}

	return S_OK;
}


//=============================================.
//		作成処理関数.
//=============================================.
HRESULT CResourceEffect::CreateEffect(CResourceEffect::enEffect enEffectType, const EFK_CHAR* pathName)
{
	//範囲外なら終了.
	if (enEffectType < CResourceEffect::enEffect::Start || CResourceEffect::enEffect::Max <= enEffectType) {
		return E_FAIL;
	}

	//ﾓﾃﾞﾙが既に存在してたら終了.
	if (m_ppCEffect[static_cast<int>(enEffectType)] != nullptr) {
		return E_FAIL;
	}

	//ﾓﾃﾞﾙ読み込み.
	m_ppCEffect[static_cast<int>(enEffectType)] = new CEffect();
	if (FAILED(
		m_ppCEffect[static_cast<int>(enEffectType)]->Init()))
	{
		return E_FAIL;
	}
	if (FAILED(m_ppCEffect[static_cast<int>(enEffectType)]->Create(m_pDevice11, m_pContext11)))
	{
		return E_FAIL;
	}
	if (FAILED(m_ppCEffect[static_cast<int>(enEffectType)]->LoadData(pathName)))
	{
		return E_FAIL;
	}

	return S_OK;


}

//=============================================.
//		解放処理関数.
//=============================================.
HRESULT CResourceEffect::ReleaseEffect(CResourceEffect::enEffect enEffectType)
{
	//範囲外なら終了.
	if (enEffectType < CResourceEffect::enEffect::Start || CResourceEffect::enEffect::Max <= enEffectType) {
		return E_FAIL;
	}
	const int EffectNo = static_cast<int>(enEffectType);

	//ﾓﾃﾞﾙが存在してなければ終了.
	if (m_ppCEffect[EffectNo] == nullptr) {
		return S_OK;
	}

	//解放処理.
	m_ppCEffect[EffectNo]->Destroy();
	delete m_ppCEffect[EffectNo];//削除.
	m_ppCEffect[EffectNo] = nullptr;

	return S_OK;

}

//=============================================.
//		解放処理関数.
//=============================================.
HRESULT CResourceEffect::ReleaseEffect()
{
	for (int effect = static_cast<int>(CResourceEffect::enEffect::Max) - 1; effect >= 0; effect--) {
		ReleaseEffect(static_cast<CResourceEffect::enEffect>(effect));
	}
	return S_OK;
}
