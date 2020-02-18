#ifndef CRESOURCE_EFFECT_H
#define	CRESOURCE_EFFECT_H

#include "..\..\Effect\CEffect.h"

class CResourceEffect
{
public:
	CResourceEffect();
	~CResourceEffect();

	//===============列挙体===================//.
	enum class enEffect {
		DispGhost_Area_Effect,	//お化けが出てくる範囲エフェクト.
		ObjectMove_Area_Effect,	//オブジェクトが動く範囲エフェクト.
		PlaySound_Area_Effect,	//音が流れる範囲エフェクト.

		Max,
		Start = DispGhost_Area_Effect,
	};

	//初期化処理関数.
	HRESULT Init(HWND hWnd,
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11);

	//Effectクラスのアドレス取得処理関数.
	CEffect* GetEffect(enEffect enMesh);
	//読み込み処理関数.
	HRESULT LoadEffect();

private:

	//作成処理関数.
	HRESULT CreateEffect(enEffect enEffectType, const EFK_CHAR* Efk_Char);
	//解放処理関数.
	HRESULT ReleaseEffect(enEffect enEffectType);
	//解放処理関数.
	HRESULT ReleaseEffect();

	//================変数====================//.
	HWND					m_hWnd;			//ウィンドウハンドル.
	ID3D11Device*			m_pDevice11;	//デバイス.
	ID3D11DeviceContext*	m_pContext11;	//デバイスコンテキスト.

	CEffect**				m_ppCEffect;
};

#endif	//#ifndef CRESOURCE_EFFECT_H.