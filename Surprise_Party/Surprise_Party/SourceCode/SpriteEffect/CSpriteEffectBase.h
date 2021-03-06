#ifndef CSPRITE_EFFECT_BASE_H
#define CSPRITE_EFFECT_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\..\Global.h"
#include "..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*********************************************
*		スプライトのエフェクト基底クラス.
********/
class CSpriteEffectBase
{
public:
	CSpriteEffectBase();
	virtual ~CSpriteEffectBase();

	//================定数====================//.
	const D3DXVECTOR3	SCALE_MAX			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//大きさ最大値.
	const D3DXVECTOR3	SCALE_MIN			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//大きさ最小値.
	const float			ALPHA_MAX			= 1.0f;								//透過値最大値.
	const float			ALPHA_MIN			= 0.0f;								//透過値最小値.

	const int			ADDITION_NUM		= 1;								//加算番号.
	const int			CHANGE_ADD_SUB		= -1;								//加算減算変更数値.

	const float			CIRCLE_HALF_ANGLE	= 180.0f;							//半円の角度.
	const float			PI					= 3.14159265358979323846264338f;	//円周率.

	//================関数====================//.
	virtual void Update() = 0;																			//更新処理関数.
	virtual void PlayStartInit(const int& num) = 0;														//エフェクト開始初期化処理関数.
	void	Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//描画処理関数.

	//==========情報置換処理関数==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }		//中央座標.
	void SetPlayFlag(const bool& flag) { m_bPlayFlag = flag; }
	void SetAngle(const float& angle);										//角度.
	void SetStartAngle(const float& angle) { m_fStartAngle = angle; }

	//==========情報取得処理関数==============//.
	int GetSpriteMax() { return m_pCSprite.size(); }						//スプライト最大数.
	bool GetRenderFlag() const { return m_bRenderFlag; }

protected:
	//================関数====================//.
	virtual void Init() = 0;							//初期化処理関数.
	virtual void Release() = 0;							//解放処理関数.
	virtual void AppeartJudgement(const int& num) = 0;	//表示判定処理関数.
	virtual void Move(const int& num) = 0;				//移動処理関数.
	void SettingDefaultValue(const int& num);			//初期値設定処理関数.
	void SettingElementsCount();						//要素数設定処理関数.
	bool ScalingTransparent(const int& num);			//透過処理関数.

	//================変数====================//.
	std::vector<CSprite*>		m_pCSprite;				//スプライトクラス.
	std::vector<D3DXVECTOR3>	m_vPos;					//座標.
	std::vector<D3DXVECTOR3>	m_vRot;					//角度.
	std::vector<D3DXVECTOR3>	m_vScale;				//大きさ.
	std::vector<float>			m_fAlpha;				//透過値.
	std::vector<float>			m_fAngle;				//角度.
	std::vector<float>			m_fDistance;			//距離.
	std::vector<D3DXVECTOR2>	m_vPart;				//元画像の場所.
	D3DXVECTOR3					m_vCenterPos;			//中央座標.
	float						m_fAlphaSpeed;			//透過速度.
	float						m_fScalingSpeed;		//大きさ速度.
	CResourceManager*			m_pCResourceManager;	//読み込み管理クラス.
	CDepth_Stencil*				m_pCDepthStencil;		//デプスステンシル.
	
	std::vector<bool>			m_bDispFlag;			//表示フラグ.
	int							m_DispTime;				//表示区切り時間.
	std::vector<int>			m_ChangeAddSub;			//加算減算変更.

	bool						m_bPlayFlag;			//再生フラグ.
	bool						m_bRenderFlag;			//描画フラグ.

	float						m_fStartAngle;			//開始座標.

	CPlaySoundManager*			m_pCPlaySoundManager;	//音再生管理クラス.

private:

};

#endif	//#ifndef CSPRITE_EFFECT_BASE_H.