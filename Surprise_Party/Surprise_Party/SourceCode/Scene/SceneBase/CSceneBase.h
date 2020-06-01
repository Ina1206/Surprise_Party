#ifndef CSCENE_BASE_H
#define CSCENE_BASE_H

#include "..\..\Global.h"

/************************************
*		シーン基底クラス.
*****/
class CSceneBase
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	//===================関数======================//.
	void	RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);	//描画初期設定.
	void	DebugSceneChange();			//デバッグ用シーン変更処理関数.
	
	virtual void UpDate()	= 0;		//更新処理関数.
	virtual void Render()	= 0;		//描画処理関数.

	//=============情報獲得処理関数================//.
	D3DXVECTOR4 GetBackColor()		{ return m_vBackColor; }	//後ろの色情報取得処理関数.
	bool		GetChangeSceneFlag(){ return m_bChangeScene; }	//シーン変更フラグ取得処理関数.
	bool		GetPauseFlag() const { return m_bPauseFlag; }	//一時停止フラグ.

	//=============情報置換処理関数================//.
	void SetPauseFlag(const bool& flag) { m_bPauseFlag = flag; }//一時停止フラグ.

protected:
	//===================関数======================//.
	virtual void Init()		= 0;		//初期化処理関数.
	virtual void Release()	= 0;		//解放処理関数.

	//===================変数======================//.
	D3DXMATRIX	m_mView;		//ビュー行列.
	D3DXMATRIX	m_mProj;		//プロジェクション行列.
	D3DXVECTOR3 m_vLightPos;	//ライト座標.
	D3DXVECTOR3 m_vCameraPos;	//カメラ座標.
	D3DXVECTOR4 m_vBackColor;	//後ろの色.
	bool		m_bChangeScene;	//シーン変更フラグ.
	bool		m_bPauseFlag;	//一時停止フラグ.

private:

};

#endif	//#ifndef CSCENE_BASE_H.