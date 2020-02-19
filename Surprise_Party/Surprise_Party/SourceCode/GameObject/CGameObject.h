#ifndef CGAME_OBJECT_H
#define CGAME_OBJECT_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"

/************************************
*	ゲームオブジェクトクラス.
*******/
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	//================定数===================//.
	const D3DXVECTOR3	STANDERD_POS = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);

	//===============列挙体==================//.
	//驚かすオブジェクトの種類.
	enum class enSurpriseObjectType {
		Disp,		//現れる.
		Switch,		//スイッチ.
	};

	//================関数===================//.
	void RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& vLightPos);	//描画初期設定処理関数.
	virtual void UpDate() = 0;		//更新処理関数.
	virtual void Render() = 0;		//描画処理関数.

	//===========情報置換処理関数============//.
	void SetPos(const D3DXVECTOR3& vPos) { m_vPos = vPos; }
	void SetDispFlag(const bool& bFlag) { m_bDisp = bFlag; }
	void SetCameraPos(const D3DXVECTOR3& vPos) { m_vCameraPos = vPos; }

	//===========情報置換処理関数============//.
	bool		GetDispFlag() { return m_bDisp; }		//表示フラグ取得.
	D3DXVECTOR3 GetPos(){ return m_vPos; }				//座標取得.
protected:
	//================関数===================//.
	virtual void Init() = 0;	//初期化処理関数.
	virtual void Release() = 0;	//解放処理関数.

	//================変数===================//.
	D3DXMATRIX	m_mView;		//ビュー行列.
	D3DXMATRIX	m_mProj;		//プロジェクション行列.
	LIGHT		m_stLight;		//ライト情報.
	D3DXVECTOR3 m_vCameraPos;	//カメラ座標.
	
	D3DXVECTOR3	m_vPos;			//座標.
	D3DXVECTOR3 m_vRot;			//角度.
	float		m_fScale;		//大きさ.
	bool		m_bDisp;		//表示フラグ.

	CResourceManager*	m_pCResourceManager;//読み込み管理クラス.
private:

};

#endif	//#ifndef CGAME_OBJECT_H.